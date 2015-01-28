//
//  VideoAndVoiceViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "VideoAndVoiceViewController.h"
#include "VideoAndAudioSet.h"
#import "SessionShowViewController.h"
#include <AudioToolbox/AudioToolbox.h>
#import  <AVFoundation/AVFoundation.h>
@interface VideoAndVoiceViewController ()

@end

@implementation VideoAndVoiceViewController
@synthesize backview1;
@synthesize backview2;
@synthesize segmentedControl1;
@synthesize slider1;
@synthesize segmentedControl2;
@synthesize segmentedControl3;
@synthesize slider2;
@synthesize sliderVideoBitrate1;
@synthesize sliderVideoBitrate2;
@synthesize pUiLabelVBitrate1;
@synthesize pUiLabelVBitrate2;
@synthesize pUiLabelFp1;
@synthesize pUiLabelFp2;
@synthesize pSessionShowViewController;
@synthesize tabBarController;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        //Custom initialization
        self.title = @"设置";
        UIImage* anImage = [UIImage imageNamed:@"设置tab.png"];
        UITabBarItem* theItem = [[UITabBarItem alloc] initWithTitle:@"设置" image:anImage tag:0];
        self.tabBarItem = theItem;
        //self.tabBarController.view.frame = [UIScreen mainScreen].applicationFrame;
        [theItem release];
    }
    return self;
}

-(IBAction)btexit:(id)sender
{
    if (styple)
    {
          
    }
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(IBAction)btOK:(id)sender
{
    VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
    unsigned int uiWidth = 0;
    unsigned int uiHeigt = 0;
    unsigned int uiVideoFps = 0;
    unsigned int uiBitRate = 0;
    if(styple)
    {
        uiVideoFps = slider2.value;
        uiBitRate = sliderVideoBitrate2.value;
        int segmentSelected=[self.segmentedControl2 selectedSegmentIndex];
        switch (segmentSelected)
        {
            case 0:
            {
                uiWidth = 160;
                uiHeigt = 120;
            }
                break;
            case 1:
            {
                uiWidth = 320;
                uiHeigt = 240;
            }
                break;
            case 2:
            {
                uiWidth = 640;
                uiHeigt = 480;
            }
                break;
            default:
                break;
        }
        
        m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
        if(mNSTimer == nil)
            mNSTimer = [NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];

    }
    else
    {
        uiVideoFps = slider1.value;
        uiBitRate = sliderVideoBitrate1.value;
        int segmentSelected=[self.segmentedControl1 selectedSegmentIndex];
        switch (segmentSelected)
        {
            case 0:
            {
                uiWidth = 160;
                uiHeigt = 120;
            }
                break;
            case 1:
            {
                uiWidth = 320;
                uiHeigt = 240;
            }
                break;
            case 2:
            {
                uiWidth = 640;
                uiHeigt = 480;
            }
                break;
            default:
                break;
        }
        
        m_pMBProgressHUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        m_pMBProgressHUD.mode = MBProgressHUDModeCustomView;
        if(mNSTimer == nil)
            mNSTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(runTimer:) userInfo:nil repeats:YES];
    }
    
    unsigned int uioldWidth = 0;
    unsigned int uioldHeigt = 0;
    unsigned int uioldBitRate = 0;
    unsigned int uioldVideoFps = 0;
    p->GetResolution(uioldWidth, uioldHeigt);
    uioldBitRate = p->GetBitRate();
    uioldVideoFps = p->GetVideoFps();
    
    if(uioldWidth != uiWidth || uioldHeigt != uiHeigt || uioldBitRate != uiBitRate || uioldVideoFps != uiVideoFps)
    {
        p->SetBitRate(uiBitRate);
        p->SetResolution(uiWidth, uiHeigt);
        p->SetVideoFps(uiVideoFps);
        
        
        NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
        
        NSString *NsWidth=[NSString stringWithFormat:@"%d",uiWidth];
        NSString *NsHeigt=[NSString stringWithFormat:@"%d",uiHeigt];
        NSString *NsBitRate=[NSString stringWithFormat:@"%d",uiBitRate];
        NSString *NsVideoFps=[NSString stringWithFormat:@"%d",uiVideoFps];
        
        [accountDefaults setObject:NsWidth forKey:@"Width"];
        [accountDefaults setObject:NsHeigt forKey:@"Heigt"];
        [accountDefaults setObject:NsBitRate forKey:@"BitRate"];
        [accountDefaults setObject:NsVideoFps forKey:@"VideoFps"];
        
        if(styple)
        {
            if(self.pSessionShowViewController!=nil)
                [pSessionShowViewController UpdatedLocalVideo];
            
            [self dismissViewControllerAnimated:YES completion:nil];
        }
    }
}

