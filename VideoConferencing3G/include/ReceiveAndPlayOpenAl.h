//
//  ReceiveAndPlayOpenAl.h
//  AudioLibrary
//
//  Created by zhangxm on 13-4-14.
//  Copyright (c) 2013年 wang guijun. All rights reserved.
//

#import <Foundation/Foundation.h>



#import"AudioDefine.h"
#include "AudioDecodes.h"
@class OpenAlPlay;
@interface ReceiveAndPlayOpenAl : NSObject
{
    OpenAlPlay *openAlPlay;
    CodeType codetype;
    AudioDecodes *audioDecode;
   
}
@property  AudioDecodes *audioDecode;
@property(nonatomic)CodeType codetype;

-(void)initOpenALMode:(CodeType) type;
-(void)openAlPaly:(char*)AudioData size:(int)size;
-(void)CloseOpenAL;
@end
