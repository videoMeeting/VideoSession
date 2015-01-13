//
//  CallHistoryViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MBProgressHUD.h"
#import "UISubTabBarController.h"
#include "LoginServer.h"

@interface CallHistoryViewController : UIViewController<UITableViewDataSource,UITableViewDelegate>
{
    UITableView             *historyTable;
    NSMutableArray          *historyArray;
    MBProgressHUD           *m_pMBProgressHUD;
    NSTimer                 *mNSTimer;
    UISubTabBarController *tabBarController;
    LoginServer *pLoginServer;
}
@property(retain,nonatomic)IBOutlet UITableView *historyTable;
@property(retain,nonatomic) NSMutableArray *historyArray;
@property(assign,nonatomic)UISubTabBarController *tabBarController;
@end
