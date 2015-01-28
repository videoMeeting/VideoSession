//
//  ServerSettingViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-3-13.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ServerSettingViewController : UIViewController<UITextFieldDelegate>
{
    UITextField *iP;
    UITextField *port;
    UILabel *label;
}

@property (retain, nonatomic)IBOutlet UITextField *iP;
@property (retain, nonatomic)IBOutlet UITextField *port;
@property (retain,nonatomic)UILabel *label;
-(IBAction)textfiledchangeIP:(id)sender;
-(BOOL) checkip:(NSString*)ip;
-(IBAction)btSave:(id)sender;
-(IBAction)btBack:(id)sender;
-(void)Alert:(NSString*) result message:(NSString*) message;
@end
