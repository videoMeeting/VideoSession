//
//  VideoViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "VideoViewController.h"
#import "CallViewController.h"
#import "VideoGroup.h"
#import "VideoGroupCell.h"
#import "EditGroupViewController.h"
#import "VideoSessionViewController.h"
#import "PhoneCallViewController.h"
#import "UIViewController+MJPopupViewController.h"
#import "CallHistoryHelp.h"
#import "LoginViewController.h"
#import "SessionShowViewController.h"

@interface VideoViewController () <MJSecondPopupDelegate>{
    PhoneCallViewController *phoneCallViewController;
}
@property(retain,nonatomic)PhoneCallViewController *phoneCallViewController;
@end

@interface VideoViewController ()
@end

@implementation VideoViewController

@synthesize callViewController;
@synthesize numlabel;
@synthesize tableview;
@synthesize backImageView;
@synthesize GroupArray;
@synthesize editGroupViewController;
@synthesize leftBtn;
@synthesize videoSessionViewController;
@synthesize phoneCallViewController;
@synthesize activityView;
@synthesize activityWheel;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        self =[super initWithNibName:@"VideoViewController_ipad" bundle:nil];
//    } else {
//        self =[super initWithNibName:@"VideoViewController" bundle:nil];
//    }
    
    self =[super initWithNibName:@"VideoViewController" bundle:nil];
    if (self) {
        // Custom initialization
       // self.title = @"视频";
        self.GroupArray=[[[NSMutableArray alloc]init]autorelease];
        UIImage* anImage = [UIImage imageNamed:@"视频tab.png"];
        UITabBarItem* theItem = [[UITabBarItem alloc] initWithTitle:@"视频" image:anImage tag:0];
        self.tabBarItem = theItem;
        [theItem release];
        isEditGroup=NO;
        m_pMBProgressHUD = nil;
        mNSTimer = nil;
        self.pIntoVessionViewController = nil;
        isCallUser = false;
        CallViewIsOpen = false;
    }
    return self;
}

-(IBAction)btCallFriends:(id)sender
{
    self.callViewController=[[[CallViewController alloc]initWithNibName:@"CallViewController" bundle:nil]autorelease];
    self.hidesBottomBarWhenPushed = YES;
    [super.navigationController pushViewController:callViewController animated:YES];
    self.hidesBottomBarWhenPushed = NO;
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    pLoginServer = LoginServer::OnGetLoginServer();
    assert(pLoginServer);
    pLoginServer->m_MMMeetingProtocol = self;
    
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.6 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    pLoginServer->m_iMGetUserGroupInfo = self;
    [self initData];
    
    NSString *UserID=[[[NSString alloc]initWithCString:pLoginServer->GetUserID().c_str() encoding: NSUTF8StringEncoding] autorelease];
   self.title = [[[NSString alloc]initWithFormat:@"视频 (%@)",UserID]autorelease];
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

-(void)viewWillDisappear:(BOOL)animated
{
    if(pLoginServer!=NULL)
        pLoginServer->m_iMGetUserGroupInfo = nil;
    self.title = @"视频";
    [super viewWillDisappear:animated];
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
            VideoGroup  *videogroup=[[[VideoGroup alloc]init]autorelease];
            [self.GroupArray addObject:videogroup];
            videogroup.name=[NSString stringWithCString:it->second.c_str() encoding:NSUTF8StringEncoding];
            char strCount[25]={0};
            sprintf(strCount, "(%d人)",pLoginServer->GetUserGropUserCount(it->second));
            videogroup.number=[NSString stringWithCString:strCount encoding:NSUTF8StringEncoding];
            it++;
        }
    }
    [self.tableview reloadData];
}

-(IBAction)BtNew:(id)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"输入分组名称" message:@""
                                                   delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"确定", nil];
	alert.alertViewStyle = UIAlertViewStylePlainTextInput;
    [alert show];
	[alert release];
}

