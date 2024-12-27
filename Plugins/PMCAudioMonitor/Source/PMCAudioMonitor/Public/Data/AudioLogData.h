#pragma once

#include "CoreMinimal.h"
#include "AudioLogData.generated.h"

USTRUCT(BlueprintType)
struct FAudioLogData
{
  GENERATED_USTRUCT_BODY()
public:
  UPROPERTY()
  int32 Id;

  UPROPERTY()
  FDateTime StartTime;

  UPROPERTY()
  float Volume;
  
  UPROPERTY()
  float Pitch;

  UPROPERTY()
  FVector3d Position;

  UPROPERTY()
  FString Context;
  
  UPROPERTY()
  FString AudioEvent;
  
  UPROPERTY()
  bool bPrevent;

  FAudioLogData() {}
};