// Copyright 2015-2022 MY.GAMES. All Rights Reserved.

#pragma once

#if PLATFORM_IOS
@interface FacebookObserver : NSObject
+ (FacebookObserver *)sharedInstance;
- (void)didFinishLaunching:(NSNotification *)notification;
@end
#endif // PLATFORM_IOS