- (void)alertView:(UIAlertView *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
	// use "buttonIndex" to decide your action
    UITextField *textName=nil;
    for (UIView *view in [actionSheet subviews])                 {
        if ([view isKindOfClass:[UITextField class]]){
            textName = (UITextField *)view;
            NSLog(@"%@",textName.text);
        }
    }
    
    if(editGroup == actionSheet)
    {
        if (buttonIndex == 1)
        {
            if([textName.text isEqualToString:@""])
            {
                return;
            }
            
            if([textName.text isEqualToString:m_oldgroupname])
            {
                self.hidesBottomBarWhenPushed = YES;
                [self.navigationController popViewControllerAnimated:YES];
              
                return;
            }
            
            std::string strGropName = [textName.text UTF8String];
            int re = pLoginServer->UserGropUpdateName([m_oldgroupname UTF8String],strGropName);
            if(re == -2)
            {
                return;
            }
            
            m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
            if(mNSTimer == nil)
                mNSTimer = [NSTimer scheduledTimerWithTimeInterval:1.6 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
        }
        return;
    }
    
    if (buttonIndex == 1)
	{
        if(pLoginServer&&textName&&![textName.text isEqualToString:@""])
        {
            std::string strGropName = [textName.text UTF8String];
            if(!pLoginServer->AddUserGrop(strGropName))
            {
                [self Alert:@"该组已经存在" message:@"请输入其它组名"];
            }
        }
	}
}

-(void)Alert:(NSString*) result message:(NSString*) message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:result message:message
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];
    [alert release];
}

-(void)EditGroup:(NSString*)groupName
{
#if 0
    self.editGroupViewController=[[[EditGroupViewController alloc]initWithNibName:@"EditGroupViewController" bundle:nil]autorelease];
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:self.editGroupViewController animated:YES];
    self.hidesBottomBarWhenPushed = NO;
    self.editGroupViewController.groupName.text = groupName;
    self.editGroupViewController.oldgroupname = groupName;
    if([groupName isEqualToString:@"我的好友"])
        [self.editGroupViewController.groupName setEnabled: NO];
#endif
    m_oldgroupname = groupName;
    editGroup = [[UIAlertView alloc] initWithTitle:@"修改组名称" message:@""
                                                   delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"确定", nil];
	editGroup.alertViewStyle = UIAlertViewStylePlainTextInput;
    [editGroup show];
	[editGroup release];
}

-(IBAction)BtEdit:(id)sender
{
    isEditGroup=!isEditGroup;
    [self.tableview setEditing:isEditGroup animated:YES];
    [self.tableview reloadData];
    if (isEditGroup) {
        [self.leftBtn setTitle:@"取消"];
    }
    else
    {
        [self.leftBtn setTitle:@"编辑"];
    }
}

-(void)showActivityViewer {
    
    self.activityView = [[[UIView alloc] initWithFrame: CGRectMake(0, 0, self.view.window.bounds.size.width, self.view.window.bounds.size.height)] autorelease];
    
    self.activityView.backgroundColor = [UIColor blackColor];
    
    self.activityView.alpha = 0.5;
    
    self.activityWheel = [[[UIActivityIndicatorView alloc] initWithFrame: CGRectMake(self.view.window.bounds.size.width / 2 - 12, self.view.window.bounds.size.height / 2 - 12, 24, 24)] autorelease];
    
    self.activityWheel.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhiteLarge;
    
    self.activityWheel.autoresizingMask = (UIViewAutoresizingFlexibleLeftMargin |
                                           
                                           UIViewAutoresizingFlexibleRightMargin |
                                           
                                           UIViewAutoresizingFlexibleTopMargin |
                                           
                                           UIViewAutoresizingFlexibleBottomMargin);
    
    [self.activityView addSubview:self.activityWheel];
    
    [self.view.window addSubview: self.activityView];
    
    [[[self.activityView subviews] objectAtIndex:0] startAnimating];
    
}

