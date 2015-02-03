//
//  CallViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "UserListViewController.h"
#import"VideoSessionViewController.h"
#import"ImsContactItem.h"
#import "UserListCell.h"
#import "SessionShowViewController.h"
#include "SessionInfo.h"
#include <sys/time.h>

@interface UserListViewController ()

@end

@implementation UserListViewController
@synthesize toolBar;
@synthesize tableview;
@synthesize ContactArr;
@synthesize imageBg;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
   // self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        self =[super initWithNibName:@"UserListViewController_ipad" bundle:nil];
//    } else {
//        self =[super initWithNibName:@"UserListViewController" bundle:nil];
//    }
    self =[super initWithNibName:@"UserListViewController" bundle:nil];
    if (self) {
        // Custom initialization
        self.ContactArr=[[[NSMutableArray alloc]init]autorelease];
        pLoginServer = NULL;
        ulRoomID = 0;
        
    }
     return self;
}

-(void)VideoCallPressed:(id)sender
{
    
    SessionInfo *sessinfo=SessionInfo::GetSessionInfo();
    for(ImsContactItem *contactItem in self.ContactArr) {
        if (contactItem.isseletct) {
            sessinfo->lEnterUser.push_back(contactItem.userid);
        }
    }
    ulRoomID = [self TimeGetTimestamp];
    if(pLoginServer)
        pLoginServer->CreateTemporaryMeeting(pLoginServer->GetUserID(), ulRoomID, Room_VIDEO);
}

-(unsigned long)TimeGetTimestamp
{
	struct timeval now;
	gettimeofday(&now,NULL);
	return now.tv_sec*1000+now.tv_usec/1000;
}

-(void) OnFriendAdd:(std::string) strUserId
{
    m_strUserId = strUserId;
    [self performSelectorOnMainThread:@selector(OnAddUserInfo:) withObject:self waitUntilDone:YES];
}


-(void) OnFriendDelete:(std::string) strUserId;
{
    m_strUserId = strUserId;
    [self performSelectorOnMainThread:@selector(OnDeleteUserInfo:) withObject:self waitUntilDone:YES];
}

-(void) OnAddUserInfo:(id)mid
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
        ImsContactItem *contactItem=[[[ImsContactItem alloc]init]autorelease];
        contactItem.userid=m_strUserId;
        contactItem.username=m_strUserId;
        contactItem.isseletct=NO;
        
        [self.ContactArr addObject:contactItem];
        [self.tableview reloadData];
    }
}

-(IBAction)btOK:(id)sender
{
    
}

-(void) OnDeleteUserInfo:(id)mid
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

-(IBAction)BtOK:(id)sender
{
    
}

-(IBAction)BtBack:(id)sender
{
    [self dismissViewControllerAnimated:YES completion:nil];
  
}
-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [UIApplication sharedApplication].statusBarHidden = YES;
    [self.ContactArr removeAllObjects];
    
    UIBarButtonItem *rightBtn = [[UIBarButtonItem alloc]initWithTitle:@"确定" style:UIBarButtonItemStyleBordered target:self action:@selector(BtOK:)];
    
    self.navigationItem.rightBarButtonItem = rightBtn;
    [rightBtn release];
    
    UIBarButtonItem *leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(BtBack:)];
    self.navigationItem.leftBarButtonItem = leftBtn;
    [leftBtn release];
    [self UpdateUser];
    
}

