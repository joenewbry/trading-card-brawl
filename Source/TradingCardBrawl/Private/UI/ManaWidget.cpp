#include "UI/ManaWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UManaWidget::SetMana(int32 Current, int32 Max)
{
	if (ManaAmountText)
	{
		ManaAmountText->SetText(FText::Format(NSLOCTEXT("ManaWidget", "ManaAmountFmt", "{0}/{1}"), Current, Max));
	}

	if (ManaIcon)
	{
		ManaIcon->SetColorAndOpacity(GetManaColor(ManaType));
	}
}

FLinearColor UManaWidget::GetManaColor(EManaType Type)
{
	switch (Type)
	{
	case EManaType::Shadow:
		return FLinearColor(0.45f, 0.22f, 0.65f, 1.0f); // purple
	case EManaType::Steel:
		return FLinearColor(0.75f, 0.75f, 0.78f, 1.0f); // silver
	case EManaType::Life:
		return FLinearColor(0.20f, 0.75f, 0.30f, 1.0f); // green
	case EManaType::Wind:
		return FLinearColor(0.00f, 0.80f, 0.90f, 1.0f); // cyan
	case EManaType::Earth:
		return FLinearColor(0.45f, 0.30f, 0.18f, 1.0f); // brown
	default:
		return FLinearColor::White;
	}
}
