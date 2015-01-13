//
//  SessionInfoViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-9.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "SessionInfoViewController.h"
#import "SessionInfoCell.h"
#import "VideoSessionViewController.h"
@interface SessionInfoViewController ()

@end

@implementation SessionInfoViewController
@synthesize tableview;
@synthesize roomUsrArray;
@synthesize actionSheetManageHasAAndV;
@synthesize actionSheetManageHasA;
@synthesize actionSheetManageHasV;
@synthesize actionSheetManage;
@synthesize actionSheetPower;
@synthesize videoSessionViewController;
@synthesize actionSheetattachUser;
@synthesize sessionShowViewController;
@synthesize toolbar;
@synthesize btRefreshBbutton;
@synthesize btAddUser;
@synthesize inviteGroupsViewController;
@synthesize actionInviteUsers;
@synthesize m_videoSessionID;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        self =[super initWithNibName:@"SessionInfoViewController_ipad" bundle:nil];
//    } else {
//        self =[super initWithNibName:@"SessionInfoViewController" bundle:nil];
//    }
    self =[super initWithNibName:@"SessionInfoViewController" bundle:nil];
    if (self) {
        // Custom initialization
    }
    if (self) {
        // Custom initialization
        pLoginServer = NULL;
        self.sessionShowViewController = nil;
        self.m_videoSessionID = 0;
        iReturnNum = 0;
        pLoginServer = LoginServer::OnGetLoginServer();
        RoomUserList.clear();
        pLoginServer->GetRoomUserList(RoomUserList);
        
    }
    return self;
}

-(IBAction)btback:(id)sender
{
    if (self.videoSessionViewController!=nil) {
        [self.videoSessionViewController ScrollViewWithPage:1];
    }
}

