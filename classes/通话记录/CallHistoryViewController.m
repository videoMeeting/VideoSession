//
//  CallHistoryViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "CallHistoryViewController.h"
#import "CallHistoryCell.h"
#import "CallHistoryClass.h"
#import "CallHistoryHelp.h"
@interface CallHistoryViewController ()

@end

@implementation CallHistoryViewController
@synthesize  historyTable;
@synthesize  historyArray;
@synthesize tabBarController;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
        self.title = @"通话记录";
        
        UIImage* anImage = [UIImage imageNamed:@"通话记录tab.png"];
        
        UITabBarItem* theItem = [[UITabBarItem alloc] initWithTitle:@"通话记录" image:anImage tag:0];
        self.historyArray =[[[NSMutableArray alloc]init]autorelease];
        self.tabBarItem = theItem;
        // self.tabBarController.view.frame = [UIScreen mainScreen].applicationFrame;
        
        [theItem release];
    }
    return self;
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.6 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    CallHistoryHelp *callHistoryHelp=[[CallHistoryHelp alloc]init];
    NSMutableArray *istoryArray=[callHistoryHelp GetHistory];
    [self.historyArray reverseObjectEnumerator];
    
    [self.historyArray removeAllObjects];
    pLoginServer = LoginServer::OnGetLoginServer();
     
    for (NSString * str  in [istoryArray reverseObjectEnumerator]) {
        
        CallHistoryClass *callHistoryClass = (CallHistoryClass *)str;
        std::string strUserID = pLoginServer->GetUserID();
        if( strncmp([callHistoryClass.CallName UTF8String], strUserID.c_str(), strlen(strUserID.c_str())) == 0)
        {
            [self.historyArray addObject:str];
        }
    }
    
    [self.historyTable reloadData];
    
    [callHistoryHelp dealloc];
    callHistoryHelp = nil;
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
-(IBAction)BtBack:(id)sender
{
    [self.tabBarController setSelectedIndex:0];
}
- (void)viewDidLoad
{
    [super viewDidLoad];
    
//    UIBarButtonItem* leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(BtBack:)];
//    self.navigationItem.leftBarButtonItem = leftBtn;
//    [leftBtn release];
    
    // Do any additional setup after loading the view from its nib.
    self.title =@"通话记录";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return  self.historyArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    NSUInteger row = [indexPath row];
    
    static NSString * DisclosureMonitorNodeCellIdentifier =
        @"CallHistoryCellIdentifier";
        
    CallHistoryCell *cell =  [tableView dequeueReusableCellWithIdentifier:
                 DisclosureMonitorNodeCellIdentifier ];
    if (cell == nil) {
            
        NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"CallHistoryCell" owner:self options:nil];
            cell = [nib objectAtIndex:0];
    }
    
//    int allcount=self.historyArray.count;
    
    CallHistoryClass *callHistoryClass = [self.historyArray objectAtIndex:row];
    
    [cell.labelName  setText:callHistoryClass.CallName];
    [cell.labelDate  setText:callHistoryClass.CallDate];
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
     
    return cell;
}
-(float)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 44;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
}

-(NSIndexPath*)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    return indexPath;
}

-(void)dealloc
{
    self.historyTable=nil;
    self.historyArray=nil;
    self.tabBarController=nil;
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
