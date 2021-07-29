// Copyright 2015-2021 Mail.Ru Group. All Rights Reserved.

#include "PsFacebookMobile.h"

#include "PsFacebookMobileDefines.h"
#include "PsFacebookMobileSettings.h"

#include "Developer/Settings/Public/ISettingsModule.h"
#include "UObject/Package.h"

#if PLATFORM_IOS && WITH_PSFACEBOOKMOBILE
#include "FacebookMobile.h"
#import <FBSDKCoreKit/FBSDKCoreKit.h>

#include "IOS/IOSAppDelegate.h"
#endif // PLATFORM_IOS && WITH_PSFACEBOOKMOBILE

#define LOCTEXT_NAMESPACE "FPsFacebookMobileModule"

#if PLATFORM_ANDROID
jclass FPsFacebookMobileModule::PsFacebookClassID;
#endif

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

#if PLATFORM_ANDROID && WITH_PSFACEBOOKMOBILE
	PsFacebookClassID = FAndroidApplication::FindJavaClassGlobalRef("com/pushkinstudio/PsFacebookMobile/PsFacebookMobile");
#endif

#if PLATFORM_IOS && WITH_PSFACEBOOKMOBILE
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
