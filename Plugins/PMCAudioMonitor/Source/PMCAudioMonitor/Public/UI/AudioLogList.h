#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Data/AudioLogData.h"

#define SIZE_ELEMENT 24
#define SCROLL_MAX_ELEMENT 15

typedef TSharedPtr<FAudioLogData> FAudioLogDataPtr;

class SAudioLogList : public SCompoundWidget
{
public:
  SLATE_BEGIN_ARGS(SAudioLogList){}
  SLATE_END_ARGS()

  void Construct(const FArguments& InArgs);
  TSharedPtr<SHeaderRow> ListHeaderWidget();

private:
  TSharedPtr<SListView<FAudioLogDataPtr>> ListView;
  
  TSharedRef<ITableRow> OnGenerateRowForListView(FAudioLogDataPtr Item, const TSharedRef<STableViewBase>& OwnerTable);
  void OnAddLog(FAudioLogDataPtr LogPtr);
};