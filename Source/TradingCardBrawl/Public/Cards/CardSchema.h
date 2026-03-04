#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "UObject/Object.h"
#include "CardSchema.generated.h"

UCLASS()
class TRADINGCARDBRAWL_API UCardSchemaValidator : public UObject
{
	GENERATED_BODY()

public:
	static bool ValidateCard(const TSharedPtr<FJsonObject>& CardJson, FString& OutError);
};
