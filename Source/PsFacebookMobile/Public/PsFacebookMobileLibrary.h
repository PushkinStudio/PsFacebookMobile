// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "PsFacebookMobileLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnFacebookLoginCompleted, bool, bSuccess, const FString&, AccessToken);
DECLARE_DELEGATE_TwoParams(FOnFacebookLoginCompletedStatic, bool, FString);

UCLASS()
class PSFACEBOOKMOBILE_API UPsFacebookMobileLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/** Initialize facebook login with permissions provided */
	UFUNCTION(BlueprintCallable, Category = "Pushkin Facebook Mobile", meta = (AutoCreateRefTerm = "SuccessCallback"))
	static void FacebookLogin(const FString& LoginPermissions, const FOnFacebookLoginCompleted& SuccessCallback);

	/** Initialize facebook login with permissions provided */
	static void FacebookLogin(const FString& LoginPermissions, const FOnFacebookLoginCompletedStatic& SuccessCallback);

	/** Logout user session if we have one */
	UFUNCTION(BlueprintCallable, Category = "Pushkin Facebook Mobile")
	static void FacebookLogout();

	/**  Check if a person is already logged in */
	UFUNCTION(BlueprintPure, Category = "Pushkin Facebook Mobile")
	static bool IsLoggedIn();

	/** Set AdvertiserTrackingEnabled */
	static void SetAdvertiserTrackingEnabled(bool bEnabled);

	/** Callback for login completed event */
	static FOnFacebookLoginCompleted LoginCompleted;

	/** Callback for login completed event */
	static FOnFacebookLoginCompletedStatic LoginCompletedStatic;

	/** Dispatch login event to main thread */
	static void DispatchFacebookLoginCompletedEvent(bool bSuccess, const FString& AccessToken);

	/**  Logs a purchase event with Facebook explicitly, in the specified amount and with the specified sku and currency */
	static bool LogPurchase(float Price, FString& Currency, FString& Sku);

private:
	/** Facebook sign-in implementation */
	static void FacebookLoginImpl(const FString& LoginPermissions);
};
