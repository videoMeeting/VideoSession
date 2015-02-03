//
//  VideoCaptureEncoding.cpp
//  VideoLibrary
//
//  Created by wang guijun on 13-1-20.
//  Copyright (c) 2013年 wang guijun. All rights reserved.
//

#include "VideoCaptureEncoding.h"
#import "iOSGLView.h"
class Initialization{
public:
    Initialization();
    ~Initialization(){};
};

Initialization::Initialization()
{
    av_register_all();
    avcodec_register_all();
}


static Initialization s_Initialization;


VideoCaptureEncod::VideoCaptureEncod(VideoCaptureDataCallBack* pVideoCaptureDataCallBack)
:m_pVideoCaptureDataCallBack(pVideoCaptureDataCallBack)
,m_pVideoWindow(nil)
,m_uiFps(15)
,m_pVideoManagement(nil)
{
    m_pVideoManagement = [[VideoManagement alloc] init];
}

VideoCaptureEncod::~VideoCaptureEncod()
{
    if(m_pVideoManagement!=nil)
        [m_pVideoManagement release];
    m_pVideoManagement=nil;
}

bool VideoCaptureEncod::StartCapture()
{
    if(m_pVideoManagement!=nil)
        [m_pVideoManagement StartCapture];
    return true;
}

void VideoCaptureEncod::StopCapture()
{
    if(m_pVideoManagement!=nil)
        [m_pVideoManagement StopCapture];
}

bool VideoCaptureEncod::setPreview(UIView *preview)
{
    [m_pVideoManagement setPreview:preview];
    return  YES;
}

bool VideoCaptureEncod::StartEncoding()
{
    if(m_pVideoManagement!=nil)
    {
        if(m_pVideoCaptureDataCallBack)
            [m_pVideoManagement SetCallBack:m_pVideoCaptureDataCallBack];
        [m_pVideoManagement StartEncoding];
    }
    return true;
}

void VideoCaptureEncod::StopEncoding()
{
    if(m_pVideoManagement!=nil)
    {
        [m_pVideoManagement SetCallBack:nil];
        [m_pVideoManagement StopEncoding];
    }
}

void VideoCaptureEncod::SetPause(bool isPause)
{
    if(m_pVideoManagement!=nil)
        [m_pVideoManagement StartTransferThread:nil];
}

void VideoCaptureEncod::SetLocalVideoWindow(void* pVideoWindow)
{
    m_pVideoWindow = pVideoWindow;
    if(m_pVideoManagement!=nil)
        [m_pVideoManagement SetLocalVideoWindow:(iOSGLView*)m_pVideoWindow];
}

void VideoCaptureEncod::SetFrontAndRearCamera(bool isFront)
{
    m_isFront = isFront;
    if(m_pVideoManagement!=nil)
    {
        [m_pVideoManagement SetFrontAndRearCamera:isFront];
    }
}

void VideoCaptureEncod::SetBitRate(unsigned int uiBitRate)
{
    m_uiBitRate = uiBitRate;
    if(m_pVideoManagement!=nil)
        [m_pVideoManagement SetBitRate:m_uiBitRate];
    
}

void VideoCaptureEncod::SetResolution(unsigned int uiWidth, unsigned int uiHeight)
{
    m_uiWidth = uiWidth;
    m_uiHeight = uiHeight;
    if(m_pVideoManagement!=nil)
        [m_pVideoManagement SetResolution:uiWidth uiHeight:uiHeight];
}
    
unsigned int VideoCaptureEncod::GetBitRate()
{
    return m_uiBitRate;
}

void VideoCaptureEncod::GetResolution(unsigned int& uiWidth, unsigned int& uiHeight)
{
    uiWidth = m_uiWidth;
    uiHeight = m_uiHeight;
}

void VideoCaptureEncod::SetVideoFps(unsigned int uiFps)
{
    m_uiFps = uiFps;
    if(m_pVideoManagement!=nil)
        [m_pVideoManagement SetVideoFps:m_uiFps];
}

unsigned int VideoCaptureEncod::GetVideoFps()
{
    return m_uiFps;
}

bool VideoCaptureEncod::StartEncodingData()
{
    if(m_pVideoManagement)
        m_pVideoManagement.bIsEncodingData = YES;
    return true;
}

void VideoCaptureEncod::StopEncodeingData()
{
    if(m_pVideoManagement)
        m_pVideoManagement.bIsEncodingData = NO;
}



