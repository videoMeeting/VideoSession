//
//  SessionShowViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-9.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "SessionShowViewController.h"
#import "VideoSessionViewController.h"
#import "AppDelegate.h"
#include "SessionInfo.h"
#import "InviteGroupsViewController.h"
#import "SessionControlViewController.h"
#import "UserListViewController.h"
#import "ImageExtras.h"
#import "sys/utsname.h"
#import "VideoAndVoiceViewController.h"
#import "SessionInfoViewController.h"
#include "VideoAndAudioSet.h"
#import "UISubLRNavgationViewController.h"
#import "Custom.h" 

@interface SessionShowViewController ()

@end

@implementation SessionShowViewController
 
 
@synthesize lable1;
@synthesize lable2;
@synthesize lable3;
@synthesize lable4;
@synthesize fullScreenType;
@synthesize fullScreen;
@synthesize splitView;
@synthesize InviteView;
@synthesize toolbar;
@synthesize videoSessionViewController;
@synthesize inviteGroupsViewController;
@synthesize isSoundOff;
@synthesize btSoundOffBbutton;
@synthesize btRefreshBbutton;
@synthesize btSwitchCamera;
@synthesize btSplitView;
@synthesize btAddUser;
@synthesize btUserList;
@synthesize btCharacter;
@synthesize btFullScreen;
@synthesize btManage;
@synthesize uiRoomVideoType;
@synthesize uiRoomAudioType;
@synthesize OpenRemoteUserMap;
@synthesize videoAndVoiceViewController;
@synthesize sessionChatViewController;
@synthesize sessionInfoViewController;
@synthesize pVideoViewController;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{

    self =[super initWithNibName:@"SessionShowViewController" bundle:nil];
    int _screenWidth = [UIScreen mainScreen].bounds.size.width;
    m_CloseNum = 0;
    if (self) {
        // Custom initialization
        pLoginServer = NULL;
        pOpenLocalUser = OpenLocalUser::GetObject();
        self.videoWindow1=[[[iOSGLView alloc]init]autorelease];
        self.videoWindow2=[[[iOSGLView alloc]init]autorelease];
        self.videoWindow3=[[[iOSGLView alloc]init]autorelease];
        self.videoWindow4=[[[iOSGLView alloc]init]autorelease];
        xpos=0;
        ypos=0;
        height=_screenWidth;//翻转后的屏幕高度
        length=[UIScreen mainScreen].bounds.size.height;//height*3/2;//翻转后的屏幕长度
        subImageViewPosy=0;//第一个小视频窗口的Y坐标
        subImageViewDis=0;//小视频窗口的纵向距离
        subheight=(height-subImageViewDis*2)/3+1;//小视频窗口的高度-subImageViewPosy*2
        sublength=subheight*4/3;//小视频窗口的宽度
        
        fullScreenType=btSplitScreen4;
        fullScreen=NO;
        OpenRemoteUserMap.clear();
        uiCount = 2;
        self.isSoundOff=NO;
        uiRoomVideoType = ROOM_SET_NO;
        uiRoomAudioType = ROOM_SET_NO;
        uiMyScreenCount = 4;
        uiScreenNum = 0;
        spliteType=0;
        bIsEnterRoom = false;
        m_pOpenRemoteUser = NULL;
        strSpeekUserID = "";
        m_Is5Window = false;
        mCount = 0;
    }
    return self;
}

-(void)ToucvideoWindow1
{
    if (splite==NO) {
        return;
    }
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), toucvideoWindow1);
    
    fullScreenType=toucvideoWindow1;
    
    [self stopAllVideo];
   
    
    [self.videoWindow1  SetOpenglFrame:CGRectMake(xpos, ypos, length-sublength,height+1)];//
    [self.view insertSubview:self.videoWindow1 atIndex:0];
    
    [self.videoWindow2  SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy, sublength,subheight)];
    [self.videoWindow3 SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy+subheight+subImageViewDis, sublength,subheight)];
    [self.videoWindow4  SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy+subheight*2+subImageViewDis*2, sublength,subheight)];
    
    [self startAllVideo];
    
    [self setLocalVideoWindow];
    
    
    //if(pOpenLocalUser!=NULL)
       // pOpenLocalUser->setVideoWindow(self.videoWindow1);
}

-(void)toucvideoWindow1:(id)sender
{
    if (self.fullScreen&&(self.fullScreenType==toucvideoWindow1||spliteType==1||spliteType==2)) {
        
        [self setFullScreen];
    }
    else
    {
        if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        {
            if(self.fullScreen)
                [self setFullScreen];
            return;
        }
        [self ToucvideoWindow1];
    }
}

-(void)ThreadSplitScreen4:(id)sender
{
    [self.videoWindow1 setHidden:NO];
    [self.videoWindow2 setHidden:NO];
    [self.videoWindow3 setHidden:NO];
    [self.videoWindow4 setHidden:NO];
    
    switch (self.fullScreenType)
    {
        case btSplitScreen1:
        {
            [self SplitScreen1];
        }
            break;
        case btSplitScreen2:
        {
            [self SplitScreen2];
        }
            break;
        case btSplitScreen4:
        {
            [self SplitScreen4];
        }
            break;
        case toucvideoWindow1:
        {
            [self ToucvideoWindow1];
        }
            break;
        case toucvideoWindow2:
        {
            [self ToucvideoWindow2];
        }
            break;
        case toucvideoWindow3:
        {
            [self ToucvideoWindow3];
        }
            break;
        case toucvideoWindow4:
        {
            [self ToucvideoWindow4];
        }
            break;
        default:
            [self SplitScreen4];
            break;
    }
}

-(void)BeginVideoThread:(id)sender
{
    usleep(100);
    [self performSelectorOnMainThread:@selector(ThreadSplitScreen4:) withObject:self  waitUntilDone:YES];
}
-(void)handleDoubleTap1:(id)sender
{
    if(sessionInfoViewController)
        sessionInfoViewController.m_videoSessionID = 1;
    [self btUserListPressed:self];
}

-(void)handleDoubleTap2:(id)sender
{
    if(sessionInfoViewController)
        sessionInfoViewController.m_videoSessionID = 2;
    [self btUserListPressed:self];
}

-(void)handleDoubleTap3:(id)sender
{
    if(sessionInfoViewController)
        sessionInfoViewController.m_videoSessionID = 3;
    [self btUserListPressed:self];
}

-(void)handleDoubleTap4:(id)sender
{
    if(sessionInfoViewController)
        sessionInfoViewController.m_videoSessionID = 4;
    [self btUserListPressed:self];
}

-(void)ToucvideoWindow2
{
    if (splite==NO) {
        return;
    }
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), toucvideoWindow2);
    
    fullScreenType=toucvideoWindow2;
    [self stopAllVideo];
    
    [self.videoWindow2  SetOpenglFrame:CGRectMake(xpos, ypos, length-sublength,height+1)];
    [self.view insertSubview:self.videoWindow2 atIndex:0];
    
    [self.videoWindow1  SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy, sublength,subheight)];
    [self.videoWindow3 SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy+subheight+subImageViewDis, sublength,subheight)];
    [self.videoWindow4  SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy+subheight*2+subImageViewDis*2, sublength,subheight)];
    [self startAllVideo];
    
    [self setLocalVideoWindow];
   // if(pOpenLocalUser!=NULL)
      //  pOpenLocalUser->setVideoWindow(self.videoWindow1);
}

-(void)toucvideoWindow2:(id)sender
{
    if (self.fullScreen&&(self.fullScreenType==toucvideoWindow2||spliteType==1||spliteType==2)) {
        
        [self setFullScreen];
    }
    else
    {
        if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        {
            if(self.fullScreen)
                [self setFullScreen];
            return;
        }
        [self ToucvideoWindow2];
    }
}

-(void)ToucvideoWindow3
{
    if (splite==NO) {
        return;
    }
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), toucvideoWindow3);
    
    fullScreenType=toucvideoWindow3;
    [self stopAllVideo];
    
    [self.videoWindow3  SetOpenglFrame:CGRectMake(xpos, ypos, length-sublength,height+1)];
    [self.view insertSubview:self.videoWindow3 atIndex:0];
    
    [self.videoWindow1  SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy, sublength,subheight)];
    [self.videoWindow2 SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy+subheight+subImageViewDis, sublength,subheight)];
    [self.videoWindow4  SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy+subheight*2+subImageViewDis*2, sublength,subheight)];
    [self startAllVideo];
    
      [self setLocalVideoWindow];
    //if(pOpenLocalUser)
      //  pOpenLocalUser->setVideoWindow(self.videoWindow1);
}

-(void)toucvideoWindow3:(id)sender
{
    if (self.fullScreen&&(self.fullScreenType==toucvideoWindow3||spliteType==1||spliteType==2)) {
        [self setFullScreen];
    }
    else
    {
        if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        {
            if(self.fullScreen)
                [self setFullScreen];
            return;
        }
        [self ToucvideoWindow3];
    }
}

-(void)ToucvideoWindow4
{
    if (splite==NO) {
        return;
    }
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), toucvideoWindow4);
    
    fullScreenType=toucvideoWindow4;
    [self stopAllVideo];
    
    [self.videoWindow4  SetOpenglFrame:CGRectMake(xpos, ypos, length-sublength,height+1)];
    [self.view insertSubview:self.videoWindow4 atIndex:0];
    
    [self.videoWindow1  SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy, sublength,subheight)];
    [self.videoWindow2 SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy+subheight+subImageViewDis, sublength,subheight)];
    [self.videoWindow3  SetOpenglFrame:CGRectMake(xpos+length-sublength,subImageViewPosy+subheight*2+subImageViewDis*2, sublength,subheight)];
    [self startAllVideo];
    
      [self setLocalVideoWindow];
   // if(pOpenLocalUser)
     //   pOpenLocalUser->setVideoWindow(self.videoWindow1);
}

-(void)toucvideoWindow4:(id)sender
{
    if (self.fullScreen&&(self.fullScreenType==toucvideoWindow4||spliteType==1||spliteType==2)) {
        [self setFullScreen];
    }
    else
    {
        if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        {
            if(self.fullScreen)
                [self setFullScreen];
            return;
        }
        [self ToucvideoWindow4];
    }
}

-(void)splitScreen
{
    [self stopAllVideo];
 
    [self.videoWindow1  SetOpenglFrame:CGRectMake(xpos, ypos, length/2,height/2)];
    [self.videoWindow2  SetOpenglFrame:CGRectMake(xpos+length/2,ypos, length/2,height/2)];
    [self.videoWindow3  SetOpenglFrame:CGRectMake(xpos, ypos+height/2, length/2,height/2)];
    [self.videoWindow4  SetOpenglFrame:CGRectMake(xpos+length/2,ypos+ height/2, length/2,height/2)];
    [self startAllVideo];
    
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    splite=YES;
    if(mCount == 0)
        [self splitScreen];
    mCount++;
    soundOff=NO;
    isHiddenbtSplit=YES;
    isHiddenInviteView=YES;
    
    [self.splitView setHidden:isHiddenbtSplit];
    [self.InviteView setHidden:isHiddenInviteView];
    appDelegate=[[UIApplication sharedApplication] delegate];
      [self setLocalVideoWindow];
    //if(pOpenLocalUser)
       // pOpenLocalUser->setVideoWindow(self.videoWindow1);
}

-(void)viewWillDisappear:(BOOL)animated
{
       [super viewWillDisappear:animated];
}

-(void) RoomManagement
{
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    IsFrontVideo = true;
    if(mEnterRoomNSTimer == nil)
        mEnterRoomNSTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(runEnterRoomTimer:) userInfo:nil repeats:YES];
}

-(void)runEnterRoomTimer:(id)timer
{
    if(pLoginServer->ISChairman())
        [self ChairmanEnterRoom];
    
    if(m_pMBProgressHUD!=nil)
    {
        [m_pMBProgressHUD hide:YES];
        m_pMBProgressHUD = nil;
    }
    [mEnterRoomNSTimer invalidate];
    mEnterRoomNSTimer = nil;
    
    if(self.pVideoViewController!=nil)
        [pVideoViewController CallInviteAllUser_EnterRoomEnd];
}

-(void) OnInitializationTemporaryMeeting:(const std::string&)strUserID ulRoomID:(unsigned long) ulRoomID uiScreenCount:(unsigned int)uiScreenCount uiVideoType:(unsigned int)uiVideoType uiAudioType:(unsigned int)uiAudioType
{
    if(pLoginServer->ISChairman())
        return;
    uiRoomVideoType = uiVideoType;
    uiRoomAudioType = uiAudioType;
    uiMyScreenCount = uiScreenCount;
    
    [self performSelectorOnMainThread:@selector(InitializationTemporaryMeeting:) withObject:self waitUntilDone:YES];
}

-(void)InitializationTemporaryMeeting:(id)mid
{
    [self OrdinaryUserEnterRoom];
}

