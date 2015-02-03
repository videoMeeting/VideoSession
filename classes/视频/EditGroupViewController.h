//
//  EditGroupViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include"LoginServer.h"
@class  HandInputViewController;
@class GroupsViewController;

@interface EditGroupViewController : UIViewController
{
    UIToolbar               *toolBar;
    UITextField             *groupName;
    HandInputViewController *handInputViewController;
    GroupsViewController    *groupsViewController;
    NSString                *oldgroupname;
    LoginServer             *pLoginServer;
}

@property(nonatomic,retain)IBOutlet UIToolbar      *toolBar;
@property(nonatomic,retain)IBOutlet UITextField    *groupName;
@property(nonatomic,retain)HandInputViewController *handInputViewController;
@property(nonatomic,retain)GroupsViewController    *groupsViewController;
@property(nonatomic,retain)NSString                *oldgroupname;

@end
