#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/AIResponseHandler.h"
#include "HttpFwd.h"
#include "AIOpponentController.generated.h"

UCLASS(Config = Game)
class TRADINGCARDBRAWL_API ATCBAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATCBAIController();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnTurnStart(const FGameState& State);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ExecuteActions(const TArray<FAIAction>& Actions);

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "AI")
	FString DGXSparkEndpoint = TEXT("http://localhost:11434/api/generate");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MaxResponseTimeSeconds = 5.0f;

private:
	void HandleAIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void HandleResponseTimeout();
	TArray<FAIAction> BuildFallbackActions(const FGameState& State) const;

	FGameState PendingState;
	FTimerHandle ResponseTimeoutTimer;
	bool bWaitingForResponse = false;
};