-(void)ChairmanEnterRoom
{
    assert(pLoginServer);
    
    bIsEnterRoom = true;
    
    uiRoomVideoType = ROOM_VIDEO_PUSH;
    uiRoomAudioType = ROOM_AUDIO_DISCUSS;
    
    if(pOpenLocalUser)
    {
        pOpenLocalUser->ConnectMediaServer(pLoginServer->GetServerIp(), pLoginServer->GetServerPort());
    }
    
    if(pOpenLocalUser)
    {
        unsigned int uiScreen = 0;
        iOSGLView* pView = [self GetWindow:pLoginServer->GetUserID() uiScreen:uiScreen IsSet:true];
        assert(pView);
        [self User_OpenLocalVideo:pLoginServer->GetUserID() pView:pView uiScreen:uiScreen IsSendCommand:false IsSendData:false bIsBroadcast:false];
    }
    
    NSString *VideoType=nil;
    NSString *AudioType=nil;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH)
    {
        VideoType=[[[NSString alloc]initWithCString:"推送" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        VideoType=[[[NSString alloc]initWithCString:"会议" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    if(uiRoomAudioType == ROOM_AUDIO_SPEAK)
    {
        AudioType=[[[NSString alloc]initWithCString:"发言" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomAudioType == ROOM_AUDIO_DISCUSS)
    {
        AudioType=[[[NSString alloc]initWithCString:"讨论" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    NSString *UserID=[[[NSString alloc]initWithCString:pLoginServer->GetUserID().c_str() encoding: NSUTF8StringEncoding] autorelease];
    self.title = [[[NSString alloc]initWithFormat:@"会议模式:视频(%@)、音频(%@)、用户(%@)",VideoType,AudioType,UserID]autorelease];
}

-(void)OrdinaryUserEnterRoom
{
    bIsEnterRoom = true;
    
    if(pOpenLocalUser)
    {
        pOpenLocalUser->ConnectMediaServer(pLoginServer->GetServerIp(), pLoginServer->GetServerPort());
    }
    
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        if(pOpenLocalUser)
        {
            unsigned int uiScreen = 0;
            iOSGLView* pView = [self GetWindow:pLoginServer->GetUserID() uiScreen:uiScreen IsSet:true];
            assert(pView);
            [self User_OpenLocalVideo:pLoginServer->GetUserID() pView:pView uiScreen:uiScreen IsSendCommand:false IsSendData:false bIsBroadcast:false];
        }
    }
    NSString *VideoType=nil;
    NSString *AudioType=nil;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH)
    {
        VideoType=[[[NSString alloc]initWithCString:"推送" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        VideoType=[[[NSString alloc]initWithCString:"会议" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    if(uiRoomAudioType == ROOM_AUDIO_SPEAK)
    {
        AudioType=[[[NSString alloc]initWithCString:"发言" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomAudioType == ROOM_AUDIO_DISCUSS)
    {
        AudioType=[[[NSString alloc]initWithCString:"讨论" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    NSString *UserID=[[[NSString alloc]initWithCString:pLoginServer->GetUserID().c_str() encoding: NSUTF8StringEncoding] autorelease];
    self.title = [[[NSString alloc]initWithFormat:@"会议模式:视频(%@)、音频(%@)、用户(%@)",VideoType,AudioType,UserID]autorelease];
}

-(void)PeerUserJoinTemporaryMeeting:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID
{
    if(pLoginServer->ISChairman())
    {
        [self BroadcastRoomInfo:strUserID];
        
         if(uiRoomVideoType == ROOM_VIDEO_PUSH)
         {
             //open new enter user video 
             unsigned int uiScreen = 0;
             iOSGLView* pView = [self GetWindow:strUserID uiScreen:uiScreen IsSet:true];
             if(pView!=nil)
             {
                 [self User_OpenPeerVideo:strUserID pView:pView uiScreen:uiScreen bIsBroadcast:true IsSendCommand:true];
             }
             
             //open host video
             uiScreen = 0;
             pView = [self GetWindow:pLoginServer->GetUserID() uiScreen:uiScreen IsSet:true];
             assert(pView);
             [self User_OpenLocalVideo:pLoginServer->GetUserID() pView:pView uiScreen:uiScreen IsSendCommand:true IsSendData:true bIsBroadcast:true];
             
             //open host open video
             OpenRemoteUser* pOpenRemoteUser = NULL;
             OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.begin();
             while(iter != OpenRemoteUserMap.end())
             {
                 pOpenRemoteUser = iter->second;
                 assert(pOpenRemoteUser);
                 if(iter->first != strUserID)
                 {
                     if(pOpenRemoteUser->IsOpenVideo())
                     {
                         uiScreen = 0;  //pView =
                        [self GetWindow:iter->first uiScreen:uiScreen IsSet:true];
                         pLoginServer->OnOpenPeerUserVideo(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), iter->first, pLoginServer->GetPeerUserVideoId(iter->first), uiScreen,true);
                     }
                 }
                 iter++;
             }
         }
        
        if(uiRoomAudioType == ROOM_AUDIO_DISCUSS)
        {
            //open new enter user audio
            [self User_OpenPeerAudio:strUserID];
            
            //open host audio
            [self User_OpenLocalAudio:pLoginServer->GetUserID() IsSendData:true];
            
            //open host open audio
            OpenRemoteUser* pOpenRemoteUser = NULL;
            OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.begin();
            while(iter != OpenRemoteUserMap.end())
            {
                pOpenRemoteUser = iter->second;
                assert(pOpenRemoteUser);
                if(iter->first != strUserID)
                {
                    if(pOpenRemoteUser->IsOpenAudio())
                    {
                        pLoginServer->OnOpenPeerUserAudio(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), iter->first, pLoginServer->GetPeerUserAudioId(iter->first), true);
                    }
                }
                iter++;
            }
            
        }
        else if(uiRoomAudioType == ROOM_AUDIO_SPEAK)
        {
            if(!strSpeekUserID.empty())
            {
                if(strSpeekUserID == pLoginServer->GetUserID())
                {
                    [self User_OpenLocalAudio:pLoginServer->GetUserID() IsSendData:true];
                }
                else
                {
                    [self User_OpenPeerAudio:strSpeekUserID];
                }
            }
        }
    }
}

-(void)BroadcastRoomInfo:(const std::string&)strUserID
{
    pLoginServer->OnInitializationTemporaryMeeting(strUserID, pLoginServer->GetRoomId(), pLoginServer->GetScreenControl(), uiRoomVideoType, uiRoomAudioType);
}

-(void)User_OpenLocalVideo:(const std::string&)strUserID pView:(iOSGLView*)pView uiScreen:(unsigned int)uiScreen IsSendCommand:(bool)IsSendCommand IsSendData:(bool)IsSendData bIsBroadcast:(bool)bIsBroadcast
{
    if(IsSendCommand)
    {
        pLoginServer->OnOpenPeerUserVideo(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), strUserID, pLoginServer->GetLocalVideoId(), uiScreen, bIsBroadcast);
    }
    
    if(pOpenLocalUser)
    {
        unsigned int uiWidth = 0;
        unsigned int uiHeight = 0;
        unsigned int uiVideoFps = 0;
        unsigned int uiBitRate = 0;
        
        VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
        p->GetResolution(uiWidth, uiHeight);
        uiVideoFps = p->GetVideoFps();
        uiBitRate = p->GetBitRate();
        
        if(!pOpenLocalUser->IsOpenVideo())
        {
            pOpenLocalUser->OpenVideo(pView, pLoginServer->GetLocalVideoId(), uiWidth, uiHeight, uiBitRate, uiVideoFps);
        }
        else if(m_Is5Window)
        {
            pOpenLocalUser->setVideoWindow(pView);
            m_Is5Window = false;
        }
        if(IsSendData && !pOpenLocalUser->IsSendVideoData())
            pOpenLocalUser->SendVideoData();
        
        if(uiRoomVideoType == ROOM_VIDEO_ROOM)
        {
            if(strUserID!=pLoginServer->GetUserID())
                pOpenLocalUser->AddOpenMeVideoUser(strUserID);
            
            if(self.sessionInfoViewController!=nil)
                [self.sessionInfoViewController MyUpdateMeetingInfo:self];
        }
    }
}

-(void)User_CloseLocalVideo:(const std::string&)strUserID IsSendCommand:(bool)IsSendCommand bIsBroadcast:(bool)bIsBroadcast

{
    if(IsSendCommand)
    {
        pLoginServer->OnClosePeerUserVideo(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), strUserID, pLoginServer->GetLocalVideoId(), bIsBroadcast);
    }
    
    if(pOpenLocalUser)
    {
        if(uiRoomVideoType == ROOM_VIDEO_ROOM)
        {
            if(pOpenLocalUser->OpenMeVideoCount() <= 1)
            {
                pOpenLocalUser->setVideoWindow(nil);
#if 0
                pOpenLocalUser->DeleteOpenMeVideoUser(strUserID);
                if(pOpenLocalUser->IsSendVideoData())
                    pOpenLocalUser->StopSendVideoData();
                if(pOpenLocalUser->IsOpenVideo())
                    pOpenLocalUser->CloseVideo();
#endif
                
                SCREENCONTROLINFOMAP::iterator it = ScreenControlinfoMap.begin();
                while(it!=ScreenControlinfoMap.end())
                {
                    if(it->second->strUserID == strUserID)
                    {
                       // [it->second->pvideoWindow setImage:[UIImage imageNamed:@""]];
                        break;
                    }
                    it++;
                }
                [self CloseWindow:strUserID];
                
                pOpenLocalUser->setVideoWindow(_videoWindow5);
                m_Is5Window = true;
            }
            //else
            //    pOpenLocalUser->DeleteOpenMeVideoUser(strUserID);
            
            if(self.sessionInfoViewController!=nil)
                [self.sessionInfoViewController MyUpdateMeetingInfo:self];
        }
        else
        {
            pOpenLocalUser->setVideoWindow(nil);
            
            if(pOpenLocalUser->IsSendVideoData())
                pOpenLocalUser->StopSendVideoData();
            if(pOpenLocalUser->IsOpenVideo())
            {  // pOpenLocalUser->setVideoWindow(nil);
                pOpenLocalUser->CloseVideo();
            }
            SCREENCONTROLINFOMAP::iterator it = ScreenControlinfoMap.begin();
            while(it!=ScreenControlinfoMap.end())
            {
                if(it->second->strUserID == pLoginServer->GetUserID())
                {
                  //  [it->second->pvideoWindow setImage:[UIImage imageNamed:@""]];
                    break;
                }
                it++;
            }
           
            [self CloseWindow:strUserID];
        }
    }
}

-(void)User_OpenLocalAudio:(const std::string&)strUserID  IsSendData:(bool)IsSendData;
{
    if(pOpenLocalUser)
    {
        if(IsSendData)
            pLoginServer->OnOpenPeerUserAudio(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), pLoginServer->GetUserID(), pLoginServer->GetLocalAudioId());
        
        if(!pOpenLocalUser->IsOpenAudio())
            pOpenLocalUser->OpenAudio(pLoginServer->GetLocalAudioId(), AMR_NBCODE);
        
        if(!pOpenLocalUser->IsSendAudioData())
            pOpenLocalUser->SendAudioData();
        
        strSpeekUserID = strUserID;
    }
}

-(void)User_CloseLocalAudio:(const std::string&)strUserID
{
    if(pOpenLocalUser)
    {
        pLoginServer->OnClosePeerUserAudio(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), pLoginServer->GetUserID(), pLoginServer->GetLocalAudioId());
        
        if(pOpenLocalUser->IsSendAudioData())
            pOpenLocalUser->StopSendAudioData();
        
        if(pOpenLocalUser->IsOpenAudio())
            pOpenLocalUser->CloseAudio();
        
        strSpeekUserID = "";
    }
}

-(void)User_OpenPeerVideo:(const std::string&)parstrPeerUserID pView:(iOSGLView*)pView uiScreen:(unsigned int)uiScreen bIsBroadcast:(bool)bIsBroadcast IsSendCommand:(bool)IsSendCommand
{
    if(pLoginServer&&pView)
    {
        if(IsSendCommand)
            pLoginServer->OnOpenPeerUserVideo(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), parstrPeerUserID, pLoginServer->GetPeerUserVideoId(parstrPeerUserID), uiScreen, bIsBroadcast);
        
        OpenRemoteUser* pOpenRemoteUser = NULL;
        OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.find(parstrPeerUserID);
        if(iter != OpenRemoteUserMap.end())
        {
            pOpenRemoteUser = iter->second;
            assert(pOpenRemoteUser);
        }
        
        if(pOpenRemoteUser==NULL)
        {
            pOpenRemoteUser = new OpenRemoteUser;
            pOpenRemoteUser->ConnectMediaServer(pLoginServer->GetServerIp(), pLoginServer->GetServerPort());
            OpenRemoteUserMap[parstrPeerUserID] = pOpenRemoteUser;
        }
        assert(pOpenRemoteUser);
        
        unsigned long ulPeerVideoId = pLoginServer->GetPeerUserVideoId(parstrPeerUserID);
        
        if(!pOpenRemoteUser->IsOpenVideo())
            pOpenRemoteUser->OpenVideo(pView);
        if(!pOpenRemoteUser->IsStartReceiverVideo())
            pOpenRemoteUser->StartPeerVideoData(parstrPeerUserID, ulPeerVideoId);
        pOpenRemoteUser->StartDisplayVideo();
    }
}

-(void)User_ClosePeerVideo:(const std::string&)parstrPeerUserID IsSendCommand:(bool)IsSendCommand bIsBroadcast:(bool)bIsBroadcast
{
    if(pLoginServer)
    {
        if(IsSendCommand)
            pLoginServer->OnClosePeerUserVideo(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), parstrPeerUserID, pLoginServer->GetPeerUserVideoId(parstrPeerUserID), bIsBroadcast);
        
        m_pOpenRemoteUser = NULL;
        OpenRemoteUser* pOpenRemoteUser = NULL;
        OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.find(parstrPeerUserID);
        if(iter != OpenRemoteUserMap.end())
        {
            pOpenRemoteUser = iter->second;
            assert(pOpenRemoteUser);
            
            if(pOpenRemoteUser->IsStartReceiverVideo())
                pOpenRemoteUser->StopDisplayVideo();
            
            m_pOpenRemoteUser = pOpenRemoteUser;
            
            [self CloseWindow:parstrPeerUserID];
            
            NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
            [NSThread detachNewThreadSelector:@selector(User_ClosePeerVideo_WorkThread:) toTarget:self withObject:self];
            [pool release];
        }
    }
}

-(void)User_ClosePeerVideo_WorkThread:(id)mid
{
    sleep(1);
    
    if(m_pOpenRemoteUser!=NULL)
    {
        if(m_pOpenRemoteUser->IsStartReceiverVideo())
            m_pOpenRemoteUser->StopPeerVideoData();
        if(m_pOpenRemoteUser->IsOpenVideo())
            m_pOpenRemoteUser->CloseVideo();
    }
    
    m_CloseNum--;
    if(m_CloseNum==0 && pLoginServer!=NULL)
        pLoginServer->SetInformationStateQueue(true);
}

-(void)User_OpenPeerAudio:(const std::string&)parstrPeerUserID
{
    if(pLoginServer)
    {
        pLoginServer->OnOpenPeerUserAudio(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), parstrPeerUserID, pLoginServer->GetPeerUserAudioId(parstrPeerUserID), true);
        
        OpenRemoteUser* pOpenRemoteUser = NULL;
        OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.find(parstrPeerUserID);
        if(iter != OpenRemoteUserMap.end())
        {
            pOpenRemoteUser = iter->second;
            assert(pOpenRemoteUser);
        }
        
        if(pOpenRemoteUser==NULL)
        {
            pOpenRemoteUser = new OpenRemoteUser;
            pOpenRemoteUser->ConnectMediaServer(pLoginServer->GetServerIp(), pLoginServer->GetServerPort());
            OpenRemoteUserMap[parstrPeerUserID] = pOpenRemoteUser;
        }
        assert(pOpenRemoteUser);
        
        unsigned long ulPeerAudioId = pLoginServer->GetPeerUserAudioId(parstrPeerUserID);
        
        if(!pOpenRemoteUser->IsOpenAudio())
            pOpenRemoteUser->OpenAudio(AMR_NBCODE);
        if(!pOpenRemoteUser->IsStartReceiverAudio())
            pOpenRemoteUser->StartPeerAudioData(parstrPeerUserID, ulPeerAudioId);
        
        strSpeekUserID = parstrPeerUserID;
    }
}

-(void)User_ClosePeerAudio:(const std::string&)parmstrPeerUserID
{
    if(pLoginServer)
    {
        pLoginServer->OnClosePeerUserAudio(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), parmstrPeerUserID, pLoginServer->GetPeerUserAudioId(parmstrPeerUserID), true);
        
        OpenRemoteUser* pOpenRemoteUser = NULL;
        OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.find(parmstrPeerUserID);
        if(iter != OpenRemoteUserMap.end())
        {
            pOpenRemoteUser = iter->second;
            assert(pOpenRemoteUser);
            
            if(pOpenRemoteUser->IsStartReceiverAudio())
                pOpenRemoteUser->StopPeerAudioData();
            
            if(pOpenRemoteUser->IsOpenAudio())
                pOpenRemoteUser->CloseAudio();
        }
        
        strSpeekUserID = "";
    }
}

-(void)User_OpenAllAudio
{
    //open host audio
    [self User_OpenLocalAudio:pLoginServer->GetUserID() IsSendData:true];
    
    std::vector<ROOMUSERINFO> UserList;
    pLoginServer->GetRoomUserList(UserList);
    
    std::vector<ROOMUSERINFO>::iterator iter = UserList.begin();
    while (iter!=UserList.end())
    {
        if(iter->strUserID!=pLoginServer->GetUserID())
        {
            [self User_OpenPeerAudio:iter->strUserID];
        }
        iter++;
    }
}

-(void)User_CloseAllAudio
{
    [self User_CloseLocalAudio:pLoginServer->GetUserID()];
    
    std::vector<ROOMUSERINFO> UserList;
    pLoginServer->GetRoomUserList(UserList);
    
    std::vector<ROOMUSERINFO>::iterator iter = UserList.begin();
    while (iter!=UserList.end())
    {
        if(iter->strUserID!=pLoginServer->GetUserID())
        {
            [self User_ClosePeerAudio:iter->strUserID];
        }
        iter++;
    }
}

-(void)User_OpenHostAllVideo
{
    //open host video
    unsigned int uiScreen = 0;
    iOSGLView* pView = [self GetWindow:pLoginServer->GetUserID() uiScreen:uiScreen IsSet:true];
    assert(pView);
    [self User_OpenLocalVideo:pLoginServer->GetUserID() pView:pView uiScreen:uiScreen IsSendCommand:true IsSendData:true bIsBroadcast:true];
    
    //open host open video
    OpenRemoteUser* pOpenRemoteUser = NULL;
    OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.begin();
    while(iter != OpenRemoteUserMap.end())
    {
        pOpenRemoteUser = iter->second;
        assert(pOpenRemoteUser);
        if(iter->first != pLoginServer->GetUserID())
        {
            if(pOpenRemoteUser->IsOpenVideo())
            {
                uiScreen = 0;
                iOSGLView* pView = [self GetWindow:iter->first uiScreen:uiScreen IsSet:true];
                assert(pView);
                
                pLoginServer->OnOpenPeerUserVideo(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), iter->first, pLoginServer->GetPeerUserVideoId(iter->first), uiScreen, true);
            }
        }
        iter++;
    }
}

-(void)User_CloseAllVideo
{
    pLoginServer->SetInformationStateQueue(false);
    [self User_CloseLocalVideo:pLoginServer->GetUserID() IsSendCommand:false bIsBroadcast:false];
    
    std::vector<ROOMUSERINFO> UserList;
    pLoginServer->GetRoomUserList(UserList);
    
    m_CloseNum = UserList.size()-1;
    
    std::vector<ROOMUSERINFO>::iterator iter = UserList.begin();
    while (iter!=UserList.end())
    {
        if(iter->strUserID!=pLoginServer->GetUserID())
        {
            [self User_ClosePeerVideo:iter->strUserID IsSendCommand:false bIsBroadcast:false];
        }
        iter++;
    }
}

-(iOSGLView*)GetWindow:(const std::string&)strUserID uiScreen:(unsigned int&)uiScreen IsSet:(bool)IsSet
{
    IMS_CONTACT_ITEM mUserInfo;
    pLoginServer->GetUserInfo(strUserID, mUserInfo);
    
    if(uiScreen != 0)
    {
        SCREENCONTROLINFOMAP::iterator it = ScreenControlinfoMap.find(uiScreen);
        if(it!=ScreenControlinfoMap.end())
        {
            it->second->strUserID = strUserID;
            it->second->bIsOpenVideo = true;
            uiScreen = it->first;
            
            switch (uiScreen)
            {
                case 1:
                {
                    NSString *UserID=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
                    [lable1 setText:UserID];
                }
                    break;
                case 2:
                {
                    NSString *UserID=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
                    [lable2 setText:UserID];
                }
                    break;
                case 3:
                {
                    NSString *UserID=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
                    [lable3 setText:UserID];
                }
                    break;
                case 4:
                {
                    NSString *UserID=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
                    [lable4 setText:UserID];
                }
                    break;
            }
            
#if 1
            if(pLoginServer->GetUserID() == strUserID)
            {
                if (IsFrontVideo)
                {
                    CGRect frame=it->second->pvideoWindow.frame;
                    it->second->pvideoWindow.transform=CGAffineTransformMakeRotation(M_PI*3/2);
                    [it->second->pvideoWindow SetOpenglFrame:frame];
                }
                else
                {
                    CGRect frame=it->second->pvideoWindow.frame;
                    it->second->pvideoWindow.transform=CGAffineTransformMakeRotation(M_PI/2);
                    [it->second->pvideoWindow SetOpenglFrame:frame];
                }
            }
            else
            {
                CGRect frame=it->second->pvideoWindow.frame;
                it->second->pvideoWindow.transform=CGAffineTransformMakeRotation(0);
                [it->second->pvideoWindow SetOpenglFrame:frame];
            }
#endif
            
            return it->second->pvideoWindow;
        }
    }
    
    SCREENCONTROLINFOMAP::iterator iter = ScreenControlinfoMap.begin();
    while(iter!=ScreenControlinfoMap.end())
    {
        if(!iter->second->bIsOpenVideo || iter->second->strUserID == strUserID)
        {
            iter->second->strUserID = strUserID;
            iter->second->bIsOpenVideo = true;
            uiScreen = iter->first;
            
            switch (uiScreen)
            {
                case 1:
                {
                    NSString *UserID=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
                    [lable1 setText:UserID];
                }
                    break;
                case 2:
                {
                    NSString *UserID=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
                    [lable2 setText:UserID];
                }
                    break;
                case 3:
                {
                    NSString *UserID=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
                    [lable3 setText:UserID];
                }
                    break;
                case 4:
                {
                    NSString *UserID=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
                    [lable4 setText:UserID];
                }
                    break;
            }
        
            if(IsSet)
            {
                if(pLoginServer->GetUserID() == strUserID)
                {
                    if (IsFrontVideo)
                    {
                        CGRect frame=iter->second->pvideoWindow.frame;
                        iter->second->pvideoWindow.transform=CGAffineTransformMakeRotation(M_PI*3/2);
                        [iter->second->pvideoWindow SetOpenglFrame:frame];
                    }
                    else
                   {
                        CGRect frame=iter->second->pvideoWindow.frame;
                        iter->second->pvideoWindow.transform=CGAffineTransformMakeRotation(M_PI/2);
                        [iter->second->pvideoWindow SetOpenglFrame:frame];
                   }
                }
                else
               {
                    CGRect frame=iter->second->pvideoWindow.frame;
                    iter->second->pvideoWindow.transform=CGAffineTransformMakeRotation(0);
                   [iter->second->pvideoWindow SetOpenglFrame:frame];
               }
            }

            return iter->second->pvideoWindow;
        }
        iter++;
    }
    return nil;
}

-(int)GetWindowScreen:(const std::string&)strUserID
{
    SCREENCONTROLINFOMAP::iterator iter = ScreenControlinfoMap.begin();
    while(iter!=ScreenControlinfoMap.end())
    {
        if(iter->second->bIsOpenVideo && iter->second->strUserID == strUserID)
        {
            return iter->first;
        }
        iter++;
    }
    return 0;
}

-(void)startAllVideo
{
    
    if(self.videoWindow1){
        [self.videoWindow1 setFps:30];
        
    }
    [self.videoWindow1 startAnimation];
    
    if(self.videoWindow2){
        [self.videoWindow2 setFps:30];
        
    }
    [self.videoWindow2 startAnimation];
    
    
    if(self.videoWindow3){
        [self.videoWindow3 setFps:30];
        
    }
    [self.videoWindow3 startAnimation];
    
    
    if(self.videoWindow4){
        [self.videoWindow4 setFps:30];
        
    }
    [self.videoWindow4 startAnimation];
    isstop=YES;
    
}

-(void)stopAllVideo
{
    
    if (isstop) {
        
        if(self.videoWindow1){
            [self.videoWindow1 unInitialize];
            
        }
        
        
        if(self.videoWindow2){
            [self.videoWindow2 unInitialize];
            
        }
        
        
        if(self.videoWindow3){
            [self.videoWindow3 unInitialize];
            
        }
        
        
        
        if(self.videoWindow4){
            [self.videoWindow4 unInitialize];
            
        }
        
        isstop=NO;
    }
}

-(void)CloseWindow:(const std::string&)strUserID
{
    [self stopAllVideo];
    SCREENCONTROLINFOMAP::iterator iter = ScreenControlinfoMap.begin();
    while(iter!=ScreenControlinfoMap.end())
    {
        if(iter->second->strUserID == strUserID)
        {
           // [iter->second->pvideoWindow setImage:[UIImage imageNamed:@"分屏"]];
            iter->second->strUserID = "";
            iter->second->bIsOpenVideo = false;
            
            switch (iter->first)
            {
                case 1:
                {
                    [lable1 setText:@""];
                }
                    break;
                case 2:
                {
                    [lable2 setText:@""];
                }
                    break;
                case 3:
                {
                    [lable3 setText:@""];
                }
                    break;
                case 4:
                {
                    [lable4 setText:@""];
                }
                    break;
            }
        }
        iter++;
    }
    [self startAllVideo];
}

-(bool)IsHasVideoWindow
{
    SCREENCONTROLINFOMAP::iterator iter = ScreenControlinfoMap.begin();
    while(iter!=ScreenControlinfoMap.end())
    {
        if(iter->second->bIsOpenVideo == false)
        {
            return true;
        }
        iter++;
    }
    
    return false;
}

-(void)PeerQuitInterimMeetingInfo:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID
{
    if(!bIsEnterRoom)
        return;
    
}

-(void)PeerDestructionInterimMeetingInfo
{
    if(QiutRoomalert!=nil)
    {
        [QiutRoomalert dismissWithClickedButtonIndex:0 animated:YES]; 
        QiutRoomalert=nil;
    }
    
    [self back];
}

-(void)back
{
#if 0
    if(!bIsEnterRoom)
        return;
#endif
    
    bIsEnterRoom = false;
    
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    
    OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.begin();
    while (iter!=OpenRemoteUserMap.end())
    {
        OpenRemoteUser* pOpenRemoteUser = iter->second;
        if(pOpenRemoteUser)
        {
            if(pOpenRemoteUser->IsStartReceiverVideo())
                pOpenRemoteUser->StopDisplayVideo();
        }
        iter++;
    }
    
    [self CloseWindow:pLoginServer->GetUserID()];
    
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [NSThread detachNewThreadSelector:@selector(ReleaseAudioAndVideo:) toTarget:self withObject:self];
    [pool release];
}

-(void)ReleaseAudioAndVideo:(id)mid
{
    sleep(1);

    OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.begin();
    while (iter!=OpenRemoteUserMap.end())
    {
        OpenRemoteUser* pOpenRemoteUser = iter->second;
        if(pOpenRemoteUser)
        {
            if(pOpenRemoteUser->IsStartReceiverVideo())
                pOpenRemoteUser->StopPeerVideoData();
            if(pOpenRemoteUser->IsStartReceiverAudio())
                pOpenRemoteUser->StopPeerAudioData();
            if(pOpenRemoteUser->IsOpenVideo())
                pOpenRemoteUser->CloseVideo();
            if(pOpenRemoteUser->IsOpenAudio())
                pOpenRemoteUser->CloseAudio();
            
            pOpenRemoteUser->ReleaseMediaSever();
            delete pOpenRemoteUser;
            pOpenRemoteUser =  NULL;
        }
        iter->second = NULL;
        iter++;
    }
    
    OpenRemoteUserMap.clear();
    
    sleep(1);
    
    [self performSelectorOnMainThread:@selector(QuitRoom:) withObject:self waitUntilDone:YES];
}

-(void) QuitRoom:(id)mid
{
    if(pOpenLocalUser)
    {
        if(pOpenLocalUser->IsSendVideoData())
            pOpenLocalUser->StopSendVideoData();
        if(pOpenLocalUser->IsSendAudioData())
            pOpenLocalUser->StopSendAudioData();
        
        if(pOpenLocalUser->IsOpenVideo())
            pOpenLocalUser->CloseVideo();
        pOpenLocalUser->setVideoWindow(nil);
        if(pOpenLocalUser->IsOpenAudio())
            pOpenLocalUser->CloseAudio();
        
        pOpenLocalUser->ReleaseMediaSever();
        pOpenLocalUser->ReleaseObject(pOpenLocalUser);
    }
    
    if(pLoginServer->ISChairman())
    {
        if(pLoginServer)
            pLoginServer->DestructionTemporaryMeeting(pLoginServer->GetUserID(), pLoginServer->GetRoomId());
    }
    else
    {
        if(pLoginServer)
            pLoginServer->QuitTemporaryMeeting(pLoginServer->GetUserID(), pLoginServer->GetRoomId());
    }
    
     [self.videoSessionViewController dismissViewControllerAnimated:YES completion:nil];
    
    if(m_pMBProgressHUD!=nil)
    {
        [m_pMBProgressHUD hide:YES];
        m_pMBProgressHUD = nil;
    }
}

-(void)SplitScreen1
{
    [self stopAllVideo];
    
    [self.videoWindow1  SetOpenglFrame:CGRectMake(xpos, ypos, length,height)];
    
    [self.view insertSubview:self.videoWindow2 atIndex:0];
    [self.view insertSubview:self.videoWindow3 atIndex:0];
    [self.view insertSubview:self.videoWindow4 atIndex:0];
    [self startAllVideo];
    splite=NO;
    spliteType=1;
      [self setLocalVideoWindow];
   
    
    //if(pOpenLocalUser)
      // pOpenLocalUser->setVideoWindow(self.videoWindow1);
}

-(IBAction)btSplitScreen1:(id)sender
{
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        return;
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), btSplitScreen1);
    
    [self SplitScreen1];
     fullScreenType=btSplitScreen1;
    isHiddenbtSplit=YES;
    [self.splitView setHidden:isHiddenbtSplit];
    [self.btSplitView setImage:[UIImage imageNamed:@"分屏开关"] forState:UIControlStateNormal ];
    
}

-(void)SplitScreen2
{
    [self stopAllVideo];
    
    [self.videoWindow1 SetOpenglFrame:CGRectMake(xpos, ypos, length/2,height)];
    [self.videoWindow2 SetOpenglFrame:CGRectMake(xpos+length/2, ypos, length/2,height)];
    [self startAllVideo];
    
    [self.view insertSubview:self.videoWindow3 atIndex:0];
    [self.view insertSubview:self.videoWindow4 atIndex:0];
    splite=NO;
    spliteType=2;
      [self setLocalVideoWindow];
        
   // if(pOpenLocalUser)
       // pOpenLocalUser->setVideoWindow(self.videoWindow1);
    
}

-(IBAction)btSplitScreen2:(id)sender
{
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        return;
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), btSplitScreen2);
    
     [self SplitScreen2];
      fullScreenType=btSplitScreen2;
    isHiddenbtSplit=YES;
    [self.splitView setHidden:isHiddenbtSplit];
    [self.btSplitView setImage:[UIImage imageNamed:@"分屏开关"] forState:UIControlStateNormal ];
    
}

-(void)SplitScreen4
{
    [self splitScreen];
    fullScreenType=btSplitScreen4;
    splite=YES;
    spliteType=4;
      [self setLocalVideoWindow];
    //if(pOpenLocalUser)
      //  pOpenLocalUser->setVideoWindow(self.videoWindow1);
}

-(IBAction)btSplitScreen4:(id)sender
{
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        return;
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), btSplitScreen4);
    
    [self SplitScreen4];
    isHiddenbtSplit=YES;
    [self.splitView setHidden:isHiddenbtSplit];

    [self.btSplitView setImage:[UIImage imageNamed:@"分屏开关"] forState:UIControlStateNormal ];

}

