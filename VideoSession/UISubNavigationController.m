//
//  UISubNavigationController.m
//  VideoSession
//
//  Created by zhangxm on 13-4-1.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "UISubNavigationController.h"

@interface UISubNavigationController ()

@end

@implementation UISubNavigationController

@synthesize alphaView;
-(id)initWithRootViewController:(UIViewController *)rootViewController{
    self = [super initWithRootViewController:rootViewController];
    if (self) {
        
     
        
        
        
     }
    return self;
}

 - (void)setbackground
{
    CGRect frame = self.navigationBar.frame;
    alphaView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
    alphaView.backgroundColor = [UIColor whiteColor];
    [self.view insertSubview:alphaView belowSubview:self.navigationBar];
    [self.navigationBar setBackgroundColor:[UIColor clearColor]];
    
    self.navigationBar.layer.masksToBounds = YES;
    [self setAlph];
}

-(void)setAlph{
//    if (_changing == NO) {
//        _changing = YES;
//        if (alphaView.alpha == 0.0 ) {
//            [UIView animateWithDuration:0.5 animations:^{
//                alphaView.alpha = 1.0;
//            } completion:^(BOOL finished) {
//                _changing = NO;
//            }];
//        }else{
            [UIView animateWithDuration:0.5 animations:^{
                alphaView.alpha = 0.3;
            } completion:^(BOOL finished) {
                _changing = NO;
                
            }];
//        }
//    }
    
    
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
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(BOOL)shouldAutorotate
{
    return NO;
}

-(NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskPortrait;
}

@end
