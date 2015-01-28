//
//  SessionChatViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-30.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "SessionChatViewController.h"
#import "VideoSessionViewController.h"
#import "SessionShowViewController.h"
#include "ImsContactItem.h"
#import "ImageExtras.h"
#import "ChatCustomCell.h"
#import "ChartUsrCell.h"
#import "Custom.h"
@interface SessionChatViewController ()

@end

@implementation SessionChatViewController
@synthesize ChartTableView;
@synthesize chartToolBar;
@synthesize UserTableView;
@synthesize charttextField;
@synthesize chatArray;
@synthesize textlabel;
@synthesize viewKeyboard;
@synthesize ContactArray;
@synthesize videoSessionViewController;
@synthesize tempWindow;
@synthesize sessionShowViewController;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    //self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        self =[super initWithNibName:@"SessionChatViewController_ipad" bundle:nil];
//    } else {
//        self =[super initWithNibName:@"SessionChatViewController" bundle:nil];
//    }
    self =[super initWithNibName:@"SessionChatViewController" bundle:nil];
    if (self) {
        // Custom initialization
        ISselect=NO;
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(KeyboardWillShowNotification:) name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(KeyboardDidShowNotification:) name:UIKeyboardDidShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(KeyboardWillHideNotification:) name:UIKeyboardWillHideNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(KeyboardDidHideNotification:) name:UIKeyboardDidHideNotification object:nil];
        self.chatArray=[[[NSMutableArray alloc]init]autorelease];
         self.ContactArray=[[[NSMutableArray alloc]init]autorelease];
    }
    return self;
}

- (void)KeyboardWillShowNotification:(NSNotification*)aNotification {
    
   /*  self.tempWindow = [[[UIApplication sharedApplication] windows] objectAtIndex:1];//知识点
    superUIView=[self.tempWindow superview];
    
   [ self.tempWindow removeFromSuperview];
     [self.viewKeyboard setHidden:NO];
    [ self.tempWindow setFrame:CGRectMake(0, 0, 240, 220)];
    [ self.tempWindow setBounds:CGRectMake(0, 0, 240, 220)];
    [self.viewKeyboard addSubview: self.tempWindow];
   
    [self.view addSubview: self.viewKeyboard];*/
}

- (void)KeyboardDidShowNotification:(NSNotification*)aNotification {
  
#if 0
    if (self.videoSessionViewController!=nil) {
        [self.videoSessionViewController loadScrollViewWithPage:2];
        
        [self.videoSessionViewController ScrollViewWithPage:2];
    }
#endif
}

- (void)KeyboardWillHideNotification:(NSNotification*)aNotification {
    NSLog(@"@@@@@@@@@@@@@@@ KeyboardWillHideNotification");
 
     //[self.viewKeyboard setHidden:YES];
   
}

- (void)KeyboardDidHideNotification:(NSNotification*)aNotification {
    NSLog(@"@@@@@@@@@@@@@@@ KeyboardDidHideNotification");
}

//键盘收起
- (void) handleBackgroundTap:(UITapGestureRecognizer*)sender
{
    [charttextField resignFirstResponder];
}

-(IBAction)btback:(id)sender
{
    [charttextField resignFirstResponder];
    
    if (self.videoSessionViewController) {
        [self.videoSessionViewController ScrollViewWithPage:1];
    }
}

-(void)GetMassage:(NSString *)message
{
    UIView *chatView = [self bubbleView:message
                                   from:NO];
	[self.chatArray addObject:[NSDictionary dictionaryWithObjectsAndKeys:@"info", @"text", @"other", @"speaker", chatView, @"view", nil]];
	
	[self.ChartTableView reloadData];
	[self.ChartTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:[self.chatArray count]-1 inSection:0]atScrollPosition:UITableViewScrollPositionBottom animated:YES];
    
    if(videoSessionViewController != nil && videoSessionViewController.m_ViewCount == 1)
    {
        if(sessionShowViewController!=nil)
            [sessionShowViewController SetChatShow:true];
    }
}

-(void)sendMassage:(NSString *)message
{
   // [self.SendTextDataDelegate SendTextMessage:[message UTF8String]];
	UIView *chatView = [self bubbleView:[NSString stringWithFormat:@"%@:%@", @"我说", message]
								   from:YES];
	[self.chatArray addObject:[NSDictionary dictionaryWithObjectsAndKeys:message, @"text", @"self", @"speaker", chatView, @"view", nil]];
	
	[self.ChartTableView reloadData];
	[self.ChartTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:[self.chatArray count]-1 inSection:0]
                           atScrollPosition:UITableViewScrollPositionBottom
                                   animated:YES];
}

