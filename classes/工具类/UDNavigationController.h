//
//  UDNavigationController.h
//  test
//
//  Created by UDi on 15-1-7.
//  Copyright (c) 2015年 Mango Media Network Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UDNavigationController : UINavigationController{
    BOOL _changing;
}
@property(nonatomic, retain)UIView *alphaView;
-(void)setAlph;
@end
