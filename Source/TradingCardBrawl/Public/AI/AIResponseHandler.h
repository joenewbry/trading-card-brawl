#pragma once

#include "CoreMinimal.h"
#include "AI/AIStateSerializer.h"
#include "UObject/Object.h"
#include "AIResponseHandler.generated.h"

USTRUCT(BlueprintType)
struct TRADINGCARDBRAWL_API FAIAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FString ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FString CardId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FString TargetId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAIActionsReady, const TArray<FAIAction>&, Actions);

UCLASS()
class TRADINGCARDBRAWL_API UAIResponseHandler : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	static TArray<FAIAction> ParseResponse(const FString& JsonResponse);

	UFUNCTION(BlueprintPure, Category = "AI")
	static bool ValidateAction(const FAIAction& Action, const FGameState& State);

	UPROPERTY(BlueprintAssignable, Category = "AI")
	FOnAIActionsReady OnAIActionsReady;
};
