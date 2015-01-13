//
//  ExitGroupViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include"LoginServer.h"
#import "MBProgressHUD.h"

@class InviteGroupUserViewController;
@interface InviteGroupsViewController : UIViewController
{
    UITableView             *tableview;
    NSMutableArray          *GroupArray;
    InviteGroupUserViewController *groupUserViewController;
    LoginServer             *pLoginServer;
    NSString                *savegroupname;
    MBProgressHUD           *m_pMBProgressHUD;
    NSTimer                 *mNSTimer;
}

@property(retain,nonatomic)IBOutlet UITableView    *tableview;
@property(retain,nonatomic)NSMutableArray          *GroupArray;
@property(retain,nonatomic)InviteGroupUserViewController *groupUserViewController;
@property(retain,nonatomic)NSString                *savegroupname;

-(void)initData;
@end
