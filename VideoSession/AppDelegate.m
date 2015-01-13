//
//  AppDelegate.m
//  VideoSession
//
//  Created by zhangxm on 13-1-7.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "AppDelegate.h"
#import "VoiceViewController.h"
#import "VideoViewController.h"
#import "CallHistoryViewController.h"
#import "VideoAndVoiceViewController.h"
#import "MoreViewController.h"
#import "imageExtras.h"
#import "UISubTabBarController.h"

@implementation AppDelegate
@synthesize loginviewController;
@synthesize tabBarController;
@synthesize userId;
- (void)dealloc
{
    [_window release];
    [userId release];
    [tabBarController release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    
    self.tabBarController = [[[UISubTabBarController alloc] init]autorelease];
    
   
     VoiceViewController *voiceViewController = [[[VoiceViewController alloc] init]autorelease];
    UINavigationController *navVoice = [[[UINavigationController alloc] initWithRootViewController: voiceViewController]autorelease];
        [navVoice.navigationBar setHidden:YES];
    CGSize csize;
    csize.width=40;
    csize.height=40;
    [voiceViewController.tabBarItem setImage:[[UIImage imageNamed:@"语音tab"]imageByScalingToSize
                                            :csize]];
//    [voiceViewController.tabBarItem setFinishedSelectedImage:nil withFinishedUnselectedImage:[[UIImage imageNamed:@"语音tab"]imageByScalingToSize:csize ]];
    
    VideoViewController *videoViewController = [[[VideoViewController alloc] init]autorelease];
    UINavigationController *navVideo= [[[UINavigationController alloc] initWithRootViewController: videoViewController]autorelease];
    [navVideo.navigationBar setHidden:NO];
    
    [videoViewController.tabBarItem setImage:[[UIImage imageNamed:@"视频tab"]imageByScalingToSize:csize]];
//    [videoViewController.tabBarItem setFinishedSelectedImage:nil withFinishedUnselectedImage:[[UIImage imageNamed:@"视频tab"]imageByScalingToSize:csize]];
//    
    CallHistoryViewController *callHistoryViewController = [[[CallHistoryViewController alloc] init]autorelease];
    UINavigationController *navCallHistory= [[[UINavigationController alloc] initWithRootViewController: callHistoryViewController]autorelease];
    //[navCallHistory.navigationBar setHidden:YES];
    
    [callHistoryViewController.tabBarItem setImage:[[UIImage imageNamed:@"通话记录tab"]imageByScalingToSize:csize]];
//    [callHistoryViewController.tabBarItem setFinishedSelectedImage:nil withFinishedUnselectedImage:[[UIImage imageNamed:@"通话记录tab"]imageByScalingToSize:csize]];
//    callHistoryViewController.tabBarController=self.tabBarController;
    
    VideoAndVoiceViewController *settingViewController = [[[VideoAndVoiceViewController alloc] initWithNibName:@"VideoAndVoiceViewController" bundle:nil]autorelease];

    UINavigationController *navSetting= [[[UINavigationController alloc] initWithRootViewController: settingViewController]autorelease];
    [settingViewController setBackview1];
    settingViewController.tabBarController=self.tabBarController;
   // [navSetting.navigationBar setHidden:YES];
    [settingViewController.tabBarItem setImage:[[UIImage imageNamed:@"设置tab"]imageByScalingToSize:csize]];
//    [settingViewController.tabBarItem setFinishedSelectedImage:nil withFinishedUnselectedImage:[[UIImage imageNamed:@"设置tab"]imageByScalingToSize:csize]];
    
    
    MoreViewController *moreViewController = [[[MoreViewController alloc] initWithNibName:@"MoreViewController" bundle:nil]autorelease];
    
    UINavigationController *navmore= [[[UINavigationController alloc] initWithRootViewController: moreViewController]autorelease];
    //[settingViewController setBackview1];
    // [navSetting.navigationBar setHidden:YES];
    //[settingViewController.tabBarItem setImage:[[UIImage imageNamed:@"设置tab"]imageByScalingToSize:csize]];
   // [settingViewController.tabBarItem setFinishedSelectedImage:nil withFinishedUnselectedImage:[[UIImage imageNamed:@"设置tab"]imageByScalingToSize:csize]];
    
     
    
    NSArray* controllers = [NSArray arrayWithObjects:navVideo,navCallHistory,navSetting,navmore,nil];
    self.tabBarController.viewControllers = controllers;
    self.window.rootViewController = self.tabBarController; 
    [self.window addSubview:self.tabBarController.view];
  //  self.tabBarController.view.frame = [UIScreen mainScreen].applicationFrame;
    
    [self.window makeKeyAndVisible];
     
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}
 -(NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window{ return UIInterfaceOrientationMaskAll;}
@end
