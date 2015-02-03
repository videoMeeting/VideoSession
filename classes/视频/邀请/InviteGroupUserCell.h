//
//  MainTableCell.h
//  FFPlayer
//
//  Created by user on 11-12-28.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "ImsContactItem.h"
#import "InviteGroupUserViewController.h"
@interface InviteGroupUserCell : UITableViewCell
{
    
    InviteGroupUserViewController *userListViewController;
    
    UILabel *uitextName1;
    UILabel *uitextName2;
    UILabel *uitextName3;
    UILabel *uitextName4;
    
    UIButton *selectBtn1;
    UIButton *selectBtn2;
     UIButton *selectBtn3;
    UIButton *selectBtn4;
    
    UILabel *uitextNnmber1;
    UILabel *uitextNnmber2;
    UILabel *uitextNnmber3;
    UILabel *uitextNnmber4;
    
    ImsContactItem *contactItem1;
    ImsContactItem *contactItem2;
    ImsContactItem *contactItem3;
    ImsContactItem *contactItem4;
    UIImageView *imageBg1;
    UIImageView *imageBg2;
    UIImageView *imageBg3;
    UIImageView *imageBg4;
}

 

@property(assign,nonatomic)IBOutlet UILabel *uitextName1;
@property(assign,nonatomic)IBOutlet UILabel *uitextName2;
@property(assign,nonatomic)IBOutlet UILabel *uitextName3;
@property(assign,nonatomic)IBOutlet UILabel *uitextName4;

@property(assign,nonatomic)IBOutlet UIButton *selectBtn1;
@property(assign,nonatomic)IBOutlet UIButton *selectBtn2;
@property(assign,nonatomic)IBOutlet UIButton *selectBtn3;
@property(assign,nonatomic)IBOutlet UIButton *selectBtn4;

@property(assign,nonatomic)IBOutlet UILabel *uitextNnmber1;
@property(assign,nonatomic)IBOutlet UILabel *uitextNnmber2;
@property(assign,nonatomic)IBOutlet UILabel *uitextNnmber3;
@property(assign,nonatomic)IBOutlet UILabel *uitextNnmber4;

@property(assign,nonatomic)IBOutlet UIImageView *imageBg1;
@property(assign,nonatomic)IBOutlet UIImageView *imageBg2;
@property(assign,nonatomic)IBOutlet UIImageView *imageBg3;
@property(assign,nonatomic)IBOutlet UIImageView *imageBg4;

@property(assign,nonatomic)ImsContactItem *contactItem1;
@property(assign,nonatomic)ImsContactItem *contactItem2;
@property(assign,nonatomic)ImsContactItem *contactItem3;
@property(assign,nonatomic)ImsContactItem *contactItem4;

@property(assign,nonatomic)InviteGroupUserViewController *userListViewController;
-(IBAction)pressNode1:(id)sender;
-(IBAction)pressNode2:(id)sender;
-(IBAction)pressNode3:(id)sender;
-(IBAction)pressNode4:(id)sender;

@end