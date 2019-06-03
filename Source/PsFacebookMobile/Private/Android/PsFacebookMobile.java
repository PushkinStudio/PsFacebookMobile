// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

package com.pushkinstudio.PsFacebookMobile;

import com.epicgames.ue4.GameActivity;

import com.facebook.FacebookSdk;
import com.facebook.appevents.AppEventsLogger;
import com.facebook.CallbackManager;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

public class PsFacebookMobile
{
	public native void nativeFacebookLoginCompleted(boolean bSuccess, String token);
	public native void nativeFacebookLogoutCompleted(boolean bSuccess);

	private GameActivity mActivity;

	public CallbackManager mCallbackManager;

	public PsFacebookMobile(GameActivity activity) 
	{
		mActivity = activity;

		FacebookSdk.sdkInitialize(mActivity.getApplicationContext());
        AppEventsLogger.activateApp(mActivity);

        mCallbackManager = CallbackManager.Factory.create();
	}

	public boolean onActivityResult(int requestCode, int resultCode, Intent data)
	{
		return mCallbackManager.onActivityResult(requestCode, resultCode, data);
	}
}
