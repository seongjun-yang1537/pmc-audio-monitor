#include "UI/AudioLogElement.h"

#define CLASS SAudioLogElement

void CLASS::Construct(const FArguments& Args)
{
	auto Log = Args._Log;
	
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
				.Text(FText::FromString(Log.Get().Msg))
		]
	];
}
