#pragma once

#include "CoreMinimal.h"
#include "Data/AudioLogData.h"

typedef TWeakObjectPtr<UAudioLogData> UAudioLogDataPtr;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddLog, UAudioLogDataPtr);

class FPMCAudioManager
{
public:
	FOnAddLog OnAddLog;
	
	FPMCAudioManager();
	~FPMCAudioManager();
	
	static FPMCAudioManager* Get();
	
	TArray<UAudioLogDataPtr>& GetLogs();
	void AddLog(UAudioLogDataPtr LogPtr);
	void ClearLog();

	TArray<UAudioLogDataPtr> History;

private:
	static TUniquePtr<FPMCAudioManager> instance;

	TArray<UAudioLogDataPtr> Logs;
};
