// Copyright Epic Games, Inc. All Rights Reserved.

#include "PMCAudioMonitor.h"

#include "PMCAudioManager.h"
#include "ToolMenus.h"
#include "UI/AudioLogList.h"
#include "UI/AudioOptionPanel.h"

#define LOCTEXT_NAMESPACE "FPMCAudioMonitorModule"
#define DOCKTAB_NAME "PMCAudioMonitorDockTab"

#pragma region Public
void FPMCAudioMonitorModule::StartupModule()
{
  RegisterMenus();
  RegisterDockTab();
  RegisterHandler();
}

void FPMCAudioMonitorModule::ShutdownModule()
{
  UnRegisterDockTab();
}

void FPMCAudioMonitorModule::RegisterMenus()
{
  FToolMenuOwnerScoped OwnerScoped(this);

  UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
  FToolMenuSection& Section = Menu->AddSection("PMC", LOCTEXT("PMC", "PMC"));
  Section.AddMenuEntry(
    "Open Audio Monitor Window",
    LOCTEXT("OpenAudioMonitorWindow", "Open Audio Monitor Window"),
    LOCTEXT("OpenAudioMonitorWindowTooltip", "Open a Audio Monitor Window."),
    FSlateIcon(FAppStyle::GetAppStyleSetName(), "FPMCAudioMonitorModuleIcon.AudioVolume"),
    FUIAction(FExecuteAction::CreateRaw(this, &FPMCAudioMonitorModule::OnSpawnDockTab))
  );
}

void FPMCAudioMonitorModule::RegisterDockTab()
{
  TSharedRef<FWorkspaceItem> WorkspaceGroup = FWorkspaceItem::NewGroup(FText::FromString(DOCKTAB_NAME));

  FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
    DOCKTAB_NAME,
    FOnSpawnTab::CreateRaw(this, &FPMCAudioMonitorModule::CreateDockTab)
  )
  .SetDisplayName(LOCTEXT(DOCKTAB_NAME, "PMC Audio Monitor"))
  .SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "FPMCAudioMonitorModuleIcon.AudioVolume"))
  .SetGroup(WorkspaceGroup);
}

void FPMCAudioMonitorModule::RegisterHandler()
{
  FEditorDelegates::BeginPIE.AddLambda([](const bool bIsSimulating)
  {
    FPMCAudioManager::Get()->ClearLog();
  });

  FEditorDelegates::EndPIE.AddLambda([](const bool bIsSimulating)
  {
    FPMCAudioManager::Get()->ClearLog();
  });
}

void FPMCAudioMonitorModule::UnRegisterDockTab()
{
  FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DOCKTAB_NAME);
}

void FPMCAudioMonitorModule::OnSpawnDockTab()
{
  FGlobalTabmanager::Get()->TryInvokeTab(FTabId(DOCKTAB_NAME));
}

TSharedRef<SDockTab> FPMCAudioMonitorModule::CreateDockTab(const FSpawnTabArgs& SpawnTabArgs)
{
  return SNew(SDockTab)
  .TabRole(ETabRole::NomadTab)
  [
    SNew(SVerticalBox)
    + SVerticalBox::Slot()
    .AutoHeight()
    [
      SNew(SAudioOptionPanel)
    ]
    + SVerticalBox::Slot()
    .AutoHeight()
    [
      SNew(SAudioLogList)
    ]
  ];
}
#pragma region

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPMCAudioMonitorModule, PMCAudioMonitor)