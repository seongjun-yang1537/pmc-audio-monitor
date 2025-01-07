#include "Data/AudioLogData.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#pragma region Public
UAudioLogData* UAudioLogData::Init(UAudioComponent* Audio)
{
	this->StartTime = FDateTime::Now();
	this->AudioComponent = Audio;

	InitHandler();

	return this;
}

void UAudioLogData::InitHandler()
{
	AudioComponent->OnAudioPlaybackPercentNative.AddLambda([&](
	const UAudioComponent* Audio,
	const USoundWave* Wave,
	const float Percent)
	{
		PlayPercent = Percent;
	});

	AudioComponent->OnAudioPlayStateChangedNative.AddLambda([&](
		const UAudioComponent* Audio,
		EAudioComponentPlayState State)
	{
		switch (State)
		{
			case EAudioComponentPlayState::Playing:
			{
				OnPlay.Broadcast();
			}break;
			case EAudioComponentPlayState::Stopped:
			{
				OnPlayEnd.Broadcast();
			}break;
		}
	});
}

float UAudioLogData::GetPitch() const
{
	if(!AudioComponent.IsValid())
	{
		return -1.0f;
	}
	return AudioComponent->PitchMultiplier;
}

float UAudioLogData::GetVolume() const
{
	if(!AudioComponent.IsValid())
	{
		return -1.0f;
	}
	return AudioComponent->VolumeMultiplier;
}

USoundCue* UAudioLogData::GetSoundCue() const
{
	if(!AudioComponent.IsValid())
	{
		return nullptr;
	}
	return Cast<USoundCue>(AudioComponent->GetSound());
}
#pragma endregion

#pragma region Private
FString UAudioLogData::GetSoundCueName() const
{
	auto SoundCue = GetSoundCue();
	if (!SoundCue)
	{
		return TEXT("Null");
	}
	return SoundCue->GetName();
}

FName UAudioLogData::GetSoundCueAssetPathName() const
{
	auto SoundCue = GetSoundCue();
	if (!SoundCue)
	{
		return TEXT("");
	}
	return FSoftObjectPath(SoundCue).GetAssetPathName();
}

float UAudioLogData::GetDuration() const
{
	if (!AudioComponent.IsValid() || !AudioComponent->Sound)
	{
		return -1.0f;
	}
	return AudioComponent->Sound->GetDuration();
}

#pragma endregion