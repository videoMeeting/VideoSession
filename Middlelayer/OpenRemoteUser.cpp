//
//  OpenRemoteUser.cpp
//  VideoSession
//
//  Created by wang guijun on 13-2-7.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#include "OpenRemoteUser.h"
#include <AUDEC/AUDEC_Header.h>
#include <AUDEC/AUDEC_CodecID.h>
#include "VIDEC/VIDEC_Header.h"
#include "AudioDefine.h"
#import "ReceiveAndPlayOpenAl.h"
#include "VideoAndAudioSet.h"

OpenRemoteUser::OpenRemoteUser()
: m_ulPeerVideoID(0)
, m_ulPeerAudioID(0)
, m_pMediaReceiver(NULL)
, m_MediaServerIp("")
, m_uiServerPort(0)
, m_pVideoView(NULL)
, m_pVideoPalyback(NULL)
, m_pAudioplayback(NULL)
//, m_receiveAndPlayOpenAl(nil)
, m_IsOpenVideo(false)
, m_IsOpenAudio(false)
, m_PeerUserVideoID("")
, m_PeerUserAudioID("")
, m_IsReceiverVideo(false)
, m_IsReceiverAudio(false)
, m_pAudioPacketBeffer(NULL)
, m_pVideoPacketBeffer(NULL)
, m_pVideoPacketLen(100)
, m_pVideoPacketBefferSeek(0)
, m_iVideoBefferState(0)
, m_iCount(0)
{
    m_pAudioPacketBeffer=(char*)malloc(65);
    memset(m_pAudioPacketBeffer, 0, 65);
    m_pVideoPalyback = CteateVideoplayback();
//#ifdef USER_SUBCONTRACTING
//    m_pVideoPacketBeffer=(char*)malloc(1000*m_pVideoPacketLen);
//    memset(m_pVideoPacketBeffer, 0, 1000*m_pVideoPacketLen);
//#endif
    
    //VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
    //m_pAudioplayback = CteateAudioplayback(p->GetSpeaker());
    //m_receiveAndPlayOpenAl = [[ReceiveAndPlayOpenAl alloc]init];
    //[m_receiveAndPlayOpenAl initOpenALMode:AMR_NBCODE];
}

OpenRemoteUser::~OpenRemoteUser()
{
    if(m_pVideoPalyback)
        ReleaseVideoplayback(m_pVideoPalyback);
    m_pVideoPalyback = NULL;
    
    LoginServer::OnGetLoginServer()->voe_manager()->DeleteChannel(m_ulPeerAudioID);
    
#if 0
    if(m_receiveAndPlayOpenAl)
    {
        [m_receiveAndPlayOpenAl CloseOpenAL];
        [m_receiveAndPlayOpenAl dealloc];
        m_receiveAndPlayOpenAl = nil;
    }
#endif
    if(m_pAudioPacketBeffer!=NULL)
    {
        free(m_pAudioPacketBeffer);
        m_pAudioPacketBeffer = NULL;
    }
    
#if 0
    if(m_pAudioplayback)
        ReleaseAudioplayback();
    m_pAudioplayback = NULL;
#endif
    
    m_IsOpenVideo = false;
    m_IsOpenAudio = false;
}

bool OpenRemoteUser::ConnectMediaServer(std::string strServerIp, unsigned int uiPort)
{
    m_MediaServerIp = strServerIp;
    m_uiServerPort = uiPort;
    m_peer_mcuid="MCU001";
    m_peer_mcuaddr=strServerIp;
    m_peer_nataddr=strServerIp;
    m_peer_locaddr=strServerIp;
    m_peer_mcuport=uiPort;
    m_peer_locport=uiPort;
    
    if(!CreateScreenReceiver())
        return false;
    
    return true;
}

void OpenRemoteUser::ReleaseMediaSever()
{
    ReleaseReceiver();
}

bool OpenRemoteUser::OpenVideo(void* pView, unsigned int uiWidth, unsigned int uiHeight)
{
    if(m_pVideoPalyback == NULL)
        return false;
    
    m_IsOpenVideo = true;
    m_pVideoPalyback->SetVideoWindow(pView);
    m_pVideoPalyback->SetResolution(uiWidth, uiHeight);
    m_pVideoPalyback->Start();
    return true;
}

void OpenRemoteUser::CloseVideo()
{
    m_IsOpenVideo = false;
    m_pVideoPalyback->Stop();
}

bool OpenRemoteUser::OpenAudio(int type)
{
    //if(m_receiveAndPlayOpenAl==nil)
    //    return false;
#if 0
    m_pAudioplayback->SetAudioDecodingMode(type);
    VideoAndAudioSet* p = VideoAndAudioSet::GetObject();
    m_pAudioplayback->Start(p->GetSpeaker());
#endif
    m_IsOpenAudio = true;
    return true;
}

