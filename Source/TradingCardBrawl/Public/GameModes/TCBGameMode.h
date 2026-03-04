#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TCBGameMode.generated.h"

UENUM(BlueprintType)
enum class ETurnPhase : uint8
{
	DrawPhase UMETA(DisplayName = "Draw Phase"),
	PlayPhase UMETA(DisplayName = "Play Phase"),
	AttackPhase UMETA(DisplayName = "Attack Phase"),
	EndPhase UMETA(DisplayName = "End Phase")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnChanged, ETurnPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, bPlayerWon);

UCLASS()
class TRADINGCARDBRAWL_API ATCBGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATCBGameMode();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartTurn();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndTurn();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void DrawCard();

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool CheckWinCondition() const;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FOnTurnChanged OnTurnChanged;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FOnGameOver OnGameOver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 PlayerHP = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 OpponentHP = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	ETurnPhase CurrentPhase = ETurnPhase::DrawPhase;
};
