#include "Data/AudioLogData.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#pragma region Public
void UAudioLogData::Init(UAudioComponent* Audio)
{
	StartTime = FDateTime::Now();
	this->AudioComponent = Audio;

	// auto SoundCue = GetSoundCue();
	// SoundCueName = SoundCue->GetName();
	// SoundCueAssetPathName = FSoftObjectPath(SoundCue).GetAssetPathName();
	//
	// auto Sound = AudioComponent->Sound;
	// SoundCueDuration = Sound->GetDuration();
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

float UAudioLogData::GetPlayTime() const
{
	if(!AudioComponent.IsValid())
	{
		return 1.0f;
	}
	if(!AudioComponent->IsPlaying())
	{
		return 0.0f;
	}
	auto Time = FDateTime::Now() - StartTime;
	return Time.GetTotalSeconds() / SoundCueDuration;
}

USoundCue* UAudioLogData::GetSoundCue() const
{
	if(!AudioComponent.IsValid())
	{
		return nullptr;
	}
	USoundBase* Sound = AudioComponent->GetSound();
	if(Sound && Sound->IsA<USoundCue>())
	{
		USoundCue* SoundCue = Cast<USoundCue>(Sound);
		if(SoundCue)
		{
			return SoundCue;
		}
	}
	return nullptr;
}
#pragma endregion

#pragma region Private
FString UAudioLogData::GetSoundCueName() const
{
	return SoundCueName;
}

FName UAudioLogData::GetSoundCueAssetPathName() const
{
	return SoundCueAssetPathName;
}
#pragma endregion