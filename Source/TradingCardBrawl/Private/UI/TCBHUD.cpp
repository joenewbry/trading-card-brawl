#include "UI/TCBHUD.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "UI/CardWidget.h"
#include "UI/TCBAudioManager.h"
#include "UI/TutorialManager.h"

#include "EngineUtils.h"

void UTCBHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (EndTurnButton)
	{
		EndTurnButton->OnClicked.RemoveDynamic(this, &UTCBHUD::OnEndTurnClicked);
		EndTurnButton->OnClicked.AddDynamic(this, &UTCBHUD::OnEndTurnClicked);
	}

	if (TutorialPromptText)
	{
		TutorialPromptText->SetVisibility(ESlateVisibility::Collapsed);
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		if (!TutorialManager)
		{
			TutorialManager = It->FindComponentByClass<UTutorialManager>();
		}

		if (!AudioManager)
		{
			AudioManager = It->FindComponentByClass<UTCBAudioManager>();
		}

		if (TutorialManager && AudioManager)
		{
			break;
		}
	}
}

void UTCBHUD::UpdateHealth(int32 PlayerHP, int32 OpponentHP)
{
	if (PlayerHealthText)
	{
		PlayerHealthText->SetText(FText::AsNumber(PlayerHP));
	}

	if (OpponentHealthText)
	{
		OpponentHealthText->SetText(FText::AsNumber(OpponentHP));
	}
}

void UTCBHUD::UpdateTurnCounter(int32 TurnNumber)
{
	if (TurnCounterText)
	{
		TurnCounterText->SetText(FText::Format(NSLOCTEXT("TCBHUD", "TurnCounter", "Turn {0}"), TurnNumber));
	}
}

void UTCBHUD::AddCardToHand(const FCardData& Card)
{
	if (!HandContainer)
	{
		return;
	}

	UCardWidget* CardWidget = CreateWidget<UCardWidget>(this, UCardWidget::StaticClass());
	if (!CardWidget)
	{
		return;
	}

	CardWidget->PopulateFromCardData(Card);
	HandContainer->AddChild(CardWidget);
}

void UTCBHUD::ClearHand()
{
	if (HandContainer)
	{
		HandContainer->ClearChildren();
	}
}

void UTCBHUD::ShowTutorialPrompt(const FString& Text)
{
	if (!TutorialPromptText)
	{
		return;
	}

	TutorialPromptText->SetText(FText::FromString(Text));
	TutorialPromptText->SetVisibility(ESlateVisibility::Visible);
}

void UTCBHUD::HideTutorialPrompt()
{
	if (TutorialPromptText)
	{
		TutorialPromptText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UTCBHUD::OnCardPlayedSound()
{
	if (AudioManager)
	{
		AudioManager->PlaySound(ETCBSoundEvent::CardPlayed);
	}
}

void UTCBHUD::OnAttackSound()
{
	if (AudioManager)
	{
		AudioManager->PlaySound(ETCBSoundEvent::CreatureAttack);
	}
}

void UTCBHUD::OnEndTurnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UTCBHUD::OnEndTurnClicked"));
}
