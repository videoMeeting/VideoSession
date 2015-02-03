//
//  VideoViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include"LoginServer.h"
#import "MBProgressHUD.h"
#import "IntoVessionViewController.h"
@class LoginViewController;
@class VideoSessionViewController;
@class CallViewController;
@class EditGroupViewController;
@class UISubNavigationController;
@interface VideoViewController : UIViewController<IMGetUserGroupInfo,MMMeetingProtocol,UITableViewDelegate,UITableViewDataSource>
{
    std::string             m_strHostId;
    unsigned long           m_ulRoomID;
    unsigned long           m_uiRoomType;
    ENTERMEETINGUSER        m_lEnterUser;
    LoginServer             *pLoginServer;
    CallViewController      *callViewController;
    UILabel                 *numlabel;
    UITableView             *tableview;
    NSMutableArray          *GroupArray;
    UIImageView             *backImageView;
    EditGroupViewController *editGroupViewController;
    bool                    isEditGroup;
    UIBarButtonItem         *leftBtn;
    MBProgressHUD           *m_pMBProgressHUD;
    NSTimer                 *mNSTimer;
    VideoSessionViewController *videoSessionViewController;
    std::string             mstrUserID;
    unsigned long           mulRoomID;
  
    bool                    isCallUser;
    bool                    CallViewIsOpen;
    UIAlertView*            editGroup;
    NSString*               m_oldgroupname;

}
@property(retain,nonatomic) UISubNavigationController *nalginController;
@property(retain,nonatomic) IntoVessionViewController  *pIntoVessionViewController;
@property(retain,nonatomic) LoginViewController *loginViewController;
@property(retain,nonatomic) UIView* activityView;
@property(retain,nonatomic) UIActivityIndicatorView *activityWheel;
@property(retain,nonatomic)CallViewController         *callViewController;
@property(retain,nonatomic)IBOutlet UILabel           *numlabel;
@property(retain,nonatomic)IBOutlet UITableView       *tableview;
@property(retain,nonatomic)NSMutableArray             *GroupArray;
@property(retain,nonatomic)IBOutlet UIImageView       *backImageView;
@property(retain,nonatomic)EditGroupViewController    *editGroupViewController;
@property(retain,nonatomic)UIBarButtonItem            *leftBtn;
@property(retain,nonatomic)VideoSessionViewController *videoSessionViewController;
 
-(void)EditGroup:(NSString*)groupName;
-(IBAction)btCallFriends:(id)sender;
//-(void)EnterInterimMeetingInfo:(id)mid;
//-(void)QuitInterimMeetingInfo:(id)mid;
-(void)MyInsertGroup:(id)mid;
-(void)OnDeleteGrop:(id)mid;
-(void)MyUpdateGroup:(id)mid;
-(void)runTimer:(id)timer;
-(void)Alert:(NSString*) result message:(NSString*) message;
-(void)MyCreateInterimMeeting:(id)mid;
-(void)MyInHostInviteUser:(id)mid;
-(void)MyEnterInterimMeetingInfo:(id)mid;
-(void)MyDestructionInterimMeetingInfo:(id)mid;
-(void)MyQuitInterimMeetingInfo:(id)mid;
-(void)MyJoinTemporaryMeeting:(id)mid;
-(void)MyPleaseOutTemporaryMeeting:(id)mid;
-(void)HostEnterRoomBegin;
-(void)HostEnterRoomEnd;
-(void)CallInviteAllUser_EnterRoomEnd;
@end
