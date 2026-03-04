#include "Cards/ManaSystem.h"

#include "Math/UnrealMathUtility.h"

namespace ManaSystemInternal
{
	static const TArray<EManaType> AllTypes =
	{
		EManaType::Shadow,
		EManaType::Steel,
		EManaType::Life,
		EManaType::Wind,
		EManaType::Earth
	};
}

FManaPool::FManaPool()
{
	for (const EManaType ManaType : ManaSystemInternal::AllTypes)
	{
		Max.Add(ManaType, 5);
		Current.Add(ManaType, 5);
	}
}

UManaSystemComponent::UManaSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UManaSystemComponent::RefillMana()
{
	for (const EManaType ManaType : ManaSystemInternal::AllTypes)
	{
		const int32 MaxMana = FMath::Max(ManaPool.Max.FindRef(ManaType), 0);
		ManaPool.Current.FindOrAdd(ManaType) = MaxMana;
		OnManaChanged.Broadcast(ManaType, MaxMana, MaxMana);
	}
}

bool UManaSystemComponent::CanAfford(const EManaType Type, const int32 Cost) const
{
	if (Cost <= 0)
	{
		return true;
	}

	return ManaPool.Current.FindRef(Type) >= Cost;
}

bool UManaSystemComponent::SpendMana(const EManaType Type, const int32 Cost)
{
	if (Cost < 0)
	{
		return false;
	}

	if (!CanAfford(Type, Cost))
	{
		return false;
	}

	const int32 UpdatedMana = ManaPool.Current.FindRef(Type) - Cost;
	ManaPool.Current.FindOrAdd(Type) = UpdatedMana;
	OnManaChanged.Broadcast(Type, UpdatedMana, ManaPool.Max.FindRef(Type));
	return true;
}

int32 UManaSystemComponent::GetCurrentMana(const EManaType Type) const
{
	return ManaPool.Current.FindRef(Type);
}