-(void)runTimer:(id)timer
{
    if(m_pMBProgressHUD!=nil)
    {
        [m_pMBProgressHUD hide:YES];
        m_pMBProgressHUD = nil;
    }
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    if (styple) {
    [UIApplication sharedApplication].statusBarHidden = styple;
    }
    [self UpDataUI];
    
}

-(void)viewWillDisappear:(BOOL)animated
{
    [UIApplication sharedApplication].statusBarHidden = NO;
        [super viewWillDisappear:animated];
}

-(void)setBackview1 
{
    styple=NO;
//    UIBarButtonItem* leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(BtBack1:)];
//    self.navigationItem.leftBarButtonItem = leftBtn;
//    [leftBtn release];
    [UIApplication sharedApplication].statusBarHidden = NO;
    for(UIView *subview in [self.view subviews])
    {
        [subview removeFromSuperview];
    }
    [self.view addSubview:self.backview1];
    //self.backview2.transform=CGAffineTransformMakeRotation(M_PI/2);
    int hight = [UIScreen mainScreen].bounds.size.width;
    int with = [UIScreen mainScreen].bounds.size.height;
    [self.view setFrame:CGRectMake(0, 0, hight,with)];
    [self.view setBounds:CGRectMake(0, 0, hight,with)];
    [self.backview1 setFrame:CGRectMake(0, 0, hight,with)];
    [self.backview1 setBounds:CGRectMake(0, 0, hight,with)];
}
-(IBAction)BtBack1:(id)sender
{
     [self.tabBarController setSelectedIndex:0];
    
}

-(IBAction)BtBack2:(id)sender
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(void)setBackview2
{
    styple=YES;
 
    
        [super viewDidLoad];
    [UIApplication sharedApplication].statusBarHidden = YES;
    
//        UIBarButtonItem* leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(BtBack2:)];
//        self.navigationItem.leftBarButtonItem = leftBtn;
//        [leftBtn release];
    
    for(UIView *subview in [self.view subviews])
    {
        [subview removeFromSuperview];
    }
    int with = [UIScreen mainScreen].bounds.size.width;
    int hight = [UIScreen mainScreen].bounds.size.height;
    [self.view  setFrame:CGRectMake(0, 0, with,hight)];
    self.view.bounds = CGRectMake(0, 0, with,hight);
    
    [self.navigationController.view  setFrame:CGRectMake(0, 0, with,hight)];
    self.navigationController.view.bounds = CGRectMake(0, 0, with,hight);
    [self.navigationController.visibleViewController.view setFrame:CGRectMake(0, 0, with, hight)];
    self.navigationController.navigationBar.frame = CGRectMake(0, 0, self.navigationController.navigationBar.frame.size.width, self.navigationController.navigationBar.frame.size.height);
    
    
     [self.view setFrame:CGRectMake(0,0,with,hight)];
    
    [self.view addSubview:self.backview2];
    [self.backview2 setFrame:CGRectMake(0, 0,with, hight)];
}

-(bool) LoudSpeaker:(bool)bOpen
{
 
    AVAudioSession *session = [AVAudioSession sharedInstance];
    
    NSError *setCategoryError = nil;
    if (![session setCategory:AVAudioSessionCategoryPlayAndRecord
                  withOptions:AVAudioSessionCategoryOptionMixWithOthers
                        error:&setCategoryError]) {
      
    }
    
    if (bOpen) {
            [session overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:nil];
        }
  else
  {
      [session overrideOutputAudioPort:AVAudioSessionPortOverrideNone error:nil];
      
  }
    
    return true;
}

- (void)segmentAction3:(id)sender
{
	//NSLog(@"segmentAction: selected segment = %d", [sender selectedSegmentIndex]);
    VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
    
    int segmentSelected=[sender selectedSegmentIndex];
    switch (segmentSelected)
    {
        case 0:
        {
            p->SetSpeaker(false);
            [self LoudSpeaker:false];
        }
            break;
        case 1:
        {
            p->SetSpeaker(true);
            [self LoudSpeaker:true];
        }
            break;
        default:
            break;
    }
}

