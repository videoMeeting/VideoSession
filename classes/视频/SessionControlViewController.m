//
//  SessionControlViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-2-18.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "SessionControlViewController.h"

@interface SessionControlViewController ()

@end

@implementation SessionControlViewController
@synthesize SegmentVoiceModel;
@synthesize SegmentViedoModel;
@synthesize btBack;
@synthesize btSoundOff;
@synthesize labelVoiceModel;
@synthesize labelSoundOff;
@synthesize labelViedoModel;
@synthesize pSessionShowViewController;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    //self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
//    {
//        self =[super initWithNibName:@"SessionControlViewController_ipad" bundle:nil];
//    } else {
//        self =[super initWithNibName:@"SessionControlViewController" bundle:nil];
//    }
    self =[super initWithNibName:@"SessionControlViewController" bundle:nil];
    if (self) {
        uiMyVideoType = ROOM_VIDEO_ROOM;
        uiMyAudioType = ROOM_AUDIO_DISCUSS;
        pSessionShowViewController = nil;
        // Custom initialization
    }
   
    return self;
}

-(IBAction)btBack:(id)sender
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(void)viewWillAppear:(BOOL)animated
{
   [UIApplication sharedApplication].statusBarHidden = YES;
    [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight];
    [super viewWillAppear:animated];
}

-(void)SegmentViedoModelAction:(id)sender
{
    if(uiMyVideoType == ROOM_VIDEO_ROOM)
    {
        uiMyVideoType = ROOM_VIDEO_PUSH;
    }
    else
        uiMyVideoType = ROOM_VIDEO_ROOM;
    
    if(self.pSessionShowViewController!=nil)
        [self.pSessionShowViewController SetMeetingType:uiMyVideoType uiAudioType:uiMyAudioType];
    
}

-(void)SegmentVoiceModelAction:(id)sender
{
    if(uiMyAudioType == ROOM_AUDIO_DISCUSS)
    {
        uiMyAudioType = ROOM_AUDIO_SPEAK;
    }
    else
        uiMyAudioType = ROOM_AUDIO_DISCUSS;
    
    if(self.pSessionShowViewController!=nil)
        [self.pSessionShowViewController SetMeetingType:uiMyVideoType uiAudioType:uiMyAudioType];
}

-(IBAction)BtBack2:(id)sender
{
     [self dismissViewControllerAnimated:YES completion:nil];
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    UIBarButtonItem* leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(BtBack2:)];
    self.navigationItem.leftBarButtonItem = leftBtn;
    [leftBtn release];
    
    int hight = [UIScreen mainScreen].bounds.size.width;
    int with = [UIScreen mainScreen].bounds.size.height;
    [self.view  setFrame:CGRectMake(0, 0, with,hight)];
    self.view.bounds = CGRectMake(0, 0, with,hight);
    
    [self.navigationController.view  setFrame:CGRectMake(0, 0, with,hight)];
    self.navigationController.view.bounds = CGRectMake(0, 0, with,hight);
    [self.navigationController.visibleViewController.view setFrame:CGRectMake(0, 0, with, hight)];
    self.navigationController.navigationBar.frame = CGRectMake(0, 0, self.navigationController.navigationBar.frame.size.width, self.navigationController.navigationBar.frame.size.height);
    [self.view setFrame:CGRectMake(0,0,with,hight)];
    [self.SegmentViedoModel addTarget:self
                             action:@selector(SegmentViedoModelAction:)
                   forControlEvents:UIControlEventValueChanged];
    [self.SegmentVoiceModel addTarget:self
                               action:@selector(SegmentVoiceModelAction:)
                     forControlEvents:UIControlEventValueChanged];
         
     if(self.pSessionShowViewController!=nil)
     {
         uiMyVideoType = pSessionShowViewController.uiRoomVideoType;
         uiMyAudioType = pSessionShowViewController.uiRoomAudioType;
         
         if(uiMyVideoType == ROOM_VIDEO_ROOM)
             [self.SegmentViedoModel setSelectedSegmentIndex:0];
         else
             [self.SegmentViedoModel setSelectedSegmentIndex:1];
         
         if(uiMyAudioType == ROOM_AUDIO_DISCUSS)
             [self.SegmentVoiceModel setSelectedSegmentIndex:0];
         else
             [self.SegmentVoiceModel setSelectedSegmentIndex:1];
     }
}

-(void)dealloc
{
    self.labelSoundOff=nil;
    self.labelViedoModel=nil;
    self.labelVoiceModel=nil;
    self.btBack=nil;
    self.btSoundOff=nil;
    self.SegmentViedoModel=nil;
    self.SegmentVoiceModel=nil;
    self.pSessionShowViewController = nil;
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
