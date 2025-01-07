#include "UI/AudioLogList.h"

#include "Widgets/Views/STableRow.h"
#include "PMCAudioManager.h"
#include "Components/AudioComponent.h"

#include "UI/AudioLogElement.h"

TArray<FAudioListHeaderElement> SAudioLogList::HeaderElements =
    {
    {TEXT("ID"), 1.0f},
    {TEXT("Start Time"), 6.0f},
    {TEXT("Volume"), 2.0f},
    {TEXT("Pitch"), 2.0f},
    {TEXT("PlayTime"), 4.0f},
    {TEXT("Position"), 6.0f},
    {TEXT("Context"), 10.0f},
    {TEXT("Audio Source"), 10.0f},
    {TEXT("Prevent"), 2.0f}
    };

#pragma region Public
SAudioLogList::~SAudioLogList()
{
    FPMCAudioManager::Get()->OnAddLog.RemoveAll(this);
}

void SAudioLogList::Construct(const FArguments& InArgs)
{
    FPMCAudioManager::Get()->OnAddLog.AddRaw(this, &SAudioLogList::OnAddLog);

    auto& Items = FPMCAudioManager::Get()->GetLogs();
    
    ListView = SNew(SListView<UAudioLogDataPtr>)
        .ItemHeight(SIZE_ELEMENT)
        .ListItemsSource(&Items) 
        .OnGenerateRow(this, &SAudioLogList::OnGenerateRowForListView);
    
    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        [
            ListTabGroup().ToSharedRef()
        ]
        + SVerticalBox::Slot()
        .AutoHeight()
        [
            ListHeaderWidget().ToSharedRef()
        ]
        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SNew(SScrollBox)
            .Orientation(Orient_Vertical)
            + SScrollBox::Slot()
            .MaxSize(SIZE_ELEMENT*SCROLL_MAX_ELEMENT)
            [
                ListView.ToSharedRef()
            ]
        ]
    ];
}

TSharedPtr<SHeaderRow> SAudioLogList::ListHeaderWidget()
{
    HeaderWidget = SNew(SHeaderRow);
    
    int32 Len = HeaderElements.Num();
    for (int32 i = 0; i < Len; i++)
    {
        auto element = HeaderElements[i];
        auto OnSort = [this, element](
            EColumnSortPriority::Type SortPriority,
            const FName& ColumnId,
            EColumnSortMode::Type SortType) 
        {
            bool bCurrent = CurrentSortColumn == *element.Name;
            
            if(bCurrent)
            {
                CurrentSortMode = (CurrentSortMode == EColumnSortMode::Ascending) ?
                    EColumnSortMode::Descending : EColumnSortMode::Ascending;
            }else
            {
                CurrentSortColumn = ColumnId;
                CurrentSortMode = EColumnSortMode::Ascending;
            }

            auto& Logs = FPMCAudioManager::Get()->GetLogs();
            if(bCurrent)
            {
                Logs.Sort([this, element](
                    const UAudioLogDataPtr& A,
                    const UAudioLogDataPtr& B) -> bool
                {
                    auto Compare = UAudioLogData::OnCompare(*element.Name);

                    if(CurrentSortMode == EColumnSortMode::Ascending)
                    {
                        return Compare.Execute(*A, *B);
                    }else
                    {
                        return !Compare.Execute(*A, *B);
                    }
                });
            }

            ListView->RequestListRefresh();
        };
        auto SortMode = [this, element]() -> EColumnSortMode::Type
        {
            return CurrentSortColumn == *element.Name ?
                CurrentSortMode : EColumnSortMode::None;
        };
        
        HeaderWidget->AddColumn(
            SHeaderRow::Column(*element.Name)
            .DefaultLabel(FText::FromString(*element.Name))
            .FillWidth(element.Weight)
            .HAlignHeader(HAlign_Center)
            .VAlignHeader(VAlign_Center)
            .SortMode_Lambda(SortMode)
            .OnSort_Lambda(OnSort)
        );
    }
    
    return HeaderWidget;
}

TSharedPtr<SHorizontalBox> SAudioLogList::ListTabGroup()
{
    auto HorizontalBox = SNew(SHorizontalBox);

    UEnum* Enum = StaticEnum<ELogVisibleType>();
    for (ELogVisibleType Type : TEnumRange<ELogVisibleType>())
    {
        FString Name = Enum->GetNameStringByValue(static_cast<int64>(Type));
        
        HorizontalBox->AddSlot()
        [
            SNew(SButton)
            .Text(FText::FromString(Name))
            .HAlign(HAlign_Center)
            .IsEnabled_Lambda([this, Type]()
            {
                
                return LogVisibleState != Type;
            })
            .OnClicked_Lambda([this, Type]()
            {
                LogVisibleState = Type;
                ListView->RebuildList();
                return FReply::Handled();
            })
        ];
    }

    return HorizontalBox;
}
#pragma region

#pragma region Private
TSharedRef<ITableRow> SAudioLogList::OnGenerateRowForListView(
  UAudioLogDataPtr Item, 
  const TSharedRef<STableViewBase>& OwnerTable)
{
    if (IsVisibleLog(LogVisibleState, Item))
    {
        return SNew(STableRow<UAudioLogDataPtr>, OwnerTable)
        [
            SNew(SAudioLogElement)
                .Log(Item)
        ];
    }
    else
    {
        return SNew(STableRow<UAudioLogDataPtr>, OwnerTable)
        [
            SNullWidget::NullWidget
        ];
    }
}

bool SAudioLogList::IsVisibleLog(ELogVisibleType VisibleType, UAudioLogDataPtr LogPtr)
{
    if (!LogPtr.IsValid())
    {
        return false;
    }
    auto AudioComponent = LogPtr->AudioComponent;
    
    switch (VisibleType)
    {
        case ELogVisibleType::Current:
            return AudioComponent.IsValid() && AudioComponent->IsPlaying();
        case ELogVisibleType::History:
            return !AudioComponent.IsValid() || !AudioComponent->IsPlaying(); 
    }
    return false;
}

void SAudioLogList::OnAddLog(UAudioLogDataPtr LogPtr)
{
    auto AudioComponent = LogPtr->AudioComponent;
    AudioComponent->OnAudioFinishedNative.AddLambda([this](auto _)
    {
        ListView->RebuildList();
    });
    ListView->RequestListRefresh();
}

#pragma endregion
