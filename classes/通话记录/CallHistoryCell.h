//
//  CallHistoryCell.h
//  VideoSession
//
//  Created by zhangxm on 13-3-17.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CallHistoryCell : UITableViewCell
{
    UILabel *labelName;
    UILabel *labelDate;
}
@property(retain,nonatomic)IBOutlet UILabel *labelName;
@property(retain,nonatomic)IBOutlet UILabel *labelDate;
@end
