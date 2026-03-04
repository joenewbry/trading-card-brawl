#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardWidget.generated.h"

class UBorder;
class UImage;
class UTextBlock;
class UCardWidget;
struct FCardData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardClicked, UCardWidget*, Card);

UCLASS()
class TRADINGCARDBRAWL_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UImage* CardArt = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardNameText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardCostText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardAttackText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardHealthText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardDescriptionText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UBorder* CardFrame = nullptr;

	UFUNCTION(BlueprintCallable, Category = "TCB|Card")
	void PopulateFromCardData(const FCardData& Card);

	UPROPERTY(BlueprintReadOnly, Category = "TCB|Card")
	bool bIsSelected = false;

	UPROPERTY(BlueprintReadOnly, Category = "TCB|Card")
	bool bCanBePlayed = true;

	UPROPERTY(BlueprintAssignable, Category = "TCB|Card")
	FOnCardClicked OnCardClicked;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