-(void)btsendPress:(id)inObject
{
    if(charttextField!=nil)
    {
        NSString* strText =  charttextField.text;
        if([strText isEqualToString:@""])
            return;
        
        [self sendMassage:strText];
        self.charttextField.text = @"";
        [charttextField resignFirstResponder];
        
        std::string strInfo = [strText UTF8String];
        for(ImsContactItem *contactItem in self.ContactArray) {
            if (contactItem.isseletct&&(contactItem.username !="所有人") ) {
                if(pLoginServer)
                    pLoginServer->OnUserSnedMsg(pLoginServer->GetUserID(), pLoginServer->GetRoomId(), contactItem.userid, strInfo);
            }
        }
    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    if (tableView.tag==0) {
        return 30;
    }
    else
        return 0;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    if (tableView.tag==0) {
        CGRect frameRect = CGRectMake(100, 0, 100, 40);
        UILabel *label = [[[UILabel alloc] initWithFrame:frameRect] autorelease];
        label.textColor=[UIColor whiteColor];
        //label.backgroundColor=[UIColor darkGrayColor];
        UIColor *color = [UIColor colorWithPatternImage:[UIImage imageNamed:@"canhui.png"]];
        [label setBackgroundColor:color];
        label.text=@"   参会成员";
        return label;
    }
    else
        return nil;
    
}

-(void)btFontPress:(id)inObject
{
    
}

-(void)btHistoryPress:(id)inObject
{
    
}

-(void)InitCtrs
{
    CGSize ImSize;
    ImSize.width=35;
    ImSize.height=48;
    
     
    self.navigationItem.rightBarButtonItem = CREATE_BARITEM_WITH_CUSTOMVIEW([Custom createItemWithTitle:nil
                                                                                                  image:@"返回"
                                                                                                 target:self
                                                                                                 action:@selector(btback:)]);

    
    
   // self.navigationItem.leftBarButtonItem = leftBtn;
    
  //  UIBarButtonItem *leftBtn = [[UIBarButtonItem alloc]initWithImage:[UIImage imageNamed:@"返回1"] style:UIBarButtonItemStyleBordered target:self action:@selector(btback:)];
//    
//    
     CGRect frame = self.view.frame ;
    CGRect bound= self.view.bounds;
//    
//    [self.view  setFrame:CGRectMake(0, 0, _screenHeight,_screenWidth)];
//    self.view.bounds = CGRectMake(0, 0, _screenHeight,_screenWidth);
//    
    self.UserTableView.tag=0;
    [self.UserTableView setFrame:CGRectMake(0,40,  140, 280)];
    
    UIColor *color = [UIColor colorWithPatternImage:[UIImage imageNamed:@"人员列表背景"]];
    [self.UserTableView setBackgroundColor:color];
    
    self.ChartTableView=[[[UITableView alloc]initWithFrame:CGRectMake(150,5,  280, 240) style:UITableViewStylePlain]autorelease];
    self.ChartTableView.separatorStyle=UITableViewCellSeparatorStyleNone;
    self.ChartTableView.delegate=self;
    self.ChartTableView.dataSource=self;
    self.ChartTableView.tag=1;
    [self.ChartTableView setBackgroundColor:[UIColor clearColor]];
    //self.chartToolBar=[[[UIToolbar alloc]init]autorelease];
   
    
   /* self.charttextField = [[[UITextField alloc] initWithFrame:CGRectMake(0,0,  200, 35)] autorelease];
    self.charttextField.delegate=self;
    self.charttextField.backgroundColor = [UIColor whiteColor];

    charttextField.keyboardAppearance=UIKeyboardAppearanceAlert;
    */
    
    [self.chartToolBar  setFrame:CGRectMake(150,260,  280, 40)];
    self.charttextField.returnKeyType = UIReturnKeyDone;
    
    [self.charttextField addTarget:self action:@selector(textFieldDidEditing:) forControlEvents:UIControlEventEditingChanged];
    CGRect btsendframe=CGRectMake(0, 0,62,32);
    
    
    
    UIButton *btsend= [UIButton buttonWithType:UIButtonTypeCustom];
    [btsend setFrame:btsendframe];
    
      [btsend setImage:[UIImage imageNamed:@"发送"]   forState:UIControlStateNormal];
    [btsend addTarget:self action:@selector(btsendPress:) forControlEvents:UIControlEventTouchUpInside];
    
    UIBarButtonItem* btsendItem= [[[UIBarButtonItem alloc] initWithCustomView:btsend]autorelease];
    
    
    /*UIButton *btFont= [UIButton buttonWithType:UIButtonTypeCustom];
    [btFont setFrame:btsendframe];
    
    [btFont setImage:[UIImage imageNamed:@"A.png"]   forState:UIControlStateNormal];
    [btFont addTarget:self action:@selector(btFontPress:) forControlEvents:UIControlEventTouchUpInside];
    
    UIBarButtonItem* btFontItem= [[[UIBarButtonItem alloc] initWithCustomView:btFont]autorelease];
   
    UIButton *btHistory= [UIButton buttonWithType:UIButtonTypeCustom];
    [btHistory setFrame:btsendframe];
    
    [btHistory setImage:[UIImage imageNamed:@"通话记录.png"]   forState:UIControlStateNormal];
    [btHistory addTarget:self action:@selector(btHistoryPress:) forControlEvents:UIControlEventTouchUpInside];
    
    UIBarButtonItem* btHistoryItem= [[[UIBarButtonItem alloc] initWithCustomView:btHistory]autorelease];
     
     */
    UIBarButtonItem* charttextItem= [[[UIBarButtonItem alloc] initWithCustomView:self.charttextField]autorelease];
    
    
    UIBarButtonItem *flexibleSpace = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil]autorelease];
    
    CGSize ImSizetoolbar;
    ImSizetoolbar.width=320;
    ImSizetoolbar.height=44;
    
   /* UIImage *toolBarIMG = [[UIImage imageNamed: @"canhui.png"]imageByScalingToSize:ImSizetoolbar];
    
    [[UIDevice currentDevice] systemVersion];
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] > 4.9) {
        
        //iOS 5
        
        if ([chartToolBar respondsToSelector:@selector(setBackgroundImage:forToolbarPosition:barMetrics:)]) {
            [chartToolBar setBackgroundImage:toolBarIMG forToolbarPosition:0 barMetrics:0];
        }
        
    } else {
        
        //iOS 4
        [chartToolBar insertSubview:[[[UIImageView alloc] initWithImage:toolBarIMG] autorelease] atIndex:0];
    }*/
       
    //[ self.chartToolBar setBackgroundColor:[UIColor blackColor]];
   // [self.chartToolBar setFrame:CGRectMake(0,240,  480, 40)];
    NSArray *items = [NSArray arrayWithObjects:charttextItem,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,flexibleSpace,btsendItem,nil];
    [self.chartToolBar setItems:items animated:NO];
    [self.view addSubview:self.ChartTableView];
    [self.view addSubview:self.chartToolBar];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
   
    [self.viewKeyboard setFrame:CGRectMake(150,25,  280, 220) ];
    [self.viewKeyboard setHidden:YES];
