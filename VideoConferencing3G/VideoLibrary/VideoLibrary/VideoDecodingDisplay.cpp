//
//  VideoDecodingDisplay.cpp
//  VideoLibrary
//
//  Created by wang guijun on 13-1-20.
//  Copyright (c) 2013年 wang guijun. All rights reserved.
//

#include "VideoDecodingDisplay.h"
#include <pthread.h>

VideoDecodingDisplay::VideoDecodingDisplay()
:m_liveFFmpegdecode(nil)
{
    pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_pMutex, &attr);
	pthread_mutexattr_destroy(&attr);
    m_VideoData_List.clear();
    m_bWantToStop = true;
    m_liveFFmpegdecode = [[liveFFmpegdecode alloc] init];
}

VideoDecodingDisplay::~VideoDecodingDisplay()
{
    if(m_bWantToStop == false)
    {
       m_bWantToStop = true ;
        (void)pthread_mutex_lock(&m_pMutex);
        VIDEODDATA_LIST::iterator iter = m_VideoData_List.begin();
        while (iter!=m_VideoData_List.end()) {
            free((*iter)->GetBuffer());
            delete *iter;
            iter++;
        }
        m_VideoData_List.clear();
        pthread_mutex_unlock(&m_pMutex);
        WaitForStop();
    }
    
    pthread_mutex_destroy(&m_pMutex);
    if(m_liveFFmpegdecode != nil)
        [m_liveFFmpegdecode release];
    m_liveFFmpegdecode = nil;
}

bool VideoDecodingDisplay::Start()
{
    if(m_liveFFmpegdecode == nil)
        return false;
    m_icount = 0;
    m_bWantToStop = false;
    StartThread();
    m_VideoData_List.clear();
    [m_liveFFmpegdecode Beginmpeg_decode_h264];
    return true;
}

void VideoDecodingDisplay::Stop()
{
    if(m_liveFFmpegdecode == nil)
        return ;
    
    m_bWantToStop = true;
    (void)pthread_mutex_lock(&m_pMutex);
    VIDEODDATA_LIST::iterator iter = m_VideoData_List.begin();
    while (iter!=m_VideoData_List.end()) {
        
        free((*iter)->GetBuffer());
        delete *iter;
        iter++;
    }
    m_VideoData_List.clear();
    pthread_mutex_unlock(&m_pMutex);
    WaitForStop();
    
    [m_liveFFmpegdecode Endinmpeg_decode_h264];
}

bool VideoDecodingDisplay::StartDisplayVideo()
{
    if(m_liveFFmpegdecode == nil)
        return false;
    return [m_liveFFmpegdecode StartDisplayVideo];
}

void VideoDecodingDisplay::StopDisplayVideo()
{
    if(m_liveFFmpegdecode == nil)
        return ;
    [m_liveFFmpegdecode StopDisplayVideo];
}

void VideoDecodingDisplay::SetResolution(unsigned int uiWidth, unsigned int uiHeight)
{
    m_uiWidth = uiWidth;
    m_uiHeight = uiHeight;
    
    if(m_liveFFmpegdecode == nil)
        return ;
    [m_liveFFmpegdecode SetResolution:m_uiWidth uiHeight:m_uiHeight];
}

void VideoDecodingDisplay::GetResolution(unsigned int& uiWidth, unsigned int& uiHeight)
{
    uiWidth = m_uiWidth;
    uiHeight = m_uiHeight;
}

void VideoDecodingDisplay::SetVideoWindow(void* pVideoWindow)
{
    if(m_liveFFmpegdecode == nil)
        return ;
    [m_liveFFmpegdecode SetLocalVideoWindow:(iOSGLView*)pVideoWindow];
}
bool VideoDecodingDisplay::AddVideoData(unsigned char*pData,int nLen)
{
    if(m_liveFFmpegdecode == nil)
        return false;
    
    if(m_bWantToStop)
        return true;
    
    char* pVideoPacketBeffer=(char*)malloc(nLen);
    memset(pVideoPacketBeffer, 0, nLen);
    memcpy(pVideoPacketBeffer,pData,nLen);
    
    KVideoBuffer *pKBuffer = new KVideoBuffer;
    pKBuffer->SetBuffer( pVideoPacketBeffer );
    pKBuffer->SetLen( nLen );
    
    while(m_icount > 10)
    {
        (void)pthread_mutex_lock(&m_pMutex);
        m_icount = (int)m_VideoData_List.size();
        (void)pthread_mutex_lock(&m_pMutex);
        usleep(10*1000);
    }
    
    (void)pthread_mutex_lock(&m_pMutex);
    m_VideoData_List.push_back(pKBuffer);
    pthread_mutex_unlock(&m_pMutex);
    //[m_liveFFmpegdecode ffmpeg_decode_h264:(unsigned char *)pData Len:nLen iCount:1];
    return true;
}

void VideoDecodingDisplay::ThreadProcMain(void)
{
    while(!m_bWantToStop)
	{
        KVideoBuffer* pRecvBuffer = NULL;
        (void)pthread_mutex_lock(&m_pMutex);
        int icount =(int) m_VideoData_List.size();
        if(icount > 0)
        {
            pRecvBuffer = (KVideoBuffer*)m_VideoData_List.front();
            m_VideoData_List.pop_front();
        }
        pthread_mutex_unlock(&m_pMutex);
        
        if(pRecvBuffer != NULL)
        {
            char* pBuffer = pRecvBuffer->GetBuffer();
            unsigned int uiLen = (unsigned int) pRecvBuffer->GetLen();
            
            [m_liveFFmpegdecode ffmpeg_decode_h264:(unsigned char *)pBuffer Len:uiLen iCount:1];
        
            free(pBuffer);
            delete pRecvBuffer;
            usleep(10*1000);
        }
	}
}