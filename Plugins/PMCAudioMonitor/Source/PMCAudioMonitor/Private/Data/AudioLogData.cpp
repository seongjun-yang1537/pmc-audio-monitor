#include "Data/AudioLogData.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#pragma region Public
FAudioLogData::FAudioLogData()
{
	StartTime = FDateTime::Now();
}
FAudioLogData::FAudioLogData(UAudioComponent* AudioComponent)
{
	StartTime = FDateTime::Now();
	this->AudioComponent = AudioComponent;

	auto SoundCue = GetSoundCue();
	SoundCueName = SoundCue->GetName();
	SoundCueAssetPathName = FSoftObjectPath(SoundCue).GetAssetPathName();

	auto Sound = AudioComponent->Sound;
	SoundCueDuration = Sound->GetDuration();
}

float FAudioLogData::GetPitch() const
{
	if(!AudioComponent)
	{
		return -1.0f;
	}
	return AudioComponent->PitchMultiplier;
}

float FAudioLogData::GetVolume() const
{
	if(!AudioComponent)
	{
		return -1.0f;
	}
	return AudioComponent->VolumeMultiplier;
}

float FAudioLogData::GetPlayTime() const
{
	if(!AudioComponent)
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

USoundCue* FAudioLogData::GetSoundCue() const
{
	if(!AudioComponent)
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
FString FAudioLogData::GetSoundCueName() const
{
	return SoundCueName;
}

FName FAudioLogData::GetSoundCueAssetPathName() const
{
	return SoundCueAssetPathName;
}
#pragma endregion