#if  0
    UIWindow* tempWindow = [[[UIApplication sharedApplication] windows] objectAtIndex:1];//知识点
    
    [tempWindow removeFromSuperview];
   
    [tempWindow setFrame:CGRectMake(0, 0, 240, 220)];
    [tempWindow setBounds:CGRectMake(0, 0, 240, 220)];
    [self.viewKeyboard addSubview:tempWindow];
    [self.view addSubview: self.viewKeyboard];

 #endif   
    
    
    pLoginServer = LoginServer::OnGetLoginServer();

}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self UpdateUser];
    [charttextField resignFirstResponder];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [charttextField resignFirstResponder];
      //[self.tempWindow removeFromSuperview];
   // =[self.tempWindow superview];
   // [superUIView addSubview:self.tempWindow];
    //[self.viewKeyboard removeFromSuperview];
   /* for(UIView *subview in [self.viewKeyboard subviews])
    {
         
            [subview removeFromSuperview];
        
    }
   */
    [super viewWillDisappear:animated];
}

- (UIView *)bubbleView:(NSString *)text from:(BOOL)fromSelf {
	// build single chat bubble cell with given text
	UIView *returnView = [[UIView alloc] initWithFrame:CGRectZero];
	returnView.backgroundColor = [UIColor clearColor];
	
	UIImage *bubble = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:fromSelf?@"bubbleSelf":@"bubble" ofType:@"png"]];
	UIImageView *bubbleImageView = [[UIImageView alloc] initWithImage:[bubble stretchableImageWithLeftCapWidth:20 topCapHeight:14]];
	bubbleImageView .backgroundColor=[UIColor clearColor];
	UIFont *font = [UIFont systemFontOfSize:13];
