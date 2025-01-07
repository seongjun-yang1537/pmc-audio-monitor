#include "UI/AudioLogList.h"

#include "Widgets/Views/STableRow.h"
#include "PMCAudioManager.h"

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

void SAudioLogList::ChangeListCurrentLogs()
{
    auto& Items = FPMCAudioManager::Get()->GetLogs();
    
    ListView->SetItemsSource(&Items);
    ListView->RequestListRefresh();
};

void SAudioLogList::ChangeListHistoryLogs()
{
    auto& Items = FPMCAudioManager::Get()->History;

    ListView->SetItemsSource(&Items);
    ListView->RequestListRefresh();
};

TSharedPtr<SHorizontalBox> SAudioLogList::ListTabGroup()
{
    ButtonCurrent = SNew(SButton)
        .Text(FText::FromString("Current"))
        .HAlign(HAlign_Center)
        .IsEnabled_Lambda([this]()
        {
            return ListTabState == EListTabState::History;
        })
        .OnClicked_Lambda([this]()
        {
            ListTabState = EListTabState::Current;
            ChangeListCurrentLogs();
            return FReply::Handled();
        });

    ButtonHistory = SNew(SButton)
        .Text(FText::FromString("History"))
        .HAlign(HAlign_Center)
        .IsEnabled_Lambda([this]()
        {
            return ListTabState == EListTabState::Current;
        })
        .OnClicked_Lambda([this]()
        {
            ListTabState = EListTabState::History;
            ChangeListHistoryLogs();
            return FReply::Handled();
        });
    
    return SNew(SHorizontalBox)
    + SHorizontalBox::Slot()
    [
        ButtonCurrent.ToSharedRef()
    ]
    +SHorizontalBox::Slot()
    [
        ButtonHistory.ToSharedRef()
    ];
}
#pragma region

#pragma region Private
TSharedRef<ITableRow> SAudioLogList::OnGenerateRowForListView(
  UAudioLogDataPtr Item, 
  const TSharedRef<STableViewBase>& OwnerTable)
{
    return SNew(STableRow<UAudioLogDataPtr>, OwnerTable)
    [
        SNew(SAudioLogElement)
            .Log(Item)
    ];
}

void SAudioLogList::OnAddLog(UAudioLogDataPtr LogPtr)
{
    ListView->RequestListRefresh();
}

#pragma endregion
