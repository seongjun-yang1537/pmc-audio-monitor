#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Data/AudioLogData.h"

typedef TWeakObjectPtr<UAudioLogData> UAudioLogDataPtr;

class SAudioLogElement : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAudioLogElement)
		: _Log()
		{}
		SLATE_ATTRIBUTE( UAudioLogDataPtr, Log )
	SLATE_END_ARGS()
	
	void Construct(const FArguments& Args);

private:
	TSharedPtr<SWidget> AudioSourceWidget(UAudioLogDataPtr LogData);
	TSharedPtr<SWidget> PlayTimeWidget(UAudioLogDataPtr LogData);
	
	void HighlightSoundCueInContentBrowser(FName ContentBrowserPath);
};
