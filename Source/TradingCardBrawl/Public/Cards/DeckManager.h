#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cards/ManaSystem.h"
#include "DeckManager.generated.h"

USTRUCT(BlueprintType)
struct TRADINGCARDBRAWL_API FCardData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString CardId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	EManaType ManaType = EManaType::Shadow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int32 Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int32 Attack = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int32 Health = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<FString> Abilities;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRADINGCARDBRAWL_API UDeckManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UDeckManager();

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void Shuffle();

	UFUNCTION(BlueprintCallable, Category = "Deck")
	FCardData DrawTopCard();

	UFUNCTION(BlueprintPure, Category = "Deck")
	bool IsDeckEmpty() const;

	UFUNCTION(BlueprintCallable, Category = "Deck")
	void DealInitialHand(int32 Count = 5);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Deck")
	TArray<FCardData> Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck")
	TArray<FCardData> Deck;
};
