//
//  MoreViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-4-22.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "MoreViewController.h"

@interface MoreViewController ()

@end

@implementation MoreViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        self.title = @"更多";
        
        UIImage* anImage = [UIImage imageNamed:@"更多1.png"];
        
        UITabBarItem* theItem = [[UITabBarItem alloc] initWithTitle:@"更多" image:anImage tag:0];
        
        self.tabBarItem = theItem;
         self.tabBarController.view.frame = [UIScreen mainScreen].applicationFrame;
        
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

@end
