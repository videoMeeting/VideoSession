//
//  VideoGroupCell.h
//  VideoSession
//
//  Created by zhangxm on 13-3-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
@class InviteGroupsViewController;

@interface InviteGroupCell : UITableViewCell
{
    UIImageView         *headPhoto;
    UILabel             *Name;
    UILabel             *Number;
    UIButton            *uibutton;
    InviteGroupsViewController *inviteGroupsViewController;
}
@property(retain,nonatomic)IBOutlet UIImageView *headPhoto;
@property(retain,nonatomic)IBOutlet UILabel     *Name;
@property(retain,nonatomic)IBOutlet UILabel     *Number;
@property(assign,nonatomic)InviteGroupsViewController *inviteGroupsViewController;
@property(nonatomic,retain)IBOutlet UIButton    *uibutton;

-(IBAction)btEdit:(id)sender;

@end
