//
//  LoginViewController.m
//  ScoPlayer
//
//  Created by user on 12-7-12.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//
#import <QuartzCore/QuartzCore.h>
#import "LoginViewController.h"
#import "AppDelegate.h"
#import "ServerSettingViewController.h"
#import "PhoneCallViewController.h"
#import "AnimationViewController.h"
#import "RegistrationViewController.h"
#import <sys/sysctl.h>
#import <mach/mach.h>

@implementation LoginViewController
@synthesize tabBarController;
@synthesize navigationController;
@synthesize configViewController;
@synthesize iSwitch;
@synthesize userName;
@synthesize passWord;
@synthesize iP;
@synthesize loginInfo;
@synthesize BtRemember;
@synthesize label;
@synthesize serverSettingViewController;
@synthesize pRegistrationViewController;
@synthesize animationViewController;


- (id)init
{
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        self =[super initWithNibName:@"LoginViewController_ipad" bundle:nil];
//    } else {
//        self =[super initWithNibName:@"LoginViewController" bundle:nil];
//    }
    
    self =[super initWithNibName:@"LoginViewController" bundle:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(screenDidConnectNotification:) name: UIScreenDidConnectNotification object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(screenDidDisconnectNotification:) name: UIScreenDidDisconnectNotification object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(screenModeDidChangeNotification:) name: UIScreenModeDidChangeNotification object: nil];
    
    pLoginServer = NULL;
    ierrorid = 0;
    NETEC_Core::Start(0,false,false,true);
    return self;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    //[self moveView:textField leaveView:NO];
    UIView *view = [[[UIView alloc] init]autorelease];
    
    self.label = [[[UILabel alloc] init] autorelease];
    [self.label setFont:[UIFont fontWithName:@"TrebuchetMS-Bold" size:18]];
    self.label.textAlignment = NSTextAlignmentCenter;
    
    [self.label setBackgroundColor:[UIColor clearColor]];
    
    [self.label setText:textField.text];
    
    view.frame = CGRectMake(0, 0, 300, 20);
    
    [view addSubview:self.label];
    
    [self.label sizeToFit];
    textField.inputAccessoryView = view;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    if (self = [self init]) {
    
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle
/*-(IBAction)BtRegister:(id)sender
{
    
}
-(IBAction)BtFindPassWord:(id)sender
{
    
}*/
-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
    isRemember=[accountDefaults boolForKey:@"isremember"];
    if (isRemember) {
        NSString *userN=[accountDefaults objectForKey:@"userName"];
        NSString *pasN=[accountDefaults objectForKey:@"passWord"];
          if (![pasN isEqualToString:@"(null)"]) {
            self.passWord.text=pasN;
        }
        if (![userN isEqualToString:@"(null)"]) {
            self.userName.text=userN;
        }
    }
    if (isRemember) {
       [ self.BtRemember setImage:[UIImage imageNamed:@"checkbuttonyes"] forState:normal];
    }
    else{
        [ self.BtRemember setImage:[UIImage imageNamed:@"checkbuttonno"] forState:normal];
    }
   
}

-(void) OnServerConnectingInfo:(CONNECT_STATUS)cs errorid:(unsigned int)errorid
{
    switch (cs)
	{
        case CS_CONNECTING:{
            [self performSelectorOnMainThread:@selector(ConnectingServer:) withObject:self waitUntilDone:YES];
		}
            break;
        case CS_FAILED:{
            ierrorid = errorid;
            [self performSelectorOnMainThread:@selector(ConnectingDeverFailed:) withObject:self waitUntilDone:YES];
		}
            break;
        case CS_DISCONNECTED:{
            [self performSelectorOnMainThread:@selector(DisconnectedServer:) withObject:self waitUntilDone:YES];
		}
            break;
        case CS_CONNECTED:{
            [self performSelectorOnMainThread:@selector(ConnectServer:) withObject:self waitUntilDone:YES];
		}
            break;
        case CS_BUSY:{
            [self performSelectorOnMainThread:@selector(ConnectServerBusy:) withObject:self waitUntilDone:YES];
		}
            break;
        case CS_RECONNECTED:
            [self performSelectorOnMainThread:@selector(ReconnectedServer:) withObject:self waitUntilDone:YES];
            break;
        case CS_RESTARTED:
            break;
        default:
            printf("%s\n","Unkown");
            break;
	}
}

-(void) OnServerConnectingOutTime;
{
    [self performSelectorOnMainThread:@selector(ServerConnectingOutTime:) withObject:self waitUntilDone:YES];
}

-(void)ServerConnectingOutTime:(id)mid
{
    [self.loginInfo setText:@"连接服务器超时!"];
    [self.animationViewController.textInfo setText:@"连接服务器超时!"];
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
}

-(void)ConnectingServer:(id)mid
{
    [self.loginInfo setText:@"正在连接服务器..."];
    [self.animationViewController.textInfo setText:@"正在连接服务器..."];
}

-(void)ConnectingDeverFailed:(id)mid
{
    [self.loginInfo setText:@"连接服务器失败,ip或者端口错误!"];
    [self.animationViewController.textInfo setText:@"连接服务器失败，ip或者端口错误!"];
    sleep(2);
    [self.animationViewController.view removeFromSuperview];
}

-(void)DisconnectedServer:(id)mid
{
    [self.loginInfo setText:@"断开和服务器的连接!"];
    [self.animationViewController.textInfo setText:@"断开和服务器的连接！"];
}

-(void)ConnectServer:(id)mid
{
    [self.loginInfo setText:@"连接服务器成功！"];
    [self.animationViewController.textInfo setText:@"连接服务器成功！"];
}

-(void)ConnectServerBusy:(id)mid
{
    [self.loginInfo setText:@"连接服务器忙碌！"];
    [self.animationViewController.textInfo setText:@"连接服务器忙碌！"];
}

-(void)ReconnectedServer:(id)mid
{
    [self.loginInfo setText:@"重新连接服务器！"];
    [self.animationViewController.textInfo setText:@"重新连接服务器！"];
}

-(void) OnServerLoginingInfo:(CONNECT_STATUS)cs errorid:(unsigned int)errorid;
{
    switch (cs)
	{
        case CS_LOGINED:
        {
            [self performSelectorOnMainThread:@selector(ServerLogin:) withObject:self waitUntilDone:YES];
		}
            break;
        case CS_LOGINFAILED:
        {
            ierrorid = errorid;
            [self performSelectorOnMainThread:@selector(ServerLoginFailed:) withObject:self waitUntilDone:YES];
		}
            break;
        default:
            break;
	}
}

-(void)ServerLoginGetUserGrop:(id)mid
{
    [self.animationViewController.textInfo setText:@"正在获取用户组..."];
}

-(void)ServerLoginGetFriend:(id)mid
{
    [self.animationViewController.textInfo setText:@"正在获取用户好友..."];
}

-(void)ServerLoginGetUserInfo:(id)mid
{
    [self.animationViewController.textInfo setText:@"正在获取用户信息..."];
}


-(void)ServerLoginEnd:(id)mid
{
    [self.animationViewController.textInfo setText:@"获取信息完成！"];
    self.tabBarController.selectedIndex=0;
    [self.animationViewController.view removeFromSuperview];
   [self dismissViewControllerAnimated:NO completion:nil];
}

-(void) OnServerBeginGetUserInfo:(CONNECT_STATUS)cs
{
    switch (cs)
	{
        case CS_GETUSERGROP:
        {
            [self performSelectorOnMainThread:@selector(ServerLoginGetUserGrop:) withObject:self waitUntilDone:YES];
		}
            break;
        case CS_GETFRIEND:
        {
            [self performSelectorOnMainThread:@selector(ServerLoginGetFriend:) withObject:self waitUntilDone:YES];
		}
            break;
        case CS_GETUSERINFO:
        {
            [self performSelectorOnMainThread:@selector(ServerLoginGetUserInfo:) withObject:self waitUntilDone:YES];
		}
            break;
        default:
            break;
	}
}

-(void) OnServerEndGetUserInfo
{
    [self performSelectorOnMainThread:@selector(ServerLoginEnd:) withObject:self waitUntilDone:NO];
}

-(void)ServerLogin:(id)mid
{
    [self.loginInfo setText:@"登录服务器成功！"];
    [self.animationViewController.textInfo setText:@"登录服务器成功！"];
    
    NSUserDefaults *MaccountDefaults = [NSUserDefaults standardUserDefaults];
    NSString* NsMediaId = [NSString stringWithFormat:@"%ld",pLoginServer->GetLocalVideoId()];
    [MaccountDefaults setObject:NsMediaId forKey:@"MediaId"];
}

-(void)ServerLoginFailed:(id)mid
{
    if(mNSTimer == nil)
        mNSTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    if(ierrorid == 20001)
    {
        [self.loginInfo setText:@"登录失败,用户名错误！"];
        [self.animationViewController.textInfo setText:@"登录失败,用户名错误!"];
    }
    if(ierrorid == 20002)
    {
        [self.loginInfo setText:@"登录失败,密码错误！"];
        [self.animationViewController.textInfo setText:@"登录失败,密码错误!"];
    }
    if(ierrorid == 20003)
    {
        [self.loginInfo setText:@"该用户已经登录！"];
        [self.animationViewController.textInfo setText:@"该用户已经登录!"];
    }
}

-(void)runTimer:(id)timer
{
    sleep(2);
    if(pLoginServer)
        pLoginServer->DoServerDisconnect();
    if(pLoginServer)
    {
        LoginServer::OnDestroy();
        pLoginServer = NULL;
    }
    [mMainNSTimer invalidate];
    mMainNSTimer = nil;
    [mNSTimer invalidate];
    mNSTimer = nil;
    [self.animationViewController.view removeFromSuperview];
}

-(IBAction)textfiledchangeUserName:(id)sender
{
    [self.label setText:self.userName.text];
    [self.label sizeToFit];
}

-(IBAction)textfiledchangePassWord:(id)sender
{
    [self.label setText:self.passWord.text];
    [self.label sizeToFit];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
   
    self.iSwitch.on = YES;
    [self.iSwitch addTarget:self action:@selector(switchAction:) forControlEvents:UIControlEventValueChanged];
    appDelegate=[[UIApplication sharedApplication] delegate];
    
    self.passWord.secureTextEntry=YES;
    self.passWord.returnKeyType =UIReturnKeyDone;
    self.userName.returnKeyType =UIReturnKeyDone;
   
    self.userName.delegate =self;
    self.passWord.delegate =self;
    
    self.serverSettingViewController=[[[ServerSettingViewController alloc]initWithNibName:@"ServerSettingViewController" bundle:nil]autorelease];
    self.pRegistrationViewController=[[[RegistrationViewController alloc]initWithNibName:@"RegistrationViewController" bundle:nil]autorelease];
    self.animationViewController=[[[AnimationViewController alloc]initWithNibName:@"AnimationViewController" bundle:nil] autorelease];
 }

-(void)switchAction:(id)sender
{
    
}
-(void)AllResignFirstResponder
{
    [self.userName resignFirstResponder]; 
    [self.passWord resignFirstResponder];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self AllResignFirstResponder];
}
 
