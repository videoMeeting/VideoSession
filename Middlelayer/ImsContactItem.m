//
//  ImsContactItem.m
//  VideoSession
//
//  Created by zhangxm on 13-1-18.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "ImsContactItem.h"

@implementation ImsContactItem

@synthesize userid;
@synthesize username;
@synthesize userlevel;
@synthesize gender;
@synthesize age;
@synthesize country;
@synthesize province;
@synthesize city;
@synthesize address;
@synthesize postcode;
@synthesize phone;
@synthesize email;
@synthesize show;
@synthesize group;
@synthesize initiator;
@synthesize acceptflag;
@synthesize smscode;
@synthesize voipcode;
@synthesize svrid;
@synthesize svraddr;
@synthesize svrport;
@synthesize svrtype;
@synthesize nodeid;
@synthesize nataddr;
@synthesize localaddr;
@synthesize localport;
@synthesize termtype;
@synthesize status;
@synthesize isseletct;
@synthesize isInRoom;
- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
        userid		= "";
		username	= "";
		userlevel	= 0;
		
		gender		= "";
		age			= "";
		country		= "";
		province	= "";
		city		= "";
		address		= "";
		postcode	= "";
		phone		= "";
		email		= "";
		show		= "private";
        
		group		= "";
		initiator	= "";
		acceptflag	= "false";
		voipcode	= "";
        
		svrid		= "";
		svraddr		= "";
		svrport		= 0;
		svrtype		= "";
        
		nodeid		= "";
		nataddr		= "";
		localaddr	= "";
		localport	= 0;
		termtype	= "";
		status		= "offline";
        isseletct   = NO;
        isInRoom    = NO;
    }
    
    return self;
}
-(void)dealloc
{
    [super dealloc];
}
@end