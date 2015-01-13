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

@interface InviteGroupUserViewController : UIViewController<IMGetUserFriendInfo,UITableViewDelegate,UITableViewDataSource>
{
    UITableView    *tableview;
    NSMutableArray *ContactArr;
    LoginServer    *pLoginServer;
    NSString       *groupname;
    NSString       *savegroupname;
    MBProgressHUD  *m_pMBProgressHUD;
    NSTimer        *mNSTimer;
    std::string    m_strUserId;
}
@property(retain)IBOutlet UITableView *tableview;
@property(retain) NSMutableArray      *ContactArr;
@property(retain,nonatomic)NSString   *groupname;
@property(retain,nonatomic)NSString   *savegroupname;
-(void) runTimer:(id)timer;
-(void) UpdateUser;

//-(void) MyCreateInterimMeeting:(id)mid;
//-(void) EnterInterimMeetingInfo:(id)mid;
//-(void) QuitInterimMeetingInfo:(id)mid;

-(void) MyFriendAdd:(id)mid;
-(void) MyFriendDelete:(id)mid;
-(void) MyFriendOnLine:(id)mid;
-(void) MyFriendOffline:(id)mid;
-(void) MyFriendEnterInterimMeeting:(id)mid;
-(void) MyFriendQuitInterimMeeting:(id)mid;
@end
