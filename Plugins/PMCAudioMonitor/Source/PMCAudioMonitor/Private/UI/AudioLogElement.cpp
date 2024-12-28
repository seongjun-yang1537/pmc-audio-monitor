#include "UI/AudioLogElement.h"

#include "FileHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Sound/SoundCue.h"
#include "UI/AudioLogList.h"
#include "Widgets/Notifications/SProgressBar.h"

#pragma region Public

#pragma region Static
FAudioLogDataComparer FAudioLogData::OnCompare(FString Element)
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
		[Element, CompareVector3d](const FAudioLogData& A, const FAudioLogData& B) -> bool
	{
		if (Element == "Id")
		{
			return A.Id < B.Id;
		}
		else if (Element == "StartTime")
		{
			return A.StartTime < B.StartTime;
		}
		else if (Element == "Volume")
		{
			return A.GetVolume() < B.GetVolume();
		}
		else if (Element == "Pitch")
		{
			return A.GetVolume() < B.GetVolume();
		}
		else if (Element == "PlayTime")
		{
			return A.PlayTime < B.PlayTime;
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
			.Text(FText::FromString(FString::FromInt(Log.Id))),
		
		SNew(STextBlock)
			.Text(FText::FromString(Log.StartTime.ToString())),

		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SProgressBar)
				.Percent(Log.GetVolume())
		]
		+ SOverlay::Slot()
		[
			SNew(STextBlock)
				.Text(FText::FromString(FString::Printf(
						TEXT("%.2f"),
						Log.GetVolume())))
		],
		
		SNew(STextBlock)
			.Text(FText::FromString(FString::Printf(
				TEXT("%.2f"),
				Log.GetPitch()))),
				
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SProgressBar)
				.Percent(Log.PlayTime)
				.FillColorAndOpacity(FLinearColor::Green)
		]
		+SOverlay::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString(FString::Printf(
					TEXT("%.2f"),
					Log.PlayTime)))
		],
		
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

		AudioSourceWidget(Log),
		
		SNew(SCheckBox)
			.IsChecked(Log.bPrevent)
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

TSharedPtr<SWidget> SAudioLogElement::AudioSourceWidget(FAudioLogData LogData)
{
	auto SoundCue = LogData.GetSoundCue();
	
	return 	SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(STextBlock)
			.Text(FText::FromString(SoundCue->GetName()))
	]
	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(SButton)
		[
			SNew(SImage)
				.Image(
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.BrowseContent").GetIcon())
		]
		.OnClicked_Lambda([this, SoundCue]() -> FReply
		{
			HighlightSoundCueInContentBrowser(SoundCue);
			return FReply::Handled();
		})
	];
}

#pragma endregion

#pragma region Private
void SAudioLogElement::HighlightSoundCueInContentBrowser(USoundCue* SoundCue)
{
	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FAssetData AssetData =
		AssetRegistry.GetAssetByObjectPath(FSoftObjectPath(SoundCue).GetAssetPathName());
	if(AssetData.IsValid())
	{
		TArray<FAssetData> SelectedAssets;
		SelectedAssets.Add(AssetData);

		GEditor->SyncBrowserToObject(AssetData);
	}
}
#pragma endregion 