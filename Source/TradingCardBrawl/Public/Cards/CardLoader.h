#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardLoader.generated.h"

USTRUCT(BlueprintType)
struct TRADINGCARDBRAWL_API FCardData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ManaType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FlavorText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ArtAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Version;
};

UCLASS()
class TRADINGCARDBRAWL_API UCardLoader : public UObject
{
	GENERATED_BODY()

public:
	static TArray<FCardData> LoadAllCards(const FString& IndexPath);
	static bool LoadCardById(const FString& CardId, const FString& IndexPath, FCardData& OutCard);
};
