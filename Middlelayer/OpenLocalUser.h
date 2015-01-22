//
//  OpenLocalUser.h
//  VideoSession
//
//  Created by wang guijun on 13-2-7.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#ifndef VideoSession_OpenLocalUser_h
#define VideoSession_OpenLocalUser_h

#include <string>
#include <vector>
#include "./NETEC/NETEC_MediaSender.h"
#include "AudioLibrary/AudioLibrary.h"
#include "VideoLibrary/VideoLibrary.h"
#include "LoginServer.h"
//
@class   CameraCapture;
typedef std::vector<std::string> OPENMEUSERLIST;

class OpenLocalUser
: public NETEC_MediaSenderCallback
, public AudioCaptureDataCallBack
, public VideoCaptureDataCallBack
{
public:
    static OpenLocalUser* GetObject();
    static void ReleaseObject(OpenLocalUser*&);
public:
    OpenLocalUser();
    ~OpenLocalUser();
public:
    bool ConnectMediaServer(std::string strServerIp, unsigned int uiPort);
    void ReleaseMediaSever();
public:
    bool OpenVideo(void* pView, unsigned long ulUserVideoId, unsigned int uiWidth, unsigned int uiHeight, unsigned int uiBitrate, unsigned int uiFramerate = 10);
    bool SendVideoData();
    void StopSendVideoData();
    void CloseVideo();
    bool AddOpenMeVideoUser(std::string strUserID);
    void DeleteOpenMeVideoUser(std::string strUserID);
    void ClearOpenMeVideoUser(){m_OpenMeVideoUserList.clear();};
    bool AddOpenMeAudioUser(std::string strUserID);
    void DeleteOpenAudioUser(std::string strUserID);
    void ClearOpenMeAudioUser(){m_OpenMeAudioUserList.clear();};
    unsigned int OpenMeVideoCount();
    unsigned int OpenMeAudioCount();
    bool OpenAudio(unsigned long ulUserAudioId, unsigned int uiAudioType);
    bool SendAudioData();
    void StopSendAudioData();
    void CloseAudio();
public:
    void SetFrontAndRearCamera(bool isFront = true);
    bool setVideoWindow (UIView*preview);
public:
    virtual void On_MediaReceiverCallbackAudio(unsigned char*pData,int nLen);
    virtual void On_MediaReceiverCallbackVideo(unsigned char*pData,int nLen, bool bKeyFrame, int nWidth, int nHeight);
private:
	bool CreateScreenSender();
	void ReleaseSender();
    
	bool StartVideo();
	bool StopVideo();
    
    bool StartAudio();
    bool StopAudio();
public:
    bool IsOpenVideo() const{return m_IsOpenVideo;};
    bool IsOpenAudio() const{return m_IsOpenAudio;};
    bool IsSendVideoData() const{return m_IsSendVideoData;};
    bool IsSendAudioData() const{return m_IsSendAudioData;};
private:
    void ProcessVideoFrame(char*pData, int nLen, bool bKeyFrame, unsigned long ulTimestamp, int nWidth, int nHeight);
public:
    void ProcessAudioFrame(char*pData, int nLen, unsigned long ulTimestamp);
    unsigned long TimeGetTimestamp();
private:
	NETEC_MediaSender*		m_pMediaSender;
	unsigned long           m_ulLocalVideoID ;			//VideoID
	unsigned long           m_ulLocalAudioID ;			//AudioID
    AudioCapture*           m_pAudioCapture;
//    VideoCapture*           m_pVideoCapture;
     CameraCapture *        m_CameraCapture;
 
private:
	bool m_bGotKeyFrameMain;
	char* m_pVideoPacket;
	int	m_nFrameBufferLength;
	unsigned short m_usVideoSequence;
    
    char* m_pAudioPacket;
    int m_nAudioFrameBufferLength;
    unsigned short m_usAudioSequence;
    unsigned long m_ulLastFrameTimestamp;
    unsigned long m_ulLastPacketTimestamp;
    
    bool m_IsOpenVideo;
    bool m_IsOpenAudio;
    bool m_IsSendVideoData;
    bool m_IsSendAudioData;
private:
    std::string             m_MediaServerIp;
    unsigned int            m_uiPort;
    void*                   m_pVideoView;
    std::string             m_strUserID;
    OPENMEUSERLIST          m_OpenMeVideoUserList;
    OPENMEUSERLIST          m_OpenMeAudioUserList;
};

#endif
