//
//  SessionChatViewController.h
//  VideoSession
//
//  Created by zhangxm on 13-1-30.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//
#include"LoginServer.h"
#import <UIKit/UIKit.h>
#import "ImsContactItem.h"

@class VideoSessionViewController;
@class SessionShowViewController;
@interface SessionChatViewController : UIViewController<UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate>
{
    UITableView *ChartTableView;
    UITableView *UserTableView;
    UITextField *charttextField;
    NSMutableArray* chatArray;
    NSMutableArray *ContactArray;
    UIToolbar *chartToolBar;
    UILabel *textlabel;
    BOOL isMove;
    NSInteger isTag;
    LoginServer *pLoginServer;
    UIView *viewKeyboard;
    VideoSessionViewController *videoSessionViewController;
    SessionShowViewController  *sessionShowViewController;
    UIWindow* tempWindow;
    UIView *superUIView;
    bool ISselect;
}
@property(retain,nonatomic)UITableView *ChartTableView;
@property(retain,nonatomic)UIWindow* tempWindow;
 @property(retain,nonatomic)IBOutlet UITableView *UserTableView;
@property(retain,nonatomic)IBOutlet UIToolbar *chartToolBar;
@property(retain,nonatomic)NSMutableArray* chatArray;
@property(retain,nonatomic)NSMutableArray *ContactArray;
@property(retain,nonatomic)UILabel *textlabel;
@property(retain,nonatomic)IBOutlet UITextField *charttextField;
@property(retain,nonatomic)IBOutlet UIView *viewKeyboard;
@property(assign,nonatomic)VideoSessionViewController *videoSessionViewController;
@property(assign,nonatomic)SessionShowViewController  *sessionShowViewController;
-(void)InitCtrs;
-(void) SetSelect;
-(void) SetAll:(ImsContactItem *)mSelect;
-(void) UpdateUser;
-(IBAction)textFieldDidEditing:(id)sender;
-(void)sendMassage:(NSString *)message;
-(void)GetMassage:(NSString *)message;
-(UIView *)bubbleView:(NSString *)text from:(BOOL)fromSelf;
-(void) MyUpdateMeetingInfo:(id)mid;

@end
