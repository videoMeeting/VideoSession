//
//  MyUILongPressGestureRecognizer.h
//  VideoSession
//
//  Created by wang guijun on 13-5-29.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MyUILongPressGestureRecognizer : UILongPressGestureRecognizer
{
    NSString* strUserID;
}

@property(retain,nonatomic)NSString *strUserID;

@end
