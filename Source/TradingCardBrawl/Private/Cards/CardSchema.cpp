#include "Cards/CardSchema.h"

namespace
{
	bool GetRequiredStringField(const TSharedPtr<FJsonObject>& CardJson, const TCHAR* FieldName, FString& OutValue, FString& OutError)
	{
		if (!CardJson->TryGetStringField(FieldName, OutValue) || OutValue.TrimStartAndEnd().IsEmpty())
		{
			OutError = FString::Printf(TEXT("Missing or empty required string field '%s'"), FieldName);
			return false;
		}

		return true;
	}

	bool GetRequiredIntField(const TSharedPtr<FJsonObject>& CardJson, const TCHAR* FieldName, int32 Min, int32 Max, int32& OutValue, FString& OutError)
	{
		double NumberValue = 0.0;
		if (!CardJson->TryGetNumberField(FieldName, NumberValue))
		{
			OutError = FString::Printf(TEXT("Missing required numeric field '%s'"), FieldName);
			return false;
		}

		const int32 IntValue = static_cast<int32>(NumberValue);
		if (!FMath::IsNearlyEqual(NumberValue, static_cast<double>(IntValue)))
		{
			OutError = FString::Printf(TEXT("Field '%s' must be an integer"), FieldName);
			return false;
		}

		if (IntValue < Min || IntValue > Max)
		{
			OutError = FString::Printf(TEXT("Field '%s' must be between %d and %d"), FieldName, Min, Max);
			return false;
		}

		OutValue = IntValue;
		return true;
	}

	bool ValidateEnumField(const TCHAR* FieldName, const FString& Value, const TSet<FString>& AllowedValues, FString& OutError)
	{
		if (!AllowedValues.Contains(Value))
		{
			OutError = FString::Printf(TEXT("Invalid '%s': '%s'"), FieldName, *Value);
			return false;
		}

		return true;
	}
}

bool UCardSchemaValidator::ValidateCard(const TSharedPtr<FJsonObject>& CardJson, FString& OutError)
{
	OutError.Empty();

	if (!CardJson.IsValid())
	{
		OutError = TEXT("Card JSON object is null");
		return false;
	}

	static const TSet<FString> ValidTypes = {
		TEXT("creature"), TEXT("spell"), TEXT("artifact"), TEXT("enchantment")
	};
	static const TSet<FString> ValidRarities = {
		TEXT("common"), TEXT("uncommon"), TEXT("rare"), TEXT("mythic")
	};
	static const TSet<FString> ValidManaTypes = {
		TEXT("Shadow"), TEXT("Steel"), TEXT("Life"), TEXT("Wind"), TEXT("Earth")
	};
	static const TSet<FString> ValidClasses = {
		TEXT("warrior"), TEXT("ranger"), TEXT("necromancer"), TEXT("druid"), TEXT("rogue"), TEXT("engineer")
	};
	static const TSet<FString> ValidAbilities = {
		TEXT("charge"), TEXT("taunt"), TEXT("windfury"), TEXT("stealth"), TEXT("divine_shield"),
		TEXT("lifesteal"), TEXT("freeze"), TEXT("poison"), TEXT("battlecry"), TEXT("deathrattle"),
		TEXT("enrage"), TEXT("combo"), TEXT("overload")
	};

	FString Id;
	if (!GetRequiredStringField(CardJson, TEXT("id"), Id, OutError))
	{
		return false;
	}

	FString Name;
	if (!GetRequiredStringField(CardJson, TEXT("name"), Name, OutError))
	{
		return false;
	}

	FString Type;
	if (!GetRequiredStringField(CardJson, TEXT("type"), Type, OutError) || !ValidateEnumField(TEXT("type"), Type, ValidTypes, OutError))
	{
		return false;
	}

	FString Rarity;
	if (!GetRequiredStringField(CardJson, TEXT("rarity"), Rarity, OutError) || !ValidateEnumField(TEXT("rarity"), Rarity, ValidRarities, OutError))
	{
		return false;
	}

	FString ManaType;
	if (!GetRequiredStringField(CardJson, TEXT("mana_type"), ManaType, OutError) || !ValidateEnumField(TEXT("mana_type"), ManaType, ValidManaTypes, OutError))
	{
		return false;
	}

	int32 Cost = 0;
	if (!GetRequiredIntField(CardJson, TEXT("cost"), 0, 7, Cost, OutError))
	{
		return false;
	}

	FString CardClass;
	if (!GetRequiredStringField(CardJson, TEXT("class"), CardClass, OutError) || !ValidateEnumField(TEXT("class"), CardClass, ValidClasses, OutError))
	{
		return false;
	}

	if (Type == TEXT("creature"))
	{
		int32 Attack = 0;
		if (!GetRequiredIntField(CardJson, TEXT("attack"), 0, 100, Attack, OutError))
		{
			return false;
		}

		int32 Health = 0;
		if (!GetRequiredIntField(CardJson, TEXT("health"), 0, 100, Health, OutError))
		{
			return false;
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* AbilityValues = nullptr;
	if (CardJson->TryGetArrayField(TEXT("abilities"), AbilityValues))
	{
		for (const TSharedPtr<FJsonValue>& AbilityValue : *AbilityValues)
		{
			FString Ability;
			if (!AbilityValue.IsValid() || !AbilityValue->TryGetString(Ability))
			{
				OutError = TEXT("Field 'abilities' must be an array of strings");
				return false;
			}

			if (!ValidAbilities.Contains(Ability))
			{
				OutError = FString::Printf(TEXT("Invalid ability '%s'"), *Ability);
				return false;
			}
		}
	}

	return true;
}
