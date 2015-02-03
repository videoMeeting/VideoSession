//
//  ServerSettingViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-3-13.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "UserRegistration.h"
#import "MBProgressHUD.h"

@interface RegistrationViewController : UIViewController<UITextFieldDelegate ,RegistrationInfo>
{
    UITextField *iP;
    UITextField *port;
    UILabel *label;
    
    UITextField* UserID;
    UITextField* Password;
    UITextField* Nickname;
    UITextField* Phone;
    UITextField* Remark;
    
    UITextField* DeleteUserId;
    UITextField* DeletePassword;
    UserRegistration* pUserRegistration;
    int ierrorid;
    MBProgressHUD           *m_pMBProgressHUD;
}

@property (retain, nonatomic)IBOutlet UITextField* UserID;
@property (retain, nonatomic)IBOutlet UITextField* Password;
@property (retain, nonatomic)IBOutlet UITextField* Nickname;
@property (retain, nonatomic)IBOutlet UITextField* Phone;
@property (retain, nonatomic)IBOutlet UITextField* Remark;

@property (retain, nonatomic)IBOutlet UITextField* DeleteUserId;
@property (retain, nonatomic)IBOutlet UITextField* DeletePassword;

@property (retain, nonatomic)IBOutlet UITextField *iP;
@property (retain, nonatomic)IBOutlet UITextField *port;
@property (retain,nonatomic)UILabel *label;
-(IBAction)textfiledchangeIP:(id)sender;
-(BOOL) checkip:(NSString*)ip;
-(IBAction)btSave:(id)sender;
-(IBAction)btBack:(id)sender;
-(IBAction)AddUser:(id)sender;
-(IBAction)DeleteUser:(id)sender;

- (BOOL)validateNumber:(NSString*)number;
-(void)Alert:(NSString*) result message:(NSString*) message;

-(void)AddUserAndDeleteUserInfo:(id)mid;
-(void) AllResignFirstResponder;

@end
