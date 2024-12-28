#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SAudioOptionPanel : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SAudioOptionPanel){}
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& Args);

private:
	FReply OnAddEmptyLog();
	FReply OnClearLogs();
};
