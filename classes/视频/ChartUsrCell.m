//
//  ChartUsrCell.m
//  VideoSession
//
//  Created by zhangxm on 13-3-15.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "ChartUsrCell.h"
#include "ImsContactItem.h"
#import "SessionChatViewController.h"
@implementation ChartUsrCell
@synthesize isSelect;
@synthesize Name;
@synthesize imsContactItem;
@synthesize sessionChatViewController;
- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

-(IBAction)BtSelect:(id)sender
{
    if ([self.Name.text isEqualToString:@"所有人"]) {
       // self.imsContactItem.isseletct =!self.imsContactItem.isseletct;
        [self.sessionChatViewController SetSelect];
        [self.sessionChatViewController.UserTableView reloadData];
    }
    else
    {
        self.imsContactItem.isseletct =!self.imsContactItem.isseletct;
        [self.sessionChatViewController.UserTableView reloadData];
        [self.sessionChatViewController SetAll:self.imsContactItem];
    }
}
-(void)dealloc
{
    self.imsContactItem=nil;
    self.sessionChatViewController=nil;
    self.isSelect=nil;
    self.Name=nil;
    [super dealloc];
}
@end