-(IBAction)btRefresh:(id)sender
{
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
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
    CGRect RefreshFrame=CGRectMake(0, 40,58,40);
    self.btRefreshBbutton= [[[UIButton alloc] initWithFrame:RefreshFrame]autorelease];
    [ self.btRefreshBbutton setImage:RefreshImage forState:UIControlStateNormal];
    [ self.btRefreshBbutton addTarget:self action:@selector(btRefresh:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem* RefreshItem= [[[UIBarButtonItem alloc] initWithCustomView:self.btRefreshBbutton]autorelease];
    
    UIImage*AddUserImage= [UIImage imageNamed:@"添加联系人"];
    CGRect AddUserFrame=CGRectMake(0, 40,58,40);
    self.btAddUser= [[[UIButton alloc] initWithFrame:AddUserFrame]autorelease];
    [ self.btAddUser setImage:AddUserImage forState:UIControlStateNormal];
    [ self.btAddUser addTarget:self action:@selector(btAddUser:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem* AddUserItem= [[[UIBarButtonItem alloc] initWithCustomView: self.btAddUser]autorelease];
    
    UIBarButtonItem *flexibleSpace = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil]autorelease]; //占位置，空格
    
    NSArray *items = [NSArray arrayWithObjects: RefreshItem,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,AddUserItem,nil];
    
    [self.toolbar setItems:items animated:NO];
    
    [self.view addSubview:self.toolbar];
    CGRect frame = self.view.frame ;
    [self.toolbar setFrame:CGRectMake(0, frame.size.height-40,480,40)];
    
    [self.tableview setFrame:CGRectMake(0, 40,480,frame.size.height-80)];
    
    if(!pLoginServer->ISChairman())
    {
        [self.btAddUser setEnabled:NO];
    }
}
- (void)viewDidLoad
{
    [super viewDidLoad];
  //
    // Do any additional setup after loading the view from its nib.
    UIBarButtonItem *leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(btback:)];
    self.navigationItem.leftBarButtonItem = leftBtn;
    [leftBtn release];
//    [self initToolBar];
}

-(void)dealloc
{
    self.tableview=nil;
    self.roomUsrArray=nil;
    self.videoSessionViewController=nil;
    self.actionSheetPower=nil;
    self.actionSheetManage=nil;
    self.actionSheetattachUser=nil;
    self.sessionShowViewController = nil;
    self.toolbar=nil;
    [super dealloc];
}
 

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return RoomUserList.size() ;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    SessionInfoCell *cell =nil;
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        static NSString * DisclosureMonitorNodeCellIdentifier =
//        @"SessionInfoCell_ipadIdentifier";
//        
//        cell =  [tableView dequeueReusableCellWithIdentifier:
//                 DisclosureMonitorNodeCellIdentifier ];
//        if (cell == nil) {
//            
//            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"SessionInfoCell_ipad" owner:self options:nil];
//            cell = [nib objectAtIndex:0];
//        }
//    }
//    else
//    {
//        static NSString * DisclosureMonitorNodeCellIdentifier =
//        @"SessionInfoCellIdentifier";
//        
//        cell =  [tableView dequeueReusableCellWithIdentifier:
//                                  DisclosureMonitorNodeCellIdentifier ];
//        if (cell == nil) {
//            
//            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"SessionInfoCell" owner:self options:nil];
//            cell = [nib objectAtIndex:0];
//        }
//    }
    static NSString * DisclosureMonitorNodeCellIdentifier =
    @"SessionInfoCellIdentifier";
    
    cell =  [tableView dequeueReusableCellWithIdentifier:
             DisclosureMonitorNodeCellIdentifier ];
    if (cell == nil) {
        
        NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"SessionInfoCell" owner:self options:nil];
        cell = [nib objectAtIndex:0];
    }
    cell.sessionInfoViewController=self;
    
   // else
   // {
   //     [cell.Power setText:@"与会者"];
   // }
    
    NSString *stsindex=[NSString stringWithFormat:@"%d",row+1];
    [cell.index setText:stsindex];
    
    IMS_CONTACT_ITEM mUserInfo;
    pLoginServer->GetUserInfo(RoomUserList[row].strUserID, mUserInfo);
    NSString *strLoginInfo;
    
    strLoginInfo=[[[NSString alloc]initWithCString:mUserInfo.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
    
    cell.strUserID = mUserInfo.userid;
    
    NSString* strPhoneNumber=[[[NSString alloc]initWithCString:mUserInfo.phone.c_str() encoding: NSUTF8StringEncoding] autorelease];
    
    [cell.PhoneNumber setText:strPhoneNumber];
    
    //cell.headPhoto.image=[UIImage imageNamed:@"Rvideo1"];
    
    if(RoomUserList[row].strUserID == pLoginServer->GetUserID())
    {
        //Local User
        if([self.sessionShowViewController LocalUserIsOpenVideo])
        {
            int iScreen = [self.sessionShowViewController GetWindowScreen:RoomUserList[row].strUserID];
            if(iScreen == 1)
                cell.RVideo.image =[UIImage imageNamed:@"Rvideo1"];
            else if(iScreen == 2)
                cell.RVideo.image =[UIImage imageNamed:@"Rvideo2"];
            else if(iScreen == 3)
                cell.RVideo.image =[UIImage imageNamed:@"Rvideo3"];
            else if(iScreen == 4)
                cell.RVideo.image =[UIImage imageNamed:@"Rvideo4"];
            else
                cell.RVideo.image =[UIImage imageNamed:@"Rvideo"]; 
        }
        else
        {
            cell.RVideo.image =[UIImage imageNamed:@"Rvideo"];
        }
        
        if([self.sessionShowViewController LocalUserIsOpenAudio])
        {
            cell.RSpeak.image = [UIImage imageNamed:@"RSpeakStart"];
        }
        else
        {
            cell.RSpeak.image = [UIImage imageNamed:@"RSpeakStop"];
        }
    }
    else
    {
        //peer user
        if([self.sessionShowViewController PeerUserISOpenAudio:RoomUserList[row].strUserID])
        {
            cell.RSpeak.image = [UIImage imageNamed:@"RSpeakStart"];
        }
        else
        {
            cell.RSpeak.image = [UIImage imageNamed:@"RSpeakStop"];
        }
        
        if([self.sessionShowViewController PeerUserIsOpenVideo:RoomUserList[row].strUserID])
        {
            int iScreen = [self.sessionShowViewController GetWindowScreen:RoomUserList[row].strUserID];
            if(iScreen == 1)
                cell.RVideo.image = [UIImage imageNamed:@"Rvideo1"];
            else if(iScreen == 2)
                cell.RVideo.image = [UIImage imageNamed:@"Rvideo2"];
            else if(iScreen == 3)
                cell.RVideo.image = [UIImage imageNamed:@"Rvideo3"];
            else if(iScreen == 4)
                cell.RVideo.image = [UIImage imageNamed:@"Rvideo4"];
            else
                cell.RVideo.image = [UIImage imageNamed:@"Rvideo"];
        }
        else
        {
            cell.RVideo.image =[UIImage imageNamed:@"Rvideo"];
        }
    }
    
    if(RoomUserList[row].bIsHost)
    {
        //[cell.Power setText:@"主持人"];
        cell.RUser.image = [UIImage imageNamed:@"主持人"];
        [cell.headPhoto setImage:[UIImage imageNamed:@"头像"] forState:normal];
    }
    else if(RoomUserList[row].bIsEnterRoom)
    {
        if(RoomUserList[row].bIsInRoom)
        {
            [cell.headPhoto setImage:[UIImage imageNamed:@"头像"] forState:normal];
            RoomUserList[row].bIsUpRoom = false;
        }
        else if(!RoomUserList[row].bIsInRoom)
        {
            [cell.headPhoto setImage:[UIImage imageNamed:@"退出会场"] forState:normal];
            cell.RVideo.image =[UIImage imageNamed:@"Rvideo"];
            cell.RSpeak.image = [UIImage imageNamed:@"RSpeakStop"];
            
            if(!RoomUserList[row].bIsUpRoom)
            {
                [self.sessionShowViewController User_ClosePeerVideo:RoomUserList[row].strUserID IsSendCommand:false bIsBroadcast:false];
                [self.sessionShowViewController User_ClosePeerAudio:RoomUserList[row].strUserID];
                RoomUserList[row].bIsUpRoom = true;
            }
        }
    }
    else if(!RoomUserList[row].bIsEnterRoom)
    {
        [cell.headPhoto setImage:[UIImage imageNamed:@"没有加入会场"] forState:normal];
        cell.RVideo.image =[UIImage imageNamed:@"Rvideo"];
        cell.RSpeak.image = [UIImage imageNamed:@"RSpeakStop"];
    }
    
    [cell.Name setText:strLoginInfo];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    return cell;
}

-(float)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 42;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
//    NSUInteger row = [indexPath row];
    // NSString *strLoginInfo=[[[NSString alloc]initWithCString:RoomUserList[row ].c_str() encoding: NSUTF8StringEncoding] autorelease];
    //RoomUserList[row].c_str();
    return;
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
	// the user clicked one of the OK/Cancel buttons
    
    if(actionSheet==self.actionSheetManageHasAAndV)
    {
        if (buttonIndex == 0)//授权发言
        {
            [self RoomHostEnevt:1];
        }
        else if(buttonIndex == 1)//停止浏览对方视频
        {
            [self RoomHostEnevt:2];
        }
        else if(buttonIndex == 2)//请出会场
        {
            [self RoomHostEnevt:3];
        }
        else if(buttonIndex == 3)//返回
        {
            
        }
    }
    else if(actionSheet==self.actionSheetManageHasA)
    {
        if (buttonIndex == 0)//授权发言
        {
            [self RoomHostEnevt:1];
        }
        else if(buttonIndex == 1)//请出会场
        {
            [self RoomHostEnevt:3];
        }
        else if(buttonIndex == 2)//返回
        {
            
        }
    }
    else if(actionSheet==self.actionSheetManageHasV)
    {
        if (buttonIndex == 0)//停止浏览对方视频
        {
            [self RoomHostEnevt:2];
        }
        else if(buttonIndex == 1)//请出会场
        {
            [self RoomHostEnevt:3];
        }
        else if(buttonIndex == 2)//返回
        {
            
        }
    }
    else if(actionSheet==self.actionSheetManage)
    {
        if (buttonIndex == 0)//请出会场
        {
            [self RoomHostEnevt:3];
        }
        else if(buttonIndex == 1)//返回
        {
            
        }
    }
    else if(actionSheet==self.actionSheetPower)
    {
        if (buttonIndex == 0)//传递管理权限
        {
            if(pLoginServer->ISChairman())
            {
                mNSTimer = [NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
                m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
                m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
                pLoginServer->OnPassPrivileges(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), strSelectUserID);
            }
        }
        else if(buttonIndex == 1)//返回
        {
             
        }
    }
    else if(actionSheet==self.actionSheetattachUser)
    {
        if (buttonIndex == 0)//申请发言或者打开关闭视频
        {
            [self RoomUserEnvet:buttonIndex];
        }
        else if(buttonIndex == 1)//停止浏览对方视频
        {
            if(iReturnNum == buttonIndex+1)
                return;
            
            [self RoomUserEnvet:buttonIndex];
        }
        else if(buttonIndex == 2)//返回
        {
            
        }
    }
    else if(actionSheet==self.actionInviteUsers)
    {
        if (buttonIndex == 0)
        {
            if(pLoginServer)
                pLoginServer->OnInviteUser(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), strSelectUserID);
            [self MyUpdateMeetingInfo:self];
        }
    }
}

