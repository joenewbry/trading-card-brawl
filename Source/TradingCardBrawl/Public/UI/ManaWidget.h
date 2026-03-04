#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManaWidget.generated.h"

class UImage;
class UTextBlock;

UENUM(BlueprintType)
enum class EManaType : uint8
{
	Shadow,
	Steel,
	Life,
	Wind,
	Earth
};

UCLASS()
class TRADINGCARDBRAWL_API UManaWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ManaAmountText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* ManaIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|Mana")
	EManaType ManaType = EManaType::Shadow;

	UFUNCTION(BlueprintCallable, Category = "TCB|Mana")
	void SetMana(int32 Current, int32 Max);

	static FLinearColor GetManaColor(EManaType Type);
};
