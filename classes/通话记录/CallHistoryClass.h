//
//  CallHistoryClass.h
//  VideoSession
//
//  Created by zhangxm on 13-3-29.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CallHistoryClass : NSObject<NSCoding>
{
   
        NSString *CallName;
        NSString *CallDate;
    
   
}
@property(retain,nonatomic)NSString *CallName;
@property(retain,nonatomic)NSString *CallDate;
@end
