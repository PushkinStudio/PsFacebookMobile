// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "PsFacebookMobileLibrary.h"

#include "PsFacebookMobile.h"
#include "PsFacebookMobileDefines.h"

#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android_native_app_glue.h>
#endif // PLATFORM_ANDROID

#if PLATFORM_IOS
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>

#include "IOSView.h"
#endif

FOnFacebookLoginCompleted UPsFacebookMobileLibrary::LoginCompleted;

UPsFacebookMobileLibrary::UPsFacebookMobileLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPsFacebookMobileLibrary::FacebookLogin(const FString& LoginPermissions, const FOnFacebookLoginCompleted& SuccessCallback)
{
	UPsFacebookMobileLibrary::LoginCompleted = SuccessCallback;

#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring LoginPermissionsJava = Env->NewStringUTF(TCHAR_TO_UTF8(*LoginPermissions));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FacebookLogin", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, LoginPermissionsJava);
		Env->DeleteLocalRef(LoginPermissionsJava);
	}
#elif PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
	  FBSDKAccessToken* accessToken = [FBSDKAccessToken currentAccessToken];
	  if (accessToken == nil)
	  {
		  NSArray* Permissions = [LoginPermissions.GetNSString() componentsSeparatedByString:@","];

		  FBSDKLoginManager* loginManager = [[FBSDKLoginManager alloc] init];
		  [loginManager logInWithReadPermissions:Permissions
							  fromViewController:[IOSAppDelegate GetDelegate].IOSController
										 handler:^(FBSDKLoginManagerLoginResult* result, NSError* error) {
										   FString AccessToken;
										   bool bSuccess = false;

										   if (error)
										   {
											   UE_LOG(LogPsFacebookMobile, Verbose, TEXT("%s: FacebookLoginCompleted: %d, ErrorCode: %d"), *PS_FUNC_LINE, false, [error code]);
										   }
										   else if (result.isCancelled)
										   {
											   UE_LOG(LogPsFacebookMobile, Verbose, TEXT("%s: FacebookLoginCompleted: %d, Cancelled"), *PS_FUNC_LINE, false);
										   }
										   else
										   {
											   AccessToken = FString([result token].tokenString);
											   bSuccess = true;
										   }

										   UE_LOG(LogPsFacebookMobile, Warning, TEXT("%s: FacebookLoginCompleted: %d, AccessToken: %s"), *PS_FUNC_LINE, true, *AccessToken);
										   DispatchFacebookLoginCompletedEvent(bSuccess, AccessToken);
										 }];
	  }
	  else
	  {
		  FString AccessToken([accessToken tokenString]);
		  UE_LOG(LogPsFacebookMobile, Warning, TEXT("%s: FacebookLoginCompleted: %d, AccessToken: %s"), *PS_FUNC_LINE, true, *AccessToken);
		  DispatchFacebookLoginCompletedEvent(true, AccessToken);
	  }
	});
#else
	SuccessCallback.ExecuteIfBound(false, TEXT(""));
#endif
}

void UPsFacebookMobileLibrary::FacebookLogout()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FacebookLogout", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#elif PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
	  if ([FBSDKAccessToken currentAccessToken])
	  {
		  FBSDKLoginManager* loginManager = [[FBSDKLoginManager alloc] init];
		  [loginManager logOut];
	  }
	});
#endif
}

bool UPsFacebookMobileLibrary::IsLoggedIn()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FacebookIsLoggedIn", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#elif PLATFORM_IOS

#endif

	return false;
}

void UPsFacebookMobileLibrary::DispatchFacebookLoginCompletedEvent(bool bSuccess, const FString& AccessToken)
{
	AsyncTask(ENamedThreads::GameThread, [bSuccess, AccessToken]() {
		UE_LOG(LogPsFacebookMobile, Warning, TEXT("%s: FacebookLoginCompleted: %d, AccessToken: %s"), *PS_FUNC_LINE, bSuccess, *AccessToken);
		UPsFacebookMobileLibrary::LoginCompleted.ExecuteIfBound(bSuccess, AccessToken);
	});
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_pushkinstudio_PsFacebookMobile_PsFacebookMobile_nativeFacebookLoginCompleted(JNIEnv* jenv, jobject thiz, jboolean bSuccess, jstring token)
{
	FString AccessToken;
	if (bSuccess)
	{
		const char* charsToken = jenv->GetStringUTFChars(token, 0);
		AccessToken = FString(UTF8_TO_TCHAR(charsToken));
		jenv->ReleaseStringUTFChars(token, charsToken);
	}

	UPsFacebookMobileLibrary::DispatchFacebookLoginCompletedEvent(bSuccess, AccessToken);
}
#endif // PLATFORM_ANDROID
