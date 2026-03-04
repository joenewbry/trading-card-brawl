#include "UI/TCBHUD.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "UI/CardWidget.h"

void UTCBHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (EndTurnButton)
	{
		EndTurnButton->OnClicked.RemoveDynamic(this, &UTCBHUD::OnEndTurnClicked);
		EndTurnButton->OnClicked.AddDynamic(this, &UTCBHUD::OnEndTurnClicked);
	}
}

void UTCBHUD::UpdateHealth(int32 PlayerHP, int32 OpponentHP)
{
	if (PlayerHealthText)
	{
		PlayerHealthText->SetText(FText::AsNumber(PlayerHP));
	}

	if (OpponentHealthText)
	{
		OpponentHealthText->SetText(FText::AsNumber(OpponentHP));
	}
}

void UTCBHUD::UpdateTurnCounter(int32 TurnNumber)
{
	if (TurnCounterText)
	{
		TurnCounterText->SetText(FText::Format(NSLOCTEXT("TCBHUD", "TurnCounter", "Turn {0}"), TurnNumber));
	}
}

void UTCBHUD::AddCardToHand(const FCardData& Card)
{
	if (!HandContainer)
	{
		return;
	}

	UCardWidget* CardWidget = CreateWidget<UCardWidget>(this, UCardWidget::StaticClass());
	if (!CardWidget)
	{
		return;
	}

	CardWidget->PopulateFromCardData(Card);
	HandContainer->AddChild(CardWidget);
}

void UTCBHUD::ClearHand()
{
	if (HandContainer)
	{
		HandContainer->ClearChildren();
	}
}

void UTCBHUD::OnEndTurnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UTCBHUD::OnEndTurnClicked"));
}