-(void)removeActivityViewer:(id)sender {
    
    [self.activityWheel removeFromSuperview];
    
    [self.activityView removeFromSuperview];
    
    self.activityWheel = nil;
    
    self.activityView = nil;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.loginViewController=[[[LoginViewController alloc]initWithNibName:@"LoginViewController" bundle:nil]autorelease];
    self.loginViewController.tabBarController=self.tabBarController;
    
     self.nalginController = [[[UISubNavigationController alloc] initWithRootViewController:self.loginViewController]autorelease];
    
    [self.nalginController.navigationBar setHidden:YES];
    
    [self presentViewController:self.nalginController animated:NO completion:nil];
    
    self.navigationItem.rightBarButtonItem = [[[UIBarButtonItem alloc]initWithTitle:@"新建" style:UIBarButtonItemStyleBordered target:self action:@selector(BtNew:)]autorelease];
  
    self.navigationItem.leftBarButtonItem = [[[UIBarButtonItem alloc]initWithTitle:@"编辑" style:UIBarButtonItemStyleBordered target:self action:@selector(BtEdit:)]autorelease];
 
  
    // Do any additional setup after loading the view from its nib.
   
    
    int _screenWidth = [UIScreen mainScreen].bounds.size.width;
    int _screenHeight = [UIScreen mainScreen].bounds.size.height;
    CGRect frameSecond = self.view.frame;
    frameSecond.size.width=_screenWidth;
    frameSecond.size.height=_screenHeight;
    [self.backImageView setFrame:frameSecond];
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        VideoGroup  *videogroup = [self.GroupArray objectAtIndex:indexPath.row];
        if(pLoginServer&&videogroup)
            pLoginServer->DeleteUserGrop([videogroup.name UTF8String]);
    }
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
    }
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    VideoGroup  *videogroup = [self.GroupArray objectAtIndex:indexPath.row];
    if([videogroup.name isEqualToString:@"我的好友"])
        return UITableViewCellEditingStyleNone;
    return UITableViewCellEditingStyleDelete;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)dealloc
{
    if (self.phoneCallViewController) {
        [phoneCallViewController release];
        //self.phoneCallViewController=nil;
    }
    pLoginServer->m_MMMeetingProtocol = nil;
    self.leftBtn=nil;
    self.callViewController=nil;
    self.numlabel=nil;
    self.tableview=nil;
    self.GroupArray=nil;
    self.backImageView=nil;
    self.editGroupViewController=nil;
    self.videoSessionViewController=nil;
   // self.pIntoVessionViewController = nil;
    
    [super dealloc];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
   return  self.GroupArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
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
  
    cell.videoViewController=self;
    VideoGroup *videoGroup = [self.GroupArray objectAtIndex:row];
    [cell.Name  setText:videoGroup.name];
    [cell.Number  setText:videoGroup.number];
    cell.uibutton.hidden = NO;
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    return cell;
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
    VideoGroup  *videogroup=[self.GroupArray objectAtIndex:[indexPath row]];
    self.callViewController=[[[CallViewController alloc]initWithNibName:@"CallViewController" bundle:nil]autorelease];
    callViewController.strGroupName = videogroup.name;
    self.callViewController.pVideoViewController = self;
    self.hidesBottomBarWhenPushed = YES;
    [super.navigationController pushViewController:callViewController animated:YES];
    self.hidesBottomBarWhenPushed = NO;
}

-(NSIndexPath*)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    return indexPath;
}

-(void) OnInsertGroup:(const std::string&)strGroup nIndex:(unsigned int)nIndex
{
    [self performSelectorOnMainThread:@selector(MyInsertGroup:) withObject:self waitUntilDone:YES];
}

-(void) OnDeleteGrop:(const std::string&)strGroup nIndex:(unsigned int)nIndex
{
    [self performSelectorOnMainThread:@selector(OnDeleteGrop:) withObject:self waitUntilDone:YES];
}

