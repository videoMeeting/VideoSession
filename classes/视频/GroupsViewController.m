//
//  ExitGroupViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "GroupsViewController.h"
#import"VideoGroup.h"
#import "VideoGroupCell.h"
#import "GroupUserViewController.h"
@interface GroupsViewController ()

@end

@implementation GroupsViewController
@synthesize tableview;
@synthesize GroupArray;
@synthesize groupUserViewController;
@synthesize savegroupname;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        self.GroupArray=[[[NSMutableArray alloc]init]autorelease];
        
    }
    return self;
}

-(void)initData
{
    [self.GroupArray removeAllObjects];
    if(pLoginServer)
    {
        std::map<unsigned int, std::string> UserGrop;
        pLoginServer->GetUserGropList(UserGrop);
        std::map<unsigned int, std::string>::iterator it = UserGrop.begin();
        while (it!=UserGrop.end()) {
            if(it->second != [self.savegroupname UTF8String])
            {
                VideoGroup  *videogroup=[[[VideoGroup alloc]init]autorelease];
                [self.GroupArray addObject:videogroup];
                videogroup.name=[NSString stringWithCString:it->second.c_str() encoding:NSUTF8StringEncoding];
                char strCount[25]={0};
                sprintf(strCount, "(%d人)",pLoginServer->GetUserGropUserCount(it->second));
                videogroup.number=[NSString stringWithCString:strCount encoding:NSUTF8StringEncoding];
            }
            it++;
        }
    }
    [self.tableview reloadData];
}

-(IBAction)BtExit:(id)sender
{
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController popViewControllerAnimated:YES];
    //self.hidesBottomBarWhenPushed = NO;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
     // self.tableview.separatorStyle = NO;
    UIBarButtonItem *leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(BtExit:)];
    self.navigationItem.leftBarButtonItem = leftBtn;
    [leftBtn release];
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    pLoginServer = LoginServer::OnGetLoginServer();
    [self initData];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
}

-(void)dealloc
{
    self.tableview=nil;
    self.GroupArray=nil;
    pLoginServer = NULL;
    self.groupUserViewController=nil;
    [super dealloc];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return  self.GroupArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSUInteger row = [indexPath row];
    VideoGroupCell *cell=nil;
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
//    {
//        static NSString * DisclosureMonitorNodeCellIdentifier =
//        @"VideoGroupCell_ipadIdentifier";
//        
//        cell =  [tableView dequeueReusableCellWithIdentifier:
//                 DisclosureMonitorNodeCellIdentifier ];
//        if (cell == nil) {
//            
//            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"VideoGroupCell_ipad" owner:self options:nil];
//            cell = [nib objectAtIndex:0];
//        }
//    }
//    else {
//        
//        static NSString * DisclosureMonitorNodeCellIdentifier =
//        @"VideoGroupCellIdentifier";
//        
//        cell =  [tableView dequeueReusableCellWithIdentifier:
//                 DisclosureMonitorNodeCellIdentifier ];
//        if (cell == nil) {
//            
//            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"VideoGroupCell" owner:self options:nil];
//            cell = [nib objectAtIndex:0];
//        }
//    }
    
    static NSString * DisclosureMonitorNodeCellIdentifier =
    @"VideoGroupCellIdentifier";
    
    cell =  [tableView dequeueReusableCellWithIdentifier:
             DisclosureMonitorNodeCellIdentifier ];
    if (cell == nil) {
        
        NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"VideoGroupCell" owner:self options:nil];
        cell = [nib objectAtIndex:0];
    }
    
    VideoGroup *videoGroup = [self.GroupArray objectAtIndex:row];
    [cell.Name  setText:videoGroup.name];
    [cell.Number  setText:videoGroup.number];
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.uibutton.hidden = YES;
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
    VideoGroup *videoGroup = [self.GroupArray objectAtIndex:[indexPath row]];
    self.groupUserViewController=[[[GroupUserViewController alloc]initWithNibName:@"GroupUserViewController" bundle:nil]autorelease];
    self.groupUserViewController.groupname = videoGroup.name;
    self.groupUserViewController.savegroupname = self.savegroupname;
    self.hidesBottomBarWhenPushed = YES;
    [super.navigationController pushViewController:groupUserViewController animated:YES];
    self.hidesBottomBarWhenPushed = NO;
}

-(NSIndexPath*)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    return indexPath;
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
