//
//  CallHistoryHelp.m
//  VideoSession
//
//  Created by zhangxm on 13-3-29.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "CallHistoryHelp.h"
#import "CallHistoryClass.h"
@implementation CallHistoryHelp
- (id)init
{
    self = [super init];
    if (self) {
    }
    return self;
}

-(void)dealloc
{
    [super dealloc];
}

-(NSString*)GetFileName
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSString *fileName =[documentsDirectory stringByAppendingPathComponent:@"Callhistory.plist"];
    return fileName;
}
-(void)insertHistory:(NSString*)callName callDate:(NSString*)callDate
{
    NSString *filePath = [self GetFileName];
    NSData *data2 = [NSData dataWithContentsOfFile:filePath];//读取文件
    NSMutableArray *array = [NSKeyedUnarchiver unarchiveObjectWithData:data2];
    if (array) {
    
        CallHistoryClass *callHistoryClass=[[[CallHistoryClass alloc]init]autorelease];
        
        callHistoryClass.CallName = callName;
        callHistoryClass.CallDate = callDate;
        [array addObject:callHistoryClass];
        
         NSData  *data1 = [NSKeyedArchiver archivedDataWithRootObject:array];//将s1序列化后,保存到NSData中
        
        [data1 writeToFile:filePath atomically:YES];
        
        array = nil;
        data2 = nil;
        data1 = nil;
        
    }
    else{
         array = [[[NSMutableArray alloc] init]autorelease];
        
        CallHistoryClass *callHistoryClass=[[[CallHistoryClass alloc]init]autorelease];
        
        callHistoryClass.CallName = callName;
        callHistoryClass.CallDate = callDate;
        [array addObject:callHistoryClass];
        //序列化
        NSData  *data1 = [NSKeyedArchiver archivedDataWithRootObject:array];//将s1序列化后,保存到NSData中
         
        [data1 writeToFile:filePath atomically:YES];//持久化保存成物理文件
        
        array = nil;
        data1 = nil;
    }
}

-(NSMutableArray*)GetHistory
{
    NSString *filePath = [self GetFileName];
     
    NSData *data2 = [NSData dataWithContentsOfFile:filePath];//读取文件
    NSMutableArray *array = [NSKeyedUnarchiver unarchiveObjectWithData:data2];
    data2 = nil;
    return  array;
}
@end
