// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PMCAudioMonitorBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PMCAUDIOMONITOR_API UPMCAudioMonitorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "PMCAudioMonitor")
	static void AddSoundLog(UAudioComponent* AudioComponent);
};
