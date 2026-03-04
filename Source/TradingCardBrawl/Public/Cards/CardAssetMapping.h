#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardAssetMapping.generated.h"

USTRUCT(BlueprintType)
struct TRADINGCARDBRAWL_API FCardAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|Cards|Assets")
	FString CardId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|Cards|Assets")
	FString PortraitAssetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|Cards|Assets")
	FString BorderAssetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCB|Cards|Assets")
	FString ClassFolder;
};

UCLASS()
class TRADINGCARDBRAWL_API UCardAssetRegistry : public UObject
{
	GENERATED_BODY()

public:
	static TMap<FString, FCardAssetData> BuildDefaultMappings();
	static FString ResolvePortraitPath(const FString& CardId, const FString& ClassName);
	static FString GetBorderPathForClass(const FString& ClassName);
};
