#pragma once

#include "CoreMinimal.h"
#include "AudioLogData.generated.h"

DECLARE_DELEGATE_RetVal_TwoParams(bool, FAudioLogDataComparer, const FAudioLogData&,  const FAudioLogData&);

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
  float PlayTime;

  UPROPERTY()
  FVector3d Position;

  UPROPERTY()
  FString Context;
  
  UPROPERTY()
  FString AudioSource;
  
  UPROPERTY()
  bool bPrevent;

  FAudioLogData() {}
  
  static FAudioLogDataComparer OnCompare(FString Element);
};