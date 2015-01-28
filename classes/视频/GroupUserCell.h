//
//  MainTableCell.h
//  FFPlayer
//
//  Created by user on 11-12-28.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "ImsContactItem.h"
@class GroupUserViewController;
@interface GroupUserCell : UITableViewCell
{
    UILabel *uitextName1;
    UILabel *uitextName2;
    
     UIButton *selectBtn1;
    UIButton *selectBtn2;
    
    UILabel *uitextNnmber1;
    UILabel *uitextNnmber2;
    
    UIImageView *imagebg1;
    UIImageView *imagebg2;
    ImsContactItem *contactItem1;
    ImsContactItem *contactItem2;
    GroupUserViewController *groupUserViewController;
}

 
 
@property(retain,nonatomic) IBOutlet UILabel *uitextName1;
@property(retain,nonatomic) IBOutlet UILabel *uitextName2;
@property(retain,nonatomic) IBOutlet UIImageView *imagebg1;
@property(retain,nonatomic) IBOutlet UIImageView *imagebg2;
@property(retain,nonatomic) IBOutlet UIButton *selectBtn1;
@property(retain,nonatomic) IBOutlet UIButton *selectBtn2;

@property(retain,nonatomic) IBOutlet UILabel *uitextNnmber1;
@property(retain,nonatomic) IBOutlet UILabel *uitextNnmber2;
@property(assign,nonatomic) ImsContactItem *contactItem1;
@property(assign,nonatomic) ImsContactItem *contactItem2;
@property(assign,nonatomic)GroupUserViewController *groupUserViewController;
-(IBAction)pressNode1:(id)sender;
-(IBAction)pressNode2:(id)sender;

@end