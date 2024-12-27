#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "AudioLogData.h"

typedef TSharedPtr<FAudioLogData> FAudioLogDataPtr;

class SAudioLogList : public SCompoundWidget
{
public:
  SLATE_BEGIN_ARGS(SAudioLogList){}
  SLATE_END_ARGS()

  void Construct(const FArguments& InArgs);

private:
  // TODO: Manager로 옮기기
  TArray<FAudioLogDataPtr> Items;

  TSharedRef<ITableRow> OnGenerateRowForListView(FAudioLogDataPtr Item, const TSharedRef<STableViewBase>& OwnerTable);
};