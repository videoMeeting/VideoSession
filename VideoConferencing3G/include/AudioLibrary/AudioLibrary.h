//
//  AudioLibrary.h
//  AudioLibrary
//
//  Created by wang guijun on 13-1-19.
//  Copyright (c) 2013年 wang guijun. All rights reserved.
//
#ifndef AUDIOLIBRARY_H
#define AUDIOLIBRARY_H

class AudioCapture
{
public:
    AudioCapture(){};
    virtual ~AudioCapture(){};
public:
    virtual bool Start() = 0;
    virtual void Stop() = 0;
public:
    virtual void SetAudioEncodingMode(int type) = 0;
};

class AudioCaptureDataCallBack
{
public:
    AudioCaptureDataCallBack(){};
    virtual ~AudioCaptureDataCallBack(){};
public:
    virtual void On_MediaReceiverCallbackAudio(unsigned char*pData,int nLen) = 0;
};

AudioCapture* CteateAudioCapture(AudioCaptureDataCallBack* pVideoCaptureDataCallBack);
void ReleaseAudioCapture();


class Audioplayback
{
public:
    Audioplayback(){};
    virtual ~Audioplayback(){};
public:
    virtual bool Start(bool bSpeaker) = 0;
    virtual void Stop() = 0;
    virtual void SetMute() = 0;
public:
    virtual void SetAudioDecodingMode(int type) = 0;
    virtual bool AddAudioData(unsigned int uiAudioId,unsigned char*pData,int nLen) = 0;
};

Audioplayback* CteateAudioplayback(bool bSpeaker);
void ReleaseAudioplayback();

Audioplayback* GetAudioplayback();

#endif

