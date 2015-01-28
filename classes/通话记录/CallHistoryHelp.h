//
//  CallHistoryHelp.h
//  VideoSession
//
//  Created by zhangxm on 13-3-29.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CallHistoryHelp : NSObject
{
}

-(NSString*)GetFileName;
-(void)insertHistory:(NSString*)callName callDate:(NSString*)callDate;
-(NSMutableArray*)GetHistory;
@end
