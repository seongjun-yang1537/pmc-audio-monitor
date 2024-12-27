#include "UI/AudioOptionPanel.h"

#include "PMCAudioManager.h"

#define CLASS SAudioOptionPanel

void CLASS::Construct(const FArguments& Args)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString("[Debug]"))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(FText::FromString("Add Empty Log"))
				.OnClicked(this, &CLASS::OnAddEmptyLog)
			]
		]
	];
}

FReply CLASS::OnAddEmptyLog()
{
	FAudioLogData EmptyLog = FAudioLogData(TEXT("Empty"));
	
	FPMCAudioManager::Get()->AddLog(EmptyLog);
	UE_LOG(LogTemp, Log, TEXT("%d"), FPMCAudioManager::Get()->GetLogs().Num());
	return FReply::Handled();
}
