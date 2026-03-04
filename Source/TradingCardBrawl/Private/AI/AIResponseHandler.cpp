#include "AI/AIResponseHandler.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"

namespace
{
	bool ParseActionObject(const TSharedPtr<FJsonObject>& ActionObject, FAIAction& OutAction)
	{
		if (!ActionObject.IsValid())
		{
			return false;
		}

		if (!ActionObject->TryGetStringField(TEXT("action_type"), OutAction.ActionType))
		{
			ActionObject->TryGetStringField(TEXT("action"), OutAction.ActionType);
		}

		ActionObject->TryGetStringField(TEXT("card_id"), OutAction.CardId);
		ActionObject->TryGetStringField(TEXT("target_id"), OutAction.TargetId);

		return !OutAction.ActionType.IsEmpty();
	}

	bool HasCardOnBoard(const FString& CardId, const TArray<FCardData>& Board)
	{
		return Board.ContainsByPredicate([&CardId](const FCardData& Card)
		{
			return Card.CardId == CardId;
		});
	}
}

TArray<FAIAction> UAIResponseHandler::ParseResponse(const FString& JsonResponse)
{
	TArray<FAIAction> ParsedActions;
	FString Normalized = JsonResponse.TrimStartAndEnd();
	if (Normalized.StartsWith(TEXT("```")))
	{
		int32 FirstNewline = INDEX_NONE;
		if (Normalized.FindChar(TEXT('\n'), FirstNewline))
		{
			Normalized.RightChopInline(FirstNewline + 1, EAllowShrinking::No);
		}
		Normalized.RemoveFromEnd(TEXT("```"), ESearchCase::CaseSensitive);
		Normalized = Normalized.TrimStartAndEnd();
	}

	TSharedPtr<FJsonObject> RootObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Normalized);
	if (!FJsonSerializer::Deserialize(Reader, RootObject) || !RootObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> RootArray;
		Reader = TJsonReaderFactory<>::Create(Normalized);
		if (FJsonSerializer::Deserialize(Reader, RootArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : RootArray)
			{
				FAIAction Action;
				if (ParseActionObject(Value->AsObject(), Action))
				{
					ParsedActions.Add(Action);
				}
			}
		}
		return ParsedActions;
	}

	const TArray<TSharedPtr<FJsonValue>>* ActionsArray = nullptr;
	if (RootObject->TryGetArrayField(TEXT("actions"), ActionsArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : *ActionsArray)
		{
			FAIAction Action;
			if (ParseActionObject(Value->AsObject(), Action))
			{
				ParsedActions.Add(Action);
			}
		}
		return ParsedActions;
	}

	FString ResponsePayload;
	if (RootObject->TryGetStringField(TEXT("response"), ResponsePayload))
	{
		TSharedPtr<FJsonObject> NestedObject;
		Reader = TJsonReaderFactory<>::Create(ResponsePayload);
		if (FJsonSerializer::Deserialize(Reader, NestedObject) && NestedObject.IsValid())
		{
			if (NestedObject->TryGetArrayField(TEXT("actions"), ActionsArray))
			{
				for (const TSharedPtr<FJsonValue>& Value : *ActionsArray)
				{
					FAIAction Action;
					if (ParseActionObject(Value->AsObject(), Action))
					{
						ParsedActions.Add(Action);
					}
				}
			}
		}
	}

	return ParsedActions;
}

bool UAIResponseHandler::ValidateAction(const FAIAction& Action, const FGameState& State)
{
	if (Action.ActionType == TEXT("end_turn"))
	{
		return true;
	}

	if (Action.ActionType == TEXT("play_card"))
	{
		if (Action.CardId.IsEmpty())
		{
			return false;
		}

		const FCardData* Card = State.PlayerHand.FindByPredicate([&Action](const FCardData& Candidate)
		{
			return Candidate.CardId == Action.CardId;
		});
		if (Card == nullptr)
		{
			return false;
		}

		const int32* AvailableMana = State.PlayerMana.Find(Card->ManaType);
		return AvailableMana != nullptr && *AvailableMana >= Card->Cost;
	}

	if (Action.ActionType == TEXT("attack"))
	{
		if (!Action.CardId.IsEmpty() && !HasCardOnBoard(Action.CardId, State.PlayerBoard))
		{
			return false;
		}

		if (Action.TargetId.IsEmpty())
		{
			return true;
		}

		const bool bDirectTarget = Action.TargetId == TEXT("opponent_hero") || Action.TargetId == TEXT("player_hero");
		return bDirectTarget || HasCardOnBoard(Action.TargetId, State.OpponentBoard);
	}

	return false;
}
