//
//  GroupUserViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "InviteGroupUserViewController.h"
#import"ImsContactItem.h"
#import "InviteGroupUserCell.h"
@interface InviteGroupUserViewController ()

@end

@implementation InviteGroupUserViewController
@synthesize tableview;
@synthesize ContactArr;
@synthesize groupname;
@synthesize savegroupname;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        pLoginServer=NULL;
        self.ContactArr=[[[NSMutableArray alloc]init]autorelease];
    }
    return self;
}

-(void)BtExit:(id)sender
{
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController popViewControllerAnimated:NO];
  //  self.hidesBottomBarWhenPushed = NO;
}

-(void) UpdateUser
{
    if(pLoginServer == NULL)
        return;
    
    std::vector<std::string> UserList;
    pLoginServer->GetUserFriendList([self.groupname UTF8String], UserList);
    
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

-(IBAction)btSave:(id)sender
{
    for(ImsContactItem *contactItem in self.ContactArr) {
        if (contactItem.isseletct&&!contactItem.isInRoom&&contactItem.status=="online") {
            if(pLoginServer)
                pLoginServer->OnInviteUser(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), contactItem.userid);
        }
    }
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController popViewControllerAnimated:NO];
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [UIApplication sharedApplication].statusBarHidden = YES;
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    pLoginServer = LoginServer::OnGetLoginServer();
    pLoginServer->m_iMGetUserFriendInfo = self;
    [self.ContactArr removeAllObjects];
    [self UpdateUser];
}

-(void)viewWillDisappear:(BOOL)animated
{
    pLoginServer->m_iMGetUserFriendInfo = nil;
     [UIApplication sharedApplication].statusBarHidden = NO;
    [super viewWillDisappear:animated];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    tableview.separatorStyle = NO;
    
    self.tableview.separatorStyle = NO;
    UIBarButtonItem *leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(BtExit:)];
    self.navigationItem.leftBarButtonItem = leftBtn;
    
    [leftBtn release];
    
    UIBarButtonItem *rightBtn = [[UIBarButtonItem alloc]initWithTitle:@"确定" style:UIBarButtonItemStyleBordered target:self action:@selector(btSave:)];
    self.navigationItem.rightBarButtonItem = rightBtn;
    [rightBtn release];
   
    // Do any additional setup after loading the view from its nib.
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
    InviteGroupUserCell *cell=nil;

   
    static NSString * DisclosureMonitorNodeCellIdentifier =
            @"InviteGroupUserCellIdentifier";
            
    cell=  [tableView dequeueReusableCellWithIdentifier:
                    DisclosureMonitorNodeCellIdentifier ];
    if (cell == nil) {
            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"InviteGroupUserCell" owner:self options:nil];
        cell = [nib objectAtIndex:0];
    }
         
    int index=row*4;
    cell.userListViewController=self;
    
    ImsContactItem *contact1 = [self.ContactArr objectAtIndex:index];
    cell.contactItem1  = contact1;
    
    if (cell.contactItem1.status == "offline")
    {
        [ cell.imageBg1 setImage:[UIImage imageNamed:@"lixian"]];
    }
    else if (cell.contactItem1.isInRoom)
    {
        [ cell.imageBg1 setImage:[UIImage imageNamed:@"meeting"] ];
    }
    else
    {
        
        [cell.imageBg1 setImage:[UIImage imageNamed:@"kongxian"]  ];
        
        if (cell.contactItem1.isseletct) {
            
            [cell.selectBtn1 setImage:[UIImage imageNamed:@"背景2"] forState:normal];
        }
        else
        {
             [cell.selectBtn1 setImage:[UIImage imageNamed:@"好友背景"] forState:normal];
        }

        
      
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
        
        if (cell.contactItem2.status == "offline")
        {
            [ cell.imageBg2 setImage:[UIImage imageNamed:@"lixian"] ];
        }
        else if (cell.contactItem2.isInRoom)
        {
            [ cell.imageBg2 setImage:[UIImage imageNamed:@"meeting"] ];
        }
        else
        {
            
            [cell.imageBg2 setImage:[UIImage imageNamed:@"kongxian"]];
            
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
        
        if (cell.contactItem3.status == "offline")
        {
            [ cell.imageBg3 setImage:[UIImage imageNamed:@"lixian"]];
        }
        else if (cell.contactItem3.isInRoom)
        {
            [ cell.imageBg3 setImage:[UIImage imageNamed:@"meeting"]];
        }
        else
        {
            
            [cell.imageBg3 setImage:[UIImage imageNamed:@"kongxian"]];
            
            if (cell.contactItem3.isseletct) {
                
                [cell.selectBtn3 setImage:[UIImage imageNamed:@"背景2"] forState:normal];
            }
            else
            {
                [cell.selectBtn3 setImage:[UIImage imageNamed:@"好友背景"] forState:normal];
            }
            
            
            
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
        
        if (cell.contactItem4.status == "offline")
        {
            [ cell.imageBg4 setImage:[UIImage imageNamed:@"lixian"] ];
        }
        else if (cell.contactItem4.isInRoom)
        {
            [ cell.imageBg4 setImage:[UIImage imageNamed:@"meeting"] ];
        }
        else
        {
            
            [cell.imageBg4 setImage:[UIImage imageNamed:@"kongxian"]];
            
            if (cell.contactItem4.isseletct) {
                
                [cell.selectBtn4 setImage:[UIImage imageNamed:@"背景2"] forState:normal];
            }
            else
            {
                [cell.selectBtn4 setImage:[UIImage imageNamed:@"好友背景"] forState:normal];
            }
            
            
            
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
//        return 120;
//    } else
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

-(void)dealloc
{
    self.tableview=nil;
    self.ContactArr=nil;
    [super dealloc];
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

-(void) OnFriendAdd:(const std::string&)strGroup strUserId:(const std::string&)strUserId
{
    if(strGroup == [self.groupname UTF8String])
    {
        m_strUserId = strUserId;
        [self performSelectorOnMainThread:@selector(MyFriendAdd:) withObject:self waitUntilDone:YES];
    }
}

-(void) OnFriendDelete:(const std::string&)strGroup strUserId:(const std::string&)strUserId
{
    if(strGroup == [self.groupname UTF8String])
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
    for(int i=0; i<[self.ContactArr count]; i++)
    {
        ImsContactItem *contactItem = [self.ContactArr objectAtIndex:i];
        if(contactItem!=nil)
        {
            if(contactItem.userid == m_strUserId)
            {
                contactItem.status = "online";
                [self.tableview reloadData];
                break;
            }
        }
    }
}

-(void) MyFriendOffline:(id)mid
{
    for(int i=0; i<[self.ContactArr count]; i++)
    {
        ImsContactItem *contactItem = [self.ContactArr objectAtIndex:i];
        if(contactItem!=nil)
        {
            if(contactItem.userid == m_strUserId)
            {
                contactItem.status = "offline";
                [self.tableview reloadData];
                break;
            }
        }
    }
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


@end
