#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TCBAudioManager.generated.h"

class UAudioComponent;
class USoundBase;

UENUM(BlueprintType)
enum class ETCBSoundEvent : uint8
{
	CardPlayed UMETA(DisplayName = "Card Played"),
	CreatureAttack UMETA(DisplayName = "Creature Attack"),
	PlayerVictory UMETA(DisplayName = "Player Victory"),
	PlayerDefeat UMETA(DisplayName = "Player Defeat"),
	ManaRefill UMETA(DisplayName = "Mana Refill"),
	TurnStart UMETA(DisplayName = "Turn Start"),
	CardDrawn UMETA(DisplayName = "Card Drawn")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRADINGCARDBRAWL_API UTCBAudioManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UTCBAudioManager();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySound(ETCBSoundEvent Event);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetMasterVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetMusicVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetSFXVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayAmbientMusic();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopAmbientMusic();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TMap<ETCBSoundEvent, USoundBase*> SoundMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* AmbientMusic = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float MasterVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float MusicVolume = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float SFXVolume = 1.0f;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Transient)
	UAudioComponent* AmbientAudioComponent = nullptr;

	void UpdateAmbientVolume() const;
};