-(void)dealloc
{ 
    self.tabBarController=nil;
    self.navigationController=nil;
    self.configViewController=nil;
    self.iSwitch=nil;
    self.loginInfo=nil;
    self.BtRemember=nil;
    self.label=nil;
      self.iP=nil;
    self.animationViewController=nil;
    self.serverSettingViewController=nil;
    self.pRegistrationViewController=nil;
    if(pLoginServer)
        pLoginServer->m_IMLoginInfo=nil;
  
    [super dealloc];
}

-(void)Alert:(NSString*) result message:(NSString*) message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:result message:message
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];	
    [alert release];
}

-(IBAction)btRemember:(id)sender
{
    isRemember=!isRemember;
    if (isRemember) {
        [ self.BtRemember setImage:[UIImage imageNamed:@"checkbuttonyes"] forState:normal];
    }
    else
    {
        [ self.BtRemember setImage:[UIImage imageNamed:@"checkbuttonno"] forState:normal];
    }
}

-(IBAction)btSetting:(id)sender
{
    if ( !self.serverSettingViewController) {
    self.serverSettingViewController=[[[ServerSettingViewController alloc]initWithNibName:@"ServerSettingViewController" bundle:nil]autorelease];
    }
    [self presentViewController:self.serverSettingViewController  animated:YES completion:nil];
}

