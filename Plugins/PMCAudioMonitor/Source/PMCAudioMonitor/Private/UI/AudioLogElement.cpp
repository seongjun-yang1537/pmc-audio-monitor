#include "UI/AudioLogElement.h"

#include "FileHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Sound/SoundCue.h"
#include "UI/AudioLogList.h"
#include "Widgets/Notifications/SProgressBar.h"

#define CREATE_ATTRIBUTE(type, lambda) TAttribute<type>::Create(\
	TAttribute<type>::FGetter::CreateLambda(lambda))

#pragma region Public

#pragma region Static
FAudioLogDataComparer UAudioLogData::OnCompare(FString Element)
{
	auto CompareVector3d = [](const FVector3d& A, const FVector3d& B) -> bool
	{
		if(A.X != B.X)
		{
			return A.X < B.X;
		}
		if(A.Y != B.Y)
		{
			return A.Y < B.Y;
		}
		return A.Z < B.Z;
	};
	
	return FAudioLogDataComparer::CreateLambda(
		[Element, CompareVector3d](const UAudioLogData& A, const UAudioLogData& B) -> bool
	{
		if (Element == "Id")
		{
			return A.Id < B.Id;
		}
		else if (Element == "Volume")
		{
			return A.GetVolume() < B.GetVolume();
		}
		else if (Element == "Pitch")
		{
			return A.GetVolume() < B.GetVolume();
		}
		else if (Element == "Position")
		{
			return CompareVector3d(A.Position, B.Position);
		}
		else if (Element == "Context")
		{
			return A.Context < B.Context;
		}
		else if (Element == "AudioSource")
		{
			return A.AudioSource < B.AudioSource;
		}
		else if (Element == "Prevent")
		{
			return A.bPrevent < B.bPrevent;
		}

		return A.Id < B.Id;	
	});
}

#pragma endregion

void SAudioLogElement::Construct(const FArguments& Args)
{
	auto Log = Args._Log.Get();

	TArray<TSharedPtr<SWidget>> Widgets =
	{
		SNew(STextBlock)
			.Text(FText::FromString(FString::FromInt(Log->Id))),
		
		SNew(STextBlock)
			.Text(FText::FromString(Log->StartTime.ToString())),

		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SProgressBar)
				.Percent(Log->GetVolume())
		]
		+ SOverlay::Slot()
		[
			SNew(STextBlock)
				.Text(FText::FromString(FString::Printf(
						TEXT("%.2f"),
						Log->GetVolume())))
		],
		
		SNew(STextBlock)
			.Text(FText::FromString(FString::Printf(
				TEXT("%.2f"),
				Log->GetPitch()))),
				
		PlayTimeWidget(Log),
		
		SNew(STextBlock)
			.Text(FText::FromString(
				FString::Printf(
					TEXT("(%.2f, %.2f, %.2f)"),
					Log->Position.X,
					Log->Position.Y,
					Log->Position.Z)
			)),
		
		SNew(STextBlock)
			.Text(FText::FromString(Log->Context)),

		AudioSourceWidget(Log),
		
		SNew(SCheckBox)
			.IsChecked(Log->bPrevent)
	};
	
	int32 Len = Widgets.Num();

	auto HeaderElements = SAudioLogList::HeaderElements;
	auto HorizontalBox = SNew(SHorizontalBox);
	
	for(int32 i = 0; i < Len; i++)
	{
		auto Widget = Widgets[i];
		auto Weight = HeaderElements[i].Weight;
		
		HorizontalBox->AddSlot()
		.FillWidth(Weight)
		.HAlign(HAlign_Center)
		[
			Widget.ToSharedRef()
		];
	}
	
	ChildSlot
	[
		HorizontalBox
	];
}

TSharedPtr<SWidget> SAudioLogElement::AudioSourceWidget(UAudioLogDataPtr LogData)
{
	auto SoundCueNameGetter = CREATE_ATTRIBUTE(FText, [LogData]() -> FText
	{
		auto fstr = LogData.IsValid() ? LogData->GetSoundCueName() : TEXT("");
		return FText::FromString(fstr);
	});
	
	return 	SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(STextBlock)
			.Text(SoundCueNameGetter)
	]
	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(SButton)
		.OnClicked_Lambda([this, LogData]() -> FReply
		{
			HighlightSoundCueInContentBrowser(LogData->GetSoundCueAssetPathName());
			return FReply::Handled();
		})
		.ButtonStyle(FCoreStyle::Get(), "NoBorder")
		[
			SNew(SImage)
				.Image(
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.BrowseContent").GetIcon())
		]
	];
}

TSharedPtr<SWidget> SAudioLogElement::PlayTimeWidget(UAudioLogDataPtr LogData)
{
	auto PlayTimeGetter = CREATE_ATTRIBUTE(TOptional<float>, [LogData]()
	{
		return TOptional(LogData.IsValid() ? LogData->PlayPercent : 1.0f);
	});

	auto PlayTimeStringGetter = CREATE_ATTRIBUTE(FText, [LogData]() -> FText
	{
		auto PlayPercent = LogData.IsValid() ? LogData->PlayPercent : 1.0f;
		auto Duration = LogData.IsValid() ? LogData->GetDuration() : 1.0f;
		
		return FText::FromString(FString::Printf(
			TEXT("%.1f/%.1f"),
			PlayPercent * Duration,
			Duration));
	});
	
	return 	SNew(SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SProgressBar)
			.Percent(PlayTimeGetter)
			.FillColorAndOpacity(FLinearColor::Green)
	]
	+SOverlay::Slot()
	[
		SNew(STextBlock)
			.Text(PlayTimeStringGetter)
	];
}
#pragma endregion

#pragma region Private
void SAudioLogElement::HighlightSoundCueInContentBrowser(FName ContentBrowserPath)
{
	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FAssetData AssetData =
		AssetRegistry.GetAssetByObjectPath(ContentBrowserPath);
	if(AssetData.IsValid())
	{
		TArray<FAssetData> SelectedAssets;
		SelectedAssets.Add(AssetData);

		GEditor->SyncBrowserToObject(AssetData);
	}
}
#pragma endregion 