//
//  LoginViewController.h
//  ScoPlayer
//
//  Created by user on 12-7-12.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#include"LoginServer.h"
@class AnimationViewController;
@class ConfigViewController;
@class AppDelegate;
@class ServerSettingViewController;
@class RegistrationViewController;

@interface LoginViewController : UIViewController<IMLoginInfo,UITextFieldDelegate>
{   
    UITextField *userName;
    UITextField *passWord;
    NSString *iP;
    UILabel *loginInfo;
    UITabBarController *tabBarController;
    UINavigationController * navigationController;
    ConfigViewController *configViewController;
    ServerSettingViewController *serverSettingViewController;
    RegistrationViewController* pRegistrationViewController;
    LoginServer *pLoginServer;
    bool isRemember;
    UIButton *BtRemember;
    UILabel *label;
    AppDelegate *appDelegate ;
    unsigned int ierrorid;
    AnimationViewController *animationViewController;
    NSTimer                 *mNSTimer;
    NSTimer                 *mMainNSTimer;
}
@property (retain, nonatomic)UILabel *label;
@property (retain, nonatomic)UITabBarController *tabBarController;
@property (retain, nonatomic)UINavigationController * navigationController;
@property (retain, nonatomic)ConfigViewController *configViewController;
@property (retain, nonatomic)ServerSettingViewController *serverSettingViewController;
@property (retain, nonatomic)RegistrationViewController *pRegistrationViewController;
@property (retain, nonatomic)IBOutlet UISwitch *iSwitch;
@property (retain, nonatomic)IBOutlet UILabel *loginInfo;
@property (retain, nonatomic)IBOutlet UITextField *userName;
@property (retain, nonatomic)IBOutlet UITextField *passWord;
@property (retain, nonatomic) NSString *iP;
@property (retain, nonatomic)IBOutlet UIButton *BtRemember;
@property (retain, nonatomic)AnimationViewController *animationViewController;
-(BOOL) checkip:(NSString*)ip;
-(void) Alert:(NSString*)result message:(NSString*) message;
-(IBAction) btLogin:(id)sender;
-(IBAction) textfiledchangeUserName:(id)sender;
-(IBAction) textfiledchangePassWord:(id)sender;
-(IBAction) btConfig:(id)sender;
-(IBAction) btRemember:(id)sender;
-(void) AllResignFirstResponder;

-(void)ServerConnectingOutTime:(id)mid;
-(void)ConnectingServer:(id)mid;
//-(void)ConnectingDerverFailed:(id)mid;
-(void)DisconnectedServer:(id)mid;
-(void)ConnectServer:(id)mid;
-(void)ConnectServerBusy:(id)mid;
-(void)ReconnectedServer:(id)mid;
-(void)ServerLogin:(id)mid;
-(void)ServerLoginFailed:(id)mid;
-(void)ServerLoginGetUserGrop:(id)mid;
-(void)ServerLoginGetFriend:(id)mid;
-(void)ServerLoginGetUserInfo:(id)mid;
-(void)ServerLoginEnd:(id)mid;
-(IBAction)btSetting:(id)sender;
-(IBAction)btRegistration:(id)sender;
-(double)availableMemory;

@end
