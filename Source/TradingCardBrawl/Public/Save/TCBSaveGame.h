// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TCBSaveGame.generated.h"

UCLASS()
class TRADINGCARDBRAWL_API UTCBSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	FString PlayerId;
	TArray<FString> OwnedCardIds;
	TArray<FString> DeckCardIds;
	int32 TotalWins;
	int32 TotalLosses;
	int32 TotalMatches;
	FString SelectedHeroClass;
	int32 BattleTokens;
	bool bTutorialCompleted = false;
	FString LastSyncTimestamp;
	FString SaveVersion = "1.0.0";
};
