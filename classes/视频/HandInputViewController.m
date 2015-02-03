//
//  HandInputViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "HandInputViewController.h"

@interface HandInputViewController ()

@end

@implementation HandInputViewController
@synthesize account;
@synthesize nickname;
@synthesize groupname;


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



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(IBAction)BtExit:(id)sender
{
     [self setHidesBottomBarWhenPushed:YES];
    [self.navigationController popViewControllerAnimated:YES];
}
-(IBAction)btSave:(id)sender
{
    if([self.account.text isEqualToString:@""])
    {
        [self Alert:@"用户账号不能为空" message:@"请输入用户账号"];
        return;
    }
   
    assert(pLoginServer);
    
    if(pLoginServer->GetUserID() == [self.account.text UTF8String])
    {
        [self Alert:@"不能添加自己为好友" message:@"请重新输入用户账号"];
        return;
    }
    
    IMS_CONTACT_ITEM mUserInfo;
    if(!pLoginServer->GetUserInfo([self.account.text UTF8String],mUserInfo))
    {
        [self Alert:@"用户账号不存在" message:@"请重新输入用户账号"];
        return;
    }
    
    if(!pLoginServer->AddUserFriend([self.groupname UTF8String], [self.account.text UTF8String]))
    {
        [self Alert:@"该用户已经是你的好友" message:@"请重新输入用户账号"];
        return;
    }
    
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self hideTabBar:self.tabBarController];
    
}


- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self showTabBar:self.tabBarController];
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    UIBarButtonItem *leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(BtExit:)];
    self.title=@"添加";
    self.navigationItem.leftBarButtonItem = leftBtn;
    [leftBtn release];
    
    UIBarButtonItem *rightBtn = [[UIBarButtonItem alloc]initWithTitle:@"保存" style:UIBarButtonItemStyleBordered target:self action:@selector(btSave:)];
    self.navigationItem.rightBarButtonItem = rightBtn;
    [rightBtn release]; 
    pLoginServer = LoginServer::OnGetLoginServer();
}

-(void)dealloc
{
    pLoginServer = NULL;
    self.account=nil;
    self.nickname=nil;
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)Alert:(NSString*)result message:(NSString*) message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:result message:message
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];
    [alert release];
}

@end
