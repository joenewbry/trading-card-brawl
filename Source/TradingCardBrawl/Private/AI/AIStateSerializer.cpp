#include "AI/AIStateSerializer.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace
{
	TSharedPtr<FJsonObject> CardToJson(const FCardData& Card)
	{
		TSharedPtr<FJsonObject> CardObject = MakeShared<FJsonObject>();
		CardObject->SetStringField(TEXT("card_id"), Card.CardId);
		CardObject->SetStringField(TEXT("name"), Card.Name);

		if (const UEnum* ManaEnum = StaticEnum<EManaType>())
		{
			CardObject->SetStringField(TEXT("mana_type"), ManaEnum->GetNameStringByValue(static_cast<int64>(Card.ManaType)));
		}
		else
		{
			CardObject->SetStringField(TEXT("mana_type"), TEXT("Unknown"));
		}

		CardObject->SetNumberField(TEXT("cost"), Card.Cost);
		CardObject->SetNumberField(TEXT("attack"), Card.Attack);
		CardObject->SetNumberField(TEXT("health"), Card.Health);

		TArray<TSharedPtr<FJsonValue>> Abilities;
		Abilities.Reserve(Card.Abilities.Num());
		for (const FString& Ability : Card.Abilities)
		{
			Abilities.Add(MakeShared<FJsonValueString>(Ability));
		}
		CardObject->SetArrayField(TEXT("abilities"), Abilities);

		return CardObject;
	}

	void AddCardsToArray(const TArray<FCardData>& Cards, TArray<TSharedPtr<FJsonValue>>& OutArray)
	{
		OutArray.Reserve(Cards.Num());
		for (const FCardData& Card : Cards)
		{
			OutArray.Add(MakeShared<FJsonValueObject>(CardToJson(Card)));
		}
	}

	FString ManaTypeToString(const EManaType ManaType)
	{
		if (const UEnum* ManaEnum = StaticEnum<EManaType>())
		{
			return ManaEnum->GetNameStringByValue(static_cast<int64>(ManaType));
		}

		return TEXT("Unknown");
	}
}

FString UAIStateSerializer::SerializeGameState(const FGameState& State)
{
	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetNumberField(TEXT("player_hp"), State.PlayerHP);
	Root->SetNumberField(TEXT("opponent_hp"), State.OpponentHP);
	Root->SetNumberField(TEXT("player_deck_size"), State.PlayerDeckSize);
	Root->SetNumberField(TEXT("opponent_deck_size"), State.OpponentDeckSize);
	Root->SetNumberField(TEXT("turn_number"), State.TurnNumber);
	Root->SetStringField(TEXT("active_mana_type"), ManaTypeToString(State.ActiveManaType));

	TArray<TSharedPtr<FJsonValue>> PlayerHand;
	AddCardsToArray(State.PlayerHand, PlayerHand);
	Root->SetArrayField(TEXT("player_hand"), PlayerHand);

	TArray<TSharedPtr<FJsonValue>> PlayerBoard;
	AddCardsToArray(State.PlayerBoard, PlayerBoard);
	Root->SetArrayField(TEXT("player_board"), PlayerBoard);

	TArray<TSharedPtr<FJsonValue>> OpponentBoard;
	AddCardsToArray(State.OpponentBoard, OpponentBoard);
	Root->SetArrayField(TEXT("opponent_board"), OpponentBoard);

	TSharedPtr<FJsonObject> ManaObject = MakeShared<FJsonObject>();
	for (const TPair<EManaType, int32>& Entry : State.PlayerMana)
	{
		ManaObject->SetNumberField(ManaTypeToString(Entry.Key), Entry.Value);
	}
	Root->SetObjectField(TEXT("player_mana"), ManaObject);

	FString Output;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Output);
	FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
	return Output;
}
