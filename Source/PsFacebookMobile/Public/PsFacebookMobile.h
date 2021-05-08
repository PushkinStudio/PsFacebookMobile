// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android_native_app_glue.h>
#endif

class UPsFacebookMobileSettings;

class FPsFacebookMobileModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline FPsFacebookMobileModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FPsFacebookMobileModule>("PsFacebookMobile");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("PsFacebookMobile");
	}

	/** Getter for internal settings object to support runtime configuration changes */
	UPsFacebookMobileSettings* GetSettings() const;

private:
	UPsFacebookMobileSettings* PsFacebookMobileSettings = nullptr;

public:
#if PLATFORM_ANDROID
	/** Internal class wrapper */
	static jclass PsFacebookClassID;
#endif
};
