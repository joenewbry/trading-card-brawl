#include "UI/TCBAudioManager.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

UTCBAudioManager::UTCBAudioManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTCBAudioManager::BeginPlay()
{
	Super::BeginPlay();
	UpdateAmbientVolume();
}

void UTCBAudioManager::PlaySound(const ETCBSoundEvent Event)
{
	if (USoundBase* const* SoundPtr = SoundMap.Find(Event))
	{
		if (USoundBase* Sound = *SoundPtr)
		{
			UGameplayStatics::PlaySound2D(this, Sound, MasterVolume * SFXVolume);
		}
	}
}

void UTCBAudioManager::SetMasterVolume(const float Volume)
{
	MasterVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
	UpdateAmbientVolume();
}

void UTCBAudioManager::SetMusicVolume(const float Volume)
{
	MusicVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
	UpdateAmbientVolume();
}

void UTCBAudioManager::SetSFXVolume(const float Volume)
{
	SFXVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void UTCBAudioManager::PlayAmbientMusic()
{
	if (AmbientAudioComponent && AmbientAudioComponent->IsPlaying())
	{
		return;
	}

	if (!AmbientMusic)
	{
		return;
	}

	AmbientAudioComponent = UGameplayStatics::SpawnSound2D(this, AmbientMusic, MasterVolume * MusicVolume, 1.0f, 0.0f, nullptr, true);
	if (AmbientAudioComponent)
	{
		AmbientAudioComponent->bIsUISound = true;
		AmbientAudioComponent->Play();
	}
}

void UTCBAudioManager::StopAmbientMusic()
{
	if (AmbientAudioComponent)
	{
		AmbientAudioComponent->Stop();
		AmbientAudioComponent = nullptr;
	}
}

void UTCBAudioManager::UpdateAmbientVolume() const
{
	if (AmbientAudioComponent)
	{
		AmbientAudioComponent->SetVolumeMultiplier(MasterVolume * MusicVolume);
	}
}
