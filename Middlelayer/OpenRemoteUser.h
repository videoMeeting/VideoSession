//
//  OpenRemoteUser.h
//  VideoSession
//
//  Created by wang guijun on 13-2-7.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#ifndef __VideoSession__OpenRemoteUser__
#define __VideoSession__OpenRemoteUser__

#include <iostream>
#include "./NETEC/NETEC_MediaReceiver.h"
#include "AudioLibrary/AudioLibrary.h"
#include "VideoLibrary/VideoLibrary.h"
#import  "ReceiveAndPlayOpenAl.h"
#include "LoginServer.h"

class OpenRemoteUser
: public NETEC_MediaReceiverCallback
{
public:
    OpenRemoteUser();
    ~OpenRemoteUser();
public:
    bool ConnectMediaServer(std::string strServerIp, unsigned int uiPort);
    void ReleaseMediaSever();
    
    bool StartPeerVideoData(std::string strUserID, unsigned long ulUserVideoId);
    void StopPeerVideoData();
    
    bool StartPeerAudioData(std::string strUserID, unsigned long ulUserAudioId);
    void StopPeerAudioData();
    
    bool StartDisplayVideo();
    void StopDisplayVideo();
public:
    bool OpenVideo(void* pView, unsigned int uiWidth = 640, unsigned int uiHeight = 480);
    void CloseVideo();
    
    bool OpenAudio(int type);
    void CloseAudio();
public:
    bool IsOpenVideo() const{return m_IsOpenVideo;};
    bool IsOpenAudio() const{return m_IsOpenAudio;};
    
    bool IsStartReceiverVideo() const{return m_IsReceiverVideo;};
    bool IsStartReceiverAudio() const{return m_IsReceiverAudio;};
    
    const std::string GetPeerUserVideoID() const{return m_PeerUserVideoID;};
    const std::string GetPeerUserAudioID() const{return m_PeerUserAudioID;};
public:
	virtual void OnNETEC_MediaReceiverCallbackAudioPacket(unsigned char*pData,int nLen);
	virtual void OnNETEC_MediaReceiverCallbackVideoPacket(unsigned char*pData,int nLen);
private:
	bool CreateScreenReceiver();
	bool StartVideoReceiver();
	bool StopVideoReceiver();
    bool StartAudioReceiver();
    bool StopAudioReceiver();
	void ReleaseReceiver();
private:
	NETEC_MediaReceiver*	m_pMediaReceiver;
    VideoPalyback*          m_pVideoPalyback;
    //ReceiveAndPlayOpenAl*   m_receiveAndPlayOpenAl;
    char*                   m_pAudioPacketBeffer;
    char*                   m_pVideoPacketBeffer;
    unsigned long           m_pVideoPacketLen;
    unsigned long           m_pVideoPacketBefferSeek;
    unsigned int            m_iVideoBefferState;
    unsigned int            m_iCount;
    Audioplayback*          m_pAudioplayback;
	unsigned long           m_ulPeerVideoID ;			//VideoID
	unsigned long           m_ulPeerAudioID ;			//AudioID
	std::string             m_peer_nodeid;
	std::string             m_peer_nataddr;/*∂‘∑ΩNATµÿ÷∑*/
	std::string             m_peer_locaddr;/*∂‘∑Ω±æµÿµÿ÷∑*/
	int                     m_peer_locport;/*∂‘∑Ω±æµÿ∂Àø⁄*/
	std::string	            m_peer_mcuid;/*∂‘∑ΩMCUID*/
	std::string	            m_peer_mcuaddr;/*∂‘∑ΩMCUµÿ÷∑*/
	int		                m_peer_mcuport;/*∂‘∑ΩMCU∂Àø⁄*/
private:
    std::string             m_MediaServerIp;
    unsigned int            m_uiServerPort;
    void*                   m_pVideoView;
private:
    bool                    m_IsOpenVideo;
    bool                    m_IsOpenAudio;
    bool                    m_IsReceiverVideo;
    bool                    m_IsReceiverAudio;
    std::string             m_PeerUserVideoID;
    std::string             m_PeerUserAudioID;
};

#endif /* defined(__VideoSession__OpenRemoteUser__) */
