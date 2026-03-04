#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TCBGameInstance.generated.h"

class UTCBSaveManager;

UCLASS()
class TRADINGCARDBRAWL_API UTCBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SavePlayerData();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void LoadPlayerData();

	UFUNCTION(BlueprintCallable, Category = "Collection")
	void AddCardToCollection(FString CardId);

	UFUNCTION(BlueprintPure, Category = "Collection")
	bool HasCard(FString CardId) const;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FString LocalPlayerId;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FString AuthToken;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FString SelectedHeroClass;

	UPROPERTY(BlueprintReadWrite, Category = "Collection")
	TArray<FString> OwnedCardIds;

	UPROPERTY(BlueprintReadWrite, Category = "Deck")
	TArray<FString> CurrentDeckIds;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	int32 BattleTokens = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 TotalWins = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 TotalLosses = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Tutorial")
	bool bTutorialCompleted = false;

	UPROPERTY(Transient)
	UTCBSaveManager* SaveManager = nullptr;
};
