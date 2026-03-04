#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TCBHUD.generated.h"

class UButton;
class UHorizontalBox;
class UTextBlock;
class UTCBAudioManager;
class UTutorialManager;
class UVerticalBox;
struct FCardData;

UCLASS()
class TRADINGCARDBRAWL_API UTCBHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HandContainer = nullptr;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerBoardZone = nullptr;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OpponentBoardZone = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TurnCounterText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerHealthText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OpponentHealthText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* EndTurnButton = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TutorialPromptText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|HUD")
	UTutorialManager* TutorialManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|HUD")
	UTCBAudioManager* AudioManager = nullptr;

	UFUNCTION(BlueprintCallable, Category = "TCB|HUD")
	void UpdateHealth(int32 PlayerHP, int32 OpponentHP);

	UFUNCTION(BlueprintCallable, Category = "TCB|HUD")
	void UpdateTurnCounter(int32 TurnNumber);

	UFUNCTION(BlueprintCallable, Category = "TCB|HUD")
	void AddCardToHand(const FCardData& Card);

	UFUNCTION(BlueprintCallable, Category = "TCB|HUD")
	void ClearHand();

	UFUNCTION(BlueprintCallable, Category = "TCB|HUD")
	void ShowTutorialPrompt(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "TCB|HUD")
	void HideTutorialPrompt();

	UFUNCTION(BlueprintCallable, Category = "TCB|HUD")
	void OnCardPlayedSound();

	UFUNCTION(BlueprintCallable, Category = "TCB|HUD")
	void OnAttackSound();

	UFUNCTION()
	void OnEndTurnClicked();

protected:
	virtual void NativeConstruct() override;
};
