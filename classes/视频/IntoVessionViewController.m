//
//  IntoVessionViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-3-26.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "IntoVessionViewController.h"

@interface IntoVessionViewController ()

@end

@implementation IntoVessionViewController
@synthesize logoImage;
@synthesize biaotiImage;
@synthesize statusLabel;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
     
}

-(void)viewWillDisappear:(BOOL)animated
{
     [super viewWillDisappear:animated];
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.logoImage.transform=CGAffineTransformMakeRotation(M_PI/2);
    [self.logoImage setFrame:CGRectMake(150, 160, 160,160)];
   
    self.biaotiImage.transform=CGAffineTransformMakeRotation(M_PI/2);
    [self.biaotiImage setFrame:CGRectMake(80, 130, 60,240)];
  
    self.statusLabel.transform=CGAffineTransformMakeRotation(M_PI/2);
    [self.statusLabel setFrame:CGRectMake(30, 130, 40,240)];
}

-(void)dealloc
{
    
    self.logoImage=nil;
    self.biaotiImage=nil;
    self.statusLabel=nil;
    [super dealloc];
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