-(void)runTimer:(id)timer
{
    [self MyUpdateMeetingInfo:self];
    if(m_pMBProgressHUD!=nil)
    {
        [m_pMBProgressHUD hide:YES];
        m_pMBProgressHUD = nil;
    }
    [mNSTimer invalidate];
    mNSTimer = nil;
}

-(void) RoomHostEnevt:(int)iCount
{
    if(iCount==1)
    {
        if(strSelectUserID == pLoginServer->GetUserID())
        {
            if([self.sessionShowViewController LocalUserIsOpenAudio])
            {
                //pOpenAudio = [NSString stringWithFormat:@"停止发言"];
                [self.sessionShowViewController User_CloseLocalAudio:strSelectUserID];
            }
            else
            {
                //pOpenAudio = [NSString stringWithFormat:@"开始发言"];
                [self.sessionShowViewController User_CloseAllAudio];
                [self.sessionShowViewController User_OpenLocalAudio:strSelectUserID IsSendData:true];
            }
        }
        else
        {
            //peer user
            if([self.sessionShowViewController PeerUserISOpenAudio:strSelectUserID])
            {
                //pOpenAudio = [NSString stringWithFormat:@"收回发言权"];
                [self.sessionShowViewController User_ClosePeerAudio:strSelectUserID];
                [self.sessionShowViewController User_OpenLocalAudio:pLoginServer->GetUserID() IsSendData:true];
            }
            else
            {
                [self.sessionShowViewController User_CloseAllAudio];
                [self.sessionShowViewController User_OpenPeerAudio:strSelectUserID];
                //pOpenAudio = [NSString stringWithFormat:@"授权发言"];
            }
        }
    }
    else if(iCount==2)
    {
        if(strSelectUserID == pLoginServer->GetUserID())
        {
            if([self.sessionShowViewController LocalUserIsOpenVideo])
            {
                //pOpenVideo = [NSString stringWithFormat:@"停止浏览自己的视频"];
                if(self.sessionShowViewController.uiRoomVideoType == ROOM_VIDEO_ROOM)
                {
                    [self.sessionShowViewController User_CloseLocalVideo:strSelectUserID IsSendCommand:false bIsBroadcast:false];
                }
                else
                {
                    [self.sessionShowViewController User_CloseLocalVideo:strSelectUserID IsSendCommand:true bIsBroadcast:true];
                }
            }
            else
            {
                //if([self.sessionShowViewController IsHasVideoWindow])
                // pOpenVideo = [NSString stringWithFormat:@"开始浏览自己的视频"];
                //unsigned int uiScreen = 0;
                iOSGLView* pView = [self.sessionShowViewController GetWindow:strSelectUserID uiScreen:m_videoSessionID IsSet:true];
                
                if(self.sessionShowViewController.uiRoomVideoType == ROOM_VIDEO_ROOM)
                {
                    if(pView!=nil)
                        [self.sessionShowViewController User_OpenLocalVideo:strSelectUserID pView:pView uiScreen:m_videoSessionID IsSendCommand:false IsSendData:false bIsBroadcast:false];
                }
                else
                {
                    if(pView!=nil)
                        [self.sessionShowViewController User_OpenLocalVideo:strSelectUserID pView:pView uiScreen:m_videoSessionID IsSendCommand:true IsSendData:true bIsBroadcast:true];
                }
                m_videoSessionID = 0;
            }
        }
        else
        {
            //peer user
            if([self.sessionShowViewController PeerUserIsOpenVideo:strSelectUserID])
            {
                //pOpenVideo = [NSString stringWithFormat:@"停止浏览对方的视频"];
                if(self.sessionShowViewController.uiRoomVideoType == ROOM_VIDEO_ROOM)
                {
                    [self.sessionShowViewController User_ClosePeerVideo:strSelectUserID IsSendCommand:true bIsBroadcast:false];
                }
                else
                    [self.sessionShowViewController User_ClosePeerVideo:strSelectUserID IsSendCommand:true bIsBroadcast:true];
            }
            else
            {
                //unsigned int uiScreen = 0;
                iOSGLView* pView = [self.sessionShowViewController GetWindow:strSelectUserID uiScreen:m_videoSessionID IsSet:true];
                if(self.sessionShowViewController.uiRoomVideoType == ROOM_VIDEO_ROOM)
                {
                    if(pView!=nil)
                        [self.sessionShowViewController User_OpenPeerVideo:strSelectUserID pView:pView uiScreen:m_videoSessionID bIsBroadcast:false IsSendCommand:true];
                }
                else
                {
                    if(pView!=nil)
                        [self.sessionShowViewController User_OpenPeerVideo:strSelectUserID pView:pView uiScreen:m_videoSessionID bIsBroadcast:true IsSendCommand:true];
                }
                m_videoSessionID = 0;
                //if([self.sessionShowViewController IsHasVideoWindow])
                // pOpenVideo = [NSString stringWithFormat:@"开始浏览对方的视频"];
            }
        }
    }
    else if(iCount==3)
    {
        if(strSelectUserID == pLoginServer->GetUserID())
        {
            [self btback:self];
            [self.sessionShowViewController back];
        }
        else
        {
            pLoginServer->OnPleaseOutTemporaryMeeting(pLoginServer->GetHostID(), pLoginServer->GetRoomId(), strSelectUserID);
        }
    }
}

