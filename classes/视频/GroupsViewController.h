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

@class GroupUserViewController;
@interface GroupsViewController : UIViewController
{
    UITableView             *tableview;
    NSMutableArray          *GroupArray;
    GroupUserViewController *groupUserViewController;
    LoginServer             *pLoginServer;
    NSString                *savegroupname;
    MBProgressHUD           *m_pMBProgressHUD;
    NSTimer                 *mNSTimer;
}

@property(retain,nonatomic)IBOutlet UITableView    *tableview;
@property(retain,nonatomic)NSMutableArray          *GroupArray;
@property(retain,nonatomic)GroupUserViewController *groupUserViewController;
@property(retain,nonatomic)NSString                *savegroupname;

-(void)initData;
@end
