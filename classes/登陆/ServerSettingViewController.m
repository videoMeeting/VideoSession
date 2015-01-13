//
//  ServerSettingViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-3-13.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "ServerSettingViewController.h"

@interface ServerSettingViewController ()

@end

@implementation ServerSettingViewController
@synthesize iP;
@synthesize label;
@synthesize port;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
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

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
    NSString *IP=[accountDefaults objectForKey:@"IP"];
    NSString *PORT=[accountDefaults objectForKey:@"PORT"];
    if (![IP isEqualToString:@"(null)"]) {
        self.iP.text=IP;
    }
    
    if(![PORT isEqualToString:@""] && ![PORT isEqualToString:@"(null)"])
    {
        self.port.text = PORT;
    }
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
    self.iP = nil;
    [super dealloc];
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
