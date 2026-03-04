// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ActorComponent.h"
#include "TCBSaveGame.h"
#include "TCBSaveManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSyncComplete, const FString&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveLoaded, const UTCBSaveGame*, SaveData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRADINGCARDBRAWL_API UTCBSaveManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SaveGame(const UTCBSaveGame* SaveData);

	UFUNCTION(BlueprintCallable)
	UTCBSaveGame* LoadGame();

	UFUNCTION(BlueprintCallable)
	void SyncToCloud(const FString& AuthToken);

	UFUNCTION(BlueprintCallable)
	void SyncFromCloud(const FString& AuthToken);

	UPROPERTY(BlueprintReadOnly, Category="Save")
	bool bHasPendingSync;

	UPROPERTY(BlueprintAssignable, Category="Save")
	FOnSyncComplete OnSyncComplete;

	UPROPERTY(BlueprintAssignable, Category="Save")
	FOnSaveLoaded OnSaveLoaded;

private:
	FString LastSaveSlotName = "PlayerSave";
};