-(void) RoomUserEnvet:(int)iCount
{
    bool IsForTheFloor = false;
    
    if(self.sessionShowViewController.uiRoomAudioType == ROOM_AUDIO_SPEAK)
    {
        if(strSelectUserID == pLoginServer->GetUserID())
        {
            //Local User
            if(![self.sessionShowViewController LocalUserIsOpenAudio])
            {
                if(iCount == 0)
                    pLoginServer->OnForTheFloor(strSelectUserID, pLoginServer->GetRoomId(), pLoginServer->GetHostID());
                IsForTheFloor = true;
            }
        }
    }
    
    if((IsForTheFloor && iCount==1) || (!IsForTheFloor && iCount==0))
    {
        if(self.sessionShowViewController.uiRoomVideoType == ROOM_VIDEO_ROOM)
        {
            if(strSelectUserID == pLoginServer->GetUserID())
            {
                if([self.sessionShowViewController LocalUserIsOpenVideo])
                {
                    //unsigned int uiScreen = 0;
                    iOSGLView* pView = [self.sessionShowViewController GetWindow:strSelectUserID uiScreen:m_videoSessionID IsSet:true];
                    
                    if(pView!=nil)
                        [self.sessionShowViewController User_OpenLocalVideo:strSelectUserID pView:pView uiScreen:m_videoSessionID IsSendCommand:false IsSendData:false bIsBroadcast:false];
                    m_videoSessionID = 0;
                    //[self.sessionShowViewController ono]
                    //pOpenVideo = [NSString stringWithFormat:@"停止浏览自己的视频"];
                }
                else
                {
                    [self.sessionShowViewController User_CloseLocalVideo:strSelectUserID IsSendCommand:false bIsBroadcast:false];
                    //pOpenVideo = [NSString stringWithFormat:@"开始浏览自己的视频"];
                }
            }
            else
            {
                if([self.sessionShowViewController PeerUserIsOpenVideo:strSelectUserID])
                {
                    //pOpenVideo = [NSString stringWithFormat:@"停止浏览对方的视频"];
                    [self.sessionShowViewController User_ClosePeerVideo:strSelectUserID IsSendCommand:true bIsBroadcast:false];
                }
                else
                {
                    //unsigned int uiScreen = 0;
                    iOSGLView* pView = [self.sessionShowViewController GetWindow:strSelectUserID uiScreen:m_videoSessionID IsSet:true];
                    
                    if(pView!=nil)
                        [self.sessionShowViewController User_OpenPeerVideo:strSelectUserID pView:pView uiScreen:m_videoSessionID bIsBroadcast:false IsSendCommand:true];
                    m_videoSessionID = 0;
                }
            }
        }
    }
}

