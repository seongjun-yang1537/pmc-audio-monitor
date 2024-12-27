#pragma once

#include "CoreMinimal.h"
#include "AudioLogData.generated.h"

USTRUCT(BlueprintType)
struct FAudioLogData
{
  GENERATED_USTRUCT_BODY()
public:
  UPROPERTY()
  FString Msg;

  FAudioLogData() {}
  FAudioLogData(FString msg) : Msg(msg) {}
};