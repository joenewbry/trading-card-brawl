// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Cards/CardAssetStreamer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetLoaded, UTexture2D*, Texture);

UCLASS()
class TRADINGCARDBRAWL_API UCardAssetStreamer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PreloadCoreAssets();

	UFUNCTION(BlueprintCallable)
	void StreamCardArt(const FString& CardId, FOnAssetLoaded Callback);

	UFUNCTION(BlueprintCallable)
	void UnloadUnusedAssets();

private:
	TMap<FString, UTexture2D*> LoadedTextures;

	FString AssetBasePath = TEXT("Cards/");
	const int32 MaxCachedTextures = 50;
};