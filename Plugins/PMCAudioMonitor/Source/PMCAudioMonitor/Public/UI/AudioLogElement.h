#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Data/AudioLogData.h"

class SAudioLogElement : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAudioLogElement)
		: _Log()
		{}
		SLATE_ATTRIBUTE( FAudioLogData, Log )
	SLATE_END_ARGS()
	
	void Construct(const FArguments& Args);

private:
	TSharedPtr<SWidget> AudioSourceWidget(FString AudioSource);
};
