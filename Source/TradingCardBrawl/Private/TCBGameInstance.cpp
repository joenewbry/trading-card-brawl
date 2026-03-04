#include "TCBGameInstance.h"

#include "Save/TCBSaveGame.h"
#include "Save/TCBSaveManager.h"

void UTCBGameInstance::Init()
{
	Super::Init();

	if (!SaveManager)
	{
		SaveManager = NewObject<UTCBSaveManager>(this);
	}

	LoadPlayerData();
}

void UTCBGameInstance::Shutdown()
{
	SavePlayerData();
	Super::Shutdown();
}

void UTCBGameInstance::SavePlayerData()
{
	if (!SaveManager)
	{
		return;
	}

	UTCBSaveGame* SaveData = NewObject<UTCBSaveGame>(this);
	if (!SaveData)
	{
		return;
	}

	SaveData->PlayerId = LocalPlayerId;
	SaveData->OwnedCardIds = OwnedCardIds;
	SaveData->DeckCardIds = CurrentDeckIds;
	if (SaveData->DeckCardIds.Num() > 40)
	{
		SaveData->DeckCardIds.SetNum(40);
	}
	SaveData->TotalWins = TotalWins;
	SaveData->TotalLosses = TotalLosses;
	SaveData->TotalMatches = TotalWins + TotalLosses;
	SaveData->SelectedHeroClass = SelectedHeroClass;
	SaveData->BattleTokens = BattleTokens;
	SaveData->bTutorialCompleted = bTutorialCompleted;

	SaveManager->SaveGame(SaveData);

	if (!AuthToken.IsEmpty())
	{
		SaveManager->SyncToCloud(AuthToken);
	}
}

void UTCBGameInstance::LoadPlayerData()
{
	if (!SaveManager)
	{
		return;
	}

	if (UTCBSaveGame* SaveData = SaveManager->LoadGame())
	{
		LocalPlayerId = SaveData->PlayerId;
		OwnedCardIds = SaveData->OwnedCardIds;
		CurrentDeckIds = SaveData->DeckCardIds;
		if (CurrentDeckIds.Num() > 40)
		{
			CurrentDeckIds.SetNum(40);
		}
		TotalWins = SaveData->TotalWins;
		TotalLosses = SaveData->TotalLosses;
		SelectedHeroClass = SaveData->SelectedHeroClass;
		BattleTokens = SaveData->BattleTokens;
		bTutorialCompleted = SaveData->bTutorialCompleted;
	}
}

void UTCBGameInstance::AddCardToCollection(FString CardId)
{
	if (CardId.IsEmpty() || HasCard(CardId))
	{
		return;
	}

	OwnedCardIds.Add(MoveTemp(CardId));
}

bool UTCBGameInstance::HasCard(FString CardId) const
{
	return OwnedCardIds.Contains(CardId);
}
