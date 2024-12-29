#include "Data/AudioLogData.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#pragma region Public
class FAssetRegistryModule;
class IAssetRegistry;

FAudioLogData::FAudioLogData()
{

}
FAudioLogData::FAudioLogData(UAudioComponent* AudioComponent)
{
	this->AudioComponent = AudioComponent;

	auto SoundCue = GetSoundCue();
	SoundCueName = SoundCue->GetName();
	SoundCueAssetPathName = FSoftObjectPath(SoundCue).GetAssetPathName();
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