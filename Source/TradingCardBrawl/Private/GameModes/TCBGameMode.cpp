#include "GameModes/TCBGameMode.h"

#include "Cards/DeckManager.h"
#include "EngineUtils.h"

ATCBGameMode::ATCBGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATCBGameMode::StartGame()
{
	PlayerHP = 30;
	OpponentHP = 30;
	StartTurn();
}

void ATCBGameMode::StartTurn()
{
	if (CheckWinCondition())
	{
		OnGameOver.Broadcast(PlayerHP > OpponentHP);
		return;
	}

	CurrentPhase = ETurnPhase::DrawPhase;
	OnTurnChanged.Broadcast(CurrentPhase);
	DrawCard();

	CurrentPhase = ETurnPhase::PlayPhase;
	OnTurnChanged.Broadcast(CurrentPhase);
}

void ATCBGameMode::EndTurn()
{
	CurrentPhase = ETurnPhase::EndPhase;
	OnTurnChanged.Broadcast(CurrentPhase);

	if (CheckWinCondition())
	{
		OnGameOver.Broadcast(PlayerHP > OpponentHP);
		return;
	}

	StartTurn();
}

void ATCBGameMode::DrawCard()
{
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		if (UDeckManager* DeckManager = It->FindComponentByClass<UDeckManager>())
		{
			DeckManager->DrawTopCard();
			break;
		}
	}
}

bool ATCBGameMode::CheckWinCondition() const
{
	if (PlayerHP <= 0 || OpponentHP <= 0)
	{
		return true;
	}

	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			if (const UDeckManager* DeckManager = It->FindComponentByClass<UDeckManager>())
			{
				if (DeckManager->IsDeckEmpty())
				{
					return true;
				}
			}
		}
	}

	return false;
}
