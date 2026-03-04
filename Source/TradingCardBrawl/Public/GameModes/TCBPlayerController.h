#pragma once

#include "CoreMinimal.h"
#include "GameModes/TCBGameMode.h"
#include "GameFramework/PlayerController.h"
#include "TCBPlayerController.generated.h"

class UCardWidget;

UCLASS()
class TRADINGCARDBRAWL_API ATCBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATCBPlayerController();

	UFUNCTION(BlueprintCallable, Category = "TCB|Input")
	void OnCardClicked(UCardWidget* Card);

	UFUNCTION(BlueprintCallable, Category = "TCB|Input")
	void OnBoardZoneClicked(bool bIsPlayerZone);

	UFUNCTION(BlueprintCallable, Category = "TCB|Input")
	void OnEndTurnPressed();

	UFUNCTION(BlueprintCallable, Category = "TCB|Input")
	void SetMyTurn(bool bTurn);

	UFUNCTION(BlueprintCallable, Category = "TCB|Input")
	void HandleTouchInput(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION(BlueprintCallable, Category = "TCB|Input")
	void ShowCardPreview(UCardWidget* Card);

	UFUNCTION(BlueprintCallable, Category = "TCB|Input")
	void HideCardPreview();

	UPROPERTY(BlueprintReadOnly, Category = "TCB|Input")
	UCardWidget* SelectedCard = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "TCB|Input")
	bool bIsMyTurn = false;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void HandleTurnPhaseChanged(ETurnPhase NewPhase);

	void HandleSelectCardInput();
	void HandlePlayCardInput();
	void HandlePrimaryTapInput();
	void HandleZoomCardPressed();
	void HandleZoomCardReleased();
	void HandleEndTurnInput();
	void HandleScrollHand(float AxisValue);
	void HandleTouchPressed(ETouchIndex::Type FingerIndex, FVector Location);
	void HandleTouchReleased(ETouchIndex::Type FingerIndex, FVector Location);
	void TriggerTouchHoldZoom();

	void ProcessPointerSelection(const FVector2D& ScreenPosition);
	void ProcessBoardZoneFromScreenPosition(const FVector2D& ScreenPosition);
	UCardWidget* ResolveCardAtScreenPosition(const FVector2D& ScreenPosition) const;
	UCardWidget* ResolveHoveredCardWidget() const;

	FTimerHandle TouchHoldTimer;
	FVector2D LastTouchScreenPosition = FVector2D::ZeroVector;
	bool bTouchPressed = false;
	bool bTouchHoldTriggered = false;
	bool bTouchMoved = false;
	float LastPrimaryTapTime = -100.0f;

	UPROPERTY(Transient)
	UCardWidget* PreviewCard = nullptr;

	FVector2D PreviewCardOriginalScale = FVector2D(1.0f, 1.0f);
	bool bHasPreviewScale = false;
};
