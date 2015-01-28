//
//  VideoAndAudioSet.cpp
//  VideoSession
//
//  Created by wang guijun on 13-4-11.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#include "VideoAndAudioSet.h"
#import "sys/utsname.h"

VideoAndAudioSet VideoAndAudioSet::m_sVideoAndAudioSet;

VideoAndAudioSet* VideoAndAudioSet::GetObject()
{
    return &m_sVideoAndAudioSet;
}

VideoAndAudioSet::VideoAndAudioSet()
: m_uiFps(1)
, m_uiWidth(160)
, m_uiHeight(120)
, m_uiBitRate(8)
, m_Speaker(false)
{
    NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
    NSString *NsWidth = [accountDefaults objectForKey:@"Width"];
    NSString *NsHeigt = [accountDefaults objectForKey:@"Heigt"];
    NSString *NsBitRate = [accountDefaults objectForKey:@"BitRate"];
    NSString *NsVideoFps = [accountDefaults objectForKey:@"VideoFps"];
    
    if(NsWidth!=nil && NsHeigt!=nil && NsBitRate!=nil && NsVideoFps!=nil && ![NsWidth isEqualToString:@""] && ![NsHeigt isEqualToString:@""] && ![NsBitRate isEqualToString:@""] && ![NsVideoFps isEqualToString:@""])
    {
        m_uiWidth = [NsWidth intValue];
        m_uiHeight = [NsHeigt intValue];
        m_uiBitRate = [NsBitRate intValue];
        m_uiFps = [NsVideoFps intValue];
    }
    else
    {
        struct utsname systemInfo;
        uname(&systemInfo);
        NSString *deviceString = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
        
        if ([deviceString isEqualToString:@"iPad2,1"] || [deviceString isEqualToString:@"iPad2,2"] ||
        [deviceString isEqualToString:@"iPad2,3"])
        {
            m_uiWidth = 640;
            m_uiHeight = 480;
        }
    }
}

VideoAndAudioSet::~VideoAndAudioSet()
{
    
}

void VideoAndAudioSet::SetAudioType(unsigned int uiType)
{
    m_AudioType = uiType;
}

unsigned int VideoAndAudioSet::GetAudioType() const
{
    return m_AudioType;
}

void VideoAndAudioSet::SetResolution(unsigned int uiWidth, unsigned int uiHeight)
{
    m_uiWidth = uiWidth;
    m_uiHeight = uiHeight;
}

void VideoAndAudioSet::GetResolution(unsigned int& uiWidth, unsigned int& uiHeight)
{
    uiWidth = m_uiWidth;
    uiHeight = m_uiHeight;
}

void VideoAndAudioSet::SetVideoFps(unsigned int uiFps)
{
    m_uiFps = uiFps;
}

unsigned int VideoAndAudioSet::GetVideoFps()
{
    return m_uiFps;
}

void VideoAndAudioSet::SetBitRate(unsigned int uiBitRate)
{
    m_uiBitRate = uiBitRate;
}
unsigned int VideoAndAudioSet::GetBitRate()
{
    return m_uiBitRate;
}

