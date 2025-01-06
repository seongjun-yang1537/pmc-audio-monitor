#pragma once

#include "CoreMinimal.h"
#include "Data/AudioLogData.h"

typedef TSharedPtr<FAudioLogData> FAudioLogDataPtr;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddLog, FAudioLogDataPtr);

class FPMCAudioManager
{
public:
	FOnAddLog OnAddLog;
	
	FPMCAudioManager();
	~FPMCAudioManager();
	
	static FPMCAudioManager* Get();
	
	TArray<FAudioLogDataPtr>& GetLogs();
	void AddLog(FAudioLogData Log);
	void ClearLog();

	TArray<FAudioLogDataPtr> History;

private:
	static TUniquePtr<FPMCAudioManager> instance;

	TArray<FAudioLogDataPtr> Logs;
};