-(void)changePower:(std::string)name
{
    if(pLoginServer->ISChairman())//是否是主席
    {
        strSelectUserID = name;
        
        std::vector<ROOMUSERINFO>::iterator it = RoomUserList.begin();
        while(it!=RoomUserList.end())
        {
            if(strSelectUserID ==it->strUserID)
            {
                if(!it->bIsInRoom || !it->bIsEnterRoom)
                {
                    return;
                }
            }
            it++;
        }

        if(strSelectUserID!=pLoginServer->GetUserID())
        {
            self.actionSheetPower= [[[UIActionSheet alloc] initWithTitle:@""
                                                                delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                       otherButtonTitles:@"传递管理权限", @"返回",nil]autorelease];
            self.actionSheetPower.actionSheetStyle = UIActionSheetStyleDefault;
            [ self.actionSheetPower showInView:self.view];
        }
    }
}

-(NSIndexPath*)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString* pOpenAudio = nil;
    NSString* pOpenVideo = nil;
    NSString* pRoomController = nil;
    self.actionSheetattachUser = nil;
    
    SessionInfoCell* SelectCell = (SessionInfoCell*)[tableView cellForRowAtIndexPath:indexPath];
    
    strSelectUserID = SelectCell.strUserID;
    
    std::vector<ROOMUSERINFO>::iterator it = RoomUserList.begin();
    while(it!=RoomUserList.end())
    {
        if(strSelectUserID ==it->strUserID)
        {
            if(!it->bIsInRoom || !it->bIsEnterRoom)
            {
                self.actionInviteUsers= [[[UIActionSheet alloc] initWithTitle:@""
                                                                         delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                                otherButtonTitles:@"邀请用户", @"返回",nil]autorelease];
                self.actionInviteUsers.actionSheetStyle = UIActionSheetStyleDefault;
                [self.actionInviteUsers showInView:self.view];
                return indexPath;
            }
        }
        it++;
    }
    
    if(pLoginServer->ISChairman())//是否是主席
    {
        if(self.sessionShowViewController.uiRoomAudioType == ROOM_AUDIO_SPEAK)
        {
            if(SelectCell.strUserID == pLoginServer->GetUserID())
            {
                //Local User
                if([self.sessionShowViewController LocalUserIsOpenAudio])
                {
                    pOpenAudio = [NSString stringWithFormat:@"停止发言"];
                }
                else
                {
                    pOpenAudio = [NSString stringWithFormat:@"开始发言"];
                }
                pRoomController = [NSString stringWithFormat:@"结束会议"];
                
                if([self.sessionShowViewController LocalUserIsOpenVideo])
                {
                    pOpenVideo = [NSString stringWithFormat:@"停止浏览自己的视频"];
                }
                else
                {
                    if([self.sessionShowViewController IsHasVideoWindow])
                        pOpenVideo = [NSString stringWithFormat:@"开始浏览自己的视频"];
                }
            }
            else
            {
                //peer user
                if([self.sessionShowViewController PeerUserISOpenAudio:SelectCell.strUserID])
                {
                    pOpenAudio = [NSString stringWithFormat:@"收回发言权"];
                }
                else
                {
                    pOpenAudio = [NSString stringWithFormat:@"授权发言"];
                }
                pRoomController = [NSString stringWithFormat:@"请出会场"];
                if([self.sessionShowViewController PeerUserIsOpenVideo:SelectCell.strUserID])
                {
                    pOpenVideo = [NSString stringWithFormat:@"停止浏览对方的视频"];
                }
                else
                {
                    if([self.sessionShowViewController IsHasVideoWindow])
                        pOpenVideo = [NSString stringWithFormat:@"开始浏览对方的视频"];
                }
            }
            
            if(pOpenVideo!=nil)
            {
                self.actionSheetManageHasAAndV= [[[UIActionSheet alloc] initWithTitle:@""
                                                                 delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                        otherButtonTitles:pOpenAudio, pOpenVideo,pRoomController, @"返回",nil]autorelease];
                self.actionSheetManageHasAAndV.actionSheetStyle = UIActionSheetStyleDefault;
                [self.actionSheetManageHasAAndV showInView:self.view];
            }
            else
            {
                self.actionSheetManageHasA= [[[UIActionSheet alloc] initWithTitle:@""
                                                                     delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                            otherButtonTitles:pOpenAudio,pRoomController, @"返回",nil]autorelease];
                self.actionSheetManageHasA.actionSheetStyle = UIActionSheetStyleDefault;
                [self.actionSheetManageHasA showInView:self.view];
            }
        }
        else 
        {
            if(SelectCell.strUserID == pLoginServer->GetUserID())
            {
                //Local User
                pRoomController = [NSString stringWithFormat:@"结束会议"];
                
                if([self.sessionShowViewController LocalUserIsOpenVideo])
                {
                    pOpenVideo = [NSString stringWithFormat:@"停止浏览自己的视频"];
                }
                else
                {
                    if([self.sessionShowViewController IsHasVideoWindow])
                        pOpenVideo = [NSString stringWithFormat:@"开始浏览自己的视频"];
                }
            }
            else
            {
                //peer user
                pRoomController = [NSString stringWithFormat:@"请出会场"];
                if([self.sessionShowViewController PeerUserIsOpenVideo:SelectCell.strUserID])
                {
                    pOpenVideo = [NSString stringWithFormat:@"停止浏览对方的视频"];
                }
                else
                {
                    if([self.sessionShowViewController IsHasVideoWindow])
                        pOpenVideo = [NSString stringWithFormat:@"开始浏览对方的视频"];
                }
            }
            
            if(pOpenVideo!=nil)
            {
                self.actionSheetManageHasV= [[[UIActionSheet alloc] initWithTitle:@""
                                                                 delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                        otherButtonTitles:pOpenVideo, pRoomController, @"返回",nil]autorelease];
                self.actionSheetManageHasV.actionSheetStyle = UIActionSheetStyleDefault;
                [self.actionSheetManageHasV showInView:self.view];
            }
            else
            {
                self.actionSheetManage= [[[UIActionSheet alloc] initWithTitle:@""
                                                                     delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                            otherButtonTitles:pRoomController, @"返回",nil]autorelease];
                self.actionSheetManage.actionSheetStyle = UIActionSheetStyleDefault;
                [self.actionSheetManage showInView:self.view];
            }
        }
        // show from our table view (pops up in the middle of the table)
    }
    else
    {
        if(self.sessionShowViewController.uiRoomAudioType == ROOM_AUDIO_SPEAK)
        {
            if(SelectCell.strUserID == pLoginServer->GetUserID())
            {
                //Local User
                if(![self.sessionShowViewController LocalUserIsOpenAudio])
                {
                    pOpenAudio = [NSString stringWithFormat:@"申请发言"];
                }
            }
        }
        
        if(self.sessionShowViewController.uiRoomVideoType == ROOM_VIDEO_ROOM)
        {
            if(SelectCell.strUserID == pLoginServer->GetUserID())
            {
                //Local User
                if([self.sessionShowViewController LocalUserIsOpenVideo])
                {
                    pOpenVideo = [NSString stringWithFormat:@"停止浏览自己的视频"];
                }
                else
                {
                    if([self.sessionShowViewController IsHasVideoWindow])
                        pOpenVideo = [NSString stringWithFormat:@"开始浏览自己的视频"];
                }
            }
            else
            {
                if([self.sessionShowViewController PeerUserIsOpenVideo:SelectCell.strUserID])
                {
                    pOpenVideo = [NSString stringWithFormat:@"停止浏览对方的视频"];
                }
                else
                {
                    if([self.sessionShowViewController IsHasVideoWindow])
                        pOpenVideo = [NSString stringWithFormat:@"开始浏览对方的视频"];
                }
            }
            
            if(pOpenAudio!=nil)
            {
                if(pOpenVideo!=nil)
                {
                    iReturnNum = 3;
                    self.actionSheetattachUser = [[[UIActionSheet alloc] initWithTitle:@""
                                                                     delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                            otherButtonTitles:pOpenAudio, pOpenVideo, @"返回",nil]autorelease];
                }
                else
                {
                    iReturnNum = 2;
                    self.actionSheetattachUser = [[[UIActionSheet alloc] initWithTitle:@""
                                                                              delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                                     otherButtonTitles:pOpenAudio, @"返回",nil]autorelease];
                }
                self.actionSheetattachUser.actionSheetStyle = UIActionSheetStyleDefault;
                [self.actionSheetattachUser showInView:self.view];
            }
            else
            {
                if(pOpenVideo!=nil)
                {
                    iReturnNum = 2;
                    self.actionSheetattachUser = [[[UIActionSheet alloc] initWithTitle:@""
                                                                     delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                            otherButtonTitles:pOpenVideo, @"返回",nil]autorelease];
                    self.actionSheetattachUser.actionSheetStyle = UIActionSheetStyleDefault;
                    [self.actionSheetattachUser showInView:self.view];
                }
            }
        }
        else
        {
            if(pOpenAudio!=nil)
            {
                iReturnNum = 2;
                self.actionSheetattachUser = [[[UIActionSheet alloc] initWithTitle:@""
                                                                      delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil
                                                             otherButtonTitles:pOpenAudio, @"返回",nil]autorelease];
                self.actionSheetattachUser.actionSheetStyle = UIActionSheetStyleDefault;
                [self.actionSheetattachUser showInView:self.view];
            }
        }
    }
    return indexPath;
}

-(void)Alert:(NSString*) result message:(NSString*) message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:result message:message
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];
    [alert release];
}

-(void) MyUpdateMeetingInfo:(id)mid
{
    if(videoSessionViewController != nil && videoSessionViewController.m_ViewCount == 1)
    {
        if(sessionShowViewController!=nil)
            [sessionShowViewController SetControlShow:true];
    }
    
    RoomUserList.clear();
    pLoginServer->GetRoomUserList(RoomUserList);
    [self.tableview reloadData];
    
    if(!pLoginServer->ISChairman())
    {
        [self.btAddUser setEnabled:NO];
    }
    else
    {
        [self.btAddUser setEnabled:YES];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)orientation
{
    if (orientation == UIInterfaceOrientationPortrait )
        return YES;
    
    return NO;
}

@end
