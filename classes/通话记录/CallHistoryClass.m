//
//  CallHistoryClass.m
//  VideoSession
//
//  Created by zhangxm on 13-3-29.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "CallHistoryClass.h"

@implementation CallHistoryClass
@synthesize CallDate;
@synthesize CallName;

- (id)init
{
    self = [super init];
    if (self) {
        
        self.CallName=@"";
        self.CallDate=nil;
    }
    return self;
}

- (void) encodeWithCoder: (NSCoder *)coder
{
	
    [coder encodeObject:self.CallName forKey:@"CallName"];
	[coder encodeObject:self.CallDate forKey:@"CallDate"];
	 
}

- (id) initWithCoder: (NSCoder *) coder
{
    
    CallName = [[coder decodeObjectForKey:@"CallName"]copy];
    CallDate = [[coder decodeObjectForKey:@"CallDate"]copy];
   
    return self;
}

-(void)dealloc
{
 
    [CallName release];
    [CallDate release];
    [super dealloc];
}
@end