-(void)BtManagePressed:(id)sender
{
    SessionControlViewController *sessionControlViewController=[[[SessionControlViewController alloc]initWithNibName:@"SessionControlViewController" bundle:Nil]autorelease];
    
    UISubLRNavgationViewController *setting= [[[UISubLRNavgationViewController alloc] initWithRootViewController: sessionControlViewController]autorelease];

    sessionControlViewController.pSessionShowViewController = self;
   
        [self.videoSessionViewController presentViewController:setting animated:YES completion:nil];
}

-(IBAction)BtBack:(id)sender
{
    QiutRoomalert = [[[UIAlertView alloc] initWithTitle:@"是否退出会议" message:@""
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles:@"取消", nil]autorelease];
	QiutRoomalert.alertViewStyle = UIAlertViewStyleDefault;
    [QiutRoomalert show];
}

-(IBAction)BtSet:(id)sender
{
    VideoAndVoiceViewController *videoView=[[[VideoAndVoiceViewController alloc]initWithNibName:@"VideoAndVoiceViewController" bundle:Nil]autorelease];
    //  sessionControlViewController.pSessionShowViewController = self;VideoAndVoiceViewController_ flat
     
    UISubLRNavgationViewController *setting= [[[UISubLRNavgationViewController alloc] initWithRootViewController: videoView]autorelease];
    
    videoView.pSessionShowViewController = self;
    [videoView setBackview2];
    
    [self.videoSessionViewController presentViewController:setting animated:YES completion:nil];
}

