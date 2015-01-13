//
//  AudioDecodes.h
//  AudioCodes
//
//  Created by zhangxm on 12-12-12.
//  Copyright (c) 2012年 zhangxm. All rights reserved.
//

#ifndef __AudioCodes__AudioDecodes__
#define __AudioCodes__AudioDecodes__
#include "AudioDefine.h"
#include <iostream>

class AudioDecodes
{
public:
	AudioDecodes();
    virtual ~AudioDecodes();
	CodeType mcodeType;
    void* DecodeHandle;
private:
    
public:
    int DecodeAudio(char*inBuffer, unsigned int inSize,char*outBuffer, unsigned int *outSize);
    int initAudioDecode(CodeType codeType);
    int unInitAudioDecode();
};

#endif /* defined(__AudioCodes__AudioDecodes__) */
