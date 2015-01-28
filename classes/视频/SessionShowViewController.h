//
//  SessionShowViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-9.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#include "LoginServer.h"
#include "OpenLocalUser.h"
#include "OpenRemoteUser.h"
#import <UIKit/UIKit.h>
#import "initAudio.h"
#import "MBProgressHUD.h"
#import "VideoAndVoiceViewController.h"
#import "SessionChatViewController.h"
#import "iOSGLView.h"
#import "VideoViewController.h"

@class SessionInfoViewController;

struct ScreenControlinfo
{
    bool        bIsOpenVideo;
    std::string strUserID;
    iOSGLView *pvideoWindow;
    bool        bIsTurn;
};

typedef std::map<unsigned int, ScreenControlinfo*> SCREENCONTROLINFOMAP;

typedef std::map<std::string, OpenRemoteUser*> OPENREMOTEUSERMAP;
typedef enum SCREEN_TYPE
{
    btSplitScreen1 ,
    btSplitScreen2 ,
    btSplitScreen4 ,
    toucvideoWindow1,
    toucvideoWindow2,
    toucvideoWindow3,
    toucvideoWindow4
} SCREEN_TYPE;

@class VideoSessionViewController;
@class AppDelegate;
@class InviteGroupsViewController;
@interface SessionShowViewController : UIViewController<MMGetRoomControl>
{
    bool       m_Is5Window;
   UILabel *lable1;
    UILabel *lable2;
    UILabel *lable3;
    UILabel *lable4;
    
    LoginServer *pLoginServer;
    OpenLocalUser* pOpenLocalUser;
    OPENREMOTEUSERMAP OpenRemoteUserMap;
    SCREENCONTROLINFOMAP ScreenControlinfoMap;
    InviteGroupsViewController *inviteGroupsViewController;
    initAudio *minitAudio;
    UIView *splitView;
    UIView *InviteView;
    int spliteType;
    CGRect oldFrame;
    int length;
    int height;
    int xpos;
    int ypos;
    int subImageViewPosy;
    int subImageViewDis;
    int subheight;
    int sublength;
    unsigned int uiCount;
    bool splite;
    bool soundOff;
    bool isHiddenbtSplit;
    bool isHiddenInviteView;
    std::string strPeerUserID;
    std::string mstrFromUserID;
    std::string strSpeekUserID;
    unsigned int m_uiScreenControl;
    AppDelegate* appDelegate;
    long roomId;
    unsigned int uiScreenNum;
    VideoSessionViewController  *videoSessionViewController;
    VideoAndVoiceViewController *videoAndVoiceViewController;
    SessionChatViewController   *sessionChatViewController;
    SessionInfoViewController   *sessionInfoViewController;
    VideoViewController*        pVideoViewController;
    unsigned int uiRoomVideoType;
    unsigned int uiRoomAudioType;
    unsigned int uiMyScreenCount;
    UIToolbar *toolbar;
    bool isSoundOff;
    UIButton *btSoundOffBbutton;
    UIButton *btRefreshBbutton;
    UIButton *btSwitchCamera;
    UIButton*btSplitView;
    UIButton *btAddUser;
    bool fullScreen;
    SCREEN_TYPE fullScreenType;
    UIButton *btUserList;
    UIButton *btCharacter;
    UIButton *btFullScreen;
    UIButton *btManage;
    MBProgressHUD              *m_pMBProgressHUD;
    NSTimer                    *mNSTimer;
    NSTimer                    *mEnterRoomNSTimer;
    bool                       bIsEnterRoom;
    bool                       IsFrontVideo;
    std::string                strReplyInviteUser;
    std::string                strUserMsg;
    OpenRemoteUser*            m_pOpenRemoteUser;
    int                        m_CloseNum;
    UIAlertView                *QiutRoomalert;
    UIAlertView                *ForTheFloor;
    bool isstop;
    unsigned short             mCount;
}
@property(nonatomic)SCREEN_TYPE fullScreenType;
@property(nonatomic)bool fullScreen;
@property(retain,nonatomic)IBOutlet UIView *splitView;
@property(retain,nonatomic)IBOutlet UIView *InviteView;
@property(retain,nonatomic)IBOutlet UIToolbar *toolbar;
@property(retain,nonatomic) IBOutlet iOSGLView *videoWindow1;
@property(retain,nonatomic) IBOutlet iOSGLView *videoWindow2;
@property(retain,nonatomic) IBOutlet iOSGLView *videoWindow3;
@property(retain,nonatomic) IBOutlet iOSGLView *videoWindow4;

@property(retain,nonatomic)IBOutlet UIImageView *videoWindow5;

@property(retain,nonatomic)IBOutlet UILabel *lable1;
@property(retain,nonatomic)IBOutlet UILabel *lable2;
@property(retain,nonatomic)IBOutlet UILabel *lable3;
@property(retain,nonatomic)IBOutlet UILabel *lable4;

@property(nonatomic)bool isSoundOff;
@property(nonatomic)OPENREMOTEUSERMAP OpenRemoteUserMap;
 