-(IBAction)btRefresh:(id)sender
{
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
}

-(void)runTimer:(id)timer
{
    if(m_pMBProgressHUD!=nil)
    {
        [m_pMBProgressHUD hide:YES];
        m_pMBProgressHUD = nil;
    }
    [mNSTimer invalidate];
    mNSTimer = nil;
}

-(IBAction)btSoundOff:(id)sender
{
    self.isSoundOff= !self.isSoundOff;
    if (self.isSoundOff)
    {
        [ self.btSoundOffBbutton setImage:[UIImage imageNamed:@"禁音1"] forState:UIControlStateNormal];
        
        if(pOpenLocalUser)
            pOpenLocalUser->StopSendAudioData();
    }
    else
    {
        [ self.btSoundOffBbutton setImage:[UIImage imageNamed:@"禁音"] forState:UIControlStateNormal];
        
        if(pOpenLocalUser)
            pOpenLocalUser->SendAudioData();
    }
}

-(void)setLocalVideoWindow
{
    SCREENCONTROLINFOMAP::iterator it = ScreenControlinfoMap.begin();
    
    while(it!=ScreenControlinfoMap.end())
    {
        if(it->second->strUserID == pLoginServer->GetUserID())
        {
            
            if(pOpenLocalUser)
                pOpenLocalUser->setVideoWindow(it->second->pvideoWindow);

            break;
        }
        it++;
    }
}

-(IBAction)btSwitchCamera:(id)sender
{
    if(pOpenLocalUser==NULL)
        return;
    if(pOpenLocalUser->IsOpenVideo())
    {
        m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
        if(mNSTimer == nil)
            mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
        pOpenLocalUser->SetFrontAndRearCamera(IsFrontVideo);
        IsFrontVideo = !IsFrontVideo;
        
        [self.videoSessionViewController SetInterfaceOrientation:IsFrontVideo];
        /////////////本地预览
        SCREENCONTROLINFOMAP::iterator it = ScreenControlinfoMap.begin();
        while(it!=ScreenControlinfoMap.end())
        {
            if(it->second->strUserID == pLoginServer->GetUserID())
            {
                CGRect frame=it->second->pvideoWindow.frame;
                
                if (IsFrontVideo) {
                   it->second->pvideoWindow.transform=CGAffineTransformMakeRotation(M_PI*3/2);
                    
                }
                else
                    
                {
                   it->second->pvideoWindow.transform=CGAffineTransformMakeRotation(M_PI/2);
                }
                
                [it->second->pvideoWindow SetOpenglFrame:frame];
                
                break;
            }
            it++;
        }
        
  
    }
}

-(IBAction)btSplitView:(id)sender
{
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        return;
    
    isHiddenbtSplit=!isHiddenbtSplit;
    [self.splitView setHidden:isHiddenbtSplit];
    if(isHiddenbtSplit)
    {
        [self.btSplitView setImage:[UIImage imageNamed:@"分屏开关"] forState:UIControlStateNormal ];
    }
    else
    {
        [self.btSplitView setImage:[UIImage imageNamed:@"分屏开关1"] forState:UIControlStateNormal ];
    }
}

-(IBAction)btVideoSession :(id)sender
{
    UserListViewController *userListViewController=[[[UserListViewController alloc]initWithNibName:@"UserListViewController" bundle:nil]autorelease];
    UISubLRNavgationViewController *nalginController = [[[UISubLRNavgationViewController alloc] initWithRootViewController:userListViewController]autorelease];
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
    }
    else
    {
        
    }
    [self.videoSessionViewController presentViewController:nalginController animated:YES completion:nil];

  
}

-(IBAction)btNetwork:(id)sender
{
    
}

