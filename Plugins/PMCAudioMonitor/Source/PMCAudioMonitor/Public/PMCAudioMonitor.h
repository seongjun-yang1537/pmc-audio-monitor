// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FPMCAudioMonitorModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

  void RegisterMenus();
  void RegisterDockTab();
	void RegisterHandler();
  
  void UnRegisterDockTab();

  TSharedRef<SDockTab> CreateDockTab(const FSpawnTabArgs& SpawnTabArgs);
  void OnSpawnDockTab();
};
