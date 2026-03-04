#include "GameModes/TCBPlayerController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameModes/TCBGameMode.h"
#include "TimerManager.h"
#include "UI/CardWidget.h"

ATCBPlayerController::ATCBPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ATCBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ATCBGameMode* GameMode = GetWorld() ? GetWorld()->GetAuthGameMode<ATCBGameMode>() : nullptr)
	{
		GameMode->OnTurnChanged.RemoveDynamic(this, &ATCBPlayerController::HandleTurnPhaseChanged);
		GameMode->OnTurnChanged.AddDynamic(this, &ATCBPlayerController::HandleTurnPhaseChanged);
		HandleTurnPhaseChanged(GameMode->CurrentPhase);
	}
}

void ATCBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent)
	{
		return;
	}

	InputComponent->BindAction(TEXT("SelectCard"), IE_Pressed, this, &ATCBPlayerController::HandleSelectCardInput);
	InputComponent->BindAction(TEXT("PlayCard"), IE_Pressed, this, &ATCBPlayerController::HandlePlayCardInput);
	InputComponent->BindAction(TEXT("EndTurn"), IE_Pressed, this, &ATCBPlayerController::HandleEndTurnInput);
	InputComponent->BindAction(TEXT("ZoomCard"), IE_Pressed, this, &ATCBPlayerController::HandleZoomCardPressed);
	InputComponent->BindAction(TEXT("ZoomCard"), IE_Released, this, &ATCBPlayerController::HandleZoomCardReleased);
	InputComponent->BindAxis(TEXT("ScrollHand"), this, &ATCBPlayerController::HandleScrollHand);

	InputComponent->BindTouch(IE_Pressed, this, &ATCBPlayerController::HandleTouchPressed);
	InputComponent->BindTouch(IE_Released, this, &ATCBPlayerController::HandleTouchReleased);
}

void ATCBPlayerController::OnCardClicked(UCardWidget* Card)
{
	if (!Card || !bIsMyTurn)
	{
		return;
	}

	if (SelectedCard == Card)
	{
		Card->bIsSelected = false;
		SelectedCard = nullptr;
		return;
	}

	if (SelectedCard)
	{
		SelectedCard->bIsSelected = false;
	}

	SelectedCard = Card;
	SelectedCard->bIsSelected = true;
}

void ATCBPlayerController::OnBoardZoneClicked(bool bIsPlayerZone)
{
	if (!bIsMyTurn)
	{
		return;
	}

	if (SelectedCard && bIsPlayerZone)
	{
		if (SelectedCard->bCanBePlayed)
		{
			UE_LOG(LogTemp, Log, TEXT("ATCBPlayerController: Play selected card to player zone"));
			SelectedCard->bIsSelected = false;
			SelectedCard = nullptr;
		}
		return;
	}

	if (SelectedCard && !bIsPlayerZone)
	{
		UE_LOG(LogTemp, Log, TEXT("ATCBPlayerController: Attack with selected card"));
		return;
	}

	if (!bIsPlayerZone)
	{
		UE_LOG(LogTemp, Log, TEXT("ATCBPlayerController: Attack board zone clicked"));
	}
}

void ATCBPlayerController::OnEndTurnPressed()
{
	if (!bIsMyTurn)
	{
		return;
	}

	if (ATCBGameMode* GameMode = GetWorld() ? GetWorld()->GetAuthGameMode<ATCBGameMode>() : nullptr)
	{
		GameMode->EndTurn();
	}
}

void ATCBPlayerController::SetMyTurn(bool bTurn)
{
	bIsMyTurn = bTurn;
	SetIgnoreMoveInput(!bTurn);
	SetIgnoreLookInput(!bTurn);
}

void ATCBPlayerController::HandleTouchInput(ETouchIndex::Type FingerIndex, FVector Location)
{
	(void)FingerIndex;
	const FVector2D TouchScreenPos(Location.X, Location.Y);
	if (UCardWidget* Card = ResolveCardAtScreenPosition(TouchScreenPos))
	{
		OnCardClicked(Card);
		return;
	}

	int32 ViewSizeX = 0;
	int32 ViewSizeY = 0;
	GetViewportSize(ViewSizeX, ViewSizeY);
	const bool bIsPlayerZone = TouchScreenPos.Y >= (static_cast<float>(ViewSizeY) * 0.5f);
	OnBoardZoneClicked(bIsPlayerZone);
}

void ATCBPlayerController::ShowCardPreview(UCardWidget* Card)
{
	UCardWidget* CardToPreview = Card ? Card : ResolveHoveredCardWidget();
	if (!CardToPreview || PreviewCard == CardToPreview)
	{
		return;
	}

	HideCardPreview();

	PreviewCard = CardToPreview;
	PreviewCardOriginalScale = PreviewCard->GetRenderTransform().Scale;
	bHasPreviewScale = true;
	PreviewCard->SetRenderScale(PreviewCardOriginalScale * 1.2f);
}

