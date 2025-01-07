#include "PMCAudioManager.h"

TUniquePtr<FPMCAudioManager> FPMCAudioManager::instance = nullptr;

FPMCAudioManager::FPMCAudioManager()
{
}

FPMCAudioManager::~FPMCAudioManager()
{
	OnAddLog.Clear();
	UE_LOG(LogTemp, Log, TEXT("[My Debug]"));
}

FPMCAudioManager* FPMCAudioManager::Get()
{
	if(!instance.IsValid())
	{
		instance = MakeUnique<FPMCAudioManager>();
	}
	return instance.Get();
}

TArray<UAudioLogDataPtr>& FPMCAudioManager::GetLogs()
{
	return Logs;
}

void FPMCAudioManager::AddLog(UAudioLogDataPtr LogPtr)
{
	Logs.Add(LogPtr);
	OnAddLog.Broadcast(LogPtr);
}

void FPMCAudioManager::ClearLog()
{
	Logs.Reset();
}
