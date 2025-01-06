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

TArray<FAudioLogDataPtr>& FPMCAudioManager::GetLogs()
{
	return Logs;
}

void FPMCAudioManager::AddLog(FAudioLogData Log)
{
	FAudioLogDataPtr LogPtr = MakeShared<FAudioLogData>(Log);
	Logs.Add(LogPtr);
	OnAddLog.Broadcast(LogPtr);
}

void FPMCAudioManager::ClearLog()
{
	Logs.Reset();
}