-(void) OnUpdateGroupName:(const std::string&)strOldGroup strNewGroup:(const std::string&)strNewGroup
{
    [self performSelectorOnMainThread:@selector(MyUpdateGroup:) withObject:self waitUntilDone:YES];
}

-(void) OnUpdateGroupIndex:(const std::string&)strGroup nIndex:(unsigned int)nIndex
{
    [self performSelectorOnMainThread:@selector(MyUpdateGroup:) withObject:self waitUntilDone:YES];
}

-(void)MyInsertGroup:(id)mid
{
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    [self initData];
}

-(void)OnDeleteGrop:(id)mid
{
    m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    [self initData];
}

-(void) MyUpdateGroup:(id)mid
{
    [self initData];
}

-(void) OnCreateInterimMeeting:(std::string)strHostId ulRoomID:(unsigned long)ulRoomID uiRoomType:(unsigned int)uiRoomType
{
    [self performSelectorOnMainThread:@selector(MyCreateInterimMeeting:) withObject:self waitUntilDone:YES];
}

-(void) MyCreateInterimMeeting:(id)mid
{
    self.videoSessionViewController=[[[VideoSessionViewController alloc]initWithNibName:@"VideoSessionViewController" bundle:nil]autorelease];
    [self presentViewController:self.videoSessionViewController animated:YES completion:nil];
    
    self.videoSessionViewController.sessionShowViewController.pVideoViewController = self;
    
    NSString* username = [NSString stringWithCString:pLoginServer->GetHostID().c_str() encoding:NSUTF8StringEncoding];
    NSString* Info = [NSString stringWithFormat:@"%@等人",username];
    
    NSDate *now = [NSDate date];
    NSCalendar *calendar = [NSCalendar currentCalendar];
    NSUInteger unitFlags = NSYearCalendarUnit | NSMonthCalendarUnit | NSDayCalendarUnit | NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit;
    NSDateComponents *dateComponent = [calendar components:unitFlags fromDate:now];
    
    NSString* timer = [NSString stringWithFormat:@"%d-%d-%d %d:%d",[dateComponent year], [dateComponent month], [dateComponent day], [dateComponent hour], [dateComponent minute]];
    
    CallHistoryHelp *callHistoryHelp=[[CallHistoryHelp alloc]init];
    [callHistoryHelp insertHistory:Info callDate:timer];
    [callHistoryHelp dealloc];
    callHistoryHelp=nil;
    	[self performSelector:@selector(HostEnterRoomEnd) withObject:nil afterDelay:1];
//    [self HostEnterRoomEnd];
}

-(void) OnHostInviteUser:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID 
{
    mstrUserID = strUserID;
    mulRoomID = ulRoomID;
    [self performSelectorOnMainThread:@selector(MyInHostInviteUser:) withObject:self waitUntilDone:YES];
}

-(void) MyInHostInviteUser:(id)mid
{
    if(isCallUser==false)
    {
        phoneCallViewController=[[PhoneCallViewController alloc]initWithNibName:@"PhoneCallViewController" bundle:nil ];
        phoneCallViewController.delegate=self;
        [self presentPopupViewController:phoneCallViewController animationType:MJPopupViewAnimationFade];
        phoneCallViewController.accpetUserID.text = [[[NSString alloc] initWithCString:mstrUserID.c_str() encoding: NSUTF8StringEncoding] autorelease];
        phoneCallViewController.accpetInfo.text=@"正在呼叫...";
        isCallUser=true;
        CallViewIsOpen = true;
    }
}

-(void) OnEnterInterimMeetingInfo:(unsigned long)ulRoomID
{
    [self performSelectorOnMainThread:@selector(MyEnterInterimMeetingInfo:) withObject:self waitUntilDone:YES];
}

