//
//  CallViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//
#import "CallViewController.h"
#import"ImsContactItem.h"
#import "ContactCell.h"
#import "SessionShowViewController.h"
#include "SessionInfo.h"
#include <sys/time.h>
#import "HandInputViewController.h"

@implementation CallViewController
@synthesize toolBar;
@synthesize tableview;
@synthesize ContactArr;
@synthesize handInputViewController;
@synthesize strGroupName;
@synthesize pVideoViewController;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
   // self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        self =[super initWithNibName:@"CallViewController_ipad" bundle:nil];
//    } else {
//        self =[super initWithNibName:@"CallViewController" bundle:nil];
//    }
    self =[super initWithNibName:@"CallViewController" bundle:nil];
    if (self) {
        // Custom initialization
        pLoginServer = NULL;
        ulRoomID = 0;
        self.pVideoViewController = nil;
        self.ContactArr=[[[NSMutableArray alloc]init]autorelease];
    }
    
    return self;
}

-(void)VideoCallPressed:(id)sender
{
    if(self.pVideoViewController!=nil)
        [self.pVideoViewController HostEnterRoomBegin];
    
    ulRoomID = [self TimeGetTimestamp];
     if(pLoginServer)
         pLoginServer->CreateTemporaryMeeting(pLoginServer->GetUserID(), ulRoomID, Room_VIDEO);
}

-(void)CallInviteAllUser
{
    for(ImsContactItem *contactItem in self.ContactArr) {
        if (contactItem.isseletct&&!contactItem.isInRoom&&contactItem.status=="online") {
            if(pLoginServer)
                pLoginServer->OnInviteUser(pLoginServer->GetUserID(), ulRoomID, contactItem.userid);
        }
    }
}

-(unsigned long)TimeGetTimestamp
{
	struct timeval now;
	gettimeofday(&now,NULL);
	return now.tv_sec*1000+now.tv_usec/1000;
}

-(void) OnFriendAdd:(const std::string&)strGroup strUserId:(const std::string&)strUserId
{
    if(strGroup == [strGroupName UTF8String])
    {
        m_strUserId = strUserId;
        [self performSelectorOnMainThread:@selector(MyFriendAdd:) withObject:self waitUntilDone:YES];
    }
}

-(void) OnFriendDelete:(const std::string&)strGroup strUserId:(const std::string&)strUserId
{
    if(strGroup == [strGroupName UTF8String])
    {
        m_strUserId = strUserId;
        [self performSelectorOnMainThread:@selector(MyFriendDelete:) withObject:self waitUntilDone:YES];
    }
}

-(void) OnFriendOnLine:(const std::string&)strUserId
{
    m_strUserId = strUserId;
    [self performSelectorOnMainThread:@selector(MyFriendOnLine:) withObject:self waitUntilDone:YES];
}

-(void) OnFriendOffline:(const std::string&)strUserId
{
    m_strUserId = strUserId;
    [self performSelectorOnMainThread:@selector(MyFriendOffline:) withObject:self waitUntilDone:YES];
}

-(void) OnFriendEnterInterimMeeting:(const std::string&)strUserId ulRoomID:(unsigned long)ulRoomID
{
    m_strUserId = strUserId;
    [self performSelectorOnMainThread:@selector(MyFriendEnterInterimMeeting:) withObject:self waitUntilDone:YES];
}

-(void) OnFriendQuitInterimMeeting:(const std::string&)strUserId ulRoomID:(unsigned long)ulRoomID
{
    m_strUserId = strUserId;
    [self performSelectorOnMainThread:@selector(MyFriendQuitInterimMeeting:) withObject:self waitUntilDone:YES];
}

-(void) MyFriendAdd:(id)mid
{
    bool bIsFound = false;
    for(int i=0; i<[self.ContactArr count]; i++)
    {
        ImsContactItem *contactItem = [self.ContactArr objectAtIndex:i];
        if(contactItem!=nil)
        {
            if(contactItem.userid == m_strUserId)
            {
                bIsFound = true;
                break;
            }
        }
    }
    if(bIsFound == false)
    {
        IMS_CONTACT_ITEM mUserInfo;
        if(pLoginServer->GetUserInfo(m_strUserId, mUserInfo))
        {
            ImsContactItem *contactItem=[[[ImsContactItem alloc]init]autorelease];
            contactItem.userid=m_strUserId;
            contactItem.username=m_strUserId;
            contactItem.isseletct=NO;
            contactItem.status = mUserInfo.status;
            [self.ContactArr addObject:contactItem];
            [self.tableview reloadData];
        }
    }
}

