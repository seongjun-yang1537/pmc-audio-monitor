#include "UI/AudioLogElement.h"

#include "Widgets/Notifications/SProgressBar.h"

#define CLASS SAudioLogElement

void CLASS::Construct(const FArguments& Args)
{
	auto Log = Args._Log.Get();

	TArray<TSharedPtr<SWidget>> Widgets =
	{
		SNew(STextBlock)
			.Text(FText::FromString(FString::FromInt(Log.Id))),
		SNew(STextBlock)
			.Text(FText::FromString(Log.StartTime.ToString())),
		SNew(SProgressBar)
			.Percent(Log.Volume),
		SNew(STextBlock)
			.Text(FText::FromString(FString::Printf(
				TEXT("%.2f"),
				Log.Pitch))),
		SNew(STextBlock)
			.Text(FText::FromString(
				FString::Printf(
					TEXT("(%.2f, %.2f, %.2f)"),
					Log.Position.X,
					Log.Position.Y,
					Log.Position.Z)
			)),
		SNew(STextBlock)
			.Text(FText::FromString(Log.Context)),
		SNew(STextBlock)
			.Text(FText::FromString(Log.AudioEvent)),
		SNew(SCheckBox)
			.IsChecked(Log.bPrevent)
	};

	TArray<float> HeaderWidthRatios =
	{
		1.0f,
		6.0f,
		2.0f,
		2.0f,
		6.0f,
		10.0f,
		10.0f,
		2.0f,
	};

	check(Widgets.Num() == HeaderWidthRatios.Num());
	int32 Len = Widgets.Num();

	auto HorizontalBox = SNew(SHorizontalBox);
	for(int32 i = 0; i < Len; i++)
	{
		auto Widget = Widgets[i];
		HorizontalBox->AddSlot()
		[
			Widget.ToSharedRef()
		]
		.FillWidth(HeaderWidthRatios[i])
		.HAlign(HAlign_Center);
	}
	
	ChildSlot
	[
		HorizontalBox
	];
}
