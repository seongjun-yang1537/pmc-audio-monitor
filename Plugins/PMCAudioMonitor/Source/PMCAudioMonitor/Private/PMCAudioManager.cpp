#include "PMCAudioManager.h"

#define CLASS FPMCAudioManager

TUniquePtr<CLASS> CLASS::instance = nullptr;

CLASS::CLASS()
{
	
}

CLASS* CLASS::Get()
{
	if(!instance.IsValid())
	{
		instance = MakeUnique<CLASS>();
	}
	return instance.Get();
}

TArray<FAudioLogDataPtr>& CLASS::GetLogs()
{
	return Logs;
}

void CLASS::AddLog(FAudioLogData Log)
{
	FAudioLogDataPtr LogPtr = MakeShared<FAudioLogData>(Log);
	Logs.Add(LogPtr);
	OnAddLog.Broadcast(LogPtr);
}