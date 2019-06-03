// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "PsFacebookMobile.h"

#include "PsFacebookMobileDefines.h"
#include "PsFacebookMobileProxy.h"
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

	// Proxy class depends on platform
	UClass* KitPlatformClass = UPsFacebookMobileProxy::StaticClass();

	// Create crashlytics kit proxy and initalize module by default
	PsFacebookMobileProxy = NewObject<UPsFacebookMobileProxy>(GetTransientPackage(), KitPlatformClass);
	PsFacebookMobileProxy->SetFlags(RF_Standalone);
	PsFacebookMobileProxy->AddToRoot();
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
		PsFacebookMobileProxy->RemoveFromRoot();
		PsFacebookMobileProxy->ClearFlags(RF_Standalone);
	}
	else
	{
		PsFacebookMobileSettings = nullptr;
		PsFacebookMobileProxy = nullptr;
	}
}

UPsFacebookMobileSettings* FPsFacebookMobileModule::GetSettings() const
{
	check(PsFacebookMobileSettings);
	return PsFacebookMobileSettings;
}

UPsFacebookMobileProxy* FPsFacebookMobileModule::GetProxy() const
{
	check(PsFacebookMobileProxy);
	return PsFacebookMobileProxy;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPsFacebookMobileModule, PsFacebookMobile)

DEFINE_LOG_CATEGORY(LogPsFacebookMobile);