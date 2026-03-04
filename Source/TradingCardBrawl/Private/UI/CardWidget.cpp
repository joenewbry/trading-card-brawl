#include "UI/CardWidget.h"

#include "Cards/CardLoader.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Input/Reply.h"

namespace
{
	FString ToLowerTrimmed(const FString& Value)
	{
		FString Out = Value;
		Out.TrimStartAndEndInline();
		Out = Out.ToLower();
		return Out;
	}
}

void UCardWidget::PopulateFromCardData(const FCardData& Card)
{
	if (CardNameText)
	{
		CardNameText->SetText(FText::FromString(Card.Name));
	}

	if (CardCostText)
	{
		CardCostText->SetText(FText::AsNumber(Card.Cost));
	}

	if (CardAttackText)
	{
		CardAttackText->SetText(FText::AsNumber(Card.Attack));
	}

	if (CardHealthText)
	{
		CardHealthText->SetText(FText::AsNumber(Card.Health));
	}

	if (CardDescriptionText)
	{
		CardDescriptionText->SetText(FText::FromString(Card.Description));
	}

	const FString PortraitPath = GetAssetPackPathForClass(Card.CardClass) + Card.Id;
	if (!PortraitPath.IsEmpty())
	{
		CardPortraitTexture = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(PortraitPath + TEXT(".") + Card.Id));
	}

	const FString BorderClass = Card.CardClass.Left(1).ToUpper() + Card.CardClass.Mid(1).ToLower();
	const FString BorderPath = FString::Printf(
		TEXT("/Game/EndlessModularTCGTradingCardCollection/CardBorders/Border_%s.Border_%s"),
		*BorderClass,
		*BorderClass);
	CardBorderTexture = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(BorderPath));

	LoadTextures();
	ShowFaceUp();
}

void UCardWidget::LoadTextures()
{
	if (CardArt)
	{
		if (UTexture2D* PortraitTexture = CardPortraitTexture.LoadSynchronous())
		{
			CardArt->SetBrushFromTexture(PortraitTexture, true);
		}
	}

	if (CardFrame)
	{
		if (UTexture2D* BorderTexture = CardBorderTexture.LoadSynchronous())
		{
			CardFrame->SetBrushFromTexture(BorderTexture);
		}
	}
}

void UCardWidget::ShowFaceDown()
{
	if (CardArt)
	{
		CardArt->SetVisibility(ESlateVisibility::Hidden);
	}

	if (CardBack)
	{
		if (UTexture2D* BackTexture = CardBackTexture.LoadSynchronous())
		{
			CardBack->SetBrushFromTexture(BackTexture, true);
		}
		CardBack->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCardWidget::ShowFaceUp()
{
	if (CardArt)
	{
		CardArt->SetVisibility(ESlateVisibility::Visible);
	}

	if (CardBack)
	{
		CardBack->SetVisibility(ESlateVisibility::Hidden);
	}
}

FString UCardWidget::GetAssetPackPathForClass(const FString& ClassName)
{
	const FString Normalized = ToLowerTrimmed(ClassName);

	if (Normalized == TEXT("warrior"))
	{
		return TEXT("/Game/EndlessModularTCGTradingCardCollection/Artwork/Warriors/");
	}
	if (Normalized == TEXT("ranger"))
	{
		return TEXT("/Game/EndlessModularTCGTradingCardCollection/Artwork/Hunter/");
	}
	if (Normalized == TEXT("necromancer"))
	{
		return TEXT("/Game/EndlessModularTCGTradingCardCollection/Artwork/Warlock/");
	}
	if (Normalized == TEXT("druid"))
	{
		return TEXT("/Game/EndlessModularTCGTradingCardCollection/Artwork/Druid/");
	}
	if (Normalized == TEXT("rogue"))
	{
		return TEXT("/Game/EndlessModularTCGTradingCardCollection/Artwork/Assassin/");
	}
	if (Normalized == TEXT("engineer"))
	{
		return TEXT("/Game/EndlessModularTCGTradingCardCollection/Artwork/Mech/");
	}

	return TEXT("");
}

FReply UCardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnCardClicked.Broadcast(this);
	return FReply::Handled();
}
