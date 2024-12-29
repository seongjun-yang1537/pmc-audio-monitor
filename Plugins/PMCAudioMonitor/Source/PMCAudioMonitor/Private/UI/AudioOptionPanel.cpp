#include "UI/AudioOptionPanel.h"

#include "PMCAudioManager.h"

void SAudioOptionPanel::Construct(const FArguments& Args)
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
				.OnClicked(this, &SAudioOptionPanel::OnAddEmptyLog)
			]
			+ SHorizontalBox::Slot()
            .AutoWidth()
            [
            	SNew(SButton)
            	.Text(FText::FromString("Clear Logs"))
            	.OnClicked(this, &SAudioOptionPanel::OnClearLogs)
            ]
		]
	];
}

FReply SAudioOptionPanel::OnAddEmptyLog()
{
	return FReply::Handled();
}

FReply SAudioOptionPanel::OnClearLogs()
{
	FPMCAudioManager::Get()->GetLogs().Reset();
	return FReply::Handled();
}