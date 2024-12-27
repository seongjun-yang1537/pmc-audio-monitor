#include "UI/AudioLogList.h"

#include "Widgets/Views/STableRow.h"
#include "PMCAudioManager.h"

#include "UI/AudioLogElement.h"

#define CLASS SAudioLogList

void CLASS::Construct(const FArguments& InArgs)
{
    FPMCAudioManager* Manager = FPMCAudioManager::Get();
    Manager->OnAddLog.AddRaw(this, &CLASS::OnAddLog);
    auto& Items = Manager->GetLogs();
    
    ListView = SNew(SListView<FAudioLogDataPtr>)
        .ItemHeight(24)
        .ListItemsSource(&Items) 
        .OnGenerateRow(this, &CLASS::OnGenerateRowForListView);
    
    ChildSlot
    [
        ListView.ToSharedRef()
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
