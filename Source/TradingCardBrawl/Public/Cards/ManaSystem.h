#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManaSystem.generated.h"

UENUM(BlueprintType)
enum class EManaType : uint8
{
	Shadow UMETA(DisplayName = "Shadow"),
	Steel UMETA(DisplayName = "Steel"),
	Life UMETA(DisplayName = "Life"),
	Wind UMETA(DisplayName = "Wind"),
	Earth UMETA(DisplayName = "Earth")
};

USTRUCT(BlueprintType)
struct TRADINGCARDBRAWL_API FManaPool
{
	GENERATED_BODY()

public:
	FManaPool();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	TMap<EManaType, int32> Current;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	TMap<EManaType, int32> Max;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnManaChanged, EManaType, ManaType, int32, CurrentMana, int32, MaxMana);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRADINGCARDBRAWL_API UManaSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UManaSystemComponent();

	UFUNCTION(BlueprintCallable, Category = "Mana")
	void RefillMana();

	UFUNCTION(BlueprintCallable, Category = "Mana")
	bool CanAfford(EManaType Type, int32 Cost) const;

	UFUNCTION(BlueprintCallable, Category = "Mana")
	bool SpendMana(EManaType Type, int32 Cost);

	UFUNCTION(BlueprintPure, Category = "Mana")
	int32 GetCurrentMana(EManaType Type) const;

	UPROPERTY(BlueprintAssignable, Category = "Mana")
	FOnManaChanged OnManaChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	FManaPool ManaPool;
};
