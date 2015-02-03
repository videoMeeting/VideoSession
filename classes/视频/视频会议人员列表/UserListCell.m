//
//  MainTableCell.m
//  FFPlayer
//
//  Created by user on 11-12-28.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "UserListCell.h"

@implementation UserListCell
 
@synthesize userListViewController;
@synthesize uitextName1;
@synthesize uitextName2;
@synthesize uitextName3;
@synthesize uitextName4;

@synthesize selectBtn1;
@synthesize selectBtn2;
@synthesize selectBtn3;
@synthesize selectBtn4;

@synthesize uitextNnmber1;
@synthesize uitextNnmber2;
@synthesize uitextNnmber3;
@synthesize uitextNnmber4;

@synthesize contactItem1;
@synthesize contactItem2;
@synthesize contactItem3;
@synthesize contactItem4;

@synthesize imageBg1;
@synthesize imageBg2;
@synthesize imageBg3;
@synthesize imageBg4;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    if ((self = [super initWithStyle:style reuseIdentifier:reuseIdentifier])) {  
        // Initialization code  
    }  
    return self;  
} 
 
 
-(IBAction)pressNode1:(id)sender
{
  self.contactItem1.isseletct=!self.contactItem1.isseletct;
    [self.userListViewController.tableview reloadData];
}

-(IBAction)pressNode2:(id)sender
{
    self.contactItem2.isseletct=!self.contactItem2.isseletct;
    [self.userListViewController.tableview reloadData];
}
-(IBAction)pressNode3:(id)sender
{
    self.contactItem3.isseletct=!self.contactItem3.isseletct;
    [self.userListViewController.tableview reloadData];
}
-(IBAction)pressNode4:(id)sender
{
    self.contactItem4.isseletct=!self.contactItem4.isseletct;
    [self.userListViewController.tableview reloadData];
}

-(void)dealloc

{   
    self.uitextName1=nil;
    self.uitextName2=nil;
    self.uitextName3=nil;
    self.uitextName4=nil;
    self.selectBtn1=nil;
    self.selectBtn2=nil;
    self.selectBtn3=nil;
    self.selectBtn4=nil;
    self.uitextNnmber1=nil;
    self.uitextNnmber2=nil;
    self.uitextNnmber3=nil;
    self.uitextNnmber4=nil;
    self.contactItem1=nil;
    self.contactItem2=nil;
    self.contactItem3=nil;
    self.contactItem4=nil;
    self.imageBg1=nil;
    self.imageBg2=nil;
    self.imageBg3=nil;
    self.imageBg4=nil;
    self.userListViewController=nil;
    [super dealloc];

}
@end