-(void) MyFriendDelete:(id)mid
{
    for(int i=0; i<[self.ContactArr count]; i++)
    {
        ImsContactItem *contactItem = [self.ContactArr objectAtIndex:i];
        if(contactItem!=nil)
        {
            if(contactItem.userid == m_strUserId)
            {
                [self.ContactArr removeObjectAtIndex:i];
                [self.tableview reloadData];
                break;
            }
        }
    }
}

-(void) MyFriendOnLine:(id)mid
{
#if 0
    for(int i=0; i<[self.ContactArr count]; i++)
    {
        ImsContactItem *contactItem = [self.ContactArr objectAtIndex:i];
        if(contactItem!=nil)
        {
            if(contactItem.userid == m_strUserId)
            {
                contactItem.status = "online";
                contactItem.isseletct = NO;
                [self.tableview reloadData];
                break;
            }
        }
    }
#endif
    [self.ContactArr removeAllObjects];
    [self UpdateUser];
}

-(void) MyFriendOffline:(id)mid
{
#if 0
    for(int i=0; i<[self.ContactArr count]; i++)
    {
        ImsContactItem *contactItem = [self.ContactArr objectAtIndex:i];
        if(contactItem!=nil)
        {
            if(contactItem.userid == m_strUserId)
            {
                contactItem.status = "offline";
                contactItem.isseletct = NO;
                [self.tableview reloadData];
                break;
            }
        }
    }
#endif
    [self.ContactArr removeAllObjects];
    [self UpdateUser];
}

-(void) MyFriendEnterInterimMeeting:(id)mid
{
    for(int i=0; i<[self.ContactArr count]; i++)
    {
        ImsContactItem *contactItem = [self.ContactArr objectAtIndex:i];
        if(contactItem!=nil)
        {
            if(contactItem.userid == m_strUserId)
            {
                contactItem.isInRoom = YES;
                [self.tableview reloadData];
                break;
            }
        }
    }
}

-(void) MyFriendQuitInterimMeeting:(id)mid
{
    for(int i=0; i<[self.ContactArr count]; i++)
    {
        ImsContactItem *contactItem = [self.ContactArr objectAtIndex:i];
        if(contactItem!=nil)
        {
            if(contactItem.userid == m_strUserId)
            {
                contactItem.isInRoom = NO;
                [self.tableview reloadData];
                break;
            }
        }
    }
}

-(void)VoiceCallPressed:(id)sender
{
    
}

-(void)InvertBbuttonPressed:(id)sender
{
    for(ImsContactItem *contactItem in self.ContactArr) {
        contactItem.isseletct=!contactItem.isseletct;
            }
    [self.tableview reloadData];
}

- (void) hideTabBar:(UITabBarController *) tabbarcontroller {
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.5];
    for(UIView *view in tabbarcontroller.view.subviews)
    {
        if([view isKindOfClass:[UITabBar class]])
        {
            [view setFrame:CGRectMake(view.frame.origin.x, 480, view.frame.size.width, view.frame.size.height)];
        }
        else
        {
            [view setFrame:CGRectMake(view.frame.origin.x, view.frame.origin.y, view.frame.size.width, 480)];
        }
    }
    [UIView commitAnimations];
}

- (void) showTabBar:(UITabBarController *) tabbarcontroller {
    
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.5];
    for(UIView *view in tabbarcontroller.view.subviews)
    {
        NSLog(@"%@", view);
        
        if([view isKindOfClass:[UITabBar class]])
        {
            [view setFrame:CGRectMake(view.frame.origin.x, 431, view.frame.size.width, view.frame.size.height)];
        }
        else
        {
            [view setFrame:CGRectMake(view.frame.origin.x, view.frame.origin.y, view.frame.size.width, 431)];
        }
    }
    
    [UIView commitAnimations];
}


-(void)inviteBbuttonPressed:(id)sender
{
    self.handInputViewController=[[[HandInputViewController alloc]initWithNibName:@"HandInputViewController" bundle:nil]autorelease];
     [self setHidesBottomBarWhenPushed:YES];
    
   [self.navigationController pushViewController:self.handInputViewController animated:YES];
    self.handInputViewController.groupname = strGroupName;
  
    
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:NO];
    
    
    [self hideTabBar:self.tabBarController];
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    pLoginServer->m_iMGetUserFriendInfo = self;
    [self.ContactArr removeAllObjects];
    [self UpdateUser];
    
    [self setHidesBottomBarWhenPushed:YES];
    
}

-(void)viewWillDisappear:(BOOL)animated
{
   
    [self showTabBar:self.tabBarController];
    pLoginServer->m_iMGetUserFriendInfo = nil;
    [self.tabBarController.tabBar setHidden:NO];
    [super viewWillDisappear:animated];
}

