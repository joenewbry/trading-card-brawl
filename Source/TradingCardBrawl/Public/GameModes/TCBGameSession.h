#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "TCBGameSession.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionEnded, const FString&, WinnerId, float, MatchDuration);

UCLASS()
class TRADINGCARDBRAWL_API ATCBGameSession : public AGameSession
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Session")
	void InitSession(FString InPlayer1Id, FString InPlayer2Id, bool bAI);

	UFUNCTION(BlueprintCallable, Category = "Session")
	void EndSession(FString WinnerId);

	UPROPERTY(BlueprintAssignable, Category = "Session")
	FOnSessionEnded OnSessionEnded;

	UPROPERTY(BlueprintReadWrite, Category = "Session")
	FString RoomId;

	UPROPERTY(BlueprintReadWrite, Category = "Session")
	FString Player1Id;

	UPROPERTY(BlueprintReadWrite, Category = "Session")
	FString Player2Id;

	UPROPERTY(BlueprintReadWrite, Category = "Session")
	bool bIsAIMatch = false;

	UPROPERTY(BlueprintReadWrite, Category = "Session")
	float SessionStartTime = 0.0f;
};
