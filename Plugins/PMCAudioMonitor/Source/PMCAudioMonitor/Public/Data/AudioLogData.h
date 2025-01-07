#pragma once

#include "CoreMinimal.h"
#include "AudioLogData.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlay);
DECLARE_MULTICAST_DELEGATE(FOnPlayEnd);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FAudioLogDataComparer, const UAudioLogData&,  const UAudioLogData&);

UCLASS(BlueprintType)
class UAudioLogData : public UObject
{
  GENERATED_BODY()
public:
#pragma region Variables
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

  UPROPERTY()
  TWeakObjectPtr<UAudioComponent> AudioComponent;
#pragma endregion 

#pragma region Events
  FOnPlay OnPlay;
  FOnPlayEnd OnPlayEnd;
#pragma endregion 

  UFUNCTION(BlueprintCallable)
  UAudioLogData* Init(UAudioComponent* Audio);
  void InitHandler();
  
  float GetPitch() const;
  float GetVolume() const;

  FString GetSoundCueName() const;
  FName GetSoundCueAssetPathName() const;
  float GetDuration() const;
  
  USoundCue* GetSoundCue() const;
  
  static FAudioLogDataComparer OnCompare(FString Element);

private:
};