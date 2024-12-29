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
  float PlayTime;

  UPROPERTY()
  FVector3d Position;

  UPROPERTY()
  FString Context;
  
  UPROPERTY()
  FString AudioSource;
  
  UPROPERTY()
  bool bPrevent;

  UPROPERTY()
  UAudioComponent* AudioComponent;

  FAudioLogData();
  FAudioLogData(UAudioComponent* AudioComponent);
  
  float GetPitch() const;
  float GetVolume() const;

  FString GetSoundCueName() const;
  FName GetSoundCueAssetPathName() const;
  
  USoundCue* GetSoundCue() const;
  
  static FAudioLogDataComparer OnCompare(FString Element);

private:
  FString SoundCueName;
  FName SoundCueAssetPathName;
};