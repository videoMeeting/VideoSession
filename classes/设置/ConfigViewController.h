//
//   ConfigViewController.h
//  ScoPlayer
//
//  Created by user on 12-7-12.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ConfigViewController : UIViewController<UITextFieldDelegate>
{
    UITextField *serverIP; 
    UITextField *HTTPort;
    UITextField *HTTPSPort;
    UITextField *Account;
    UITextField *Password;
    UIButton * SaveButton;
    UILabel *label;
}


@property(retain,nonatomic)IBOutlet UITextField *serverIP; 
@property(retain,nonatomic)IBOutlet UITextField *HTTPort;
@property(retain,nonatomic)IBOutlet UITextField *HTTPSPort;
@property(retain,nonatomic)IBOutlet UITextField *Account;
@property(retain,nonatomic)IBOutlet UITextField *Password;
@property(retain,nonatomic) UILabel *label;
@property(retain,nonatomic)IBOutlet UIButton * SaveButton;
-(IBAction)textfiledchangeserverIP:(id)sender;
-(IBAction)textfiledchangeHTTPort:(id)sender;
-(IBAction)textfiledchangeHTTPSPort:(id)sender;
-(IBAction)textfiledchangeAccount:(id)sender;
-(IBAction)textfiledchangePassword:(id)sender;
-(IBAction)btSave:(id)sender;
-(IBAction)btBack:(id)sender;
- (BOOL) checkip:(NSString*)ip;
- (BOOL)isPureInt:(NSString *)string;
- (NSString *)dataFilePath;
-(void)initialData;
-(bool)saveLogInfo;
-(void)HideButton;
@end
