#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Data/AudioLogData.h"

typedef TSharedPtr<FAudioLogData> FAudioLogDataPtr;

class SAudioLogList : public SCompoundWidget
{
public:
  SLATE_BEGIN_ARGS(SAudioLogList){}
  SLATE_END_ARGS()

  void Construct(const FArguments& InArgs);

private:
  TSharedPtr<SListView<FAudioLogDataPtr>> ListView;
  
  TSharedRef<ITableRow> OnGenerateRowForListView(FAudioLogDataPtr Item, const TSharedRef<STableViewBase>& OwnerTable);
  void OnAddLog(FAudioLogDataPtr LogPtr);
};