-(IBAction)btRegistration:(id)sender
{
    if(!self.pRegistrationViewController)
    {
        self.pRegistrationViewController=[[[RegistrationViewController alloc]initWithNibName:@"RegistrationViewController" bundle:nil]autorelease];
    }
    [self presentViewController:self.pRegistrationViewController animated:YES completion:nil];
}

-(IBAction)btLogin:(id)sender
{
    NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
    NSString *IP=[accountDefaults objectForKey:@"IP"];
    NSString *PORT=[accountDefaults objectForKey:@"PORT"];
    mMainNSTimer = nil;
    [self.loginInfo setText:@""];
    [self.animationViewController.textInfo setText:@""];
    
    if (![IP isEqualToString:@"(null)"] || ![PORT isEqualToString:@"(null)"]) {
        
        if ([self checkip:IP]) {
            self.iP=IP;
        }
        else
        {
            self.iP=nil;
           [self Alert:@"确定" message:@"请配置正确的服务器ip"];
              return;
        }
    }
    else
    {
        self.iP=nil;
        [self Alert:@"确定" message:@"请配置服务器ip"];
        return;
    }
    if (self.iP==nil) {
        // [self Alert:@"确定" message:@"请先配置服务器ip"];
      return;
    }
    
#if 0
    self.tabBarController.selectedIndex=0; 
    [self  dismissViewControllerAnimated:NO completion:nil];
    
    return;
#endif
    
    if ([self.userName.text isEqualToString:@""]||[self.passWord.text isEqualToString:@""]) {
        [self Alert:@"登陆失败" message:@"请完整输入用户名和密码"];
        return;
    }
    
    NSUserDefaults *MaccountDefaults = [NSUserDefaults standardUserDefaults];
    NSString *NsMediaId = [MaccountDefaults objectForKey:@"MediaId"];
    unsigned long ulMediaId = 0;
    if(NsMediaId!=nil && ![NsMediaId isEqualToString:@""])
    {
        ulMediaId = [NsMediaId intValue];
    }
    
    pLoginServer = LoginServer::OnGetLoginServer(ulMediaId);
    pLoginServer->m_IMLoginInfo=self;
    if(pLoginServer == NULL)
        return;
    
    std::string strUserId = [self.userName.text UTF8String];
    std::string strPassWord = [self.passWord.text UTF8String];
    std::string strStatus = "online";
    
    pLoginServer->DoServerConnect([self.iP UTF8String], [PORT integerValue], strUserId, strPassWord, strStatus);
    if (isRemember) {
        NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
        NSString *userN=self.userName.text;
        [accountDefaults setObject:userN    forKey:@"userName"];
        NSString *pasN=self.passWord.text;
        [accountDefaults setObject:pasN    forKey:@"passWord"];
        [accountDefaults setBool:isRemember forKey:@"isremember"];
    }
    else
    {
        NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
       [accountDefaults setBool:isRemember forKey:@"isremember"]; 
    }
    appDelegate.userId=self.userName.text;
    
    if(mMainNSTimer == nil)
        mMainNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(MainRunTimer:) userInfo:nil repeats:YES];
    [self.view addSubview:animationViewController.view];