-(void)viewWillDisappear:(BOOL)animated
{
   [self.tabBarController.tabBar setHidden:NO];
    [super viewWillDisappear:animated];
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
   
    [self.navigationController.navigationBar setHidden:NO];
    
    pLoginServer = LoginServer::OnGetLoginServer();
    
     self.imageBg.transform=CGAffineTransformMakeRotation(M_PI/2);
    int with=0;
    int hight=0;
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        with=1024;
//        hight=768;
//     } else {
//         with=480;
//         hight=320;
//     }
    with=480;
    hight=320;
    
    [ self.imageBg setFrame:CGRectMake(0,0,with,hight)];
    [self.view  setFrame:CGRectMake(0, 0, with,hight)];
    self.view.bounds = CGRectMake(0, 0, with,hight);
    self.navigationController.view.transform=CGAffineTransformMakeRotation(M_PI/2);
    
    [self.navigationController.view  setFrame:CGRectMake(0, 0, with,hight)];
    self.navigationController.view.bounds = CGRectMake(0, 0, with,hight);
    [self.navigationController.visibleViewController.view setFrame:CGRectMake(0, 0, with, hight)];
    self.navigationController.navigationBar.frame = CGRectMake(0, 0, self.navigationController.navigationBar.frame.size.width, self.navigationController.navigationBar.frame.size.height);
    [self.tableview setFrame:CGRectMake(0,0,with,hight)];
    
    tableview.separatorStyle = NO;
    
    self.title=@"我的好友";
}

-(void)dealloc
{
    if (pLoginServer) {
        //pLoginServer->m_IMGetUserInfo = nil;
    }
    
    self.toolBar=nil;
    self.tableview=nil;
    self.ContactArr=nil;
    pLoginServer = NULL;
    self.imageBg=nil;
    [super dealloc];
}

