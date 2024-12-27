#include "AudioLogList.h"

#include "Widgets/Views/STableRow.h"

#define CLASS SAudioLogList

void CLASS::Construct(const FArguments& InArgs)
{
    Items.Add(MakeShared<FAudioLogData>(FAudioLogData{TEXT("Log Message 1")}));
    Items.Add(MakeShared<FAudioLogData>(FAudioLogData{TEXT("Log Message 2")}));
    Items.Add(MakeShared<FAudioLogData>(FAudioLogData{TEXT("Log Message 3")}));

    // SListView 생성
    ChildSlot
    [
        SNew(SListView<FAudioLogDataPtr>)
        .ItemHeight(24)
        .ListItemsSource(&Items)  // 리스트 데이터 소스
        .OnGenerateRow(this, &CLASS::OnGenerateRowForListView)  // 아이템을 생성하는 함수
    ];
}

TSharedRef<ITableRow> CLASS::OnGenerateRowForListView(
  FAudioLogDataPtr Item, 
  const TSharedRef<STableViewBase>& OwnerTable)
{
    return SNew(STableRow<FAudioLogDataPtr>, OwnerTable)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .AutoWidth()
            [
                SNew(STextBlock)
                .Text(FText::FromString(*Item->Msg))
            ]
        ];
}