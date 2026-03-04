#include "Cards/DeckManager.h"

#include "Math/UnrealMathUtility.h"

UDeckManager::UDeckManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDeckManager::Shuffle()
{
	for (int32 Index = Deck.Num() - 1; Index > 0; --Index)
	{
		const int32 SwapIndex = FMath::RandRange(0, Index);
		Deck.Swap(Index, SwapIndex);
	}
}

FCardData UDeckManager::DrawTopCard()
{
	if (Deck.IsEmpty())
	{
		return FCardData();
	}

	const FCardData TopCard = Deck.Pop();
	if (Hand.Num() < 10)
	{
		Hand.Add(TopCard);
	}

	return TopCard;
}

bool UDeckManager::IsDeckEmpty() const
{
	return Deck.IsEmpty();
}

void UDeckManager::DealInitialHand(const int32 Count)
{
	const int32 CardsToDraw = FMath::Max(0, Count);
	for (int32 CardIndex = 0; CardIndex < CardsToDraw; ++CardIndex)
	{
		if (Deck.IsEmpty() || Hand.Num() >= 10)
		{
			break;
		}

		DrawTopCard();
	}
}