-(void) UpdateUser
{
    if(pLoginServer == NULL)
        return;
    
    std::vector<std::string> UserList;
    //pLoginServer->GetUserFriendList([strGroupName UTF8String], UserList);
    
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
    if (self.ContactArr.count>0) {
        if (self.ContactArr.count%4>0) {
            return  self.ContactArr.count/4+1;
        }
        else
        {
            return  self.ContactArr.count/4;
        }
    }
    else
        return 0;
    
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSUInteger row = [indexPath row];

    UserListCell *cell=nil;
    
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
//    {
//        static NSString * DisclosureMonitorNodeCellIdentifier =
//        @"UserListCell_ipadIdentifier";
//        
//        cell=  [tableView dequeueReusableCellWithIdentifier:
//                DisclosureMonitorNodeCellIdentifier ];
//        if (cell == nil) {
//            
//            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"UserListCell_ipad" owner:self options:nil];
//            cell = [nib objectAtIndex:0];
//        }  } else
//    
//    {
//        static NSString * DisclosureMonitorNodeCellIdentifier =
//        @"UserListCellIdentifier";
//        
//         cell=  [tableView dequeueReusableCellWithIdentifier:
//            DisclosureMonitorNodeCellIdentifier ];
//        if (cell == nil) {
//            
//            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"UserListCell" owner:self options:nil];
//            cell = [nib objectAtIndex:0];
//        }
//    
//    }
    static NSString * DisclosureMonitorNodeCellIdentifier =
    @"UserListCellIdentifier";
    
    cell=  [tableView dequeueReusableCellWithIdentifier:
            DisclosureMonitorNodeCellIdentifier ];
    if (cell == nil) {
        
        NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"UserListCell" owner:self options:nil];
        cell = [nib objectAtIndex:0];
    }
    
    int index=row*4;
    cell.userListViewController=self;
    
    ImsContactItem *contact1 = [self.ContactArr objectAtIndex:index];
    cell.contactItem1  = contact1;
    
    
    if (cell.contactItem1.isseletct) {
        [ cell.selectBtn1 setImage:[UIImage imageNamed:@"选中"] forState:normal];
    }
    else
    {
        [ cell.selectBtn1 setImage:[UIImage imageNamed:@"未选中"] forState:normal];
    }
    
    NSString *strLoginInfo1=[[[NSString alloc]initWithCString:contact1.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
    
    NSString *strphone1=[[[NSString alloc]initWithCString:contact1.phone.c_str() encoding: NSUTF8StringEncoding] autorelease];
    
    [cell.uitextName1 setText:strLoginInfo1];
    [cell.uitextNnmber1 setText:strphone1];
    
    if (self.ContactArr.count>index+1)
    {
        [cell.selectBtn2 setHidden:NO];
        [cell.uitextName2 setHidden:NO];
        [cell.uitextNnmber2 setHidden:NO];
        [cell.imageBg2 setHidden:NO];
        
        ImsContactItem *contact2 = [self.ContactArr objectAtIndex:index+1];
        cell.contactItem2  = contact2;
        if (cell.contactItem2.isseletct) {
            [ cell.selectBtn2 setImage:[UIImage imageNamed:@"选中"] forState:normal];
        }
        else
        {
            [ cell.selectBtn2 setImage:[UIImage imageNamed:@"未选中"] forState:normal];
            
        }
        NSString *strLoginInfo2=[[[NSString alloc]initWithCString:contact2.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        NSString *strphone2=[[[NSString alloc]initWithCString:contact2.phone.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        [cell.uitextName2 setText:strLoginInfo2];
        [cell.uitextNnmber2 setText:strphone2];
    }
    else
    {
        [cell.selectBtn2 setHidden:YES];
        [cell.uitextName2 setHidden:YES];
        [cell.uitextNnmber2 setHidden:YES];
        [cell.imageBg2 setHidden:YES];
    }
    
    if (self.ContactArr.count>index+2)
    {
        [cell.selectBtn3 setHidden:NO];
        [cell.uitextName3 setHidden:NO];
        [cell.uitextNnmber3 setHidden:NO];
        [cell.imageBg3 setHidden:NO];
        
        ImsContactItem *contact3 = [self.ContactArr objectAtIndex:index+2];
        cell.contactItem3  = contact3;
        if (cell.contactItem3.isseletct) {
            [ cell.selectBtn3 setImage:[UIImage imageNamed:@"选中"] forState:normal];
        }
        else
        {
            [ cell.selectBtn3 setImage:[UIImage imageNamed:@"未选中"] forState:normal];
            
        }
        NSString *strLoginInfo3=[[[NSString alloc]initWithCString:contact3.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        NSString *strphone3=[[[NSString alloc]initWithCString:contact3.phone.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        [cell.uitextName3 setText:strLoginInfo3];
        [cell.uitextNnmber3 setText:strphone3];
 
    }
    else
    {
        [cell.selectBtn3 setHidden:YES];
        [cell.uitextName3 setHidden:YES];
        [cell.uitextNnmber3 setHidden:YES];
        [cell.imageBg3 setHidden:YES];
    }
    
    if (self.ContactArr.count>index+3)
    {
        [cell.selectBtn4 setHidden:NO];
        [cell.uitextName4 setHidden:NO];
        [cell.uitextNnmber4 setHidden:NO];
        [cell.imageBg4 setHidden:NO];
        ImsContactItem *contact4 = [self.ContactArr objectAtIndex:index+3];
        cell.contactItem4 = contact4;
        if (cell.contactItem4.isseletct) {
            [ cell.selectBtn4 setImage:[UIImage imageNamed:@"选中"] forState:normal];
        }
        else
        {
            [ cell.selectBtn4 setImage:[UIImage imageNamed:@"未选中"] forState:normal];
            
        }
        NSString *strLoginInfo4=[[[NSString alloc]initWithCString:contact4.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        NSString *strphone4=[[[NSString alloc]initWithCString:contact4.phone.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        [cell.uitextName4 setText:strLoginInfo4];
        [cell.uitextNnmber4 setText:strphone4];
    }
    else
    {
        [cell.selectBtn4 setHidden:YES];
        [cell.uitextName4 setHidden:YES];
        [cell.uitextNnmber4  setHidden:YES];
    
        [cell.imageBg4 setHidden:YES];
    }
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    return cell;
}

-(float)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
//    {
//        return 100;
//    }
//    else
//    {
//        return 60;
//    }
    return 60;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
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

@end
