//
//  UISubLRNavgationViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-4-22.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "UISubLRNavgationViewController.h"

@interface UISubLRNavgationViewController ()

@end

@implementation UISubLRNavgationViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        [UIApplication sharedApplication].statusBarHidden = YES;
        //self.view.transform=CGAffineTransformMakeRotation(M_PI/2);
        int hight = [UIScreen mainScreen].bounds.size.width;
        int  with = [UIScreen mainScreen].bounds.size.height;
        [self.view setBounds:CGRectMake(0, 0, hight,with)];
    }
    return self;
}
-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    // Do any additional setup after loading the view.
    [UIApplication sharedApplication].statusBarHidden = YES;
    
}
- (void)viewDidLoad
{
    [super viewDidLoad];
  
    [UIApplication sharedApplication].statusBarHidden = YES;
    //self.view.transform=CGAffineTransformMakeRotation(M_PI/2);
    int hight = [UIScreen mainScreen].bounds.size.width;
    int  with = [UIScreen mainScreen].bounds.size.height;
    [self.view setBounds:CGRectMake(0, 0, hight,with)];
    //[self.view setFrame:CGRectMake(0, 0, hight,with)];

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

-(NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskLandscape;
}

-(BOOL)shouldAutorotate
{
    return NO;
}
@end
