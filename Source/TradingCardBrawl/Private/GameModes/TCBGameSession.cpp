#include "GameModes/TCBGameSession.h"

#include "Engine/World.h"

void ATCBGameSession::InitSession(FString InPlayer1Id, FString InPlayer2Id, bool bAI)
{
	Player1Id = MoveTemp(InPlayer1Id);
	Player2Id = MoveTemp(InPlayer2Id);
	bIsAIMatch = bAI;
	SessionStartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}

void ATCBGameSession::EndSession(FString WinnerId)
{
	const float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : SessionStartTime;
	const float MatchDuration = FMath::Max(0.0f, CurrentTime - SessionStartTime);
	OnSessionEnded.Broadcast(WinnerId, MatchDuration);
}
