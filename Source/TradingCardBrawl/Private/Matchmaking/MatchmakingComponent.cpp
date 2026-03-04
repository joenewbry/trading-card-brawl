#include "Matchmaking/MatchmakingComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"

UMatchmakingComponent::UMatchmakingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMatchmakingComponent::JoinQueue(FString PlayerId, int32 SkillRating, FString PreferredClass)
{
	CurrentPlayerId = MoveTemp(PlayerId);
	CurrentSkillRating = SkillRating;
	CurrentPreferredClass = MoveTemp(PreferredClass);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(QueueTimer);
		World->GetTimerManager().SetTimer(QueueTimer, this, &UMatchmakingComponent::HandleQueueTimerExpired, QueueTimeoutSeconds, false);
	}
}

void UMatchmakingComponent::LeaveQueue()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(QueueTimer);
	}

	CurrentPlayerId.Reset();
	CurrentSkillRating = 0;
	CurrentPreferredClass.Reset();
}

void UMatchmakingComponent::OnMatchFound(FString OpponentId, FString RoomId)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(QueueTimer);
	}

	MatchFound.Broadcast(OpponentId, RoomId);
}

void UMatchmakingComponent::OnQueueTimeout()
{
	QueueTimeoutReached.Broadcast();

	// Hook for AI opponent fallback behavior when no match is found in time.
	UE_LOG(LogTemp, Warning, TEXT("Matchmaking queue timeout reached for player %s; trigger AI fallback."), *CurrentPlayerId);
}

void UMatchmakingComponent::HandleQueueTimerExpired()
{
	OnQueueTimeout();
}
