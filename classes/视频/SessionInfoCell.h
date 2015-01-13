//
//  SessionInfoCell.h
//  VideoSession
//
//  Created by zhangxm on 13-2-19.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <string>
@class  SessionInfoViewController;
@interface SessionInfoCell : UITableViewCell
{
    UILabel *index;
    UILabel *Name;
    UILabel *Power;
    UILabel *PhoneNumber;
    //UIImageView *headPhoto;
    UIImageView *RVideo;
    UIImageView *RSpeak;
    UIImageView *RUser;
    UIButton    *headPhoto;
    std::string strUserID;
    SessionInfoViewController *sessionInfoViewController;
}
@property(nonatomic,retain)IBOutlet UILabel *Name;
@property(nonatomic,retain)IBOutlet UILabel *index;
@property(nonatomic,retain)IBOutlet UIButton *headPhoto;
@property(nonatomic,retain)IBOutlet UILabel *Power;
@property(nonatomic,retain)IBOutlet UILabel *PhoneNumber;
@property(nonatomic,retain)SessionInfoViewController *sessionInfoViewController;
@property(nonatomic,retain)IBOutlet UIImageView *RVideo;
@property(nonatomic,retain)IBOutlet UIImageView *RSpeak;
@property(nonatomic,retain)IBOutlet UIImageView *RUser;
@property(nonatomic)std::string strUserID;

-(IBAction)btType:(id)sender;
-(IBAction)btStatus:(id)sender;
-(IBAction)btOffLine:(id)sender;
-(IBAction)btHeadPhoto:(id)sender;
@end
