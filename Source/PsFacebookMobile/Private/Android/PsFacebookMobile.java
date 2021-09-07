// Copyright 2015-2021 Mail.Ru Group. All Rights Reserved.

package com.pushkinstudio.PsFacebookMobile;

import com.epicgames.ue4.GameActivity;

import com.facebook.FacebookSdk;
import com.facebook.appevents.AppEventsConstants;
import com.facebook.appevents.AppEventsLogger;
import com.facebook.AccessToken;
import com.facebook.CallbackManager;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.text.TextUtils;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.lang.String;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Currency;
import java.math.BigDecimal;

public class PsFacebookMobile
{
    public native void nativeFacebookLoginCompleted(boolean bSuccess, String token);

    private static GameActivity _activity;
    private static CallbackManager _callbackManager;
    private static AppEventsLogger _logger;

    private static final String LOGTAG = "UE4-PS-FACEBOOK";

    public PsFacebookMobile(GameActivity activity) 
    {
        Log.d(LOGTAG, "Init");

        _activity = activity;
        _callbackManager = CallbackManager.Factory.create();
        _logger = AppEventsLogger.newLogger(_activity);
    }

    public void Initialize()
    {
        Log.d(LOGTAG, "Init Facebook SDK manager");
        // @TODO Refactor plugin to use only static methods and move constructor here
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

    public void SetAutoLogAppEventsEnabled(boolean bEnabled)
    {
        FacebookSdk.setAutoLogAppEventsEnabled(bEnabled);
    }

    public void SetAdvertiserTrackingEnabled(boolean bEnabled)
    {
        FacebookSdk.setAdvertiserIDCollectionEnabled(bEnabled);
    }
    
    static public boolean LogPurchase(float InPrice, String InCurrency, String InSku)
    {
       Bundle params = new Bundle();
       params.putString(AppEventsConstants.EVENT_PARAM_CONTENT_ID, InSku);

       try {
           _logger.logPurchase(new BigDecimal(Float.toString(InPrice)), Currency.getInstance(InCurrency), params);
           return true;
       }
       catch (Exception e) {
           Log.e(LOGTAG, "LogPurchase (" + InPrice + ") (" + InCurrency + ") (" + InSku + ") Error: " + e.toString());
       }

       return false;
    }
}