- (void)initctrl
{
    [self.navigationController.navigationBar setHidden:NO];
    self.title=strGroupName;
    pLoginServer = LoginServer::OnGetLoginServer();
    
    UIBarButtonItem *VideoCallItem = [[UIBarButtonItem alloc]initWithTitle:@"视频呼叫" style:UIBarButtonItemStyleBordered target:self action:@selector(VideoCallPressed:)];
    
    //UIBarButtonItem *VoiceCallItem = [[UIBarButtonItem alloc]initWithTitle:@"语音呼叫" style:UIBarButtonItemStyleBordered target:self action:@selector(VoiceCallPressed:)];
    
    // UIBarButtonItem *InvertItem = [[UIBarButtonItem alloc]initWithTitle:@"反选" style:UIBarButtonItemStyleBordered target:self action:@selector(InvertBbuttonPressed:)];
    
    UIBarButtonItem *inviteItem = [[UIBarButtonItem alloc]initWithTitle:@"添加" style:UIBarButtonItemStyleBordered target:self action:@selector(inviteBbuttonPressed:)];
    
    UIBarButtonItem *flexibleSpace = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil]autorelease]; //占位置，空格
    NSArray *items = [NSArray arrayWithObjects: VideoCallItem,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,inviteItem,nil];
    
    [self.toolBar setItems:items animated:NO];
    tableview.separatorStyle = NO;
    
    NSString *UserID=[[[NSString alloc]initWithCString:pLoginServer->GetUserID().c_str() encoding: NSUTF8StringEncoding] autorelease];
    self.title = [[[NSString alloc]initWithFormat:@"我的好友 (%@)",UserID]autorelease];

}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self initctrl];
    }

-(void)dealloc
{
    self.toolBar=nil;
    self.tableview=nil;
    self.ContactArr=nil;
    pLoginServer = NULL;
    self.handInputViewController=nil;
    [super dealloc];
}

