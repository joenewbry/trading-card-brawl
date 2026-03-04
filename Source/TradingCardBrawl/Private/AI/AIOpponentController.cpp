#include "AI/AIOpponentController.h"

#include "AI/AIStateSerializer.h"
#include "Dom/JsonObject.h"
#include "GameModes/TCBGameMode.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "TimerManager.h"

ATCBAIController::ATCBAIController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATCBAIController::OnTurnStart(const FGameState& State)
{
	PendingState = State;

	if (bWaitingForResponse)
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(ResponseTimeoutTimer);
		}
		bWaitingForResponse = false;
	}

	const FString SerializedState = UAIStateSerializer::SerializeGameState(State);
	TSharedPtr<FJsonObject> RequestBody = MakeShared<FJsonObject>();
	RequestBody->SetStringField(TEXT("model"), TEXT("dgx-spark"));
	RequestBody->SetBoolField(TEXT("stream"), false);
	RequestBody->SetStringField(
		TEXT("prompt"),
		FString::Printf(
			TEXT("You are a Trading Card Brawl AI. Return strict JSON with shape {\"actions\":[{\"action_type\":\"play_card|attack|end_turn\",\"card_id\":\"\",\"target_id\":\"\"}]}. GameState:%s"),
			*SerializedState));

	FString RequestPayload;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestPayload);
	FJsonSerializer::Serialize(RequestBody.ToSharedRef(), Writer);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(DGXSparkEndpoint);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetContentAsString(RequestPayload);
	Request->OnProcessRequestComplete().BindUObject(this, &ATCBAIController::HandleAIResponse);

	bWaitingForResponse = true;
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(ResponseTimeoutTimer, this, &ATCBAIController::HandleResponseTimeout, MaxResponseTimeSeconds, false);
	}

	if (!Request->ProcessRequest())
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(ResponseTimeoutTimer);
		}
		bWaitingForResponse = false;
		ExecuteActions(BuildFallbackActions(State));
	}
}

void ATCBAIController::ExecuteActions(const TArray<FAIAction>& Actions)
{
	ATCBGameMode* GameMode = GetWorld() ? GetWorld()->GetAuthGameMode<ATCBGameMode>() : nullptr;
	if (GameMode == nullptr)
	{
		return;
	}

	for (const FAIAction& Action : Actions)
	{
		if (!UAIResponseHandler::ValidateAction(Action, PendingState))
		{
			continue;
		}

		if (Action.ActionType == TEXT("play_card"))
		{
			UE_LOG(LogTemp, Log, TEXT("AI play_card action accepted for CardId=%s"), *Action.CardId);
			continue;
		}

		if (Action.ActionType == TEXT("attack"))
		{
			const FString EffectiveTarget = Action.TargetId.IsEmpty() ? TEXT("opponent_hero") : Action.TargetId;
			if (EffectiveTarget == TEXT("opponent_hero") || EffectiveTarget == TEXT("player_hero"))
			{
				GameMode->PlayerHP = FMath::Max(0, GameMode->PlayerHP - 1);
			}
			continue;
		}

		if (Action.ActionType == TEXT("end_turn"))
		{
			GameMode->EndTurn();
			return;
		}
	}

	GameMode->EndTurn();
}

void ATCBAIController::HandleAIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, const bool bConnectedSuccessfully)
{
	if (!bWaitingForResponse)
	{
		return;
	}

	bWaitingForResponse = false;
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ResponseTimeoutTimer);
	}

	if (!bConnectedSuccessfully || !Response.IsValid())
	{
		ExecuteActions(BuildFallbackActions(PendingState));
		return;
	}

	const TArray<FAIAction> ParsedActions = UAIResponseHandler::ParseResponse(Response->GetContentAsString());
	if (ParsedActions.IsEmpty())
	{
		ExecuteActions(BuildFallbackActions(PendingState));
		return;
	}

	ExecuteActions(ParsedActions);
}

void ATCBAIController::HandleResponseTimeout()
{
	if (!bWaitingForResponse)
	{
		return;
	}

	bWaitingForResponse = false;
	ExecuteActions(BuildFallbackActions(PendingState));
}

TArray<FAIAction> ATCBAIController::BuildFallbackActions(const FGameState& State) const
{
	TArray<FAIAction> Actions;

	const FCardData* CheapestPlayableCard = nullptr;
	for (const FCardData& Card : State.PlayerHand)
	{
		const int32* ManaAmount = State.PlayerMana.Find(Card.ManaType);
		if (ManaAmount == nullptr || *ManaAmount < Card.Cost)
		{
			continue;
		}

		if (CheapestPlayableCard == nullptr || Card.Cost < CheapestPlayableCard->Cost)
		{
			CheapestPlayableCard = &Card;
		}
	}

	if (CheapestPlayableCard != nullptr)
	{
		FAIAction PlayAction;
		PlayAction.ActionType = TEXT("play_card");
		PlayAction.CardId = CheapestPlayableCard->CardId;
		PlayAction.TargetId = TEXT("");
		Actions.Add(PlayAction);
	}

	FAIAction AttackAction;
	AttackAction.ActionType = TEXT("attack");
	AttackAction.CardId = TEXT("");
	AttackAction.TargetId = TEXT("opponent_hero");
	Actions.Add(AttackAction);

	FAIAction EndTurnAction;
	EndTurnAction.ActionType = TEXT("end_turn");
	EndTurnAction.CardId = TEXT("");
	EndTurnAction.TargetId = TEXT("");
	Actions.Add(EndTurnAction);

	return Actions;
}
