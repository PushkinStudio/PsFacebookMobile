// Copyright 2015-2023 MY.GAMES. All Rights Reserved.

#include "FacebookMobile.h"

#if PLATFORM_IOS && WITH_PSFACEBOOKMOBILE
#include "IOS/IOSAppDelegate.h"

// clang-format off
#import <SafariServices/SafariServices.h>
#import <AuthenticationServices/AuthenticationServices.h>
#import <FBSDKCoreKit/FBSDKCoreKit-Swift.h>
// clang-format on

@implementation FacebookObserver

static FacebookObserver* FacebookObserverInstance = nil;

- (id)init
{
	self = [super init];
	return self;
}

+ (void)load
{
	[super load];

	if (FacebookObserverInstance == nil)
	{
		FacebookObserverInstance = [[FacebookObserver alloc] init];
		[FacebookObserverInstance registerLifeCycleListener];
	}
}

+ (FacebookObserver*)sharedInstance
{
	if (FacebookObserverInstance == nil)
	{
		[FacebookObserver load];
	}

	return FacebookObserverInstance;
}

- (void)registerLifeCycleListener
{
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(didFinishLaunching:)
												 name:UIApplicationDidFinishLaunchingNotification
											   object:nil];
}

- (void)didFinishLaunching:(NSNotification*)notification
{
	[[FBSDKApplicationDelegate sharedInstance] application:[UIApplication sharedApplication]
							 didFinishLaunchingWithOptions:[IOSAppDelegate GetDelegate].launchOptions];
}

@end

#endif // PLATFORM_IOS && WITH_PSFACEBOOKMOBILE
