// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "PsFacebookMobile.h"

#include "PsFacebookMobileDefines.h"
#include "PsFacebookMobileSettings.h"

#include "Developer/Settings/Public/ISettingsModule.h"
#include "UObject/Package.h"

#define LOCTEXT_NAMESPACE "FPsFacebookMobileModule"

void FPsFacebookMobileModule::StartupModule()
{
	PsFacebookMobileSettings = NewObject<UPsFacebookMobileSettings>(GetTransientPackage(), "PsFacebookMobileSettings", RF_Standalone);
	PsFacebookMobileSettings->AddToRoot();

	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "PsFacebookMobile",
			LOCTEXT("RuntimeSettingsName", "PsFacebookMobile"),
			LOCTEXT("RuntimeSettingsDescription", "Configure PsFacebookMobile plugin"),
			PsFacebookMobileSettings);
	}
}

void FPsFacebookMobileModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "PsFacebookMobile SDK");
	}

	if (!GExitPurge)
	{
		// If we're in exit purge, this object has already been destroyed
		PsFacebookMobileSettings->RemoveFromRoot();
	}
	else
	{
		PsFacebookMobileSettings = nullptr;
	}
}

UPsFacebookMobileSettings* FPsFacebookMobileModule::GetSettings() const
{
	check(PsFacebookMobileSettings);
	return PsFacebookMobileSettings;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPsFacebookMobileModule, PsFacebookMobile)

DEFINE_LOG_CATEGORY(LogPsFacebookMobile);