//
//  UISubNavigationController.h
//  VideoSession
//
//  Created by zhangxm on 13-4-1.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UISubNavigationController : UINavigationController{
    BOOL _changing;
}
- (void)setbackground;
@property(nonatomic, retain)UIView *alphaView;
-(void)setAlph;
@end
