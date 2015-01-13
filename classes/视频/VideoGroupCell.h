//
//  VideoGroupCell.h
//  VideoSession
//
//  Created by zhangxm on 13-3-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
@class VideoViewController;

@interface VideoGroupCell : UITableViewCell
{
    UIImageView         *headPhoto;
    UILabel             *Name;
    UILabel             *Number;
    UIButton            *uibutton;
    VideoViewController *videoViewController;
}
@property(retain,nonatomic)IBOutlet UIImageView *headPhoto;
@property(retain,nonatomic)IBOutlet UILabel     *Name;
@property(retain,nonatomic)IBOutlet UILabel     *Number;
@property(assign,nonatomic)VideoViewController  *videoViewController;
@property(nonatomic,retain)IBOutlet UIButton    *uibutton;

-(IBAction)btEdit:(id)sender;

@end
