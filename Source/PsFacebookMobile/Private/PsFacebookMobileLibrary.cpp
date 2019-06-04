// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "PsFacebookMobileLibrary.h"

#include "PsFacebookMobile.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android_native_app_glue.h>
#endif // PLATFORM_ANDROID

UPsFacebookMobileLibrary::UPsFacebookMobileLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPsFacebookMobileLibrary::FacebookLogin(const FString& LoginPermissions)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring LoginPermissionsJava = Env->NewStringUTF(TCHAR_TO_UTF8(*LoginPermissions));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FacebookLogin", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, LoginPermissionsJava);
		Env->DeleteLocalRef(LoginPermissionsJava);
	}
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
#endif

	return false;
}
