//
//  AppDelegate.h
//  VideoSession
//
//  Created by zhangxm on 13-1-7.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
@class LoginViewController;
@class UISubTabBarController;
@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    UISubTabBarController *tabBarController;
    LoginViewController* loginviewController;
    NSString *userId;
}
@property (strong, nonatomic) UIWindow *window;
@property (retain, nonatomic)LoginViewController* loginviewController;
@property (retain, nonatomic)UISubTabBarController *tabBarController;
@property (retain, nonatomic)NSString *userId;
@end