-(void) UpdateUser
{
    if(pLoginServer == NULL)
        return;
    
    std::vector<std::string> UserList;
    pLoginServer->GetUserFriendList([strGroupName UTF8String], UserList);
    
    std::vector<std::string>::iterator iter = UserList.begin();
    while(iter!=UserList.end())
    {
        IMS_CONTACT_ITEM mUserInfo;
        if(pLoginServer->GetUserInfo(*iter, mUserInfo))
        {
            ImsContactItem *contactItem=[[[ImsContactItem alloc]init]autorelease];
            contactItem.userid=*iter;
            contactItem.username=*iter;
            contactItem.isseletct=NO;
            if(mUserInfo.IsEnterRoom)
                contactItem.isInRoom=YES;
            else
                contactItem.isInRoom=NO;
            contactItem.status = mUserInfo.status;
            [self.ContactArr addObject:contactItem];
        }
        ++iter;
    }
    
    [self.tableview reloadData];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(self.ContactArr.count>0)
    return  (self.ContactArr.count/2+self.ContactArr.count%2);
    else
        return  0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSUInteger row = [indexPath row];
    ContactCell *cell=nil;
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
//    {
//        static NSString * DisclosureMonitorNodeCellIdentifier =
//        @"ContactCell_ipadIdentifier";
//        
//        cell =  [tableView dequeueReusableCellWithIdentifier:
//                 DisclosureMonitorNodeCellIdentifier ];
//        if (cell == nil) {
//            
//            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"ContactCell_ipad" owner:self options:nil];
//            cell = [nib objectAtIndex:0];
//        }
//    }
//    else {
//        
//        static NSString * DisclosureMonitorNodeCellIdentifier =
//        @"ContactCellIdentifier";
//        
//        cell =  [tableView dequeueReusableCellWithIdentifier:
//                 DisclosureMonitorNodeCellIdentifier ];
//        if (cell == nil) {
//            
//            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"ContactCell" owner:self options:nil];
//            cell = [nib objectAtIndex:0];
//        }
//    }
    static NSString * DisclosureMonitorNodeCellIdentifier =
    @"ContactCellIdentifier";
    
    cell =  [tableView dequeueReusableCellWithIdentifier:
             DisclosureMonitorNodeCellIdentifier ];
    if (cell == nil) {
        
        NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"ContactCell" owner:self options:nil];
        cell = [nib objectAtIndex:0];
    }
    int index=row*2;
    cell.callViewController=self;
    
    ImsContactItem *contact1 = [self.ContactArr objectAtIndex:index];
    cell.contactItem1  = contact1;
    
    if (cell.contactItem1.status == "offline")
    {
        [cell.HeadImage1 setImage:[UIImage imageNamed:@"lixian"] ];
        cell.contactItem1.isseletct = NO;
        [cell.selectBtn1 setImage:[UIImage imageNamed:@"好友背景"]forState:normal];
    }
    else if (cell.contactItem1.isInRoom)
    {
        [cell.HeadImage1 setImage:[UIImage imageNamed:@"meeting"] ];
    }
    else  
    {
        [cell.HeadImage1 setImage:[UIImage imageNamed:@"kongxian"]  ];
       
        if (cell.contactItem1.isseletct) {
            
            [cell.selectBtn1 setImage:[UIImage imageNamed:@"背景2"]forState:normal];
        }
        else
        {
             [cell.selectBtn1 setImage:[UIImage imageNamed:@"好友背景"]forState:normal];
        }
    }
     
    
    NSString *strLoginInfo1=[[[NSString alloc]initWithCString:contact1.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
    
    NSString *strphone1=[[[NSString alloc]initWithCString:contact1.phone.c_str() encoding: NSUTF8StringEncoding] autorelease];
    
    [cell.uitextName1 setText:strLoginInfo1];
    [cell.uitextNnmber1 setText:strphone1];
    
    MyUILongPressGestureRecognizer *longpressGesutre1=[[[MyUILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(LongToucvideoWindow:)]autorelease];
    //longpressGesutre1.minimumPressDuration=1;
    //longpressGesutre1.numberOfTouchesRequired=1;
    //[longpressGesutre1 setMinimumPressDuration:2.0];
    longpressGesutre1.strUserID = strLoginInfo1;
    [cell.selectBtn1 addGestureRecognizer:longpressGesutre1];
    
    if (self.ContactArr.count>index+1)
    {
        [cell.selectBtn2 setHidden:NO];
        [cell.uitextName2 setHidden:NO];
        [cell.uitextNnmber2 setHidden:NO];
        [cell.HeadImage2 setHidden:NO];
        
        ImsContactItem *contact2 = [self.ContactArr objectAtIndex:index+1];
        cell.contactItem2  = contact2;
        if (cell.contactItem2.status == "offline")
        {
            [cell.HeadImage2 setImage:[UIImage imageNamed:@"lixian"]];
            cell.contactItem2.isseletct = NO;
            [cell.selectBtn2 setImage:[UIImage imageNamed:@"好友背景"]forState:normal];
        }
        else if (cell.contactItem2.isInRoom)
        {
            [cell.HeadImage2 setImage:[UIImage imageNamed:@"meeting"] ];
        }
        else
        {
            [cell.HeadImage2 setImage:[UIImage imageNamed:@"kongxian"]];
            
            if (cell.contactItem2.isseletct) {
                
                [cell.selectBtn2 setImage:[UIImage imageNamed:@"背景2"] forState:normal];
            }
            else
            {
                [cell.selectBtn2 setImage:[UIImage imageNamed:@"好友背景"] forState:normal];
            }
        }
        NSString *strLoginInfo2=[[[NSString alloc]initWithCString:contact2.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        NSString *strphone2=[[[NSString alloc]initWithCString:contact2.phone.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        [cell.uitextName2 setText:strLoginInfo2];
        [cell.uitextNnmber2 setText:strphone2];
        
        MyUILongPressGestureRecognizer *longpressGesutre2=[[[MyUILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(LongToucvideoWindow:)]autorelease];
        //longpressGesutre2.minimumPressDuration=1;
        //longpressGesutre2.numberOfTouchesRequired=1;
        //[longpressGesutre2 setMinimumPressDuration:2.0];
        longpressGesutre2.strUserID = strLoginInfo2;
        [cell.selectBtn2 addGestureRecognizer:longpressGesutre2];
    }
    else
    {
        [cell.selectBtn2 setHidden:YES];
        [cell.uitextName2 setHidden:YES];
        [cell.uitextNnmber2 setHidden:YES];
        [cell.HeadImage2 setHidden:YES];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    return cell;
}

-(IBAction)LongToucvideoWindow:(MyUILongPressGestureRecognizer*)sender
{
    if(sender!=nil && sender.state==UIGestureRecognizerStateBegan)
    {
        DeleteUseralert = [[UIAlertView alloc] initWithTitle:@"是否删除改用户" message:@""
                                                  delegate:self cancelButtonTitle:@"确定" otherButtonTitles:@"取消", nil];
        DeleteUseralert.alertViewStyle = UIAlertViewStyleDefault;
        [DeleteUseralert show];
        [DeleteUseralert release];
        deleteUserID = sender.strUserID;
    }
}

- (void)alertView:(UIAlertView *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if(DeleteUseralert == actionSheet)
    {
        if (buttonIndex == 0)
        {
            if(pLoginServer!=NULL)
                pLoginServer->DeleteUserFriend([strGroupName UTF8String], [deleteUserID UTF8String]);
        }
    }
}

-(float)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
//    {
//        return 120;
//    }
//    else
//    {
//        return 60;
//    }
    return 60;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    return;
}

-(NSIndexPath*)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    return indexPath;
}

-(void)Alert:(NSString*) result message:(NSString*) message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:result message:message
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];
    [alert release];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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

@end
