//
//  ServerSettingViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-3-13.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "RegistrationViewController.h"

@interface RegistrationViewController ()

@end

@implementation RegistrationViewController
@synthesize iP;
@synthesize label;
@synthesize port;

@synthesize UserID;
@synthesize Password;
@synthesize Nickname;
@synthesize Phone;
@synthesize Remark;

@synthesize DeleteUserId;
@synthesize DeletePassword;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        pUserRegistration = new UserRegistration;
        
    }
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

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    return [self validateNumber:string];
}

- (BOOL)validateNumber:(NSString*)number {
    BOOL res = YES;
    NSCharacterSet* tmpSet = [NSCharacterSet characterSetWithCharactersInString:@"0123456789"];
    int i = 0;
    while (i < number.length) {
        NSString * string = [number substringWithRange:NSMakeRange(i, 1)];
        NSRange range = [string rangeOfCharacterFromSet:tmpSet];
        if (range.length == 0) {
            res = NO;
            break;
        }
        i++;
    }
    return res;
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
    NSString *IP=[accountDefaults objectForKey:@"IP"];
    NSString *PORT=[accountDefaults objectForKey:@"PORT"];
    
    if(!IP||[IP isEqualToString:@""])
    {
        [self Alert:@"确定" message:@"请在设置处输入正确的ip！"];
        return;
    }
    if(!PORT||[PORT isEqualToString:@""])
    {
        [self Alert:@"确定" message:@"请在设置处输入正确的端口！"];
        return;
    }
    
    if(pUserRegistration!=NULL)
    {
        pUserRegistration->m_RegistrationInfo = self;
        pUserRegistration->StaticConnectSever([IP UTF8String],atoi([PORT UTF8String]));
        m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
    }
}

-(void)viewWillDisappear:(BOOL)animated
{
    if(pUserRegistration!=NULL)
    {
        pUserRegistration->StopConnectSever();
        pUserRegistration->m_RegistrationInfo = nil;
    }
    [super viewWillDisappear:animated];
}

-(IBAction)textfiledchangeIP:(id)sender
{
    [self.label setText:self.iP.text];
    [self.label sizeToFit];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.iP.returnKeyType =UIReturnKeyDone;
    self.iP.delegate =self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self AllResignFirstResponder];
    [self.iP resignFirstResponder];
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

-(void)Alert:(NSString*) result message:(NSString*) message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:result message:message
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];
    [alert release];
}
-(IBAction)btBack:(id)sender
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(IBAction)btSave:(id)sender
{
    if (![self checkip:self.iP.text]) {
    [self Alert:@"确定" message:@"请输入正确的ip"];
     return;
    }
    else
    {
        NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
       
        NSString *IP=self.iP.text;
        NSString *PORT = self.port.text;
        [accountDefaults setObject:IP forKey:@"IP"];
        [accountDefaults setObject:PORT forKey:@"PORT"];
      //  [self Alert:@"确定" message:@"保存成功"];
    }
    
    [self dismissViewControllerAnimated:YES completion:nil];
}
-(void)dealloc
{
    if(pUserRegistration!=NULL)
        delete pUserRegistration;
    pUserRegistration = NULL;
    self.iP=nil;
    [super dealloc];
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(IBAction)AddUser:(id)sender
{
    if([self.UserID.text isEqualToString:@""])
    {
        [self Alert:@"确定" message:@"请输入用户名!"];
        return;
    }
    if([self.Password.text isEqualToString:@""])
    {
        [self Alert:@"确定" message:@"请输入用户密码!"];
        return;
    }
    if([self.Nickname.text isEqualToString:@""])
    {
        [self Alert:@"确定" message:@"请输入用户昵称!"];
        return;
    }
    if([self.Phone.text isEqualToString:@""])
    {
        [self Alert:@"确定" message:@"请输入用户电话号!"];
        return;
    }
    
    if(pUserRegistration!=NULL)
        pUserRegistration->AddUser([self.UserID.text UTF8String], [self.Password.text UTF8String], [self.Nickname.text UTF8String], [self.Phone.text UTF8String], [self.Remark.text UTF8String]);
}

-(IBAction)DeleteUser:(id)sender
{
    if([self.DeleteUserId.text isEqualToString:@""])
    {
        [self Alert:@"确定" message:@"请输入用户名!"];
        return;
    }
    if([self.DeletePassword.text isEqualToString:@""])
    {
        [self Alert:@"确定" message:@"请输入用户密码!"];
        return;
    }
    
    if(pUserRegistration!=NULL)
        pUserRegistration->DeleteUser([self.DeleteUserId.text UTF8String], [self.DeletePassword.text UTF8String]);
}

-(void) OnServerConnectingInfo:(unsigned int)errorid
{
    ierrorid = errorid;
    [self performSelectorOnMainThread:@selector(AddUserAndDeleteUserInfo:) withObject:self waitUntilDone:YES];
}

-(void) OnAddUserInfo:(unsigned int)errorid
{
    ierrorid = errorid;
    [self performSelectorOnMainThread:@selector(AddUserAndDeleteUserInfo:) withObject:self waitUntilDone:YES];
}

-(void) OnDeleteUserInfo:(unsigned int)errorid
{
    ierrorid = errorid;
    [self performSelectorOnMainThread:@selector(AddUserAndDeleteUserInfo:) withObject:self waitUntilDone:YES];
}

-(void)AddUserAndDeleteUserInfo:(id)mid
{
    switch (ierrorid)
    {
        case C_FAILED:
        {
            if(m_pMBProgressHUD!=nil)
            {
                [m_pMBProgressHUD hide:YES];
                m_pMBProgressHUD = nil;
            }
            [self Alert:@"确定" message:@"连接服务器失败!"];
        }
            break;
        case C_CONNECTED:
        {
            if(m_pMBProgressHUD!=nil)
            {
                [m_pMBProgressHUD hide:YES];
                m_pMBProgressHUD = nil;
            }
            //[self Alert:@"确定" message:@"请输入用户名!"];
        }
            break;
        case C_ADDUSERExist:
        {
            [self Alert:@"确定" message:@"添加的用户名已经存在!"];
        }
            break;
        case C_ADDUSEROK:
        {
            [self Alert:@"确定" message:@"添加用户成功!"];
        }
            break;
        case C_DELETEUSERNTExist:
        {
            [self Alert:@"确定" message:@"删除的用户不存在!"];
        }
            break;
        case C_DELETEUserPasswordErro:
        {
            [self Alert:@"确定" message:@"密码错误!"];
        }
            break;
        case C_DELETEUSEROK:
        {
            [self Alert:@"确定" message:@"删除用户成功!"];
        }
            break;
        case C_DATAERR:
        {
            [self Alert:@"确定" message:@"服务器数据库连接失败!"];
        }
            break;
    }
}

-(void)AllResignFirstResponder
{
    [self.UserID resignFirstResponder];
    [self.Password resignFirstResponder];
    [self.Nickname resignFirstResponder];
    [self.Phone resignFirstResponder];
    [self.Remark resignFirstResponder];
    
    [self.DeleteUserId resignFirstResponder];
    [self.DeletePassword resignFirstResponder];
}

@end
