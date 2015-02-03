//
//  VideoCaptureEncoding.h
//  VideoLibrary
//
//  Created by wang guijun on 13-1-20.
//  Copyright (c) 2013年 wang guijun. All rights reserved.
//

#ifndef VideoLibrary_VideoCaptureEncoding_h
#define VideoLibrary_VideoCaptureEncoding_h

#import "VideoLibrary.h"
#import "VideoManagement.h"
#import <UIKit/UIKit.h>
class VideoCaptureEncod : public VideoCapture
{
public:
    VideoCaptureEncod(VideoCaptureDataCallBack* pVideoCaptureDataCallBack);
    ~VideoCaptureEncod();
public:
    virtual bool StartCapture();
    virtual void StopCapture();
    virtual bool setPreview(UIView *preview);
public:
    virtual bool StartEncoding();
    virtual void StopEncoding();
    virtual bool StartEncodingData();
    virtual void StopEncodeingData();
public:
    virtual void SetFrontAndRearCamera(bool isFront = true);
    virtual void SetLocalVideoWindow(void* pVideoWindow);
    virtual void SetPause(bool isPause = true);
public:
    virtual void SetBitRate(unsigned int uiBitRate);
    virtual void SetResolution(unsigned int uiWidth, unsigned int uiHeight);
    
    virtual unsigned int GetBitRate();
    virtual void GetResolution(unsigned int& uiWidth, unsigned int& uiHeight);
    
    virtual void SetVideoFps(unsigned int uiFps);
    virtual unsigned int GetVideoFps();
private:
    unsigned int m_uiBitRate;
    unsigned int m_uiWidth;
    unsigned int m_uiHeight;
    unsigned int m_uiFps;
    bool         m_isFront;
    void*        m_pVideoWindow;
    VideoCaptureDataCallBack* m_pVideoCaptureDataCallBack;
    VideoManagement*          m_pVideoManagement;
};

#endif
