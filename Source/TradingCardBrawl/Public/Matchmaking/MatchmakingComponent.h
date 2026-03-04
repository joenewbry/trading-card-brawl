#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MatchmakingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMatchFound, const FString&, OpponentId, const FString&, RoomId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQueueTimeoutReached);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRADINGCARDBRAWL_API UMatchmakingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMatchmakingComponent();

	UFUNCTION(BlueprintCallable, Category = "Matchmaking")
	void JoinQueue(FString PlayerId, int32 SkillRating, FString PreferredClass);

	UFUNCTION(BlueprintCallable, Category = "Matchmaking")
	void LeaveQueue();

	UFUNCTION(BlueprintCallable, Category = "Matchmaking")
	void OnMatchFound(FString OpponentId, FString RoomId);

	UFUNCTION(BlueprintCallable, Category = "Matchmaking")
	void OnQueueTimeout();

	UPROPERTY(BlueprintAssignable, Category = "Matchmaking")
	FOnMatchFound MatchFound;

	UPROPERTY(BlueprintAssignable, Category = "Matchmaking")
	FOnQueueTimeoutReached QueueTimeoutReached;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Matchmaking")
	FTimerHandle QueueTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Matchmaking")
	float QueueTimeoutSeconds = 15.0f;

private:
	UFUNCTION()
	void HandleQueueTimerExpired();

	UPROPERTY(VisibleAnywhere, Category = "Matchmaking")
	FString CurrentPlayerId;

	UPROPERTY(VisibleAnywhere, Category = "Matchmaking")
	int32 CurrentSkillRating = 0;

	UPROPERTY(VisibleAnywhere, Category = "Matchmaking")
	FString CurrentPreferredClass;
};
