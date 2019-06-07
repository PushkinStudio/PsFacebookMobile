// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "FacebookMobile.h"

#if PLATFORM_IOS

#import <FBSDKCoreKit/FBSDKCoreKit.h>

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
		FacebookObserverInstance = [[FacebookObserverInstance alloc] init];
		[FacebookObserverInstance registerLifeCycleListener];
	}
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
	[[FBSDKApplicationDelegate sharedInstance] application:application
							 didFinishLaunchingWithOptions:launchOptions];
}

@end

#endif // PLATFORM_IOS
