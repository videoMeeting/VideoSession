//
//  SettingViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//
#import "UISubNavigationController.h"
#import "SettingViewController.h"
#import "VideoAndVoiceViewController.h"
#import"LoginViewController.h"
@interface SettingViewController ()

@end

@implementation SettingViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
        self.title = @"设置";
        
        UIImage* anImage = [UIImage imageNamed:@"设置tab.png"];
        
        UITabBarItem* theItem = [[UITabBarItem alloc] initWithTitle:@"设置" image:anImage tag:0];
        
        self.tabBarItem = theItem;
        // self.tabBarController.view.frame = [UIScreen mainScreen].applicationFrame;
        
        [theItem release];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

 
-(IBAction)btVideoAndVoice:(id)sender
{
    VideoAndVoiceViewController *videoAndVoiceViewController=[[[VideoAndVoiceViewController alloc]initWithNibName:@"VideoAndVoiceViewController" bundle:nil]autorelease];
    [self.navigationController pushViewController:videoAndVoiceViewController animated:YES];
}
 

@end