//	CGSize size = [text sizeWithFont:font constrainedToSize:CGSizeMake(150.0f, 1000.0f) lineBreakMode:UILineBreakModeWordWrap];
    NSDictionary *attribute = @{NSFontAttributeName: font};
    CGSize size = [text boundingRectWithSize:CGSizeMake(150.0f, 1000.0f)  options:\
                        NSStringDrawingTruncatesLastVisibleLine |
                        NSStringDrawingUsesLineFragmentOrigin |
                        NSStringDrawingUsesFontLeading
                                                    attributes:attribute context:nil].size;
    
    
	
	UILabel *bubbleText = [[UILabel alloc] initWithFrame:CGRectMake(21.0f, 20.0f, size.width+12, size.height+10)];
	bubbleText.backgroundColor = [UIColor clearColor];
	bubbleText.font = font;
	bubbleText.numberOfLines = 0;
	bubbleText.lineBreakMode = NSLineBreakByWordWrapping;
	bubbleText.text = text;
	
	bubbleImageView.frame = CGRectMake(0.0f, 14.0f, bubbleText.frame.size.width+48.0f, bubbleText.frame.size.height+20.0f);
	if(fromSelf)
		returnView.frame = CGRectMake(240.0f-bubbleText.frame.size.width, 0.0f, bubbleText.frame.size.width+30.0f, bubbleText.frame.size.height+30.0f);
	else
		returnView.frame = CGRectMake(0.0f, 0.0f, bubbleText.frame.size.width+30.0f, bubbleText.frame.size.height+30.0f);
	
	[returnView addSubview:bubbleImageView];
	[bubbleImageView release];
	[returnView addSubview:bubbleText];
	[bubbleText release];
	
	return [returnView autorelease];
}
/////////////////聊天的table内容

#pragma mark -
#pragma mark Table View DataSource Methods
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
      
    if ( tableView.tag==1) {
        return [self.chatArray count];
    }
    else if(tableView.tag==0)
    {
        return [self.ContactArray count];
    }
    return 0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	
    
    if ( tableView.tag==1) {
        
    if ([[self.chatArray objectAtIndex:[indexPath row]] isKindOfClass:[NSDate class]]) {
		return 30;
	}else {
		UIView *chatView = [[self.chatArray objectAtIndex:[indexPath row]] objectForKey:@"view"];
		return chatView.frame.size.height+10;
	   }
    }
    else if(tableView.tag==0)
    {
        return  32;
    }
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (tableView.tag==1) {
   
    static NSString *CommentCellIdentifier = @"CommentCell";
	ChatCustomCell *cell = (ChatCustomCell*)[tableView dequeueReusableCellWithIdentifier:CommentCellIdentifier];
	if (cell == nil) {
		cell = [[[NSBundle mainBundle] loadNibNamed:@"ChatCustomCell" owner:self options:nil] lastObject];
	}
	
	if ([[self.chatArray objectAtIndex:[indexPath row]] isKindOfClass:[NSDate class]]) {
		// Set up the cell...
		NSDateFormatter  *formatter = [[NSDateFormatter alloc] init];
		[formatter setDateFormat:@"yy-MM-dd HH:mm"];
		NSMutableString *timeString = [NSMutableString stringWithFormat:@"%@",[formatter stringFromDate:[self.chatArray objectAtIndex:[indexPath row]]]];
		[formatter release];
        
		[cell.dateLabel setText:timeString];
		cell.deleteButton.hidden = YES;
        
	}else {
		// Set up the cell...
		NSDictionary *chatInfo = [self.chatArray objectAtIndex:[indexPath row]];
		UIView *chatView = [chatInfo objectForKey:@"view"];
		
		cell.deleteButton.tag = [indexPath row];
		cell.deleteButton.frame = CGRectMake(20.0f, chatView.center.y - 10.0f, 29.0f, 29.0f);
		[cell.deleteButton addTarget:self action:@selector(deleteItemAction:) forControlEvents:UIControlEventTouchUpInside];
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
		[cell.contentView addSubview:chatView];
		
		/* if (self.isEdit) {
         if ([chatInfo objectForKey:@"speaker"] == @"other")
         chatView.frame = CGRectMake(50.0f, 0.0f,  chatView.frame.size.width, chatView.frame.size.height);
         cell.deleteButton.hidden = NO;
         }else {
         if ([chatInfo objectForKey:@"speaker"] == @"other")
         chatView.frame = CGRectMake(0.0f, 0.0f,  chatView.frame.size.width, chatView.frame.size.height);
         cell.deleteButton.hidden = YES;
         //} */
        }
        return cell;
    }
    else if(tableView.tag==0)
    {
        int index=[indexPath row];
        
        static NSString * DisclosureMonitorNodeCellIdentifier =
                @"chatUserCellIdentifer";
        
        ChartUsrCell *cell=  [tableView dequeueReusableCellWithIdentifier:
                        DisclosureMonitorNodeCellIdentifier ];
        if (cell == nil)
        {
            NSArray * nib = [[NSBundle mainBundle] loadNibNamed:@"ChartUsrCell" owner:self options:nil];
            cell = [nib objectAtIndex:0];
        }

        cell.sessionChatViewController=self;
        
        ImsContactItem *contact = [self.ContactArray objectAtIndex:index];
        cell.imsContactItem  = contact;
        
        if (cell.imsContactItem.isseletct) {
            [ cell.isSelect setImage:[UIImage imageNamed:@"checkbuttonyesa"] forState:normal];
        }
        else
        {
            [ cell.isSelect setImage:[UIImage imageNamed:@"checkbuttonnoa"] forState:normal];
        }
        
        NSString *strLoginInfo=[[[NSString alloc]initWithCString:contact.username.c_str() encoding: NSUTF8StringEncoding] autorelease];
        
        [cell.Name setText:strLoginInfo];
        return cell;
    }
    return  nil;
}