-(void) MyEnterInterimMeetingInfo:(id)mid
{
 
   /*if(self.pIntoVessionViewController!=nil)
    {
        [self.pIntoVessionViewController dismissModalViewControllerAnimated:NO];
      self.pIntoVessionViewController = nil;
    }*/
  
    [self dismissPopupViewControllerWithanimationType:MJPopupViewAnimationFade];
    if ( self.pIntoVessionViewController) {
         self.pIntoVessionViewController=nil;
    }
    [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeLeft animated:NO];
    
    self.videoSessionViewController=[[[VideoSessionViewController alloc]initWithNibName:@"VideoSessionViewController" bundle:nil]autorelease];
    [self presentViewController:self.videoSessionViewController animated:YES completion:nil];
    
    NSString* username = [NSString stringWithCString:pLoginServer->GetHostID().c_str() encoding:NSUTF8StringEncoding];
    NSString* Info = [NSString stringWithFormat:@"%@等人",username];
    
    NSDate *now = [NSDate date];
    NSCalendar *calendar = [NSCalendar currentCalendar];
    NSUInteger unitFlags = NSYearCalendarUnit | NSMonthCalendarUnit | NSDayCalendarUnit | NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit;
    NSDateComponents *dateComponent = [calendar components:unitFlags fromDate:now];
    
    NSString* timer = [NSString stringWithFormat:@"%d-%d-%d %d:%d",[dateComponent year], [dateComponent month], [dateComponent day], [dateComponent hour], [dateComponent minute]];
    
    CallHistoryHelp *callHistoryHelp=[[CallHistoryHelp alloc]init];
    [callHistoryHelp insertHistory:Info callDate:timer];
    [callHistoryHelp dealloc];
    callHistoryHelp=nil;
}

-(void) OnJoinTemporaryMeeting:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID
{
    mstrUserID = strUserID;
    mulRoomID = ulRoomID;
    [self performSelectorOnMainThread:@selector(MyJoinTemporaryMeeting:) withObject:self waitUntilDone:YES];
}

-(void) MyJoinTemporaryMeeting:(id)mid
{
    if(self.videoSessionViewController!=nil)
    {
        if(pLoginServer->GetIsInRoom() && pLoginServer->GetRoomId() == mulRoomID)
        {
            [self.videoSessionViewController PeerUserJoinTemporaryMeeting:mstrUserID ulRoomID:mulRoomID];
        }
       [self.videoSessionViewController MyUpdateMeetingInfo:mid];
    }
}

-(void) OnPleaseOutTemporaryMeeting:(const std::string&)strHostID ulRoomID:(unsigned long)ulRoomID strUserID:(const std::string&)strUserID
{
    mstrUserID = strUserID;
    mulRoomID = ulRoomID;
    [self performSelectorOnMainThread:@selector(MyPleaseOutTemporaryMeeting:) withObject:self waitUntilDone:YES];
}

-(void)MyPleaseOutTemporaryMeeting:(id)mid
{
    if(mstrUserID == pLoginServer->GetUserID())
    {
        if(self.videoSessionViewController!=nil)
        {
            [self.videoSessionViewController PeerDestructionInterimMeetingInfo];
            //[self.videoSessionViewController dismissModalViewControllerAnimated:NO];
        }
        self.videoSessionViewController = nil;
        if (CallViewIsOpen&&self.phoneCallViewController) {
            [self dismissPopupViewControllerWithanimationType:MJPopupViewAnimationFade];
            [phoneCallViewController release];
            //self.phoneCallViewController=nil;
            CallViewIsOpen = false;
        }
        isCallUser=false;
    }
}

-(void) OnDestructionInterimMeetingInfo:(std::string)strHostId ulRoomID:(unsigned long)ulRoomID
{
    mstrUserID = strHostId;
    [self performSelectorOnMainThread:@selector(MyDestructionInterimMeetingInfo:) withObject:self waitUntilDone:YES];
}

