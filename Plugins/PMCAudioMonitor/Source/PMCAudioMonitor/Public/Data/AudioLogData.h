#pragma once

#include "CoreMinimal.h"
#include "AudioLogData.generated.h"

DECLARE_DELEGATE_RetVal_TwoParams(bool, FAudioLogDataComparer, const UAudioLogData&,  const UAudioLogData&);

UCLASS(BlueprintType)
class UAudioLogData : public UObject
{
  GENERATED_BODY()
public:
  UPROPERTY()
  int32 Id;

  UPROPERTY()
  FDateTime StartTime;

  UPROPERTY()
  float PlayPercent;

  UPROPERTY()
  FVector3d Position;

  UPROPERTY()
  FString Context;
  
  UPROPERTY()
  FString AudioSource;
  
  UPROPERTY()
  bool bPrevent;

  UFUNCTION(BlueprintCallable)
  void Init(UAudioComponent* Audio);
  void InitHandler();
  
  UPROPERTY()
  TWeakObjectPtr<UAudioComponent> AudioComponent;
  
  float GetPitch() const;
  float GetVolume() const;
  float GetPlayTime() const;

  FString GetSoundCueName() const;
  FName GetSoundCueAssetPathName() const;
  
  USoundCue* GetSoundCue() const;
  
  static FAudioLogDataComparer OnCompare(FString Element);

private:
  FString SoundCueName;
  FName SoundCueAssetPathName;
  float SoundCueDuration;
};