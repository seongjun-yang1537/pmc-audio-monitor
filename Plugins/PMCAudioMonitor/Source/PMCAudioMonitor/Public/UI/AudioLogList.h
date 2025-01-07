#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Data/AudioLogData.h"

#define SIZE_ELEMENT 24
#define SCROLL_MAX_ELEMENT 15

typedef TWeakObjectPtr<UAudioLogData> UAudioLogDataPtr;

struct FAudioListHeaderElement
{
public:
  FString Name;
  float Weight;

  FAudioListHeaderElement(FString Name, float Weight) : Name(Name), Weight(Weight) {}
};

UENUM(BlueprintType)
enum class ELogVisibleType : uint8
{
  Current UMETA(DisplayName = "Current"),
  History UMETA(DisplayName = "History"),
  Max UMETA(Hidden),
};
ENUM_RANGE_BY_COUNT(ELogVisibleType, ELogVisibleType::Max);

class SAudioLogList : public SCompoundWidget
{
public:
  SLATE_BEGIN_ARGS(SAudioLogList){}
  SLATE_END_ARGS()

  ~SAudioLogList();

#pragma region Variables
  static TArray<FAudioListHeaderElement> HeaderElements;
  
  ELogVisibleType LogVisibleState = ELogVisibleType::Current;
#pragma endregion 

#pragma region Methods
  void Construct(const FArguments& InArgs);
  
  TSharedPtr<SHeaderRow> ListHeaderWidget();
  TSharedPtr<SHorizontalBox> ListTabGroup();
  
  bool IsVisibleLog(ELogVisibleType VisibleType, UAudioLogDataPtr LogPtr);
#pragma endregion
  
private:
#pragma region Variables
  TSharedPtr<SListView<UAudioLogDataPtr>> ListView;
  TSharedPtr<SHeaderRow> HeaderWidget;
  
  FName CurrentSortColumn = NAME_None;
  EColumnSortMode::Type CurrentSortMode = EColumnSortMode::None;
#pragma endregion

#pragma region Methods
  TSharedRef<ITableRow> OnGenerateRowForListView(UAudioLogDataPtr Item, const TSharedRef<STableViewBase>& OwnerTable);
  void OnAddLog(UAudioLogDataPtr LogPtr);
#pragma endregion 
};