- (void)segmentAction:(id)sender
{
	//NSLog(@"segmentAction: selected segment = %d", [sender selectedSegmentIndex]);
    int segmentSelected=[sender selectedSegmentIndex];
    switch (segmentSelected)
    {
        case 0:
            break;
        case 1:
            break;
        default:
            break;
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title=@"设置";
    [self.segmentedControl1 addTarget:self
                              action:@selector(segmentAction:)
                    forControlEvents:UIControlEventValueChanged];
    //self.segmentedControl1.segmentedControlStyle = UISegmentedControlStyleBar;
    self.segmentedControl1.selectedSegmentIndex = 0;
    [self.segmentedControl2 addTarget:self
                               action:@selector(segmentAction:)
                     forControlEvents:UIControlEventValueChanged];
    //self.segmentedControl2.segmentedControlStyle = UISegmentedControlStyleBar;
    self.segmentedControl2.selectedSegmentIndex = 0;
    
    [self.segmentedControl3 addTarget:self
                               action:@selector(segmentAction3:)
                     forControlEvents:UIControlEventValueChanged];
    //self.segmentedControl3.segmentedControlStyle = UISegmentedControlStyleBar;
    self.segmentedControl3.selectedSegmentIndex = 0;
    
    [self.slider1 addTarget:self action:@selector(SetFp1:) forControlEvents:UIControlEventValueChanged];
    [self.slider2 addTarget:self action:@selector(SetFp2:) forControlEvents:UIControlEventValueChanged];
    
    [self.sliderVideoBitrate1 addTarget:self action:@selector(SetBitrate1:) forControlEvents:UIControlEventValueChanged];
    [self.sliderVideoBitrate2 addTarget:self action:@selector(SetBitrate2:) forControlEvents:UIControlEventValueChanged];
}

- (void)SetFp1:(id)sender
{
    unsigned int uiVideoFps = slider1.value;
    pUiLabelFp1.text = [[[NSString alloc ] initWithFormat:@"%d",uiVideoFps] autorelease];
}

- (void)SetFp2:(id)sender
{
    unsigned int uiVideoFps = slider2.value;
    pUiLabelFp2.text = [[[NSString alloc ] initWithFormat:@"%d",uiVideoFps] autorelease];
}

- (void)SetBitrate1:(id)sender
{
    unsigned int uiBitRate = sliderVideoBitrate1.value;
    pUiLabelVBitrate1.text = [[[NSString alloc ] initWithFormat:@"%d",uiBitRate] autorelease];
}

- (void)SetBitrate2:(id)sender
{
    unsigned int uiBitRate = sliderVideoBitrate2.value;
    pUiLabelVBitrate2.text = [[[NSString alloc ] initWithFormat:@"%d",uiBitRate] autorelease];
}

-(void)UpDataUI
{
    VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
    unsigned int uiWidth = 0;
    unsigned int uiHeigt = 0;
    unsigned int uiBitRate = 0;
    unsigned int uiVideoFps = 0;
    p->GetResolution(uiWidth, uiHeigt);
    uiBitRate = p->GetBitRate();
    uiVideoFps = p->GetVideoFps();
    
    if(styple)
    {
        [slider2 setValue:(float)uiVideoFps];
        [sliderVideoBitrate2 setValue:(float)uiBitRate];
        pUiLabelVBitrate2.text = [[[NSString alloc ] initWithFormat:@"%d",uiBitRate] autorelease];
        pUiLabelFp2.text = [[[NSString alloc ] initWithFormat:@"%d",uiVideoFps] autorelease];
        
        if(uiWidth == 176 && uiHeigt == 144)
        {
            self.segmentedControl2.selectedSegmentIndex = 0;
        }
        else if(uiWidth == 320 && uiHeigt == 240)
        {
            self.segmentedControl2.selectedSegmentIndex = 1;
        }
        else if(uiWidth == 640 && uiHeigt == 480)
        {
            self.segmentedControl2.selectedSegmentIndex = 2;
        }
    }
    else
    {
        [slider1 setValue:(float)uiVideoFps];
        [sliderVideoBitrate1 setValue:(float)uiBitRate];
        pUiLabelVBitrate1.text = [[[NSString alloc ] initWithFormat:@"%d",uiBitRate] autorelease];
        pUiLabelFp1.text = [[[NSString alloc ] initWithFormat:@"%d",uiVideoFps] autorelease];
        
        if(uiWidth == 176 && uiHeigt == 144)
        {
            self.segmentedControl1.selectedSegmentIndex = 0;
        }
        else if(uiWidth == 320 && uiHeigt == 240)
        {
            self.segmentedControl1.selectedSegmentIndex = 1;
        }
        else if(uiWidth == 640 && uiHeigt == 480)
        {
            self.segmentedControl1.selectedSegmentIndex = 2;
        }
    }
}

-(void)dealloc
{
    self.segmentedControl1=nil;
    self.backview1=nil;
    self.backview2=nil;
    self.slider1=nil;
    self.segmentedControl2=nil;
    self.slider2=nil;
    self.tabBarController=nil;
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

-(BOOL)shouldAutorotate
{
    return YES;
}

-(NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskLandscape;
}
@end