void ATCBPlayerController::HideCardPreview()
{
	if (!PreviewCard)
	{
		return;
	}

	if (bHasPreviewScale)
	{
		PreviewCard->SetRenderScale(PreviewCardOriginalScale);
	}

	PreviewCard = nullptr;
	bHasPreviewScale = false;
}

void ATCBPlayerController::HandleTurnPhaseChanged(ETurnPhase NewPhase)
{
	SetMyTurn(NewPhase == ETurnPhase::PlayPhase || NewPhase == ETurnPhase::AttackPhase);
}

void ATCBPlayerController::HandleSelectCardInput()
{
	HandlePrimaryTapInput();
}

void ATCBPlayerController::HandlePlayCardInput()
{
	HandlePrimaryTapInput();
}

void ATCBPlayerController::HandlePrimaryTapInput()
{
	if (!GetWorld())
	{
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - LastPrimaryTapTime <= KINDA_SMALL_NUMBER)
	{
		return;
	}
	LastPrimaryTapTime = Now;

	float ScreenX = 0.0f;
	float ScreenY = 0.0f;
	if (!GetMousePosition(ScreenX, ScreenY))
	{
		return;
	}

	ProcessPointerSelection(FVector2D(ScreenX, ScreenY));
}

void ATCBPlayerController::HandleZoomCardPressed()
{
	ShowCardPreview(nullptr);
}

void ATCBPlayerController::HandleZoomCardReleased()
{
	HideCardPreview();
}

void ATCBPlayerController::HandleEndTurnInput()
{
	OnEndTurnPressed();
}

void ATCBPlayerController::HandleScrollHand(float AxisValue)
{
	if (!FMath::IsNearlyZero(AxisValue))
	{
		UE_LOG(LogTemp, Verbose, TEXT("ATCBPlayerController: ScrollHand axis=%f"), AxisValue);
	}
}

void ATCBPlayerController::HandleTouchPressed(ETouchIndex::Type FingerIndex, FVector Location)
{
	LastTouchScreenPosition = FVector2D(Location.X, Location.Y);
	bTouchPressed = true;
	bTouchMoved = false;
	bTouchHoldTriggered = false;

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TouchHoldTimer);
		GetWorld()->GetTimerManager().SetTimer(TouchHoldTimer, this, &ATCBPlayerController::TriggerTouchHoldZoom, 0.5f, false);
	}
}

void ATCBPlayerController::HandleTouchReleased(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TouchHoldTimer);
	}

	if (bTouchHoldTriggered)
	{
		HideCardPreview();
	}
	else if (bTouchPressed && !bTouchMoved)
	{
		HandleTouchInput(FingerIndex, Location);
	}

	bTouchPressed = false;
	bTouchMoved = false;
	bTouchHoldTriggered = false;
}

void ATCBPlayerController::TriggerTouchHoldZoom()
{
	if (!bTouchPressed)
	{
		return;
	}

	bTouchHoldTriggered = true;
	ShowCardPreview(ResolveCardAtScreenPosition(LastTouchScreenPosition));
}

void ATCBPlayerController::ProcessPointerSelection(const FVector2D& ScreenPosition)
{
	if (UCardWidget* Card = ResolveCardAtScreenPosition(ScreenPosition))
	{
		OnCardClicked(Card);
		return;
	}

	ProcessBoardZoneFromScreenPosition(ScreenPosition);
}

void ATCBPlayerController::ProcessBoardZoneFromScreenPosition(const FVector2D& ScreenPosition)
{
	int32 ViewSizeX = 0;
	int32 ViewSizeY = 0;
	GetViewportSize(ViewSizeX, ViewSizeY);

	if (ViewSizeY <= 0)
	{
		return;
	}

	const bool bIsPlayerZone = ScreenPosition.Y >= (static_cast<float>(ViewSizeY) * 0.5f);
	OnBoardZoneClicked(bIsPlayerZone);
}

UCardWidget* ATCBPlayerController::ResolveCardAtScreenPosition(const FVector2D& ScreenPosition) const
{
	(void)ScreenPosition;
	return ResolveHoveredCardWidget();
}

UCardWidget* ATCBPlayerController::ResolveHoveredCardWidget() const
{
	if (!GetWorld())
	{
		return nullptr;
	}

	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UCardWidget::StaticClass(), false);
	for (UUserWidget* Widget : Widgets)
	{
		if (UCardWidget* CardWidget = Cast<UCardWidget>(Widget))
		{
			if (CardWidget->IsHovered())
			{
				return CardWidget;
			}
		}
	}

	return nullptr;
}
