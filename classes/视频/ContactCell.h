//
//  MainTableCell.h
//  FFPlayer
//
//  Created by user on 11-12-28.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
@class ContactCell;
#include "ImsContactItem.h"
#import "CallViewController.h"
@interface ContactCell : UITableViewCell
{
    UILabel            *uitextName1;
    UILabel            *uitextName2;
    
    UIButton           *selectBtn1;
    UIButton           *selectBtn2;
    
    UILabel            *uitextNnmber1;
    UILabel            *uitextNnmber2;
    
    UIImageView        *HeadImage1;
    UIImageView        *HeadImage2;
    ImsContactItem     *contactItem1;
    ImsContactItem     *contactItem2;
    CallViewController *callViewController;
}

@property(retain,nonatomic) IBOutlet UILabel *uitextName1;
@property(retain,nonatomic) IBOutlet UILabel *uitextName2;
@property(retain,nonatomic) IBOutlet UIImageView *HeadImage1;
@property(retain,nonatomic) IBOutlet UIImageView *HeadImage2;
@property(retain,nonatomic) IBOutlet UIButton *selectBtn1;
@property(retain,nonatomic) IBOutlet UIButton *selectBtn2;

@property(retain,nonatomic) IBOutlet UILabel *uitextNnmber1;
@property(retain,nonatomic) IBOutlet UILabel *uitextNnmber2;
@property(assign,nonatomic) ImsContactItem *contactItem1;
@property(assign,nonatomic) ImsContactItem *contactItem2;
@property(assign,nonatomic)CallViewController *callViewController;
-(IBAction)pressNode1:(id)sender;
-(IBAction)pressNode2:(id)sender;

@end