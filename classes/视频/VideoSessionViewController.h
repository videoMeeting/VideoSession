//
//  VideoSessionViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <string>
#import "UISubScrollView.h"
#import "UISubNavigationController.h"
@class SessionInfoViewController;
@class SessionShowViewController;
@class SessionChatViewController;
@interface VideoSessionViewController : UIViewController<UIScrollViewDelegate>
{
    IBOutlet UISubScrollView *scrollView;
   // IBOutlet UIPageControl *pageControl;
    BOOL pageControlUsed;
    SessionInfoViewController *sessionInfoViewController;
    SessionShowViewController *sessionShowViewController;
    SessionChatViewController *sessionChatViewController;
//    bool isBackCam;
    UISubNavigationController *sessionShowNavCtrl;
    UISubNavigationController *sessionInfoNavCtrl;
    UINavigationController *sessionChatNavCtrl;
    int  m_ViewCount;
}
@property (nonatomic)bool isBackCam;
@property (nonatomic)int  m_ViewCount;
@property (nonatomic, retain) SessionInfoViewController *sessionInfoViewController;
@property (nonatomic, retain) SessionShowViewController *sessionShowViewController;
@property (nonatomic, retain) SessionChatViewController *sessionChatViewController;
@property (nonatomic, retain) UISubNavigationController *sessionShowNavCtrl;
@property (nonatomic, retain) UISubNavigationController *sessionInfoNavCtrl;
@property (nonatomic, retain) UINavigationController *sessionChatNavCtrl;
@property (nonatomic, retain) UISubScrollView *scrollView;
- (void)ScrollViewWithPage:(int)page;
+ (NSString*)deviceString;
- (void)loadScrollViewWithPage:(int)page;
- (void)scrollViewDidScroll:(UIScrollView *)sender;
- (void)MyUpdateMeetingInfo:(id)mid;
- (void)initViews;
- (void)PeerUserJoinTemporaryMeeting:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID;
- (void)PeerQuitInterimMeetingInfo:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID;
- (void)PeerDestructionInterimMeetingInfo;
- (void)SetInterfaceOrientation:(bool)isBack;
@end
