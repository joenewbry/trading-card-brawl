#include "UI/TutorialManager.h"

#include "EngineUtils.h"

UTutorialManager::UTutorialManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTutorialManager::BeginPlay()
{
	Super::BeginPlay();

	Steps.Reset();
	Steps.Reserve(5);

	FTutorialStepData DrawCardsStep;
	DrawCardsStep.Step = ETutorialStep::DrawCards;
	DrawCardsStep.InstructionText = TEXT("Draw your opening hand of 5 cards.");
	DrawCardsStep.HighlightTarget = TEXT("DrawButton");
	DrawCardsStep.RewardCard = MakeRewardCard(TEXT("warrior-iron-vow"), TEXT("Iron Vow"), TEXT("common"));
	Steps.Add(DrawCardsStep);

	FTutorialStepData PlayCardStep;
	PlayCardStep.Step = ETutorialStep::PlayCard;
	PlayCardStep.InstructionText = TEXT("Play a card by spending mana.");
	PlayCardStep.HighlightTarget = TEXT("HandContainer");
	PlayCardStep.RewardCard = MakeRewardCard(TEXT("ranger-swift-shot"), TEXT("Swift Shot"), TEXT("common"));
	Steps.Add(PlayCardStep);

	FTutorialStepData AttackStep;
	AttackStep.Step = ETutorialStep::AttackWithMinion;
	AttackStep.InstructionText = TEXT("Attack the opponent with your minion.");
	AttackStep.HighlightTarget = TEXT("PlayerBoardZone");
	AttackStep.RewardCard = MakeRewardCard(TEXT("druid-mosshide"), TEXT("Mosshide"), TEXT("common"));
	Steps.Add(AttackStep);

	FTutorialStepData EndTurnStep;
	EndTurnStep.Step = ETutorialStep::EndTurn;
	EndTurnStep.InstructionText = TEXT("End your turn to let your opponent play.");
	EndTurnStep.HighlightTarget = TEXT("EndTurnButton");
	EndTurnStep.RewardCard = MakeRewardCard(TEXT("necromancer-grave-whisper"), TEXT("Grave Whisper"), TEXT("common"));
	Steps.Add(EndTurnStep);

	FTutorialStepData WinMatchStep;
	WinMatchStep.Step = ETutorialStep::WinMatch;
	WinMatchStep.InstructionText = TEXT("Reduce your opponent to 0 HP to win!");
	WinMatchStep.HighlightTarget = TEXT("OpponentHealthText");
	WinMatchStep.RewardCard = MakeRewardCard(TEXT("rogue-shadow-step"), TEXT("Shadow Step"), TEXT("uncommon"));
	Steps.Add(WinMatchStep);
}

void UTutorialManager::StartTutorial()
{
	bTutorialActive = !Steps.IsEmpty();
	CurrentStepIndex = bTutorialActive ? 0 : INDEX_NONE;
	CurrentStep = bTutorialActive ? Steps[0].Step : ETutorialStep::Complete;
}

void UTutorialManager::AdvanceStep()
{
	if (!bTutorialActive)
	{
		return;
	}

	++CurrentStepIndex;
	if (!Steps.IsValidIndex(CurrentStepIndex))
	{
		CurrentStep = ETutorialStep::Complete;
		bTutorialActive = false;
		CurrentStepIndex = INDEX_NONE;
		OnTutorialComplete.Broadcast();
		return;
	}

	CurrentStep = Steps[CurrentStepIndex].Step;
}

void UTutorialManager::CompleteStep(const ETutorialStep Step)
{
	if (!bTutorialActive || CurrentStep != Step)
	{
		return;
	}

	if (FTutorialStepData* StepData = FindCurrentStepData())
	{
		GrantReward(StepData->RewardCard);
		OnStepComplete.Broadcast(StepData->RewardCard);
	}

	AdvanceStep();
}

ETutorialStep UTutorialManager::GetCurrentStep() const
{
	return CurrentStep;
}

bool UTutorialManager::IsTutorialActive() const
{
	return bTutorialActive;
}

FTutorialStepData* UTutorialManager::FindCurrentStepData()
{
	if (!Steps.IsValidIndex(CurrentStepIndex))
	{
		return nullptr;
	}

	return &Steps[CurrentStepIndex];
}

void UTutorialManager::GrantReward(const FCardData& RewardCard)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		if (UDeckManager* DeckManager = It->FindComponentByClass<UDeckManager>())
		{
			if (DeckManager->Hand.Num() < 10)
			{
				DeckManager->Hand.Add(RewardCard);
			}
			else
			{
				DeckManager->Deck.Add(RewardCard);
			}
			return;
		}
	}
}

FCardData UTutorialManager::MakeRewardCard(const FString& CardId, const FString& CardName, const FString& Rarity)
{
	FCardData RewardCard;
	RewardCard.CardId = CardId;
	RewardCard.Name = CardName;
	RewardCard.Cost = 1;
	RewardCard.Attack = 1;
	RewardCard.Health = 1;
	RewardCard.Abilities.Add(FString::Printf(TEXT("rarity:%s"), *Rarity));
	return RewardCard;
}
