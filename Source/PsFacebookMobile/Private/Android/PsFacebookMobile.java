// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

package com.pushkinstudio.PsFacebookMobile;

import com.epicgames.ue4.GameActivity;

import com.facebook.FacebookSdk;
import com.facebook.appevents.AppEventsLogger;
import com.facebook.AccessToken;
import com.facebook.CallbackManager;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.text.TextUtils;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.lang.String;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public class PsFacebookMobile
{
    public native void nativeFacebookLoginCompleted(boolean bSuccess, String token);

    private GameActivity _activity;
    private CallbackManager _callbackManager;

    private static final String LOGTAG = "UE4-PS-FACEBOOK";

    public PsFacebookMobile(GameActivity activity) 
    {
        Log.d(LOGTAG, "Init");

        _activity = activity;
        _callbackManager = CallbackManager.Factory.create();
    }

    public boolean onActivityResult(int requestCode, int resultCode, Intent data)
    {
        return _callbackManager.onActivityResult(requestCode, resultCode, data);
    }

    public boolean Login(String LoginPermissions)
    {
        Log.d(LOGTAG, "Login: " + LoginPermissions);

        try
        {
            AccessToken accessToken = AccessToken.getCurrentAccessToken();
            if (accessToken == null || accessToken.isExpired())
            {
                LoginManager.getInstance().registerCallback(
                    _callbackManager,
                    new FacebookCallback<LoginResult>()
                    {
                        @Override
                        public void onSuccess(LoginResult loginResult)
                        {
                            Log.d(LOGTAG, "Login Success");
                            nativeFacebookLoginCompleted(true, AccessToken.getCurrentAccessToken().getToken());
                        }

                        @Override
                        public void onCancel()
                        {
                            Log.d(LOGTAG, "Login Cancel");
                            nativeFacebookLoginCompleted(false, "");
                        }

                        @Override
                        public void onError(FacebookException e)
                        {
                            Log.d(LOGTAG, "Login Error: " + e.toString());
                            nativeFacebookLoginCompleted(false, "");
                        }
                    }
                );

                HashSet<String> loginPermissions = new HashSet(Arrays.asList(TextUtils.split(LoginPermissions, ",")));
                LoginManager.getInstance().logIn(_activity, loginPermissions);
            }
            else
            {
                Log.d(LOGTAG, "User is already logged in");
                nativeFacebookLoginCompleted(true, accessToken.getToken());
            }

            return true;
        }
        catch (Exception e)
        {
            Log.d(LOGTAG, e.toString());
        }

        nativeFacebookLoginCompleted(false, "");
        return false;
    }

    public boolean Logout()
    {
        Log.d(LOGTAG, "Logout");

        try
        {
            LoginManager.getInstance().logOut();
            return true;
        }
        catch (Exception e)
        {
            Log.d(LOGTAG, "Logout Error: " + e.toString());
        }

        return false;
    }

    public boolean IsLoggedIn()
    {
        AccessToken accessToken = AccessToken.getCurrentAccessToken();
        return accessToken != null && !accessToken.isExpired();
    }
}
