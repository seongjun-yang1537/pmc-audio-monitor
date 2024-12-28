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
	auto Manager = FPMCAudioManager::Get();
	int32 Len = Manager->GetLogs().Num();
	
	FAudioLogData EmptyLog = FAudioLogData();
	EmptyLog.Id = Len+1;
	EmptyLog.StartTime = FDateTime::Now();
	EmptyLog.Volume = FMath::FRandRange(0.0f, 1.0f);
	EmptyLog.Pitch = FMath::FRandRange(0.0f, 1.0f);
	EmptyLog.PlayTime = FMath::FRandRange(0.0f, 1.0f);
	EmptyLog.Position = FVector3d(
		FMath::FRandRange(0.0f, 100.0f),
		FMath::FRandRange(0.0f, 100.0f),
		FMath::FRandRange(0.0f, 100.0f)
	);
	EmptyLog.Context = TEXT("Context");
	EmptyLog.AudioSource = TEXT("Audio Source");
	EmptyLog.bPrevent = Len%2 == 0;
	
	Manager->AddLog(EmptyLog);
	return FReply::Handled();
}
