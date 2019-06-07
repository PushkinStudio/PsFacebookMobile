// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "PsFacebookMobileLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnFacebookLoginCompleted, bool, bSuccess, const FString&, AccessToken);

UCLASS()
class PSFACEBOOKMOBILE_API UPsFacebookMobileLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/** Initialize facebook login with permissions provided */
	UFUNCTION(BlueprintCallable, Category = "Pushkin Facebook Mobile", meta = (AutoCreateRefTerm = "SuccessCallback"))
	static void FacebookLogin(const FString& LoginPermissions, const FOnFacebookLoginCompleted& SuccessCallback);

	/** Logout user session if we have one */
	UFUNCTION(BlueprintCallable, Category = "Pushkin Facebook Mobile")
	static void FacebookLogout();

	/**  Check if a person is already logged in */
	UFUNCTION(BlueprintPure, Category = "Pushkin Facebook Mobile")
	static bool IsLoggedIn();

	/** Callback for login completed event */
	static FOnFacebookLoginCompleted LoginCompleted;

	/** Dispatch login event to main thread */
	static void DispatchFacebookLoginCompletedEvent(bool bSuccess, const FString& AccessToken);
};
