#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeckBuilderComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeckChanged);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRADINGCARDBRAWL_API UDeckBuilderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDeckBuilderComponent();

	UFUNCTION(BlueprintCallable, Category = "TCB|DeckBuilder")
	bool AddCard(FString CardId);

	UFUNCTION(BlueprintCallable, Category = "TCB|DeckBuilder")
	bool RemoveCard(FString CardId);

	UFUNCTION(BlueprintCallable, Category = "TCB|DeckBuilder")
	bool ValidateDeck() const;

	UFUNCTION(BlueprintPure, Category = "TCB|DeckBuilder")
	int32 GetCopyCount(FString CardId) const;

	UFUNCTION(BlueprintPure, Category = "TCB|DeckBuilder")
	TArray<FString> GetClassBreakdown() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|DeckBuilder")
	TArray<FString> CurrentDeck;

	UPROPERTY(BlueprintAssignable, Category = "TCB|DeckBuilder")
	FOnDeckChanged OnDeckChanged;

private:
	static constexpr int32 MaxDeckSize = 40;
	static constexpr int32 MinDeckSize = 40;
	static constexpr int32 MaxCopiesPerCard = 3;

	FString ResolveCardClass(const FString& CardId) const;
};
