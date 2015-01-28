//
//  IntoVessionViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-3-26.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface IntoVessionViewController : UIViewController
{
    UIImageView *logoImage;
    UIImageView *biaotiImage;
    UILabel * statusLabel;
}
@property(retain,nonatomic)IBOutlet UIImageView *logoImage;
@property(retain,nonatomic)IBOutlet UIImageView *biaotiImage;
@property(retain,nonatomic)IBOutlet UILabel * statusLabel;
@end
