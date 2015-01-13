//
//  SessionControlViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-2-18.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//
#include"LoginServer.h"
#import <UIKit/UIKit.h>
#import "SessionShowViewController.h"

@interface SessionControlViewController : UIViewController
{
    UILabel                      *labelSoundOff;
    UILabel                      *labelViedoModel;
    UILabel                      *labelVoiceModel;
    UIButton                     *btBack;
    UIButton                     *btSoundOff;
    UISegmentedControl           *SegmentViedoModel;
    UISegmentedControl           *SegmentVoiceModel;
    unsigned int                 uiMyVideoType;
    unsigned int                 uiMyAudioType;
    SessionShowViewController *pSessionShowViewController;
}

@property(nonatomic,retain)IBOutlet UILabel *labelSoundOff;
@property(nonatomic,retain)IBOutlet UILabel *labelViedoModel;
@property(nonatomic,retain)IBOutlet UILabel *labelVoiceModel;
@property(nonatomic,retain)IBOutlet UIButton* btBack;
@property(nonatomic,retain)IBOutlet UIButton* btSoundOff;
@property(nonatomic,retain)IBOutlet UISegmentedControl *SegmentViedoModel;
@property(nonatomic,retain)IBOutlet UISegmentedControl *SegmentVoiceModel;
@property(nonatomic,retain)SessionShowViewController *pSessionShowViewController;

-(IBAction)btBack:(id)sender;
@end
