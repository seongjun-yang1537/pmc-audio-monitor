// Copyright Epic Games, Inc. All Rights Reserved.

#include "PMCAudioMonitor.h"

#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "FPMCAudioMonitorModule"
#define CLASS FPMCAudioMonitorModule
#define DOCKTAB_NAME "PMCAudioMonitorDockTab"

void CLASS::StartupModule()
{
  RegisterMenus();
  RegisterDockTab();
}

void CLASS::ShutdownModule()
{
  UnRegisterDockTab();
}

void CLASS::RegisterMenus()
{
  FToolMenuOwnerScoped OwnerScoped(this);

  UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
  FToolMenuSection& Section = Menu->AddSection("PMC", LOCTEXT("PMC", "PMC"));
  Section.AddMenuEntry(
    "Open Audio Monitor Window",
    LOCTEXT("OpenAudioMonitorWindow", "Open Audio Monitor Window"),
    LOCTEXT("OpenAudioMonitorWindowTooltip", "Open a Audio Monitor Window."),
    FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.AudioVolume"),
    FUIAction(FExecuteAction::CreateRaw(this, &CLASS::OnSpawnDockTab))
  );
}

void CLASS::RegisterDockTab()
{
  TSharedRef<FWorkspaceItem> WorkspaceGroup = FWorkspaceItem::NewGroup(FText::FromString(DOCKTAB_NAME));

  FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
    DOCKTAB_NAME,
    FOnSpawnTab::CreateRaw(this, &CLASS::CreateDockTab)
  )
  .SetDisplayName(LOCTEXT(DOCKTAB_NAME, "PMC Audio Monitor"))
  .SetGroup(WorkspaceGroup);
}

void CLASS::UnRegisterDockTab()
{
  FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DOCKTAB_NAME);
}

void CLASS::OnSpawnDockTab()
{
  FGlobalTabmanager::Get()->TryInvokeTab(FTabId(DOCKTAB_NAME));
}

TSharedRef<SDockTab> CLASS::CreateDockTab(const FSpawnTabArgs& SpawnTabArgs)
{
  return SNew(SDockTab)
  .TabRole(ETabRole::NomadTab)
  [
    SNew(STextBlock)
      .Text(FText::FromString("Text"))  
  ];
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPMCAudioMonitorModule, PMCAudioMonitor)