@property(retain,nonatomic)UIButton *btSoundOffBbutton;
@property(retain,nonatomic)UIButton *btRefreshBbutton;
@property(retain,nonatomic)UIButton *btSwitchCamera;
@property(retain,nonatomic)UIButton *btSplitView;
@property(retain,nonatomic)UIButton *btAddUser;
@property(retain,nonatomic)UIButton *btUserList;
@property(retain,nonatomic)UIButton *btCharacter;
@property(retain,nonatomic)UIButton *btFullScreen;
@property(retain,nonatomic)UIButton *btManage;
@property(nonatomic)unsigned int uiRoomVideoType;
@property(nonatomic)unsigned int uiRoomAudioType;
@property(assign,nonatomic)VideoAndVoiceViewController *videoAndVoiceViewController;
@property(assign,nonatomic)VideoSessionViewController *videoSessionViewController;
@property(assign,nonatomic)InviteGroupsViewController *inviteGroupsViewController;
@property(assign,nonatomic)SessionChatViewController   *sessionChatViewController;
@property(assign,nonatomic)SessionInfoViewController   *sessionInfoViewController;
@property(assign,nonatomic)VideoViewController         *pVideoViewController;
@property(assign,nonatomic)UISubNavigationController         *sessionShowNavCtrl;
-(void)toucvideoWindow1:(id)sender;
-(void)toucvideoWindow2:(id)sender;
-(void)toucvideoWindow3:(id)sender;
-(void)toucvideoWindow4:(id)sender;

-(void)back;
-(IBAction)btSplitScreen1:(id)sender;
-(IBAction)btSplitScreen2:(id)sender;
-(IBAction)btSplitScreen4:(id)sender;
-(void)SplitScreen1;
-(void)SplitScreen2;
-(void)SplitScreen4;
-(void)splitScreen;
-(void)setLocalVideoWindow;
-(void)showButtons:(bool)isfullScreen;

-(IBAction)btVideoSession :(id)sender;
-(IBAction)btNetwork:(id)sender;
-(IBAction)btPhoneNumber:(id)sender;

-(void)RoomManagement;

-(void)ChairmanEnterRoom;
-(void)OrdinaryUserEnterRoom;
-(void)BroadcastRoomInfo:(const std::string&)strUserID;

-(void)PeerUserJoinTemporaryMeeting:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID;
-(void)PeerQuitInterimMeetingInfo:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID;
-(void)PeerDestructionInterimMeetingInfo;

-(void)User_OpenLocalVideo:(const std::string&)strUserID pView:(iOSGLView*) pView uiScreen:(unsigned int)uiScreen IsSendCommand:(bool)IsSendCommand IsSendData:(bool)IsSendData bIsBroadcast:(bool)bIsBroadcast;
-(void)User_CloseLocalVideo:(const std::string&)strUserID IsSendCommand:(bool)IsSendCommand bIsBroadcast:(bool)bIsBroadcast;
-(void)User_OpenLocalAudio:(const std::string&)strUserID IsSendData:(bool)IsSendData;
-(void)User_CloseLocalAudio:(const std::string&)strUserID;
-(void)User_OpenPeerVideo:(const std::string&)strPeerUserID pView:(iOSGLView*)pView uiScreen:(unsigned int)uiScreen bIsBroadcast:(bool)bIsBroadcast IsSendCommand:(bool)IsSendCommand;
-(void)User_ClosePeerVideo:(const std::string&)strPeerUserID IsSendCommand:(bool)IsSendCommand bIsBroadcast:(bool)bIsBroadcast;
-(void)User_OpenPeerAudio:(const std::string&)strPeerUserID;
-(void)User_ClosePeerAudio:(const std::string&)strPeerUserID;

-(void)User_OpenAllAudio;
-(void)User_CloseAllAudio;
-(void)User_OpenHostAllVideo;
-(void)User_CloseAllVideo;

-(void)MySetVideoMeetingType:(id)mid;
-(void)MySetAudioMeetingType:(id)mid;

-(iOSGLView*)GetWindow:(const std::string&)strUserID uiScreen:(unsigned int&)uiScreen IsSet:(bool)IsSet;
-(int)GetWindowScreen:(const std::string&)strUserID;
-(void)CloseWindow:(const std::string&)strUserID;
-(bool)IsHasVideoWindow;

-(void)InitializationTemporaryMeeting:(id)mid;
-(void)OpenUserVideo:(id)mid;
-(void)CloseUserVideo:(id)mid;
-(void)OpenUserAudio:(id)mid;
-(void)CloseUserAudio:(id)mid;

-(void)OnForTheFloor:(id)mid;
-(void)OnPassPrivileges:(id)mid;
-(void)OnUserSnedMsg:(id)mid;
-(void)OnUserReplyInviteUser:(id)mid;

-(void)SetMeetingType:(unsigned int)uiVideoType uiAudioType:(unsigned int)uiAudioType;
-(void)SetScreenControl:(id)mid;

//-(void)QuitTemporaryMeeting:(id)mid;
-(void)initButtons;
-(void)startAllVideo;
-(void)stopAllVideo;
-(void)Room_OpenVideo_Push;
-(void)Room_CloseVideo_Push;

-(void)Room_OpenVideo_Room;
-(void)Room_CloseVideo_Room;

-(void)Room_OpenAudio_Discuss_Speak;
-(void)Room_CloseAudio_Discuss_Speak;

-(bool)LocalUserIsOpenVideo;
-(bool)LocalUserIsOpenAudio;

-(bool)PeerUserIsOpenVideo:(std::string)strUserId;
-(bool)PeerUserISOpenAudio:(std::string)sreUserId;

-(void)UpdatedLocalVideo;

-(void)SetChatShow:(bool)bisShow;
-(void)SetControlShow:(bool)bisShow;

@end
