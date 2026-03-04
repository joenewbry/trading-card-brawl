#include "UI/DeckBuilderComponent.h"

UDeckBuilderComponent::UDeckBuilderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UDeckBuilderComponent::AddCard(FString CardId)
{
	if (CardId.IsEmpty())
	{
		return false;
	}

	if (CurrentDeck.Num() >= MaxDeckSize)
	{
		return false;
	}

	if (GetCopyCount(CardId) >= MaxCopiesPerCard)
	{
		return false;
	}

	CurrentDeck.Add(MoveTemp(CardId));
	OnDeckChanged.Broadcast();
	return true;
}

bool UDeckBuilderComponent::RemoveCard(FString CardId)
{
	if (CardId.IsEmpty())
	{
		return false;
	}

	const int32 RemovedCount = CurrentDeck.RemoveSingle(CardId);
	if (RemovedCount > 0)
	{
		OnDeckChanged.Broadcast();
		return true;
	}

	return false;
}

bool UDeckBuilderComponent::ValidateDeck() const
{
	if (CurrentDeck.Num() < MinDeckSize || CurrentDeck.Num() > MaxDeckSize)
	{
		return false;
	}

	TMap<FString, int32> CopyMap;
	for (const FString& CardId : CurrentDeck)
	{
		const int32 NewCount = CopyMap.FindOrAdd(CardId) + 1;
		CopyMap[CardId] = NewCount;
		if (NewCount > MaxCopiesPerCard)
		{
			return false;
		}
	}

	const TArray<FString> Classes = GetClassBreakdown();
	return Classes.Num() >= 2;
}

int32 UDeckBuilderComponent::GetCopyCount(FString CardId) const
{
	if (CardId.IsEmpty())
	{
		return 0;
	}

	int32 Count = 0;
	for (const FString& ExistingId : CurrentDeck)
	{
		if (ExistingId == CardId)
		{
			++Count;
		}
	}

	return Count;
}

TArray<FString> UDeckBuilderComponent::GetClassBreakdown() const
{
	TSet<FString> UniqueClasses;
	for (const FString& CardId : CurrentDeck)
	{
		const FString CardClass = ResolveCardClass(CardId);
		if (!CardClass.IsEmpty())
		{
			UniqueClasses.Add(CardClass);
		}
	}

	TArray<FString> Result = UniqueClasses.Array();
	Result.Sort();
	return Result;
}

FString UDeckBuilderComponent::ResolveCardClass(const FString& CardId) const
{
	if (CardId.IsEmpty())
	{
		return FString();
	}

	FString Left;
	FString Right;
	if (CardId.Split(TEXT(":"), &Left, &Right))
	{
		return Left;
	}

	if (CardId.Split(TEXT("_"), &Left, &Right))
	{
		return Left;
	}

	if (CardId.Split(TEXT("-"), &Left, &Right))
	{
		return Left;
	}

	return CardId;
}
