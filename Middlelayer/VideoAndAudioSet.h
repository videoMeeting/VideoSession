//
//  VideoAndAudioSet.h
//  VideoSession
//
//  Created by wang guijun on 13-4-11.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#ifndef __VideoSession__VideoAndAudioSet__
#define __VideoSession__VideoAndAudioSet__

#include <iostream>

class VideoAndAudioSet
{
public:
    static VideoAndAudioSet* GetObject();
public:
    VideoAndAudioSet();
    ~VideoAndAudioSet();
public:
    void SetAudioType(unsigned int uiType);
    unsigned int GetAudioType() const;
    
    void SetResolution(unsigned int uiWidth, unsigned int uiHeight);
    void GetResolution(unsigned int& uiWidth, unsigned int& uiHeight);
    
    void SetVideoFps(unsigned int uiFps);
    unsigned int GetVideoFps();
    
    void SetBitRate(unsigned int uiBitRate);
    unsigned int GetBitRate();
    
    void SetSpeaker(bool mSpeaker){ m_Speaker = mSpeaker;};
    bool GetSpeaker(){ return m_Speaker;};
private:
    unsigned int m_uiWidth;
    unsigned int m_uiHeight;
    unsigned int m_uiFps;
    unsigned int m_uiBitRate;
    bool         m_Speaker;
private:
    unsigned int m_AudioType;
private:
    static VideoAndAudioSet m_sVideoAndAudioSet;
};


#endif /* defined(__VideoSession__VideoAndAudioSet__) */
