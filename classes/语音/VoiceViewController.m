//
//  VoiceViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-7.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "VoiceViewController.h"

#import "UISubNavigationController.h"
@interface VoiceViewController ()

@end

@implementation VoiceViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
        self.title = @"音频";
        
        UIImage* anImage = [UIImage imageNamed:@"语音1.png"];
        
        UITabBarItem* theItem = [[UITabBarItem alloc] initWithTitle:@"音频" image:anImage tag:0];
        
        self.tabBarItem = theItem;
        // self.tabBarController.view.frame = [UIScreen mainScreen].applicationFrame;
        
        [theItem release];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
   
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
