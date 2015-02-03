//
//  SessionInfoViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-9.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include"LoginServer.h"
#import "SessionShowViewController.h"
#import "InviteGroupsViewController.h"
@class VideoSessionViewController;
@interface SessionInfoViewController : UIViewController<UITableViewDelegate,UIActionSheetDelegate,UITableViewDataSource>
{
    UIToolbar *toolbar;
    UIButton *btRefreshBbutton;
    
    UIButton *btAddUser;
    UITableView *tableview;
    NSMutableArray *roomUsrArray;
    LoginServer *pLoginServer;
    std::vector<ROOMUSERINFO> RoomUserList;
    VideoSessionViewController *videoSessionViewController;
    SessionShowViewController  *sessionShowViewController;
    UIActionSheet *actionSheetPower;
    UIActionSheet *actionSheetManageHasAAndV;
    UIActionSheet *actionSheetManageHasA;
    UIActionSheet *actionSheetManageHasV;
    UIActionSheet *actionSheetManage;
    UIActionSheet *actionSheetattachUser;
    UIActionSheet *actionInviteUsers;
    std::string   strSelectUserID;
    int           iReturnNum;
    MBProgressHUD              *m_pMBProgressHUD;
    NSTimer                    *mNSTimer;
    InviteGroupsViewController *inviteGroupsViewController;
    unsigned int               m_videoSessionID;
}

@property(assign,nonatomic)InviteGroupsViewController *inviteGroupsViewController;
@property( nonatomic,retain)UIButton *btRefreshBbutton;
@property( nonatomic,retain)UIButton *btAddUser;
@property( nonatomic,retain)IBOutlet UIToolbar *toolbar;
@property( nonatomic,retain)IBOutlet UITableView *tableview;
@property( nonatomic,retain)NSMutableArray *roomUsrArray;
@property( nonatomic,retain)UIActionSheet *actionSheetPower;
@property( nonatomic,retain)UIActionSheet *actionSheetManageHasAAndV;
@property( nonatomic,retain)UIActionSheet *actionSheetManageHasA;
@property( nonatomic,retain)UIActionSheet *actionSheetManageHasV;
@property( nonatomic,retain)UIActionSheet *actionSheetManage;
@property( nonatomic,retain)UIActionSheet *actionSheetattachUser;
@property( nonatomic,retain)UIActionSheet *actionInviteUsers;
@property( nonatomic)unsigned int         m_videoSessionID;
@property(assign,nonatomic)VideoSessionViewController *videoSessionViewController;
@property(assign,nonatomic)SessionShowViewController  *sessionShowViewController;
-(void)changePower:(std::string)index;

-(void) MyUpdateMeetingInfo:(id)mid;
-(void) initToolBar;
-(void) RoomUserEnvet:(int)iCount;
-(void) RoomHostEnevt:(int)iCount;

@end
