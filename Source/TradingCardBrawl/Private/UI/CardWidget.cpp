#include "UI/CardWidget.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Input/Reply.h"

void UCardWidget::PopulateFromCardData(const FCardData& Card)
{
	(void)Card;

	// Base UI fallback values until full card-data binding is connected.
	if (CardNameText)
	{
		CardNameText->SetText(NSLOCTEXT("CardWidget", "DefaultName", "Card"));
	}

	if (CardCostText)
	{
		CardCostText->SetText(FText::FromString(TEXT("0")));
	}

	if (CardAttackText)
	{
		CardAttackText->SetText(FText::FromString(TEXT("0")));
	}

	if (CardHealthText)
	{
		CardHealthText->SetText(FText::FromString(TEXT("0")));
	}

	if (CardDescriptionText)
	{
		CardDescriptionText->SetText(FText::GetEmpty());
	}
}

FReply UCardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	const FReply SuperReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	OnCardClicked.Broadcast(this);
	return SuperReply.IsEventHandled() ? SuperReply : FReply::Handled();
}
