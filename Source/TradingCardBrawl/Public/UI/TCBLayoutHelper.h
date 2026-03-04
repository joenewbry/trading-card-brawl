#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

struct FTCBLayoutHelper
{
	static FVector2D GetCardSize()
	{
		const float ScreenWidth = GetScreenWidth();
		return (ScreenWidth < 600.0f) ? FVector2D(120.0f, 168.0f) : FVector2D(160.0f, 224.0f);
	}

	static int32 GetMaxHandDisplayCards()
	{
		const float ScreenWidth = GetScreenWidth();
		return (ScreenWidth < 600.0f) ? 5 : 10;
	}

private:
	static float GetScreenWidth()
	{
		if (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport)
		{
			return static_cast<float>(GEngine->GameViewport->Viewport->GetSizeXY().X);
		}

		return 1920.0f;
	}
};
