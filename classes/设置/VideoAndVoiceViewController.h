//
//  VideoAndVoiceViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MBProgressHUD.h"

#import "UISubTabBarController.h"
@class SessionShowViewController;

@interface VideoAndVoiceViewController : UIViewController
{
    UIView *backview1;
    UIView *backview2;
    bool styple;
    UISegmentedControl*  segmentedControl1;
    UISlider *slider1;
    UISegmentedControl*  segmentedControl2;
    UISegmentedControl*  segmentedControl3;
    UISlider *slider2;
    UISlider *sliderVideoBitrate1;
    UISlider *sliderVideoBitrate2;
    UILabel *pUiLabelVBitrate1;
    UILabel *pUiLabelVBitrate2;
    UILabel *pUiLabelFp1;
    UILabel *pUiLabelFp2;
    MBProgressHUD              *m_pMBProgressHUD;
    NSTimer                    *mNSTimer;
    SessionShowViewController  *pSessionShowViewController;
    UISubTabBarController *tabBarController;
}
@property(assign,nonatomic)UISubTabBarController *tabBarController;
@property(retain,nonatomic)IBOutlet UIView *backview1;
@property(retain,nonatomic)IBOutlet UIView *backview2;
@property(retain,nonatomic)IBOutlet UISegmentedControl*  segmentedControl1;
@property(retain,nonatomic)IBOutlet UISlider *slider1;
@property(retain,nonatomic)IBOutlet UISegmentedControl*  segmentedControl2;
@property(retain,nonatomic)IBOutlet UISegmentedControl*  segmentedControl3;
@property(retain,nonatomic)IBOutlet UISlider *slider2;
@property(retain,nonatomic)IBOutlet UISlider *sliderVideoBitrate1;
@property(retain,nonatomic)IBOutlet UISlider *sliderVideoBitrate2;
@property(retain,nonatomic)IBOutlet UILabel *pUiLabelVBitrate1;
@property(retain,nonatomic)IBOutlet UILabel *pUiLabelVBitrate2;
@property(retain,nonatomic)IBOutlet UILabel *pUiLabelFp1;
@property(retain,nonatomic)IBOutlet UILabel *pUiLabelFp2;
@property(retain,nonatomic)SessionShowViewController *pSessionShowViewController;

-(void)setBackview1;
-(IBAction)btexit:(id)sender;
-(IBAction)btOK:(id)sender;
-(void)setBackview2;
@end
