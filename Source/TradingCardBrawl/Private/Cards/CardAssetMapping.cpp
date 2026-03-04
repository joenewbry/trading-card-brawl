#include "Cards/CardAssetMapping.h"

#include "UI/CardWidget.h"

namespace
{
	FString NormalizeClassName(const FString& ClassName)
	{
		FString Normalized = ClassName;
		Normalized.TrimStartAndEndInline();
		Normalized = Normalized.ToLower();
		return Normalized;
	}

	FString ToBorderClassName(const FString& ClassName)
	{
		const FString Normalized = NormalizeClassName(ClassName);
		if (Normalized == TEXT("warrior"))
		{
			return TEXT("Warrior");
		}
		if (Normalized == TEXT("ranger"))
		{
			return TEXT("Ranger");
		}
		if (Normalized == TEXT("necromancer"))
		{
			return TEXT("Necromancer");
		}
		if (Normalized == TEXT("druid"))
		{
			return TEXT("Druid");
		}
		if (Normalized == TEXT("rogue"))
		{
			return TEXT("Rogue");
		}
		if (Normalized == TEXT("engineer"))
		{
			return TEXT("Engineer");
		}

		if (ClassName.IsEmpty())
		{
			return FString();
		}

		FString Fallback = ClassName;
		Fallback.TrimStartAndEndInline();
		if (!Fallback.IsEmpty())
		{
			Fallback[0] = FChar::ToUpper(Fallback[0]);
		}
		return Fallback;
	}

	void AddMapping(
		TMap<FString, FCardAssetData>& Map,
		const FString& CardId,
		const FString& ClassName,
		const FString& ClassFolder)
	{
		FCardAssetData Data;
		Data.CardId = CardId;
		Data.ClassFolder = ClassFolder;
		Data.PortraitAssetPath = FString::Printf(
			TEXT("/Game/EndlessModularTCGTradingCardCollection/Artwork/%s/%s"),
			*ClassFolder,
			*CardId);
		Data.BorderAssetPath = UCardAssetRegistry::GetBorderPathForClass(ClassName);
		Map.Add(CardId, Data);
	}
}

TMap<FString, FCardAssetData> UCardAssetRegistry::BuildDefaultMappings()
{
	TMap<FString, FCardAssetData> Mappings;
	Mappings.Reserve(30);

	AddMapping(Mappings, TEXT("warrior-ironveil-sentinel"), TEXT("warrior"), TEXT("Warriors"));
	AddMapping(Mappings, TEXT("warrior-shieldbreaker-maul"), TEXT("warrior"), TEXT("Warriors"));
	AddMapping(Mappings, TEXT("warrior-aegis-of-the-wall"), TEXT("warrior"), TEXT("Warriors"));
	AddMapping(Mappings, TEXT("warrior-retributive-chain"), TEXT("warrior"), TEXT("Warriors"));
	AddMapping(Mappings, TEXT("warrior-the-iron-oath"), TEXT("warrior"), TEXT("Warriors"));

	AddMapping(Mappings, TEXT("ranger-dustfoot-stalker"), TEXT("ranger"), TEXT("Hunter"));
	AddMapping(Mappings, TEXT("ranger-galewing-trap"), TEXT("ranger"), TEXT("Hunter"));
	AddMapping(Mappings, TEXT("ranger-skydancer-blade"), TEXT("ranger"), TEXT("Hunter"));
	AddMapping(Mappings, TEXT("ranger-arrowstorm-volley"), TEXT("ranger"), TEXT("Hunter"));
	AddMapping(Mappings, TEXT("ranger-whisperwind-the-unseen-path"), TEXT("ranger"), TEXT("Hunter"));

	AddMapping(Mappings, TEXT("necromancer-bone-revenant"), TEXT("necromancer"), TEXT("Warlock"));
	AddMapping(Mappings, TEXT("necromancer-soul-drain"), TEXT("necromancer"), TEXT("Warlock"));
	AddMapping(Mappings, TEXT("necromancer-carrion-wurm"), TEXT("necromancer"), TEXT("Warlock"));
	AddMapping(Mappings, TEXT("necromancer-grave-pact"), TEXT("necromancer"), TEXT("Warlock"));
	AddMapping(Mappings, TEXT("necromancer-lich-kings-ascension"), TEXT("necromancer"), TEXT("Warlock"));

	AddMapping(Mappings, TEXT("druid-sproutling"), TEXT("druid"), TEXT("Druid"));
	AddMapping(Mappings, TEXT("druid-healing-bloom"), TEXT("druid"), TEXT("Druid"));
	AddMapping(Mappings, TEXT("druid-ancient-treant"), TEXT("druid"), TEXT("Druid"));
	AddMapping(Mappings, TEXT("druid-rampant-growth"), TEXT("druid"), TEXT("Druid"));
	AddMapping(Mappings, TEXT("druid-world-trees-embrace"), TEXT("druid"), TEXT("Druid"));

	AddMapping(Mappings, TEXT("rogue-shadow-dagger"), TEXT("rogue"), TEXT("Assassin"));
	AddMapping(Mappings, TEXT("rogue-ghoststep"), TEXT("rogue"), TEXT("Assassin"));
	AddMapping(Mappings, TEXT("rogue-deceptive-draw"), TEXT("rogue"), TEXT("Assassin"));
	AddMapping(Mappings, TEXT("rogue-whispering-knife"), TEXT("rogue"), TEXT("Assassin"));
	AddMapping(Mappings, TEXT("rogue-mirage-gambit"), TEXT("rogue"), TEXT("Assassin"));

	AddMapping(Mappings, TEXT("engineer-gearcore-battery"), TEXT("engineer"), TEXT("Mech"));
	AddMapping(Mappings, TEXT("engineer-turret-bot"), TEXT("engineer"), TEXT("Mech"));
	AddMapping(Mappings, TEXT("engineer-repair-drone"), TEXT("engineer"), TEXT("Mech"));
	AddMapping(Mappings, TEXT("engineer-clockwork-colossus"), TEXT("engineer"), TEXT("Mech"));
	AddMapping(Mappings, TEXT("engineer-anvil-forge"), TEXT("engineer"), TEXT("Mech"));

	return Mappings;
}

FString UCardAssetRegistry::ResolvePortraitPath(const FString& CardId, const FString& ClassName)
{
	return UCardWidget::GetAssetPackPathForClass(ClassName) + CardId;
}

FString UCardAssetRegistry::GetBorderPathForClass(const FString& ClassName)
{
	const FString BorderClassName = ToBorderClassName(ClassName);
	if (BorderClassName.IsEmpty())
	{
		return FString();
	}

	return TEXT("/Game/EndlessModularTCGTradingCardCollection/CardBorders/Border_") + BorderClassName;
}
