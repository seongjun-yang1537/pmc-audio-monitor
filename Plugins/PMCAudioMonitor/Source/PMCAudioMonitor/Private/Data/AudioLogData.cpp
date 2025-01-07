#include "Data/AudioLogData.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#pragma region Public
void UAudioLogData::Init(UAudioComponent* Audio)
{
	this->StartTime = FDateTime::Now();
	this->AudioComponent = Audio;

	InitHandler();
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