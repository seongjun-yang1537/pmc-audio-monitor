#include "Data/AudioLogData.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

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