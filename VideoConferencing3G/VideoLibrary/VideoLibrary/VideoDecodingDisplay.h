//
//  VideoDecodingDisplay.h
//  VideoLibrary
//
//  Created by wang guijun on 13-1-20.
//  Copyright (c) 2013年 wang guijun. All rights reserved.
//

#ifndef VideoLibrary_VideoDecodingDisplay_h
#define VideoLibrary_VideoDecodingDisplay_h

#include "liveFFmpegdecode.h"
#import "VideoLibrary.h"
#define AFX_EXT_CLASS
#include "../../include/WYBASE/Thread.h"
#include <list>

class KVideoBuffer
{
public:
    KVideoBuffer():m_cpBuffer(NULL),m_ulLen(0)
    {}
public:
    void SetBuffer( char* cpBuffer){ m_cpBuffer = cpBuffer;};
    void SetLen(const unsigned long ulLen){ m_ulLen = ulLen;};
    
    char* GetBuffer() const { return m_cpBuffer;};
    const unsigned long GetLen() const { return m_ulLen;};
private:
    char* m_cpBuffer;
    unsigned long m_ulLen;
};

typedef std::list<KVideoBuffer*> VIDEODDATA_LIST;

class VideoDecodingDisplay : public VideoPalyback , public KThread
{
public:
    VideoDecodingDisplay();
    ~VideoDecodingDisplay();
public:
    virtual void SetResolution(unsigned int uiWidth, unsigned int uiHeight);
    virtual void GetResolution(unsigned int& uiWidth, unsigned int& uiHeight);
public:
    virtual bool Start();
    virtual void Stop();
public:
    virtual bool StartDisplayVideo();
    virtual void StopDisplayVideo();
public:
    virtual void SetVideoWindow(void* pVideoWindow);
    virtual bool AddVideoData(unsigned char*pData,int nLen);
protected:
    virtual void ThreadProcMain(void);
private:
    unsigned int m_uiWidth;
    unsigned int m_uiHeight;
    liveFFmpegdecode*       m_liveFFmpegdecode;
    VIDEODDATA_LIST         m_VideoData_List;
    pthread_mutex_t         m_pMutex;
    bool                    m_bWantToStop;
    int                     m_icount;
};


#endif