-(void) MyDestructionInterimMeetingInfo:(id)mid
{
    if(mstrUserID == pLoginServer->GetUserID())
    {
        self.videoSessionViewController=nil;
    }
    else
    {
        if(self.videoSessionViewController!=nil)
        {
            [self.videoSessionViewController PeerDestructionInterimMeetingInfo];
            //[self.videoSessionViewController dismissModalViewControllerAnimated:NO];
        }
        self.videoSessionViewController = nil;
    }
    if (CallViewIsOpen&&self.phoneCallViewController) {
        [self dismissPopupViewControllerWithanimationType:MJPopupViewAnimationFade];
        [phoneCallViewController release];
        CallViewIsOpen = false;
        //self.phoneCallViewController=nil;
    }
    isCallUser=false;
}

-(void) OnQuitInterimMeetingInfo:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID
{
    mstrUserID = strUserID;
    mulRoomID = ulRoomID;
    [self performSelectorOnMainThread:@selector(MyQuitInterimMeetingInfo:) withObject:self waitUntilDone:YES];
}

-(void)MyQuitInterimMeetingInfo:(id)mid
{
    if(mstrUserID == pLoginServer->GetUserID())
    {
        self.videoSessionViewController=nil;
        if (CallViewIsOpen&&self.phoneCallViewController) {
            [self dismissPopupViewControllerWithanimationType:MJPopupViewAnimationFade];
            [phoneCallViewController release];
            CallViewIsOpen = false;
            //self.phoneCallViewController=nil;
        }
        isCallUser=false;
    }
    else
    {
        if(self.videoSessionViewController!=nil)
        {
            [self.videoSessionViewController PeerQuitInterimMeetingInfo:mstrUserID ulRoomID:mulRoomID];
            [self.videoSessionViewController MyUpdateMeetingInfo:mid];
        }
    }
}

- (void)cancelButtonClicked:(PhoneCallViewController *)aSecondDetailViewController
{
    [self dismissPopupViewControllerWithanimationType:MJPopupViewAnimationFade];
    if (self.phoneCallViewController) {
        [phoneCallViewController release];
    }
    isCallUser=false;
    CallViewIsOpen = false;
    
    if(pLoginServer)
        pLoginServer->OnReplyInviteUser(pLoginServer->GetUserID(), mulRoomID,mstrUserID, false);
}

- (void)OKButtonClicked:(PhoneCallViewController *)aSecondDetailViewController
{
    [self dismissPopupViewControllerWithanimationType:MJPopupViewAnimationFade];
    if (self.phoneCallViewController) {
        [phoneCallViewController release];
    }
   
     self.pIntoVessionViewController = [[[IntoVessionViewController alloc] initWithNibName:@"IntoVessionViewController" bundle:nil]autorelease];
   
    [self presentPopupViewController:self.pIntoVessionViewController animationType:MJPopupViewAnimationFade];
 
    if(pLoginServer)
        pLoginServer->JoinTemporaryMeeting(pLoginServer->GetUserID(), pLoginServer->GetUserID(), mulRoomID);
    isCallUser=true;
    CallViewIsOpen = false;
}

-(void)HostEnterRoomBegin
{
    
    
    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:NO];

     self.pIntoVessionViewController = [[[IntoVessionViewController alloc] initWithNibName:@"IntoVessionViewController" bundle:nil]autorelease];
      [self presentPopupViewController:self.pIntoVessionViewController animationType:MJPopupViewAnimationSlideBottomTop];
}

-(void)HostEnterRoomEnd
{
    
    [self dismissPopupViewControllerWithanimationType:MJPopupViewAnimationFade];
//    
    if (self.pIntoVessionViewController) {
            self.pIntoVessionViewController=nil;
    }
}

-(void) CallInviteAllUser_EnterRoomEnd
{
    if(self.callViewController)
        [self.callViewController CallInviteAllUser];
}

@end
