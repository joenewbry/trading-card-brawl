#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cards/DeckManager.h"
#include "TutorialManager.generated.h"

UENUM(BlueprintType)
enum class ETutorialStep : uint8
{
	DrawCards UMETA(DisplayName = "Draw Cards"),
	PlayCard UMETA(DisplayName = "Play Card"),
	AttackWithMinion UMETA(DisplayName = "Attack With Minion"),
	EndTurn UMETA(DisplayName = "End Turn"),
	WinMatch UMETA(DisplayName = "Win Match"),
	Complete UMETA(DisplayName = "Complete")
};

USTRUCT(BlueprintType)
struct TRADINGCARDBRAWL_API FTutorialStepData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial")
	ETutorialStep Step = ETutorialStep::DrawCards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial")
	FString InstructionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial")
	FString HighlightTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial")
	FCardData RewardCard;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepComplete, const FCardData&, RewardCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTutorialComplete);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRADINGCARDBRAWL_API UTutorialManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UTutorialManager();

	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void StartTutorial();

	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void AdvanceStep();

	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void CompleteStep(ETutorialStep Step);

	UFUNCTION(BlueprintPure, Category = "Tutorial")
	ETutorialStep GetCurrentStep() const;

	UFUNCTION(BlueprintPure, Category = "Tutorial")
	bool IsTutorialActive() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tutorial")
	TArray<FTutorialStepData> Steps;

	UPROPERTY(BlueprintAssignable, Category = "Tutorial")
	FOnStepComplete OnStepComplete;

	UPROPERTY(BlueprintAssignable, Category = "Tutorial")
	FOnTutorialComplete OnTutorialComplete;

protected:
	virtual void BeginPlay() override;

private:
	ETutorialStep CurrentStep = ETutorialStep::Complete;
	bool bTutorialActive = false;
	int32 CurrentStepIndex = INDEX_NONE;

	FTutorialStepData* FindCurrentStepData();
	void GrantReward(const FCardData& RewardCard);
	static FCardData MakeRewardCard(const FString& CardId, const FString& CardName, const FString& Rarity);
};