void OpenRemoteUser::CloseAudio()
{
    //if(m_receiveAndPlayOpenAl==nil)
    //    return;

    m_IsOpenAudio = false;
#if 0
    m_pAudioplayback->Stop();
#endif
}

bool OpenRemoteUser::StartPeerVideoData(std::string strUserID, unsigned long ulUserVideoId)
{
    if(strUserID.empty() || ulUserVideoId==0)
        return false;
    
    m_ulPeerVideoID = ulUserVideoId;
    m_PeerUserVideoID = strUserID;
    
    if(!StartVideoReceiver())
        return false;
    m_IsReceiverVideo = true;
    
    return true;
}
void OpenRemoteUser::StopPeerVideoData()
{
    m_IsReceiverVideo = false;
    StopVideoReceiver();
    m_ulPeerVideoID = 0;
    m_PeerUserVideoID = "";
}

bool OpenRemoteUser::StartPeerAudioData(std::string strUserID, unsigned long ulUserAudioId)
{
    if(strUserID.empty() || ulUserAudioId==0)
    {
        assert(false);
        return false;
    }
    
    m_PeerUserAudioID = strUserID;
    m_ulPeerAudioID = ulUserAudioId;
    if(!StartAudioReceiver())
        return false;
    m_IsReceiverAudio = true;
    
    return true;
}
void OpenRemoteUser::StopPeerAudioData()
{
    m_IsReceiverAudio = false;
    StopAudioReceiver();
    m_PeerUserAudioID = "";
    m_ulPeerAudioID = 0;
}

bool OpenRemoteUser::StartDisplayVideo()
{
    if(m_pVideoPalyback == NULL)
        return false;
    m_IsReceiverVideo = true;
    return m_pVideoPalyback->StartDisplayVideo();
}

void OpenRemoteUser::StopDisplayVideo()
{
    if(m_pVideoPalyback == NULL)
        return ;
    m_IsReceiverVideo = false;
    m_pVideoPalyback->StopDisplayVideo();
}

bool OpenRemoteUser::CreateScreenReceiver()
{
	m_pMediaReceiver=NETEC_MediaReceiver::Create(*this);
	if (m_pMediaReceiver!=NULL)
	{
#if 1
		m_pMediaReceiver->SetLocalMCUID("MCU-001");
		m_pMediaReceiver->SetLocalMCIIP(m_MediaServerIp.c_str());
		m_pMediaReceiver->SetLocalMCUPort(m_uiServerPort);
#endif
		if (0!=m_pMediaReceiver->Open(m_peer_nodeid.c_str(), m_peer_nataddr.c_str(), m_peer_locaddr.c_str(), m_peer_locport, m_peer_mcuid.c_str(), m_peer_mcuaddr.c_str(), m_peer_mcuport))
		{
			m_pMediaReceiver->Close();
			delete m_pMediaReceiver;
			m_pMediaReceiver=NULL;
			return false;
		}
		return true;
	}
	return false;
}

bool OpenRemoteUser::StartVideoReceiver()
{
	if (m_pMediaReceiver==NULL || m_ulPeerVideoID==0)
	{
		return false;
	}
	if(0!=m_pMediaReceiver->SetVideoID(m_ulPeerVideoID))
		return false;
	if(0!=m_pMediaReceiver->StartVideo())
		return false;
	return true;
}

bool OpenRemoteUser::StopVideoReceiver()
{
	if (m_pMediaReceiver==NULL || m_ulPeerVideoID==0)
	{
		return false;
	}
	m_pMediaReceiver->StopVideo();
	return true;
}

bool OpenRemoteUser::StartAudioReceiver()
{
	if (m_pMediaReceiver==NULL || m_ulPeerAudioID==0)
	{
		return false;
	}
#if 1
      LoginServer::OnGetLoginServer()->voe_manager()->CreateChannel(m_ulPeerAudioID);
    
    if (LoginServer::OnGetLoginServer()->voe_manager()->StartReceive(m_ulPeerAudioID) != 0)
    {
        // LOGI("OpenRemoteUser::StartReceiveAudioData Start Audio Receiver Failed m_ulPeerVideoID:%u",m_ulPeerAudioID - 100);
        return false;
    }
    
    if(LoginServer::OnGetLoginServer()->voe_manager()->StartPlayout(m_ulPeerAudioID) != 0)
    {
        //LOGI("[OpenRemoteUser] StartPlayout() Failed m_ulPeerVideoID:%u",m_ulPeerAudioID - 100);
    }
#endif
    
#if 1
	if(0!=m_pMediaReceiver->SetAudioID(m_ulPeerAudioID))
		return false;
	if(0!=m_pMediaReceiver->StartAudio())
		return false;
#endif
	return true;
}

