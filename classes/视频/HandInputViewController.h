//
//  HandInputViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include"LoginServer.h"

@interface HandInputViewController : UIViewController
{
    UITextField *account;
    UITextField *nickname;
    NSString    *groupname;
    LoginServer *pLoginServer;
}
@property(retain,nonatomic)IBOutlet UITextField *account;
@property(retain,nonatomic)IBOutlet UITextField *nickname;
@property(retain,nonatomic)NSString             *groupname;

-(void)Alert:(NSString*)result message:(NSString*) message;

@end
