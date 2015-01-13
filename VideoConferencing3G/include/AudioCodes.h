//
//  AudioCodes.h
//  AudioCodes
//
//  Created by zhangxm on 12-12-12.
//  Copyright (c) 2012年 zhangxm. All rights reserved.
//

#ifndef __AudioCodes__AudioCodes__
#define __AudioCodes__AudioCodes__

#include "AudioDefine.h"
#include <iostream>
class AudioCodes
{
public:
	AudioCodes();
    virtual ~AudioCodes();
	CodeType mcodeType;
    void* CodeHandle;
private:
	 
public:
    int CodeAudio(char*inBuffer,int inSize,char*outBuffer,int *outSize);
    int initAudioCode(CodeType codeType);
    int unInitAudioCode();
};

#endif /* defined(__AudioCodes__AudioCodes__) */
