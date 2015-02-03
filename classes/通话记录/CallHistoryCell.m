//
//  CallHistoryCell.m
//  VideoSession
//
//  Created by zhangxm on 13-3-17.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "CallHistoryCell.h"

@implementation CallHistoryCell
@synthesize labelDate;
@synthesize labelName;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

-(void)dealloc
{
    self.labelDate=nil;
    self.labelName=nil;
    [super dealloc];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
