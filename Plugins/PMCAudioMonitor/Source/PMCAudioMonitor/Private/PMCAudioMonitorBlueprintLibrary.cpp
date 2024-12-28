// Fill out your copyright notice in the Description page of Project Settings.


#include "PMCAudioMonitorBlueprintLibrary.h"

#include "PMCAudioManager.h"
#include "Data/AudioLogData.h"

void UPMCAudioMonitorBlueprintLibrary::AddSoundLog(UAudioComponent* AudioComponent)
{
	auto Manager = FPMCAudioManager::Get();
	int32 Len = Manager->GetLogs().Num();
	
	FAudioLogData EmptyLog = FAudioLogData();
	EmptyLog.Id = Len+1;
	EmptyLog.StartTime = FDateTime::Now();
	EmptyLog.Volume = FMath::FRandRange(0.0f, 1.0f);
	EmptyLog.Pitch = FMath::FRandRange(0.0f, 1.0f);
	EmptyLog.PlayTime = FMath::FRandRange(0.0f, 1.0f);
	EmptyLog.Position = FVector3d(
		FMath::FRandRange(0.0f, 100.0f),
		FMath::FRandRange(0.0f, 100.0f),
		FMath::FRandRange(0.0f, 100.0f)
	);
	EmptyLog.Context = TEXT("Context");
	EmptyLog.AudioSource = TEXT("Audio Source");
	EmptyLog.bPrevent = Len%2 == 0;
	
	Manager->AddLog(EmptyLog);
}