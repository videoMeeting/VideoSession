//
//  GroupUserViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "GroupUserViewController.h"
#import"ImsContactItem.h"
#import "GroupUserCell.h"
@interface GroupUserViewController ()

@end

@implementation GroupUserViewController
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
    [self.navigationController popViewControllerAnimated:YES];
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
        ImsContactItem *contactItem=[[[ImsContactItem alloc]init]autorelease];
        contactItem.userid=*iter;
        contactItem.username=*iter;
        contactItem.isseletct=NO;
        [self.ContactArr addObject:contactItem];
        ++iter;
    }
    
    [self.tableview reloadData];
}

-(IBAction)btSave:(id)sender
{
   
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    pLoginServer = LoginServer::OnGetLoginServer();
    [self.ContactArr removeAllObjects];
    [self UpdateUser];
    [self.tableview reloadData];
}

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    
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
    if(self.ContactArr.count>0)
        return  (self.ContactArr.count/2+self.ContactArr.count%2) ;
    else
        return  0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSUInteger row = [indexPath row];
   
    static NSString * DisclosureMonitorNodeCellIdentifier =
        @"GroupUserCellIdentifier";
        
    GroupUserCell *cell =  [tableView dequeueReusableCellWithIdentifier:
                 DisclosureMonitorNodeCellIdentifier ];
    if (cell == nil) {
            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"GroupUserCell" owner:self options:nil];
            cell = [nib objectAtIndex:0];
        }
        
    int index=row*2;
    cell.groupUserViewController=self;
    
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
        [cell.imagebg2 setHidden:NO];
        
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
        [cell.imagebg2 setHidden:YES];
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

@end
