//
//  VideoGroupCell.m
//  VideoSession
//
//  Created by zhangxm on 13-3-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "VideoGroupCell.h"
#import "VideoViewController.h"

@implementation VideoGroupCell

@synthesize headPhoto;
@synthesize Name;
@synthesize Number;
@synthesize videoViewController;
@synthesize uibutton;

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

-(IBAction)btEdit:(id)sender
{
    if(self.videoViewController)
    {
        [self.videoViewController EditGroup:self.Name.text];
    }
}

-(void)dealloc
{
    self.headPhoto =nil;
    self.Name=nil;
    self.Number=nil;
    [super dealloc];
    
}
@end
