//
//  CallViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include"LoginServer.h"
#import "MBProgressHUD.h"
#import "VideoViewController.h"

@class HandInputViewController;
@class AppDelegate;
#import "MyUILongPressGestureRecognizer.h"

@interface CallViewController : UIViewController<IMGetUserFriendInfo,UITableViewDelegate,UITableViewDataSource>
{
    UIToolbar                  *toolBar;
    UITableView                *tableview;
    NSMutableArray             *ContactArr;
    LoginServer                *pLoginServer;
    std::string                m_strUserId;
    unsigned long              ulRoomID;
    HandInputViewController    *handInputViewController;
    NSString                   *strGroupName;
    MBProgressHUD              *m_pMBProgressHUD;
    NSTimer                    *mNSTimer;
    VideoViewController        *pVideoViewController;
    UIAlertView                *DeleteUseralert;
    NSString                   *deleteUserID;
}

@property(retain)IBOutlet UIToolbar                   *toolBar;
@property(retain)IBOutlet UITableView                 *tableview;
@property(retain)NSMutableArray                       *ContactArr;
@property(retain,nonatomic)HandInputViewController    *handInputViewController;
@property(retain,nonatomic)NSString                   *strGroupName;
@property(retain,nonatomic)VideoViewController        *pVideoViewController;

-(unsigned long)TimeGetTimestamp;
-(void) UpdateUser;

//-(void) MyCreateInterimMeeting:(id)mid;
//-(void) EnterInterimMeetingInfo:(id)mid;
//-(void) QuitInterimMeetingInfo:(id)mid;

-(void)CallInviteAllUser;

-(void) MyFriendAdd:(id)mid;
-(void) MyFriendDelete:(id)mid;
-(void) MyFriendOnLine:(id)mid;
-(void) MyFriendOffline:(id)mid;
-(void) MyFriendEnterInterimMeeting:(id)mid;
-(void) MyFriendQuitInterimMeeting:(id)mid;

-(void) runTimer:(id)timer;

@end
