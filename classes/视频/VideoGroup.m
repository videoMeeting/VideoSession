//
//  VideoGroup.m
//  VideoSession
//
//  Created by zhangxm on 13-3-9.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "VideoGroup.h"

@implementation VideoGroup
@synthesize headPhoto;
@synthesize name;
@synthesize number;
@synthesize groupId;
@synthesize isSelected;
- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
        isSelected=NO;
    }
    return self;
}

-(void)dealloc
{
    self.headPhoto=nil;
    self.name=nil;
    self.number=nil;
    self.groupId=nil;
    
    [super dealloc];
}

@end
