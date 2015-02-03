//
//  GroupUserViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include"LoginServer.h"
#import "MBProgressHUD.h"

@interface GroupUserViewController : UIViewController<UITableViewDelegate,UITableViewDataSource>
{
    UITableView    *tableview;
    NSMutableArray *ContactArr;
    LoginServer    *pLoginServer;
    NSString       *groupname;
    NSString       *savegroupname;
    MBProgressHUD  *m_pMBProgressHUD;
    NSTimer        *mNSTimer;
}
@property(retain)IBOutlet UITableView *tableview;
@property(retain) NSMutableArray      *ContactArr;
@property(retain,nonatomic)NSString   *groupname;
@property(retain,nonatomic)NSString   *savegroupname;
-(void) runTimer:(id)timer;
-(void) UpdateUser;
@end
