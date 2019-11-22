// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "PsFacebookMobile.h"

#include "PsFacebookMobileDefines.h"
#include "PsFacebookMobileSettings.h"

#include "Developer/Settings/Public/ISettingsModule.h"
#include "UObject/Package.h"

#if PLATFORM_IOS
#include "FacebookMobile.h"
#import <FBSDKCoreKit/FBSDKCoreKit.h>

#include "IOS/IOSAppDelegate.h"
#endif

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

#if PLATFORM_IOS
	[FacebookObserver load];
	[[FacebookObserver sharedInstance] didFinishLaunching:nil];

	FIOSCoreDelegates::OnOpenURL.AddLambda([this](UIApplication* application, NSURL* url, NSString* sourceApplication, id annotation) {
		[[FBSDKApplicationDelegate sharedInstance] application:application
													   openURL:url
											 sourceApplication:sourceApplication
													annotation:annotation];
	});
#endif
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
