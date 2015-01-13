//
//  VideoGroup.h
//  VideoSession
//
//  Created by zhangxm on 13-3-9.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VideoGroup : NSObject
{
    NSString *headPhoto;
    NSString *name;
    NSString *number;
    NSString *groupId;
    bool     isSelected;
}
@property(nonatomic,retain)NSString *headPhoto;
@property(nonatomic,retain)NSString *name;
@property(nonatomic,retain)NSString *number;
@property(nonatomic,retain)NSString *groupId;
@property bool                      isSelected;
@end
