//
//  ChartUsrCell.h
//  VideoSession
//
//  Created by zhangxm on 13-3-15.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ImsContactItem;
@class SessionChatViewController;
@interface ChartUsrCell : UITableViewCell
{
    UIButton *isSelect;
    UILabel *Name;
    ImsContactItem *imsContactItem;
    SessionChatViewController *sessionChatViewController;
}
@property(retain,nonatomic)IBOutlet UIButton *isSelect;
@property(retain,nonatomic)IBOutlet UILabel *Name;
@property(assign,nonatomic)ImsContactItem *imsContactItem;
@property(assign,nonatomic)SessionChatViewController *sessionChatViewController;
-(IBAction)BtSelect:(id)sender;
@end