-(IBAction)btPhoneNumber:(id)sender
{
    
}

-(IBAction)btAddUser:(id)sender
{
    self.inviteGroupsViewController=[[[InviteGroupsViewController alloc]initWithNibName:@"InviteGroupsViewController" bundle:Nil]autorelease];
 
    UINavigationController* groupsViewControllerNavCtrl = [[[UINavigationController alloc] initWithRootViewController:inviteGroupsViewController]autorelease];
 
    [self.videoSessionViewController presentViewController:groupsViewControllerNavCtrl animated:NO completion:nil];
    
    groupsViewControllerNavCtrl.view.transform=CGAffineTransformMakeRotation(M_PI/2);
    [groupsViewControllerNavCtrl.view setFrame:[UIScreen mainScreen].bounds];
    
}

-(void)initToolBar
{
    UIImage*RefreshImage= [UIImage imageNamed:@"刷新"];
    CGRect RefreshFrame=CGRectMake(0, 0,58,40);
    self.btRefreshBbutton= [[[UIButton alloc] initWithFrame:RefreshFrame]autorelease];
    [ self.btRefreshBbutton setImage:RefreshImage forState:UIControlStateNormal];
    [ self.btRefreshBbutton addTarget:self action:@selector(btRefresh:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem* RefreshItem= [[[UIBarButtonItem alloc] initWithCustomView:self.btRefreshBbutton]autorelease];
    
    UIImage*SoundOffImage= [UIImage imageNamed:@"禁音"];
    CGRect SoundOffFrame=CGRectMake(0, 0,58,40);
    self.btSoundOffBbutton= [[[UIButton alloc] initWithFrame:SoundOffFrame]autorelease];
    [ self.btSoundOffBbutton setImage:SoundOffImage forState:UIControlStateNormal];
    [ self.btSoundOffBbutton addTarget:self action:@selector(btSoundOff:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem* SoundOffItem= [[[UIBarButtonItem alloc] initWithCustomView:self.btSoundOffBbutton]autorelease];
    
    UIImage*SwitchCameraImage= [UIImage imageNamed:@"切换摄像头"];
    CGRect SwitchCameraFrame=CGRectMake(0, 0,58,40);
    self.btSwitchCamera= [[[UIButton alloc] initWithFrame:SwitchCameraFrame]autorelease];
    [ self.btSwitchCamera setImage:SwitchCameraImage forState:UIControlStateNormal];
    [ self.btSwitchCamera addTarget:self action:@selector(btSwitchCamera:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem* SwitchCameraItem= [[[UIBarButtonItem alloc] initWithCustomView:self.btSwitchCamera]autorelease];
    
    UIImage*SplitViewImage= [UIImage imageNamed:@"分屏开关"];
    CGRect SplitViewFrame=CGRectMake(0, 0,58,40);
    self.btSplitView= [[[UIButton alloc] initWithFrame:SplitViewFrame]autorelease];
    [ self.btSplitView setImage:SplitViewImage forState:UIControlStateNormal];
    [ self.btSplitView addTarget:self action:@selector(btSplitView:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem* SplitViewItem= [[[UIBarButtonItem alloc] initWithCustomView: self.btSplitView]autorelease];
    CGRect  splitViewFrame=CGRectMake(length+2*xpos, ypos+height-100,58,40*3);
   
    [ self.splitView  setFrame:splitViewFrame];
    
    splitViewFrame.origin.x+=58;
    [ self.InviteView  setFrame:splitViewFrame];
    
    UIImage*AddUserImage= [UIImage imageNamed:@"添加联系人"];
    CGRect AddUserFrame=CGRectMake(0, 0,58,40);
    self.btAddUser= [[[UIButton alloc] initWithFrame:AddUserFrame]autorelease];
    [ self.btAddUser setImage:AddUserImage forState:UIControlStateNormal];
    [ self.btAddUser addTarget:self action:@selector(btAddUser:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem* AddUserItem= [[[UIBarButtonItem alloc] initWithCustomView: self.btAddUser]autorelease];
    
    UIBarButtonItem *flexibleSpace = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil]autorelease]; //占位置，空格
    
    NSArray *items = [NSArray arrayWithObjects: RefreshItem,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,SoundOffItem,SwitchCameraItem,SplitViewItem,AddUserItem,nil];
    
    if(!pLoginServer->ISChairman())
    {
        [self.btAddUser setEnabled:NO];
        [self.btManage setEnabled:NO];
    }
    
    [self.toolbar setItems:items animated:NO];
}

-(void)btUserListPressed:(id)sender
{
    [self.btUserList setImage:[UIImage imageNamed:@"成员列表"]  forState:UIControlStateNormal];
    [self.videoSessionViewController ScrollViewWithPage:0];
}

-(void)btCharacterPressed:(id)sender
{
    [self.btCharacter setImage:[UIImage imageNamed:@"文字聊天"]  forState:UIControlStateNormal];
    [self.videoSessionViewController ScrollViewWithPage:2];
}

-(void)showButtons:(bool)isfullScreen
{
    [self.btUserList setHidden:isfullScreen];
    [self.btCharacter setHidden:isfullScreen];
    [self.toolbar setHidden:isfullScreen];
    [self.btFullScreen setHidden:isfullScreen];
    [self.btManage setHidden:isfullScreen];
   
    [self.navigationController.navigationBar setHidden:isfullScreen];
}

+ (NSString*)deviceString
{
    // 需要#import "sys/utsname.h"
    struct utsname systemInfo;
    uname(&systemInfo);
    NSString *deviceString = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    
    if ([deviceString isEqualToString:@"iPhone1,1"])    return @"iPhone 1G";
    if ([deviceString isEqualToString:@"iPhone1,2"])    return @"iPhone 3G";
    if ([deviceString isEqualToString:@"iPhone2,1"])    return @"iPhone 3GS";
    if ([deviceString isEqualToString:@"iPhone3,1"])    return @"iPhone 4";
    if ([deviceString isEqualToString:@"iPhone4,1"])    return @"iPhone 4S";
    if ([deviceString isEqualToString:@"iPhone5,2"])    return @"iPhone 5";
    if ([deviceString isEqualToString:@"iPhone3,2"])    return @"Verizon iPhone 4";
    if ([deviceString isEqualToString:@"iPod1,1"])      return @"iPod Touch 1G";
    if ([deviceString isEqualToString:@"iPod2,1"])      return @"iPod Touch 2G";
    if ([deviceString isEqualToString:@"iPod3,1"])      return @"iPod Touch 3G";
    if ([deviceString isEqualToString:@"iPod4,1"])      return @"iPod Touch 4G";
    if ([deviceString isEqualToString:@"iPod5,1"])      return @"iPod Touch 5G";
    
    if ([deviceString isEqualToString:@"iPad1,1"])      return @"iPad";
    if ([deviceString isEqualToString:@"iPad2,1"])      return @"iPad 2 (WiFi)";
    if ([deviceString isEqualToString:@"iPad2,2"])      return @"iPad 2 (GSM)";
    if ([deviceString isEqualToString:@"iPad2,3"])      return @"iPad 2 (CDMA)";
    if ([deviceString isEqualToString:@"i386"])         return @"Simulator";
    if ([deviceString isEqualToString:@"x86_64"])       return @"Simulator";
    NSLog(@"NOTE: Unknown device type: %@", deviceString);
    return deviceString;
}

-(void)setFullScreen
{
    
    [self.videoWindow1 setHidden:YES];
    [self.videoWindow2 setHidden:YES];
    [self.videoWindow3 setHidden:YES];
    [self.videoWindow4 setHidden:YES];
     self.fullScreen=!self.fullScreen;
    
    [self showButtons:self.fullScreen];
    
     [self.navigationController.view setFrame:[UIScreen mainScreen].applicationFrame];
 
    if (self.fullScreen)
    {
         
//        NSString*str= [VideoSessionViewController deviceString];
        
//        if ([str isEqualToString:@"iPhone 5"]||[str isEqualToString:@"iPod Touch 5G"])
//        {
//            xpos=46;
//            ypos=46;
//              
//            
//            
//                int _screenWidth = [UIScreen mainScreen].applicationFrame.size.width;
//            height=_screenWidth;//翻转后的屏幕高度
//            length=[UIScreen mainScreen].applicationFrame.size.height;;//翻转后的屏幕长度
//            subImageViewPosy=0;//第一个小视频窗口的Y坐标
//            subImageViewDis=1;//小视频窗口的纵向距离
//            subheight=(height-subImageViewDis*2)/3+1;//小视频窗口的高度
//            sublength=subheight*4/3;//小视频窗口的宽度
//            
//            
//         }
//        else
//        {
             xpos=40;
            ypos=40;
         
            int _screenWidth = [UIScreen mainScreen].applicationFrame.size.width;
            
            height=_screenWidth;//翻转后的屏幕高度
            length=height*3/2;//翻转后的屏幕长度
            subImageViewPosy=0;//第一个小视频窗口的Y坐标
            subImageViewDis=2;//小视频窗口的纵向距离
            subheight=(height-subImageViewDis*2)/3+1;//小视频窗口的高度
            sublength=subheight*4/3;//小视频窗口的宽度
            
//            
//              
//        }
//        
        
        [self.videoSessionViewController loadScrollViewWithPage:1];
        [self.videoSessionViewController ScrollViewWithPage:1];
 
        [NSThread detachNewThreadSelector:@selector(BeginVideoThread:) toTarget:self withObject:nil];
        
    }
    else
    {
        xpos=46;
        ypos=46;
        
        int _screenWidth = [UIScreen mainScreen].bounds.size.width;
       
        height=_screenWidth-100;//翻转后的屏幕高度
        length=height*3/2;//翻转后的屏幕长度
        subImageViewPosy=6;//第一个小视频窗口的Y坐标
        subImageViewDis=1;//小视频窗口的纵向距离
        subheight=(height-subImageViewDis*2)/3+1;//小视频窗口的高度-subImageViewPosy*2
        sublength=subheight*4/3;//小视频窗口的宽度
        
         
        [self.videoSessionViewController loadScrollViewWithPage:1];
        [self.videoSessionViewController ScrollViewWithPage:1];
        [NSThread detachNewThreadSelector:@selector(BeginVideoThread:) toTarget:self withObject:nil];
        
        ypos=6;
    }
    /*
    switch (self.fullScreenType)
    {
        case btSplitScreen1:
        {
            [self SplitScreen1];
        }
            break;
        case btSplitScreen2:
        {
            [self SplitScreen2];
        }
            break;
        case btSplitScreen4:
        {
            [self SplitScreen4];
        }
            break;
        case toucvideoWindow1:
        {
            [self ToucvideoWindow1];
        }
            break;
        case toucvideoWindow2:
        {
            [self ToucvideoWindow2];
        }
            break;
        case toucvideoWindow3:
        {
            [self ToucvideoWindow3];
        }
            break;
        case toucvideoWindow4:
        {
            [self ToucvideoWindow4];
        }
            break;
        default:
            [self SplitScreen4];
            break;
    }*/
  
}

-(void)btFullScreenPressed:(id)sender
{
    if (!isHiddenbtSplit) {
        isHiddenbtSplit=!isHiddenbtSplit;
        [self.splitView setHidden:isHiddenbtSplit];
        if(isHiddenbtSplit)
        {
            [self.btSplitView setImage:[UIImage imageNamed:@"分屏开关"] forState:UIControlStateNormal ];
        }
        else
        {
            [self.btSplitView setImage:[UIImage imageNamed:@"分屏开关1"] forState:UIControlStateNormal ];
        }
    }
    
    [self setFullScreen];
}

-(void)initButtons
{
    self.btUserList = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.btUserList setFrame:CGRectMake(length+2*xpos, ypos,80,32)];
    [self.btUserList setTitleColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:1]
                           forState:UIControlStateNormal];
    self.btUserList.autoresizingMask = UIViewAutoresizingFlexibleTopMargin|UIViewAutoresizingFlexibleBottomMargin|UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleWidth;
    [self.btUserList addTarget:self action:@selector(btUserListPressed:)forControlEvents:UIControlEventTouchUpInside];
    [self.btUserList setImage:[UIImage imageNamed:@"成员列表"]  forState:UIControlStateNormal];
    [self.btUserList setTitle :@"成员列表" forState:UIControlStateNormal];
    [self.view addSubview:self.btUserList];
    
    self.btCharacter = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.btCharacter setFrame:CGRectMake(length+2*xpos, ypos+36,80,32)];
    [self.btCharacter setTitleColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:1]
                           forState:UIControlStateNormal];
    self.btCharacter.autoresizingMask = UIViewAutoresizingFlexibleTopMargin|UIViewAutoresizingFlexibleBottomMargin|UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleWidth;
    [self.btCharacter addTarget:self action:@selector(btCharacterPressed:)forControlEvents:UIControlEventTouchUpInside];
    [self.btCharacter setImage:[UIImage imageNamed:@"文字聊天"]  forState:UIControlStateNormal];
    [self.btCharacter setTitle :@"文字聊天" forState:UIControlStateNormal];
    [self.view addSubview:self.btCharacter];
    
    self.btFullScreen = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.btFullScreen setFrame:CGRectMake(length+2*xpos,ypos+72,80,32)];
    [self.btFullScreen setTitleColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:1]
                        forState:UIControlStateNormal];
    self.btFullScreen.autoresizingMask = UIViewAutoresizingFlexibleTopMargin|UIViewAutoresizingFlexibleBottomMargin|UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleWidth;
    [self.btFullScreen addTarget:self action:@selector(btFullScreenPressed:)forControlEvents:UIControlEventTouchUpInside];
    [self.btFullScreen setImage:[UIImage imageNamed:@"全屏显示"]  forState:UIControlStateNormal];
    [self.btFullScreen setTitle :@"全屏显示" forState:UIControlStateNormal];
    [self.view addSubview:self.btFullScreen];
    
    self.btManage = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.btManage setFrame:CGRectMake(length+2*xpos,ypos+108,80,32)];
    
    [self.btManage setTitleColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:1]
                        forState:UIControlStateNormal];
    self.btManage.autoresizingMask = UIViewAutoresizingFlexibleTopMargin|UIViewAutoresizingFlexibleBottomMargin|UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleWidth;
    [self.btManage addTarget:self action:@selector(BtManagePressed:)forControlEvents:UIControlEventTouchUpInside];
    [self.btManage setImage:[UIImage imageNamed:@"会场控制"]  forState:UIControlStateNormal];
    [self.btManage setTitle :@"会场控制" forState:UIControlStateNormal];
    [self.view addSubview:self.btManage];
}

 -(IBAction)LongToucvideoWindow1:(UIGestureRecognizer*)sender
{
    //if (self.fullScreen) {
    //
    //    [self setFullScreen];
    //}
    if(fullScreenType==btSplitScreen1 || fullScreenType==btSplitScreen2)
        return;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        return;
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), btSplitScreen4);
    [self SplitScreen4];
 }

