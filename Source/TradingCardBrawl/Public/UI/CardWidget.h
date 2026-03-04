// Task 1: CardWidget.h - Updated for UE5.7 Asset Pack Integration
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "Engine/SoftObjectPath.h"
#include "CardWidget.generated.h"

class UBorder;
class UImage;
class UTextBlock;
class UCardWidget;
struct FCardData;

class UCardAssetRegistry; // Forward declaration

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardClicked, UCardWidget*, Card);

UCLASS()
class TRADINGCARDBRAWL_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|Card|Textures")
	TSoftObjectPtr<UTexture2D> CardPortraitTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|Card|Textures")
	TSoftObjectPtr<UTexture2D> CardBorderTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|Card|Textures")
	TSoftObjectPtr<UTexture2D> CardBackTexture;

	UPROPERTY(meta = (BindWidget))
	UImage* CardArt = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* CardBack = nullptr;

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

	// Public interface
	UFUNCTION(BlueprintCallable, Category = "TCB|Card|Textures")
	void LoadTextures();

	UFUNCTION(BlueprintCallable, Category = "TCB|Card|Textures")
	void ShowFaceDown();

	UFUNCTION(BlueprintCallable, Category = "TCB|Card|Textures")
	void ShowFaceUp();

	static FString GetAssetPackPathForClass(const FString& ClassName);

	UPROPERTY(BlueprintReadOnly, Category = "TCB|Card")
	bool bIsSelected = false;

	UPROPERTY(BlueprintReadOnly, Category = "TCB|Card")
	bool bCanBePlayed = true;

	UPROPERTY(BlueprintAssignable, Category = "TCB|Card")
	FOnCardClicked OnCardClicked;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