//    [self presentViewController:animationViewController animated:YES completion:nil];
}

-(void)MainRunTimer:(id)time
{
    if(pLoginServer)
        pLoginServer->Run();
}

-(IBAction)btConfig:(id)sender
{
    // Do any additional setup after loading the view from its nib.
    CATransition  *animation = [CATransition animation];
    [animation setDuration:0.5f];
    [animation setTimingFunction:[CAMediaTimingFunction
                                   functionWithName:kCAMediaTimingFunctionEaseIn]];
    [animation setType:kCATransitionPush];
    [animation setSubtype: kCATransitionFromRight];
    [self.view.layer addAnimation:animation forKey:@"Push"];
     //[self.view  addSubview:self.configViewController.view];
    //[self.configViewController.SaveButton setHidden:NO];
}
- (BOOL) checkip:(NSString*)ip
{
    NSString *list = ip;
    NSArray *listItems = [list componentsSeparatedByString:@"."];
    unsigned count = [listItems count];
    if (count != 4) {
        
        goto iperror;
  	}
    for (unsigned i = 0; i < count ; i++) {
        NSString* subip = [listItems objectAtIndex:i];
        //	 NSLog(@"%@",subip);
        unsigned unsubip = [subip intValue];
        
        if (unsubip == 0) {
            NSString* zero = @"0";
            if ([subip isEqual:zero])
            {
                continue;
            }
            else
            {
                goto iperror;
            }
        }
        if (unsubip>255)
        {
            goto iperror;
        }
        else
        {
            NSString * myString  = [NSString stringWithFormat:@"%d",unsubip];
            if(![myString isEqualToString: subip])
                goto iperror;
        }
    }
    return YES;
iperror:
    {
        return NO;
    }
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(BOOL)shouldAutorotate
{
    return NO;
}

-(NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskPortrait;
}

- (double)availableMemory
{
    vm_statistics_data_t vmStats;
    mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
    kern_return_t kernReturn = host_statistics(mach_host_self(),
                                               HOST_VM_INFO,
                                               (host_info_t)&vmStats,
                                               &infoCount);
    
    if (kernReturn != KERN_SUCCESS) {
        return NSNotFound;
    }
    
    return ((vm_page_size *vmStats.free_count) / 1024.0) / 1024.0;
}

@end