-(IBAction)LongToucvideoWindow2:(UIGestureRecognizer*)sender
{
    //if (self.fullScreen) {
    //
    //    [self setFullScreen];
    // }
    if(fullScreenType==btSplitScreen1 || fullScreenType==btSplitScreen2)
        return;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        return;
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), btSplitScreen4);
    [self SplitScreen4];
}

-(IBAction)LongToucvideoWindow3:(UIGestureRecognizer*)sender
{
   // if (self.fullScreen) {
   //
   //     [self setFullScreen];
   // }
    if(fullScreenType==btSplitScreen1 || fullScreenType==btSplitScreen2)
        return;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        return;
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), btSplitScreen4);
    [self SplitScreen4];
}

-(IBAction)LongToucvideoWindow4:(UIGestureRecognizer*)sender
{
    //if (self.fullScreen) {
    //
    //    [self setFullScreen];
    //}
    if(fullScreenType==btSplitScreen1 || fullScreenType==btSplitScreen2)
        return;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
        return;
    
    if(pLoginServer->ISChairman())
        pLoginServer->OnScreenControl(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), btSplitScreen4);
    [self SplitScreen4];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
   isstop=NO;
    CGSize ImSize;
    ImSize.width=60;
    ImSize.height=40;
//    self.navigationItem.leftBarButtonItem = CREATE_BARITEM_WITH_CUSTOMVIEW([Custom createItemWithTitle:nil
//																								 image:@"退出0"
//																								target:self
//																								action:@selector(BtBack:)]);
//	self.navigationItem.rightBarButtonItem = CREATE_BARITEM_WITH_CUSTOMVIEW([Custom createItemWithTitle:nil
//																								 image:@"配置"
//																								target:self
//																								action:@selector(BtSet:)]);
     [self.navigationController setNavigationBarHidden:YES];
    
    CGRect framelen=[[UIScreen mainScreen] bounds];
    
    int len=(framelen.size.height>framelen.size.width)?framelen.size.height:framelen.size.width;
   
    
//    CGRect frame = self.navigationController.navigationBar.frame;
    
   UIView * alphaView = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, len,32)]autorelease];
    
   UIButton*btnleft= [Custom createItemWithTitle:nil
                          image:@"退出0"
                         target:self
                         action:@selector(BtBack:)];
    [btnleft setFrame:CGRectMake(0, 2, 52, 29)];
    [alphaView addSubview:btnleft];
    
    UIButton*btnright= [Custom createItemWithTitle:nil
                      																							 image:@"配置"
                       																							target:self
                     																								action:@selector(BtSet:)];
    [btnright setFrame:CGRectMake(len-52,2 , 52, 29)];
    [alphaView addSubview:btnright];
    
    
     alphaView.backgroundColor = [UIColor grayColor];
     alphaView.alpha = 0.7;
    [self.navigationController.view insertSubview:alphaView belowSubview:self.navigationController.navigationBar];
      [self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"bigShadow.png"] forBarMetrics:UIBarMetricsCompact];
   self.navigationController.navigationBar.layer.masksToBounds = YES;
//
    [self.lable1 removeFromSuperview];
    [self.lable1 setFrame:CGRectMake(0,0,80,20)];
    
    [self.videoWindow1 addSubview:self.lable1];
    
    [self.lable2 removeFromSuperview];
    [self.lable2 setFrame:CGRectMake(0,0,80,20)];
    [self.videoWindow2 addSubview:self.lable2];
    
    [self.lable3  removeFromSuperview];
    
    
    [self.lable3 setFrame:CGRectMake(0,0,80,20)];
    [self.videoWindow3 addSubview:self.lable3];
    
    [self.lable4 removeFromSuperview];
    [self.lable4 setFrame:CGRectMake(0,0,80,20)];
    [self.videoWindow4 addSubview:self.lable4];
    
  
    [self.view addSubview:self.videoWindow1];
    
    [self.view addSubview:self.videoWindow2];
    
    
    [self.view addSubview:self.videoWindow3];
    
    
    [self.view addSubview:self.videoWindow4];
    

    pLoginServer = LoginServer::OnGetLoginServer();
    pLoginServer->m_MMGetRoomControl = self;
    
    if(pLoginServer->ISChairman())
        strSpeekUserID = pLoginServer->GetUserID();
    
    UILongPressGestureRecognizer *longpressGesutre1=[[[UILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(LongToucvideoWindow1:)]autorelease];
    longpressGesutre1.minimumPressDuration=1;
        
    longpressGesutre1.numberOfTouchesRequired=1;
   
    [self.videoWindow1 addGestureRecognizer:longpressGesutre1];
    
    UILongPressGestureRecognizer *longpressGesutre2=[[[UILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(LongToucvideoWindow2:)]autorelease];
    longpressGesutre2.minimumPressDuration=1;
  
    longpressGesutre2.numberOfTouchesRequired=1;
    
    [self.videoWindow2 addGestureRecognizer:longpressGesutre2];
    
    UILongPressGestureRecognizer *longpressGesutre3=[[[UILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(LongToucvideoWindow3:)]autorelease];
    longpressGesutre3.minimumPressDuration=1;
   
    longpressGesutre3.numberOfTouchesRequired=1;
    
    [self.videoWindow3 addGestureRecognizer:longpressGesutre3];
    
    UILongPressGestureRecognizer *longpressGesutre4=[[[UILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(LongToucvideoWindow4:)]autorelease];
    longpressGesutre4.minimumPressDuration=1;
 
    longpressGesutre4.numberOfTouchesRequired=1;
    
    [self.videoWindow4 addGestureRecognizer:longpressGesutre4];
    
    UITapGestureRecognizer *RecognizervideoWindow1= [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(toucvideoWindow1:)]autorelease];
    [self.videoWindow1 addGestureRecognizer:RecognizervideoWindow1];
    
    UITapGestureRecognizer *doubleTap = [[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(handleDoubleTap1:)]autorelease];
    doubleTap.numberOfTapsRequired = 2;
    doubleTap.numberOfTouchesRequired = 1;
    [self.videoWindow1 addGestureRecognizer: doubleTap];
      [RecognizervideoWindow1 requireGestureRecognizerToFail:doubleTap];
    
    UITapGestureRecognizer *RecognizervideoWindow2= [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(toucvideoWindow2:)]autorelease];
    [self.videoWindow2 addGestureRecognizer:RecognizervideoWindow2];
    
    UITapGestureRecognizer *doubleTap2 = [[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(handleDoubleTap2:)] autorelease];
    doubleTap2.numberOfTapsRequired = 2;
    doubleTap2.numberOfTouchesRequired = 1;
    [self.videoWindow2 addGestureRecognizer: doubleTap2];
    [RecognizervideoWindow2 requireGestureRecognizerToFail:doubleTap2];
    
    UITapGestureRecognizer *RecognizervideoWindow3= [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(toucvideoWindow3:)]autorelease];
    [self.videoWindow3 addGestureRecognizer:RecognizervideoWindow3];
    
    UITapGestureRecognizer *doubleTap3 = [[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(handleDoubleTap3:)] autorelease];
    doubleTap3.numberOfTapsRequired = 2;
    doubleTap3.numberOfTouchesRequired = 1;
    [self.videoWindow3 addGestureRecognizer: doubleTap3];
    
    [RecognizervideoWindow3 requireGestureRecognizerToFail:doubleTap3];
    
    
    UITapGestureRecognizer *doubleTap4 = [[[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(handleDoubleTap4:)] autorelease];
    doubleTap4.numberOfTapsRequired = 2;
    doubleTap4.numberOfTouchesRequired = 1;
    [self.videoWindow4 addGestureRecognizer: doubleTap4];
    
    UITapGestureRecognizer *RecognizervideoWindow4= [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(toucvideoWindow4:)]autorelease];
    [self.videoWindow4 addGestureRecognizer:RecognizervideoWindow4];
    
    
    [RecognizervideoWindow4 requireGestureRecognizerToFail:doubleTap4];
   
    
    minitAudio = [[[initAudio alloc]init]autorelease];
    [minitAudio initAudios];
    [self initButtons];
    self.title =@"会议模式";
    [self initToolBar];
    
    for(int i = 1;i<=4;i++)
    {
        ScreenControlinfo* pScreenControlinfo = new ScreenControlinfo;
        pScreenControlinfo->strUserID = "";
        pScreenControlinfo->bIsOpenVideo = false;
        pScreenControlinfo->bIsTurn = false;
        if(i==1)
            pScreenControlinfo->pvideoWindow = self.videoWindow1;
        else if(i==2)
            pScreenControlinfo->pvideoWindow = self.videoWindow2;
        else if(i==3)
            pScreenControlinfo->pvideoWindow = self.videoWindow3;
        else if(i==4)
            pScreenControlinfo->pvideoWindow = self.videoWindow4;
        ScreenControlinfoMap[i] = pScreenControlinfo;
    }

    [self RoomManagement];
    
    
    SCREENCONTROLINFOMAP::iterator it = ScreenControlinfoMap.begin();
    while(it!=ScreenControlinfoMap.end())
    {
        if(it->second->strUserID == pLoginServer->GetUserID())
        {
            CGRect frame=it->second->pvideoWindow.frame;
            
            if (IsFrontVideo) {
                it->second->pvideoWindow.transform=CGAffineTransformMakeRotation(M_PI*3/2);
                
            }
            else
                
            {
                it->second->pvideoWindow.transform=CGAffineTransformMakeRotation(M_PI/2);
            }
            
            [it->second->pvideoWindow SetOpenglFrame:frame];
            
            break;
        }
        it++;
    }
//    UISubNavigationController *nav = (UISubNavigationController *)self.navigationController;
//     [self setbackground];
   
//     [self splitScreen];
}

-(void)stopShowVideo
{
    if(pOpenLocalUser)
        pOpenLocalUser->setVideoWindow(nil);
}

-(void)startShowVideo
{
    //if(pOpenLocalUser)
       // pOpenLocalUser->setVideoWindow(self.videoWindow1);
    [self setLocalVideoWindow];
}