#pragma mark -
#pragma mark Table View Delegate Methods
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    [charttextField resignFirstResponder];
    
}

#pragma mark -
#pragma mark TextField Delegate Methods

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
	return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    UIView *view = [[[UIView alloc] init]autorelease];
    [view setBackgroundColor:[UIColor whiteColor]];
    textlabel = [[[UILabel alloc] init] autorelease];
    [textlabel setFont:[UIFont fontWithName:@"TrebuchetMS-Bold" size:18]];
    textlabel.textAlignment = NSTextAlignmentCenter;
    
    [textlabel setBackgroundColor:[UIColor clearColor]];
    
    [textlabel setText:textField.text];
    
    view.frame = CGRectMake(0, 0, 300, 20);
    
    [view addSubview:textlabel];
    
    [textlabel sizeToFit];
    textField.inputAccessoryView = view;
}

-(IBAction)textFieldDidEditing:(id)sender
{
    [textlabel setText:charttextField.text];
    [textlabel sizeToFit];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [self.charttextField resignFirstResponder];
    return YES;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self.charttextField resignFirstResponder];
}

-(void)dealloc
{
    self.ChartTableView=nil;
    self.chartToolBar=nil;
    self.charttextField=nil;
    self.chatArray=nil;
    self.textlabel=nil;
    self.videoSessionViewController=nil;
    self.UserTableView=nil;
    self.viewKeyboard=nil;
    self.ContactArray=nil;
    [super dealloc];
}

-(void) SetSelect
{
    //ISselect=!ISselect;
    for(ImsContactItem *contactItem in self.ContactArray)
    {
        if(contactItem.username == "所有人")
        {
            ISselect = !contactItem.isseletct;
            break;
        }
    }
        
    for(ImsContactItem *contactItem in self.ContactArray) {
        contactItem.isseletct = ISselect;
    }
}

-(void) SetAll:(ImsContactItem *)mSelect
{
    if(!mSelect.isseletct)
    {
        for(ImsContactItem *contactItem in self.ContactArray) {
        if(contactItem.username == "所有人"){
            contactItem.isseletct = false;
            break;
        }
        }
    }
    else
    {
        for(ImsContactItem *contactItem in self.ContactArray) {
            if(mSelect.username != contactItem.username && contactItem.username != "所有人" && contactItem.isseletct == false){
                return;
            }
        }
        
        for(ImsContactItem *contactItem in self.ContactArray) {
            if(contactItem.username == "所有人"){
                contactItem.isseletct = true;
                break;
            }
        }
    }
}

-(void) UpdateUser
{
    if(pLoginServer == NULL)
        return;
    [self.ContactArray removeAllObjects];
     ImsContactItem *allcontactItem=[[[ImsContactItem alloc]init]autorelease];
    allcontactItem.username="所有人";
    [self.ContactArray addObject:allcontactItem];
    
    std::vector<ROOMUSERINFO> RoomUserList;
    pLoginServer->GetRoomUserList(RoomUserList);
    
    std::vector<ROOMUSERINFO>::iterator iter = RoomUserList.begin();
    while(iter!=RoomUserList.end())
    {
        if(iter->strUserID!=pLoginServer->GetUserID())
        {
            ImsContactItem *contactItem=[[[ImsContactItem alloc]init]autorelease];
            contactItem.userid=iter->strUserID;
            contactItem.username=iter->strUserID;
            contactItem.isseletct=NO;
            [self.ContactArray addObject:contactItem];
        }
        ++iter;
    }
    
    [self.UserTableView reloadData];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) MyUpdateMeetingInfo:(id)mid
{
    [self UpdateUser];
}

 
@end
