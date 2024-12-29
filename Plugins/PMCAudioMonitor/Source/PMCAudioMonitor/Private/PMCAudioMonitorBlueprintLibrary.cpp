#include "PMCAudioMonitorBlueprintLibrary.h"

#include "PMCAudioManager.h"
#include "Components/AudioComponent.h"
#include "Data/AudioLogData.h"
#include "Sound/SoundCue.h"

void UPMCAudioMonitorBlueprintLibrary::AddSoundLog(UAudioComponent* AudioComponent)
{
	if(!AudioComponent)
	{
		return;
	}
	
	auto Manager = FPMCAudioManager::Get();
	int32 Len = Manager->GetLogs().Num();
	
	FAudioLogData Log = FAudioLogData(AudioComponent);
	Log.Id = Len+1;
	Log.StartTime = FDateTime::Now();
	Log.Position = AudioComponent->GetComponentLocation();
	Log.Context = TEXT("Context");
	Log.AudioSource = TEXT("Audio Source");
	Log.bPrevent = Len%2 == 0;

	USoundCue* SoundCue = Log.GetSoundCue();
	UE_LOG(LogTemp, Log, TEXT("%s"), *SoundCue->GetName());
	
	Manager->AddLog(Log);
}