-(void)dealloc
{
    self.videoSessionViewController=nil;
    self.inviteGroupsViewController=nil;
    self.videoWindow1=nil;
    self.videoWindow2=nil;
    self.videoWindow3=nil;
    self.videoWindow4=nil;
    self.videoAndVoiceViewController=nil;
    self.btUserList=nil;
    self.btCharacter=nil;
    self.btFullScreen=nil;
    self.btManage=nil;
    
    self.splitView=nil;
    self.toolbar=nil;
    self.InviteView=nil;
    self.btSoundOffBbutton=nil;
    self.btRefreshBbutton=nil;
    self.btSwitchCamera=nil;
    self.btSplitView=nil;
    self.btAddUser=nil;
    //[minitAudio dealloc];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) OnOpenUserVideo:(std::string) strFromUserID strUserId:(std::string)strUserId ulRoomID:(unsigned long)ulRoomID ulUserVideoID:(unsigned long)ulUserVideoID uiScreenControl:(unsigned int)uiScreenControl
{
    if(!bIsEnterRoom)
        return;
    mstrFromUserID = strFromUserID;
    strPeerUserID = strUserId;
    m_uiScreenControl = uiScreenControl;
    [self performSelectorOnMainThread:@selector(OpenUserVideo:) withObject:self waitUntilDone:YES];
}

-(void) OnCloseUserVideo:(std::string) strFromUserID strUserId:(std::string)strUserId ulRoomID:(unsigned long)ulRoomID ulUserVideoID:(unsigned long)ulUserVideoID
{
    if(!bIsEnterRoom)
        return;
    mstrFromUserID = strFromUserID;
    strPeerUserID = strUserId;
    [self performSelectorOnMainThread:@selector(CloseUserVideo:) withObject:self waitUntilDone:YES];
}

-(void) OnOpenUserAudio:(std::string) strFromUserID strUserId:(std::string)strUserId ulRoomID:(unsigned long)ulRoomID ulUserAudioID:(unsigned long)ulUserAudioID
{
    if(!bIsEnterRoom)
        return;
    mstrFromUserID = strFromUserID;
    strPeerUserID = strUserId;
    [self performSelectorOnMainThread:@selector(OpenUserAudio:) withObject:self waitUntilDone:YES];
}

-(void) OnCloseUserAudio:(std::string) strFromUserID strUserId:(std::string)strUserId ulRoomID:(unsigned long)ulRoomID ulUserAudioID:(unsigned long)ulUserAudioID
{
    if(!bIsEnterRoom)
        return;
    mstrFromUserID = strFromUserID;
    strPeerUserID = strUserId;
    [self performSelectorOnMainThread:@selector(CloseUserAudio:) withObject:self waitUntilDone:YES];
}

-(void) OnMeetingType:(unsigned long)ulRoomID uiType:(unsigned int)uiType
{
    if(!bIsEnterRoom)
        return;
    
    self.isSoundOff = NO;
    [self.btSoundOffBbutton setImage:[UIImage imageNamed:@"禁音"] forState:UIControlStateNormal];
    if(pOpenLocalUser)
        pOpenLocalUser->SendAudioData();
    
    if(pLoginServer->ISChairman())
        return;
    
    switch (uiType)
    {
        case ROOM_VIDEO_PUSH:
        {
            uiRoomVideoType = ROOM_VIDEO_PUSH;
            [self performSelectorOnMainThread:@selector(MySetVideoMeetingType:) withObject:self waitUntilDone:YES];
        }
            break;
        case ROOM_VIDEO_ROOM:
        {
            uiRoomVideoType = ROOM_VIDEO_ROOM;
            [self performSelectorOnMainThread:@selector(MySetVideoMeetingType:) withObject:self waitUntilDone:YES];
        }
            break;
        case ROOM_AUDIO_SPEAK:
        {
            uiRoomAudioType = ROOM_AUDIO_SPEAK;
            [self performSelectorOnMainThread:@selector(MySetAudioMeetingType:) withObject:self waitUntilDone:YES];
        }
            break;
        case ROOM_AUDIO_DISCUSS:
        {
            uiRoomAudioType = ROOM_AUDIO_DISCUSS;
            [self performSelectorOnMainThread:@selector(MySetAudioMeetingType:) withObject:self waitUntilDone:YES];
        }
            break;
        default:
            break;
    }
}

-(void)MySetVideoMeetingType:(id)mid
{
    if(uiRoomVideoType == ROOM_VIDEO_PUSH)
    {
        [self User_CloseAllVideo];
    }
    NSString *VideoType=nil;
    NSString *AudioType=nil;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH)
    {
        VideoType=[[[NSString alloc]initWithCString:"推送" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        VideoType=[[[NSString alloc]initWithCString:"会议" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    if(uiRoomAudioType == ROOM_AUDIO_SPEAK)
    {
        AudioType=[[[NSString alloc]initWithCString:"发言" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomAudioType == ROOM_AUDIO_DISCUSS)
    {
        AudioType=[[[NSString alloc]initWithCString:"讨论" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    NSString *UserID=[[[NSString alloc]initWithCString:pLoginServer->GetUserID().c_str() encoding: NSUTF8StringEncoding] autorelease];
    self.title = [[[NSString alloc]initWithFormat:@"会议模式:视频(%@)、音频(%@)、用户(%@)",VideoType,AudioType,UserID]autorelease];
    
}

-(void)MySetAudioMeetingType:(id)mid
{
    if(uiRoomAudioType == ROOM_AUDIO_SPEAK)
    {
        //User_CloseAllAudio
    }
    else
    {
        
    }
    NSString *VideoType=nil;
    NSString *AudioType=nil;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH)
    {
        VideoType=[[[NSString alloc]initWithCString:"推送" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        VideoType=[[[NSString alloc]initWithCString:"会议" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    if(uiRoomAudioType == ROOM_AUDIO_SPEAK)
    {
        AudioType=[[[NSString alloc]initWithCString:"发言" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomAudioType == ROOM_AUDIO_DISCUSS)
    {
        AudioType=[[[NSString alloc]initWithCString:"讨论" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    NSString *UserID=[[[NSString alloc]initWithCString:pLoginServer->GetUserID().c_str() encoding: NSUTF8StringEncoding] autorelease];
    self.title = [[[NSString alloc]initWithFormat:@"会议模式:视频(%@)、音频(%@)、用户(%@)",VideoType,AudioType,UserID]autorelease];
}

-(void) OnScreenControl:(std::string)strUserID ulRoomID:(unsigned long)ulRoomID uiScreenCount:(unsigned int)uiScreenCount
{
    if(!bIsEnterRoom)
        return;
    uiScreenNum = uiScreenCount;
    [self performSelectorOnMainThread:@selector(SetScreenControl:) withObject:self waitUntilDone:YES];
}

-(void) OnForTheFloor:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID strHostID:(const std::string&)strHostID
{
    if(!bIsEnterRoom)
        return;
    strPeerUserID = strUserID;
    [self performSelectorOnMainThread:@selector(OnForTheFloor:) withObject:self waitUntilDone:YES];
}

-(void) OnPassPrivileges:(const std::string&)strHostID ulRoomID:(unsigned long)ulRoomID
{
    if(!bIsEnterRoom)
        return;
    [self performSelectorOnMainThread:@selector(OnPassPrivileges:) withObject:self waitUntilDone:YES];
}

-(void) OnUserReplyInviteUser:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID bIsAgree:(bool)bIsAgree
{
    if(!bIsEnterRoom)
        return;
    strReplyInviteUser = strUserID;
    [self performSelectorOnMainThread:@selector(OnUserReplyInviteUser:) withObject:self waitUntilDone:YES];
}

-(void) OnUserSnedMsg:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID strPeerUserID:(const std::string&)PeerUserID ulUserMsg:(std::string&)ulUserMsg
{
    if(!bIsEnterRoom)
        return;
    
    strUserMsg = ulUserMsg;
    strPeerUserID = strUserID;
    [self performSelectorOnMainThread:@selector(OnUserSnedMsg:) withObject:self waitUntilDone:YES];
}

-(void) OnForTheFloor:(id)mid
{
    NSString *UserID=[[[NSString alloc]initWithCString:strPeerUserID.c_str() encoding: NSUTF8StringEncoding] autorelease];
    NSString *Userinfo = [[[NSString alloc]initWithFormat:@"用户%@申请发言",UserID]autorelease];
    ForTheFloor = [[UIAlertView alloc] initWithTitle:Userinfo message:@""
                                                   delegate:self cancelButtonTitle:@"拒绝" otherButtonTitles:@"同意", nil];
	ForTheFloor.alertViewStyle = UIAlertViewStyleDefault;
    [ForTheFloor show];
	[ForTheFloor release];
}

- (void)alertView:(UIAlertView *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if(ForTheFloor == actionSheet)
    {
        if (buttonIndex == 1)
        {
            [self User_CloseAllAudio];
            [self User_OpenPeerAudio:strPeerUserID];
        }
    }
    else if(QiutRoomalert == actionSheet)
    {
        if (buttonIndex == 0)
        {
            [self back];
        }
        QiutRoomalert = nil;
    }
}

-(void) OnPassPrivileges:(id)mid
{
    if(self.videoSessionViewController!=nil)
    {
        [self.videoSessionViewController.sessionInfoViewController MyUpdateMeetingInfo:self];
    }
    if(!pLoginServer->ISChairman())
    {
        [self.btAddUser setEnabled:NO];
        [self.btManage setEnabled:NO];
    }
    else
    {
        [self.btAddUser setEnabled:YES];
        [self.btManage setEnabled:YES];
    }
}

-(void) OnUserReplyInviteUser:(id)mid
{
    //strReplyInviteUser
    NSString *UserID=[[[NSString alloc]initWithCString:strReplyInviteUser.c_str() encoding: NSUTF8StringEncoding] autorelease];
    NSString *Userinfo = [[[NSString alloc]initWithFormat:@"用户%@拒绝邀请",UserID]autorelease];
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"" message:Userinfo
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];
    [alert release];
}

-(void) OnUserSnedMsg:(id)mid
{
    NSString* info = [NSString stringWithCString:strUserMsg.c_str() encoding:NSUTF8StringEncoding];
    NSString* strUserName = [NSString stringWithCString:strPeerUserID.c_str() encoding:NSUTF8StringEncoding];
    NSString* strGetInfo = [NSString stringWithFormat:@"%@%@%@",strUserName,@"说:",info];

    if(self.sessionChatViewController!=nil)
        [self.sessionChatViewController GetMassage:strGetInfo];
}

-(void)SetMeetingType:(unsigned int)uiVideoType uiAudioType:(unsigned int)uiAudioType
{
    if(!bIsEnterRoom)
        return;
    
    if(uiRoomVideoType != uiVideoType)
    {
        uiRoomVideoType = uiVideoType;
        pLoginServer->OnSetMeetingType(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), uiRoomVideoType);
        
        if(uiRoomVideoType == ROOM_VIDEO_PUSH)
        {
            [self User_OpenHostAllVideo];
        }
    }
    
    if(uiRoomAudioType != uiAudioType)
    {
        uiRoomAudioType = uiAudioType;
        pLoginServer->OnSetMeetingType(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), uiRoomAudioType);
        
        if(uiRoomAudioType == ROOM_AUDIO_SPEAK)
        {
            [self User_CloseAllAudio];
            [self User_OpenLocalAudio:pLoginServer->GetUserID() IsSendData:true];
        }
        else
        {
            [self User_OpenAllAudio];
        }
    }
    NSString *VideoType=nil;
    NSString *AudioType=nil;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH)
    {
        VideoType=[[[NSString alloc]initWithCString:"推送" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        VideoType=[[[NSString alloc]initWithCString:"会议" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    if(uiRoomAudioType == ROOM_AUDIO_SPEAK)
    {
        AudioType=[[[NSString alloc]initWithCString:"发言" encoding: NSUTF8StringEncoding] autorelease];
    }
    if(uiRoomAudioType == ROOM_AUDIO_DISCUSS)
    {
        AudioType=[[[NSString alloc]initWithCString:"讨论" encoding: NSUTF8StringEncoding] autorelease];
    }
    
    NSString *UserID=[[[NSString alloc]initWithCString:pLoginServer->GetUserID().c_str() encoding: NSUTF8StringEncoding] autorelease];
    self.title = [[[NSString alloc]initWithFormat:@"会议模式:视频(%@)、音频(%@)、用户(%@)",VideoType,AudioType,UserID]autorelease];
}

-(void)UpdatedLocalVideo
{
    bool bIsSendVideo = false;
    if(pOpenLocalUser->IsOpenVideo())
    {
        if(pOpenLocalUser->IsSendVideoData())
        {
            pOpenLocalUser->StopSendVideoData();
            bIsSendVideo = true;
        }
        pOpenLocalUser->CloseVideo();
        pOpenLocalUser->setVideoWindow(nil);

        unsigned int uiScreen = 0;
        iOSGLView* pView = [self GetWindow:pLoginServer->GetUserID() uiScreen:uiScreen IsSet:false];
        assert(pView);
        
        unsigned int uiWidth = 0;
        unsigned int uiHeight = 0;
        unsigned int uiVideoFps = 0;
        unsigned int uiBitRate = 0;
        
        VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
        p->GetResolution(uiWidth, uiHeight);
        uiVideoFps = p->GetVideoFps();
        uiBitRate = p->GetBitRate();
        
        if(!pOpenLocalUser->IsOpenVideo())
            pOpenLocalUser->OpenVideo(pView, pLoginServer->GetLocalVideoId(), uiWidth, uiHeight, uiBitRate, uiVideoFps);
        if(bIsSendVideo && !pOpenLocalUser->IsSendVideoData())
            pOpenLocalUser->SendVideoData();
        
    }
}

-(void)SetScreenControl:(id)mid
{
    if(!bIsEnterRoom)
        return;
    
    if(uiRoomVideoType == ROOM_VIDEO_PUSH && !pLoginServer->ISChairman())
    {
        switch (uiScreenNum)
        {
            case btSplitScreen1:
            {
                [self SplitScreen1];
            }
                break;
            case btSplitScreen2:
            {
                [self SplitScreen2];
            }
                break;
            case btSplitScreen4:
            {
                [self SplitScreen4];
            }
                break;
            case toucvideoWindow1:
            {
                [self ToucvideoWindow1];
            }
                break;
            case toucvideoWindow2:
            {
                [self ToucvideoWindow2];
            }
                break;
            case toucvideoWindow3:
            {
                [self ToucvideoWindow3];
            }
                break;
            case toucvideoWindow4:
            {
                [self ToucvideoWindow4];
            }
                break;
                
        };
    }
}

-(void) OpenUserVideo:(id)mid
{
    if(strPeerUserID.empty())
        return;
    assert(pLoginServer);
    assert(pOpenLocalUser);
    
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        [self Room_OpenVideo_Room];
    }
    else if(uiRoomVideoType == ROOM_VIDEO_PUSH)
    {
        [self Room_OpenVideo_Push];
    }
}

-(void)Room_OpenVideo_Push
{
    if(strPeerUserID == pLoginServer->GetUserID())
    {
        if(pOpenLocalUser)
        {
            unsigned int uiScreen = m_uiScreenControl;
            iOSGLView* pView = [self GetWindow:pLoginServer->GetUserID() uiScreen:uiScreen IsSet:true];
            assert(pView);
            
            unsigned int uiWidth = 0;
            unsigned int uiHeight = 0;
            unsigned int uiVideoFps = 0;
            unsigned int uiBitRate = 0;
            
            VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
            p->GetResolution(uiWidth, uiHeight);
            uiVideoFps = p->GetVideoFps();
            uiBitRate = p->GetBitRate();
            
            if(!pOpenLocalUser->IsOpenVideo())
                pOpenLocalUser->OpenVideo(pView, pLoginServer->GetLocalVideoId(), uiWidth, uiHeight, uiBitRate, uiVideoFps);

            if(!pOpenLocalUser->IsSendVideoData())
                pOpenLocalUser->SendVideoData();
        }
        
        if(self.sessionInfoViewController!=nil)
            [self.sessionInfoViewController MyUpdateMeetingInfo:self];
        
        return;
    }
    
    unsigned int uiScreen = m_uiScreenControl;
    iOSGLView* pView = [self GetWindow:strPeerUserID uiScreen:uiScreen IsSet:true];
    if(pView!=nil)
    {
        [self User_OpenPeerVideo:strPeerUserID pView:pView uiScreen:uiScreen bIsBroadcast:true IsSendCommand:false];
    }
    
    if(self.sessionInfoViewController!=nil)
        [self.sessionInfoViewController MyUpdateMeetingInfo:self];
}

-(void) CloseUserVideo:(id)mid
{
    if(strPeerUserID.empty())
        return;
    assert(pLoginServer);
    assert(pOpenLocalUser);
    
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        [self Room_CloseVideo_Room];
    }
    else if(uiRoomVideoType == ROOM_VIDEO_PUSH)
    {
        [self Room_CloseVideo_Push];
    }
}

-(void)Room_CloseVideo_Push
{
    if(pLoginServer->ISChairman()&&strPeerUserID == pLoginServer->GetUserID())
    {
        if(self.sessionInfoViewController!=nil)
            [self.sessionInfoViewController MyUpdateMeetingInfo:self];
        return;
    }
    
    if(strPeerUserID == pLoginServer->GetUserID())
    {
        pOpenLocalUser->setVideoWindow(nil);
        SCREENCONTROLINFOMAP::iterator it = ScreenControlinfoMap.begin();
        while(it!=ScreenControlinfoMap.end())
        {
            if(it->second->strUserID == pLoginServer->GetUserID())
            {
               // [it->second->pvideoWindow setImage:[UIImage imageNamed:@""]];
                break;
            }
            it++;
        }
        pOpenLocalUser->ClearOpenMeVideoUser();
        if(pOpenLocalUser->IsSendVideoData())
            pOpenLocalUser->StopSendVideoData();
        if(pOpenLocalUser->IsOpenVideo())
            pOpenLocalUser->CloseVideo();
        
        
        [self CloseWindow:strPeerUserID];
        
        if(self.sessionInfoViewController!=nil)
            [self.sessionInfoViewController MyUpdateMeetingInfo:self];
        
        return;
    }
    
    [self User_ClosePeerVideo:strPeerUserID IsSendCommand:false bIsBroadcast:false];
    
    if(self.sessionInfoViewController!=nil)
        [self.sessionInfoViewController MyUpdateMeetingInfo:self];
}

-(void)Room_OpenVideo_Room
{
    if(strPeerUserID == pLoginServer->GetUserID())
    {
        if(pOpenLocalUser)
        {
            unsigned int uiWidth = 0;
            unsigned int uiHeight = 0;
            unsigned int uiVideoFps = 0;
            unsigned int uiBitRate = 0;
            
            VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
            p->GetResolution(uiWidth, uiHeight);
            uiVideoFps = p->GetVideoFps();
            uiBitRate = p->GetBitRate();
            
            if(!pOpenLocalUser->IsOpenVideo())
                pOpenLocalUser->OpenVideo(nil, pLoginServer->GetLocalVideoId(), uiWidth, uiHeight, uiBitRate, uiVideoFps);
        
            if(!pOpenLocalUser->IsSendVideoData())
                pOpenLocalUser->SendVideoData();
            pOpenLocalUser->AddOpenMeVideoUser(mstrFromUserID);
        }
        
        if(self.sessionInfoViewController!=nil)
            [self.sessionInfoViewController MyUpdateMeetingInfo:self];
        return;
    }
}

-(void)Room_CloseVideo_Room
{
    if(strPeerUserID == pLoginServer->GetUserID())
    {
#if 0
        if(pOpenLocalUser->OpenMeVideoCount() <= 1)
        {
            pOpenLocalUser->setVideoWindow(nil);
            
            if(pOpenLocalUser->IsSendVideoData())
                pOpenLocalUser->StopSendVideoData();
            if(pOpenLocalUser->IsOpenVideo())
                pOpenLocalUser->CloseVideo();
            
            SCREENCONTROLINFOMAP::iterator it = ScreenControlinfoMap.begin();
            while(it!=ScreenControlinfoMap.end())
            {
                if(it->second->strUserID == pLoginServer->GetUserID())
                {
                    [it->second->pvideoWindow setImage:[UIImage imageNamed:@""]];
                    break;
                }
                it++;
            }
            [self CloseWindow:pLoginServer->GetUserID()];
        }
#endif
        pOpenLocalUser->DeleteOpenMeVideoUser(mstrFromUserID);
        
        if(self.sessionInfoViewController!=nil)
            [self.sessionInfoViewController MyUpdateMeetingInfo:self];
        return;
    }
}

-(void) OpenUserAudio:(id)mid
{
    if(strPeerUserID.empty())
        return;
    assert(pLoginServer);
    assert(pOpenLocalUser);
    [self Room_OpenAudio_Discuss_Speak];
}

-(void) CloseUserAudio:(id)mid
{
    if(strPeerUserID.empty())
        return;
    assert(pLoginServer);
    assert(pOpenLocalUser);
    
    [self Room_CloseAudio_Discuss_Speak];
}

-(void)Room_OpenAudio_Discuss_Speak
{
    if(strPeerUserID == pLoginServer->GetUserID())
    {
        if(!pLoginServer->ISChairman()&&!pOpenLocalUser->IsOpenAudio())
            pOpenLocalUser->OpenAudio(pLoginServer->GetLocalAudioId(), AMR_NBCODE);
        if(!pLoginServer->ISChairman()&&!pOpenLocalUser->IsSendAudioData())
            pOpenLocalUser->SendAudioData();
        
        if(self.sessionInfoViewController!=nil)
            [self.sessionInfoViewController MyUpdateMeetingInfo:self];
        
        return;
    }
    
    //unsigned long ulPeerVideoId = pLoginServer->GetPeerUserVideoId(strPeerUserID);
    unsigned long ulPeerAudioId = pLoginServer->GetPeerUserAudioId(strPeerUserID);
    OpenRemoteUser* pOpenRemoteUser = NULL;
    OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.find(strPeerUserID);
    if(iter != OpenRemoteUserMap.end())
    {
        pOpenRemoteUser = iter->second;
        assert(pOpenRemoteUser);
    }
    
    if(pOpenRemoteUser == NULL)
    {
        pOpenRemoteUser = new OpenRemoteUser;
        pOpenRemoteUser->ConnectMediaServer(pLoginServer->GetServerIp(), pLoginServer->GetServerPort());
        OpenRemoteUserMap[strPeerUserID] = pOpenRemoteUser;
    }
    assert(pOpenRemoteUser);
    if(!pOpenRemoteUser->IsOpenAudio())
        pOpenRemoteUser->OpenAudio(AMR_NBCODE);
    if(!pOpenRemoteUser->IsStartReceiverAudio())
        pOpenRemoteUser->StartPeerAudioData(strPeerUserID, ulPeerAudioId);
    
    if(self.sessionInfoViewController!=nil)
        [self.sessionInfoViewController MyUpdateMeetingInfo:self];
}

-(void)Room_CloseAudio_Discuss_Speak
{
    if(pLoginServer->ISChairman()&&strPeerUserID == pLoginServer->GetUserID())
        return;
    
    if(strPeerUserID == pLoginServer->GetUserID())
    {
        pOpenLocalUser->ClearOpenMeAudioUser();
        if(pOpenLocalUser->IsSendAudioData())
            pOpenLocalUser->StopSendAudioData();
        if(pOpenLocalUser->IsOpenAudio())
            pOpenLocalUser->CloseAudio();
    }
    
    OpenRemoteUser* pOpenRemoteUser = NULL;
    OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.find(strPeerUserID);
    if(iter != OpenRemoteUserMap.end())
    {
        pOpenRemoteUser = iter->second;
        assert(pOpenRemoteUser);
    }
    
    if(pOpenRemoteUser)
    {
        if(pOpenRemoteUser->IsStartReceiverAudio())
            pOpenRemoteUser->StopPeerAudioData();
        if(pOpenRemoteUser->IsOpenAudio())
            pOpenRemoteUser->CloseAudio();
    }
    
    if(self.sessionInfoViewController!=nil)
        [self.sessionInfoViewController MyUpdateMeetingInfo:self];
}

-(bool)LocalUserIsOpenVideo
{
    if(pOpenLocalUser==NULL)
        return false;
    
    if(uiRoomVideoType == ROOM_VIDEO_ROOM)
    {
        return !m_Is5Window;
    }
    
    return pOpenLocalUser->IsOpenVideo();
}

-(bool)LocalUserIsOpenAudio
{
    if(pOpenLocalUser==NULL)
        return false;
    
    return pOpenLocalUser->IsOpenAudio();
}

-(bool)PeerUserIsOpenVideo:(std::string)strUserId
{
    OpenRemoteUser* pOpenRemoteUser = NULL;
    OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.find(strUserId);
    if(iter != OpenRemoteUserMap.end())
    {
        pOpenRemoteUser = iter->second;
        assert(pOpenRemoteUser);
        return pOpenRemoteUser->IsOpenVideo();
    }
    return false;
}

-(bool)PeerUserISOpenAudio:(std::string)strUserId
{
    OpenRemoteUser* pOpenRemoteUser = NULL;
    OPENREMOTEUSERMAP::iterator iter = OpenRemoteUserMap.find(strUserId);
    if(iter != OpenRemoteUserMap.end())
    {
        pOpenRemoteUser = iter->second;
        assert(pOpenRemoteUser);
        return pOpenRemoteUser->IsOpenAudio();
    }
    return false;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(void)SetChatShow:(bool)bisShow
{
    if(bisShow)
        [self.btCharacter setImage:[UIImage imageNamed:@"文字聊天1"]  forState:UIControlStateNormal];
    else
        [self.btCharacter setImage:[UIImage imageNamed:@"文字聊天"]  forState:UIControlStateNormal];
}

-(void)SetControlShow:(bool)bisShow
{
    if(bisShow)
        [self.btUserList setImage:[UIImage imageNamed:@"成员列表1"]  forState:UIControlStateNormal];
    else
        [self.btUserList setImage:[UIImage imageNamed:@"成员列表"]  forState:UIControlStateNormal];
        
}

@end
