//
//   ConfigViewController.m
//  ScoPlayer
//
//  Created by user on 12-7-12.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import "ConfigViewController.h"
#import <QuartzCore/QuartzCore.h>
@implementation ConfigViewController
@synthesize serverIP; 
@synthesize HTTPort;
@synthesize HTTPSPort;
@synthesize Account;
@synthesize Password;
@synthesize label;
@synthesize SaveButton;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
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

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self initialData];
}

 

-(void)dealloc
{  
    self.serverIP=nil;
    self.HTTPort=nil;
    self.HTTPSPort=nil;
    self.Account=nil;
    self.Password=nil;
    self.label=nil;
    self.SaveButton=nil;
     
    [super dealloc];  
}

-(IBAction)textfiledchangeserverIP:(id)sender
{
    [label setText:serverIP.text]; 
    [label sizeToFit];
}

-(IBAction)textfiledchangeHTTPort:(id)sender
{
    [label setText:HTTPort.text]; 
    [label sizeToFit];
}


-(IBAction)textfiledchangeHTTPSPort:(id)sender
{
    [label setText:HTTPSPort.text]; 
    [label sizeToFit];
}


-(IBAction)textfiledchangeAccount:(id)sender
{
    [label setText:Account.text]; 
    [label sizeToFit];
}

-(IBAction)textfiledchangePassword:(id)sender
{
    [label setText:Password.text]; 
    [label sizeToFit];
}

-(NSString *)dataFilePath
{
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    return [documentsDirectory stringByAppendingPathComponent:@"LoginConfig.plist"];
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
       UIView *view = [[[UIView alloc] init]autorelease];
    
    label = [[[UILabel alloc] init] autorelease];
    [label setFont:[UIFont fontWithName:@"TrebuchetMS-Bold" size:18]];
    //label.textAlignment = UITextAlignmentCenter;
    
    [label setBackgroundColor:[UIColor clearColor]];
    
    [label setText:textField.text]; 
    
    view.frame = CGRectMake(0, 0, 300, 20);
    
    [view addSubview:label];
    
    [label sizeToFit];
    textField.inputAccessoryView = view;
}
-(void)initialData
{
    //获取属性表的数据
    
   
}
- (void)textFieldDidEndEditing:(UITextField *)textField
{ 
 
}
 
- (BOOL)textFieldShouldClear:(UITextField *)textField
{
    [textField resignFirstResponder];
    textField.text=@"";
    return NO;
}

-(void)AllResignFirstResponder
{
    [self.serverIP resignFirstResponder]; 
    [self.HTTPort resignFirstResponder];
    [self.HTTPSPort resignFirstResponder];  
    [self.Account resignFirstResponder];
    [self.Password resignFirstResponder];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    [self AllResignFirstResponder];
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

- (BOOL)isPureInt:(NSString *)string{
    
    NSScanner* scan = [NSScanner scannerWithString:string]; 
    
    int val; 
    
    return [scan scanInt:&val] && [scan isAtEnd];
    
}

-(bool)saveLogInfo
{ 
    
    return YES;
}


-(IBAction)btSave:(id)sender
{
    if ([self saveLogInfo]) {
        
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"保存成功" message:@"本地配置保存成功"
                                                       delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
        [alert show];	
        [alert release];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"保存失败" message:@"本地配置保存失败"
                                                       delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
        [alert show];	
        [alert release];  
    }

}

-(IBAction)btBack:(id)sender
{
    
    CATransition  *animation = [CATransition animation];
    [animation setDuration:0.5f];
    [animation setTimingFunction:[CAMediaTimingFunction
                                  functionWithName:kCAMediaTimingFunctionEaseIn]];
    [animation setType:kCATransitionMoveIn];
    [animation setSubtype: kCATransitionFromLeft];
    [self.view.superview.layer addAnimation:animation forKey:@"Push"];
    [self.view removeFromSuperview];
    
}
-(void)HideButton
{
    [self.SaveButton setHidden:YES];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
