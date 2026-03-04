#include "Cards/CardLoader.h"

#include "Cards/CardSchema.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY_STATIC(LogCardLoader, Log, All);

namespace
{
	FString ResolveIndexPath(const FString& IndexPath)
	{
		if (IndexPath.IsEmpty())
		{
			return FString();
		}

		if (FPaths::FileExists(IndexPath))
		{
			return IndexPath;
		}

		const FString FromProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir(), IndexPath);
		if (FPaths::FileExists(FromProjectDir))
		{
			return FromProjectDir;
		}

		const FString FromContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir(), IndexPath);
		if (FPaths::FileExists(FromContentDir))
		{
			return FromContentDir;
		}

		return FString();
	}

	int32 JsonNumberToInt(const TSharedPtr<FJsonObject>& Object, const TCHAR* FieldName, int32 DefaultValue = 0)
	{
		double NumberValue = 0.0;
		if (Object->TryGetNumberField(FieldName, NumberValue))
		{
			return static_cast<int32>(NumberValue);
		}

		return DefaultValue;
	}

	FCardData BuildCardData(const TSharedPtr<FJsonObject>& CardObject)
	{
		FCardData Card;

		CardObject->TryGetStringField(TEXT("id"), Card.Id);
		CardObject->TryGetStringField(TEXT("name"), Card.Name);
		CardObject->TryGetStringField(TEXT("type"), Card.Type);
		CardObject->TryGetStringField(TEXT("rarity"), Card.Rarity);
		CardObject->TryGetStringField(TEXT("mana_type"), Card.ManaType);
		Card.Cost = JsonNumberToInt(CardObject, TEXT("cost"));
		Card.Attack = JsonNumberToInt(CardObject, TEXT("attack"));
		Card.Health = JsonNumberToInt(CardObject, TEXT("health"));
		CardObject->TryGetStringField(TEXT("description"), Card.Description);
		CardObject->TryGetStringField(TEXT("flavor_text"), Card.FlavorText);
		CardObject->TryGetStringField(TEXT("class"), Card.CardClass);
		CardObject->TryGetStringField(TEXT("art_asset"), Card.ArtAsset);
		CardObject->TryGetStringField(TEXT("version"), Card.Version);

		const TArray<TSharedPtr<FJsonValue>>* AbilityValues = nullptr;
		if (CardObject->TryGetArrayField(TEXT("abilities"), AbilityValues))
		{
			for (const TSharedPtr<FJsonValue>& AbilityValue : *AbilityValues)
			{
				FString Ability;
				if (AbilityValue.IsValid() && AbilityValue->TryGetString(Ability))
				{
					Card.Abilities.Add(Ability);
				}
			}
		}

		return Card;
	}
}

TArray<FCardData> UCardLoader::LoadAllCards(const FString& IndexPath)
{
	TArray<FCardData> Cards;

	const FString ResolvedIndexPath = ResolveIndexPath(IndexPath);
	if (ResolvedIndexPath.IsEmpty())
	{
		UE_LOG(LogCardLoader, Error, TEXT("Card index file not found: %s"), *IndexPath);
		return Cards;
	}

	FString JsonText;
	if (!FFileHelper::LoadFileToString(JsonText, *ResolvedIndexPath))
	{
		UE_LOG(LogCardLoader, Error, TEXT("Failed to read card index file: %s"), *ResolvedIndexPath);
		return Cards;
	}

	TArray<TSharedPtr<FJsonValue>> RootArray;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
	if (!FJsonSerializer::Deserialize(Reader, RootArray))
	{
		UE_LOG(LogCardLoader, Error, TEXT("Failed to parse card index JSON: %s"), *ResolvedIndexPath);
		return Cards;
	}

	for (const TSharedPtr<FJsonValue>& Value : RootArray)
	{
		if (!Value.IsValid() || Value->Type != EJson::Object)
		{
			UE_LOG(LogCardLoader, Warning, TEXT("Skipping non-object card entry in index: %s"), *ResolvedIndexPath);
			continue;
		}

		const TSharedPtr<FJsonObject> CardObject = Value->AsObject();
		FString ValidationError;
		if (!UCardSchemaValidator::ValidateCard(CardObject, ValidationError))
		{
			FString CardId;
			CardObject->TryGetStringField(TEXT("id"), CardId);
			UE_LOG(LogCardLoader, Warning, TEXT("Skipping invalid card '%s': %s"), *CardId, *ValidationError);
			continue;
		}

		Cards.Add(BuildCardData(CardObject));
	}

	return Cards;
}

bool UCardLoader::LoadCardById(const FString& CardId, const FString& IndexPath, FCardData& OutCard)
{
	if (CardId.IsEmpty())
	{
		UE_LOG(LogCardLoader, Warning, TEXT("LoadCardById called with empty CardId"));
		return false;
	}

	const TArray<FCardData> Cards = LoadAllCards(IndexPath);
	for (const FCardData& Card : Cards)
	{
		if (Card.Id.Equals(CardId, ESearchCase::IgnoreCase))
		{
			OutCard = Card;
			return true;
		}
	}

	return false;
}
