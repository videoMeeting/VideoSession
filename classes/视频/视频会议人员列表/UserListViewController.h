//
//  CallViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include"LoginServer.h"
@class AppDelegate;
@interface UserListViewController : UIViewController<UITableViewDelegate,UITableViewDataSource>
{
    UIToolbar *toolBar;
    UITableView *tableview;
    NSMutableArray *ContactArr;
    LoginServer *pLoginServer;
    std::string  m_strUserId;
    UIImageView *imageBg;
    
    unsigned long ulRoomID;
}
@property( retain)IBOutlet UIToolbar *toolBar;
@property( retain)IBOutlet UITableView *tableview;
@property( retain) NSMutableArray *ContactArr;
@property( retain)IBOutlet UIImageView *imageBg;
-(unsigned long)TimeGetTimestamp;
-(void) UpdateUser;
-(void) OnAddUserInfo:(id)mid;
-(void) OnDeleteUserInfo:(id)mid;


@end
