#include "UI/AudioLogList.h"

#include "Widgets/Views/STableRow.h"
#include "PMCAudioManager.h"

#include "UI/AudioLogElement.h"

#define CLASS SAudioLogList

void CLASS::Construct(const FArguments& InArgs)
{
    FPMCAudioManager::Get()->OnAddLog.AddRaw(this, &CLASS::OnAddLog);

    auto& Items = FPMCAudioManager::Get()->GetLogs();
    
    ListView = SNew(SListView<FAudioLogDataPtr>)
        .ItemHeight(SIZE_ELEMENT)
        .ListItemsSource(&Items) 
        .OnGenerateRow(this, &CLASS::OnGenerateRowForListView);
    
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

TSharedPtr<SHeaderRow> CLASS::ListHeaderWidget()
{
    TArray<FString> HeaderElements =
    {
        TEXT("ID"),
        TEXT("Start Time"),
        TEXT("Volume"),
        TEXT("Pitch"),
        TEXT("Position"),
        TEXT("Context"),
        TEXT("Audio Source"),
        TEXT("Prevent"),
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
    
    TSharedPtr<SHeaderRow> Header = SNew(SHeaderRow);

    check(HeaderElements.Num() ==  HeaderWidthRatios.Num());
    int32 Len = HeaderElements.Num();
    for (int32 i = 0; i < Len; i++)
    {
        auto element = HeaderElements[i];
        Header->AddColumn(
            SHeaderRow::Column(*element)
            .DefaultLabel(FText::FromString(element))
            .FillWidth(HeaderWidthRatios[i])
            .HAlignHeader(HAlign_Center)
            .VAlignHeader(VAlign_Center)
        );
    }
    
    return Header;
}

void CLASS::ChangeListCurrentLogs()
{
    auto& Items = FPMCAudioManager::Get()->GetLogs();
    
    ListView->SetItemsSource(&Items);
    ListView->RequestListRefresh();
};

void CLASS::ChangeListHistoryLogs()
{
    auto& Items = FPMCAudioManager::Get()->History;

    ListView->SetItemsSource(&Items);
    ListView->RequestListRefresh();
};

TSharedPtr<SHorizontalBox> CLASS::ListTabGroup()
{
    return SNew(SHorizontalBox)
    + SHorizontalBox::Slot()
    [
        SNew(SButton)
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
            })
    ]
    +SHorizontalBox::Slot()
    [
        SNew(SButton)
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
            })
    ];
}

TSharedRef<ITableRow> CLASS::OnGenerateRowForListView(
  FAudioLogDataPtr Item, 
  const TSharedRef<STableViewBase>& OwnerTable)
{
    return SNew(STableRow<FAudioLogDataPtr>, OwnerTable)
    [
        SNew(SAudioLogElement)
            .Log(*Item)
    ];
}

void CLASS::OnAddLog(FAudioLogDataPtr LogPtr)
{
    ListView->RequestListRefresh();
}
