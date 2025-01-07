#include "PMCAudioMonitorBlueprintLibrary.h"

#include "PMCAudioManager.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

void UPMCAudioMonitorBlueprintLibrary::AddSoundLog(UAudioComponent* AudioComponent)
{
	if(!AudioComponent)
	{
		return;
	}
	
	auto Manager = FPMCAudioManager::Get();
	int32 Len = Manager->GetLogs().Num();

	UAudioLogData* Ptr = NewObject<UAudioLogData>();
	Ptr->Init(AudioComponent);
	
	UAudioLogDataPtr LogPtr = MakeWeakObjectPtr<UAudioLogData>(Ptr);
	LogPtr->Id = Len+1;
	LogPtr->Position = AudioComponent->GetComponentLocation();
	LogPtr->Context = TEXT("Context");
	LogPtr->AudioSource = TEXT("Audio Source");
	LogPtr->bPrevent = Len%2 == 0;
	
	Manager->AddLog(LogPtr);
}
