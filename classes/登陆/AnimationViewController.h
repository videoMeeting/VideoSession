//
//  AnimationViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-3-18.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AnimationViewController : UIViewController
{
    UILabel *textInfo;
    UIImageView *BackImage;
}
@property(retain,nonatomic)IBOutlet UILabel *textInfo;
@property(retain,nonatomic)IBOutlet UIImageView *BackImage;
@end
