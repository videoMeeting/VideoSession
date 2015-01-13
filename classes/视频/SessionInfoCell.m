//
//  SessionInfoCell.m
//  VideoSession
//
//  Created by zhangxm on 13-2-19.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "SessionInfoCell.h"
#import "SessionInfoViewController.h"
@implementation SessionInfoCell
@synthesize Name;
@synthesize PhoneNumber;
@synthesize Power;
@synthesize RSpeak;
@synthesize RVideo;
@synthesize headPhoto;
@synthesize RUser;
@synthesize index;
@synthesize strUserID;

@synthesize sessionInfoViewController;
- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

-(IBAction)btHeadPhoto:(id)sender
{
    if ( self.sessionInfoViewController) {
        [self.sessionInfoViewController changePower:self.strUserID];
    }
}
-(IBAction)btType:(id)sender
{
    
}

-(IBAction)btStatus:(id)sender
{
    
}

-(IBAction)btOffLine:(id)sender
{
    
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    // Configure the view for the selected state
}

-(void)dealloc
{
    self.sessionInfoViewController=nil;
    self.index=nil;
    self.headPhoto=nil;
    self.Name=nil;
    self.Power=nil;
    self.RVideo=nil;
    self.RSpeak=nil;
    self.PhoneNumber=nil;
    self.RUser=nil;
    [super dealloc];
}
@end
