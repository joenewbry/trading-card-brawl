// Fill out your copyright notice in the Description page of Project Settings.

#include "TCBSaveManager.h"
#include "Engine/Engine.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

// Tick is required for component, but we don't need logic yet
void UTCBSaveManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTCBSaveManager::SaveGame(const UTCBSaveGame* SaveData)
{
	if (!SaveData) return;
	
	UGameplayStatics::SaveGameToSlot(const_cast<UTCBSaveGame*>(SaveData), LastSaveSlotName, 0);
	bHasPendingSync = true;
}

UTCBSaveGame* UTCBSaveManager::LoadGame()
{
	UTCBSaveGame* LoadedSave = Cast<UTCBSaveGame>(UGameplayStatics::LoadGameFromSlot(LastSaveSlotName, 0));
	if (LoadedSave)
	{
		OnSaveLoaded.Broadcast(LoadedSave);
	}
	return LoadedSave;
}

void UTCBSaveManager::SyncToCloud(const FString& AuthToken)
{
	if (!bHasPendingSync) return;

	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.openarcade.io/api/save/sync"));
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("Authorization", ("Bearer " + AuthToken).ToString());

	// Serialize save data to JSON (simplified)
	FString JsonString = TEXT("{\"playerId\": \"\"}"); // Placeholder - real serialization needed
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response->GetResponseCode() == 200)
		{
			bHasPendingSync = false;
			OnSyncComplete.Broadcast(TEXT("Sync successful"));
		}
		else
		{
			OnSyncComplete.Broadcast(TEXT("Sync failed"));
		}
	});

	Request->ProcessRequest();
}

void UTCBSaveManager::SyncFromCloud(const FString& AuthToken)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.openarcade.io/api/save/load"));
	Request->SetVerb("GET");
	Request->SetHeader("Authorization", ("Bearer " + AuthToken).ToString());

	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response->GetResponseCode() == 200)
		{
			FString Content = Response->GetContentAsString();
			// Parse JSON and create save object
			// UGameplayStatics::SaveGameToSlot(...) here
			OnSyncComplete.Broadcast(TEXT("Load successful"));
		}
		else
		{
			OnSyncComplete.Broadcast(TEXT("Load failed"));
		}
	});

	Request->ProcessRequest();
}