bool OpenRemoteUser::StopAudioReceiver()
{
	if (m_pMediaReceiver==NULL || m_ulPeerAudioID==0)
	{
		return false;
	}
    
    LoginServer::OnGetLoginServer()->voe_manager()->StopReceive(m_ulPeerAudioID);
    
    if(LoginServer::OnGetLoginServer()->voe_manager()->StopPlayout(m_ulPeerAudioID) != 0)
    {
        //LOGI("[OpenRemoteUser] StopPlayout() Failed");
    }
    
	m_pMediaReceiver->StopAudio();
	return true;
}

void OpenRemoteUser::ReleaseReceiver()
{
	if (m_pMediaReceiver!=NULL)
	{
		m_pMediaReceiver->Close();
		delete m_pMediaReceiver;
		m_pMediaReceiver=NULL;
	}
}

void OpenRemoteUser::OnNETEC_MediaReceiverCallbackAudioPacket(unsigned char*pData,int nLen)
{
    if(pData != NULL && nLen>8 &&m_IsReceiverAudio)
	{
        LoginServer::OnGetLoginServer()->voe_manager()->CallbackAudioPacket(m_ulPeerAudioID, pData, nLen);
#if 0
        int nHeaderSize=AUDEC_HEADER_GET_LEN(pData);
         //if(m_receiveAndPlayOpenAl)
         {
             memcpy((m_pAudioPacketBeffer+13*m_iCount),pData+nHeaderSize,nLen-nHeaderSize);
             
             m_iCount++;
             if(m_iCount==5)
             {
              //   [m_receiveAndPlayOpenAl openAlPaly:(char*)m_pAudioPacketBeffer size:65];
                 if(m_pAudioplayback)
                     m_pAudioplayback->AddAudioData((unsigned int)this,(unsigned char*)m_pAudioPacketBeffer, 65);
                 m_iCount = 0;
                 memset(m_pAudioPacketBeffer, 0, 65);
             }
             //receiveAndPlayOpenAl
         }
#endif
    }
}

void OpenRemoteUser::OnNETEC_MediaReceiverCallbackVideoPacket(unsigned char*pData,int nLen)
{
//#ifdef USER_SUBCONTRACTING
//    if(pData != NULL && nLen>16 && m_IsReceiverVideo)
//    {
//        int nHeaderLen=VIDEC_HEADER_EXT_GET_LEN(pData);
//        int nSubHeaderLen=VIDEC_KEY_SUBCONTRACTING_GET_LEN(pData+nHeaderLen);
//        
//        unsigned short isBeging = VIDEC_KEY_SUBCONTRACTING_GET_BEGING(pData+nHeaderLen);
//        unsigned short isEnd = VIDEC_KEY_SUBCONTRACTING_GET_END(pData+nHeaderLen);
//        
//        if(isBeging == 1 && isEnd == 1)
//        {
//            if(m_pVideoPalyback)
//                m_pVideoPalyback->AddVideoData(pData+(nHeaderLen+nSubHeaderLen), nLen-(nHeaderLen+nSubHeaderLen));
//            return;
//        }
//        
//        if(isBeging == 1 && isEnd == 0 && m_iVideoBefferState == 0)
//        {
//            memcpy(m_pVideoPacketBeffer + m_pVideoPacketBefferSeek, pData+(nHeaderLen+nSubHeaderLen), nLen-(nHeaderLen+nSubHeaderLen));
//            m_pVideoPacketBefferSeek += (nLen-(nHeaderLen+nSubHeaderLen));
//            m_iVideoBefferState = 1;
//        }
//        else if(isBeging == 0 && isEnd == 0 && m_iVideoBefferState == 1)
//        {
//            memcpy(m_pVideoPacketBeffer + m_pVideoPacketBefferSeek, pData+(nHeaderLen+nSubHeaderLen), nLen-(nHeaderLen+nSubHeaderLen));
//            m_pVideoPacketBefferSeek += (nLen-(nHeaderLen+nSubHeaderLen));
//        }
//        else if(isBeging == 0 && isEnd == 1 && m_iVideoBefferState == 1)
//        {
//            memcpy(m_pVideoPacketBeffer + m_pVideoPacketBefferSeek, pData+(nHeaderLen+nSubHeaderLen), nLen-(nHeaderLen+nSubHeaderLen));
//            if(m_pVideoPalyback)
//                m_pVideoPalyback->AddVideoData((unsigned char*)m_pVideoPacketBeffer, m_pVideoPacketBefferSeek);
//            m_pVideoPacketBefferSeek = 0;
//            m_iVideoBefferState = 0;
//        }
//        else
//            assert(0);
//    }
//#else
    if(pData != NULL && nLen>16 && m_IsReceiverVideo)
    {
        int nHeaderLen=VIDEC_HEADER_EXT_GET_LEN(pData);
        
        if(m_pVideoPalyback)
            m_pVideoPalyback->AddVideoData(pData+nHeaderLen, nLen-nHeaderLen);
    }
//#endif
}
