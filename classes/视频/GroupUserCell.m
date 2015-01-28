//
//  MainTableCell.m
//  FFPlayer
//
//  Created by user on 11-12-28.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "GroupUserCell.h"
 
#import "GroupUserViewController.h"
@implementation GroupUserCell
@synthesize contactItem1;
@synthesize contactItem2;
 
@synthesize groupUserViewController;
 
@synthesize uitextName1;
@synthesize uitextName2;

@synthesize selectBtn1;
@synthesize selectBtn2;

@synthesize uitextNnmber1;
@synthesize uitextNnmber2;
@synthesize imagebg1;
@synthesize imagebg2;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    if ((self = [super initWithStyle:style reuseIdentifier:reuseIdentifier])) {  
        // Initialization code  
    }  
    return self;  
} 

-(IBAction)pressNode1:(id)sender
{
    self.contactItem1.isseletct=!self.contactItem1.isseletct;
    [self.groupUserViewController.tableview reloadData];
}

-(IBAction)pressNode2:(id)sender
{
    self.contactItem2.isseletct=!self.contactItem2.isseletct;
    [self.groupUserViewController.tableview reloadData];
}

-(void)dealloc
{   
    self.contactItem1=nil;
    self.contactItem2=nil;
    self.uitextName1=nil;
    self.uitextName2=nil;
    self.selectBtn1=nil;
    self.selectBtn2=nil;
    self.uitextNnmber1=nil;
    self.uitextNnmber2=nil;
    self.groupUserViewController=nil;
    self.imagebg1=nil;
    self.imagebg2=nil;
    [super dealloc];
}
@end
