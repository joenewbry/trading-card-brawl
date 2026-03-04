#pragma once

#include "CoreMinimal.h"
#include "Cards/DeckManager.h"
#include "Cards/ManaSystem.h"
#include "UObject/Object.h"
#include "AIStateSerializer.generated.h"

USTRUCT(BlueprintType)
struct TRADINGCARDBRAWL_API FGameState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<FCardData> PlayerHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<FCardData> PlayerBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<FCardData> OpponentBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 PlayerHP = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 OpponentHP = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 PlayerDeckSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 OpponentDeckSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 TurnNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EManaType ActiveManaType = EManaType::Shadow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TMap<EManaType, int32> PlayerMana;
};

UCLASS()
class TRADINGCARDBRAWL_API UAIStateSerializer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	static FString SerializeGameState(const FGameState& State);
};
