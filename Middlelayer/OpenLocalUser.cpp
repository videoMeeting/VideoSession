//
//  OpenLocalUser.cpp
//  VideoSession
//
//  Created by wang guijun on 13-2-7.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#include "OpenLocalUser.h"
#include <AUDEC/AUDEC_Header.h>
#include <AUDEC/AUDEC_CodecID.h>
#include "VIDEC/VIDEC_Header.h"
#include "NETEC/NETEC_Setting.h"
#include <sys/time.h>
#import "CameraCapture.h"

typedef enum {
	VIDEC_CODEC_H261=0,		//unsupport
	VIDEC_CODEC_H263,
	VIDEC_CODEC_H263P,
	VIDEC_CODEC_H263PP,		//same to H263P
	VIDEC_CODEC_H264,
	VIDEC_CODEC_LSCC,		//unsupport
	VIDEC_CODEC_AH400,
	VIDEC_CODEC_MPEG4,		//unsupport
	VIDEC_CODEC_DH264,
	VIDEC_CODEC_HIKH,
	VIDEC_CODEC_H264_SVC,
	VIDEC_CODEC_HIKC,
	VIDEC_CODEC_COUNT
}VIDEC_CODEC_TYPE;


OpenLocalUser* OpenLocalUser::GetObject()
{
    OpenLocalUser* p = new OpenLocalUser;
    return p;
}

void OpenLocalUser::ReleaseObject(OpenLocalUser*& p)
{
    if(p)
        delete p;
    p = NULL;
}

OpenLocalUser::OpenLocalUser()
: m_ulLocalVideoID(0)
, m_ulLocalAudioID(0)
, m_pMediaSender(NULL)
, m_bGotKeyFrameMain(false)
, m_pVideoPacket(NULL)
#ifdef USER_SUBCONTRACTING
, m_nFrameBufferLength(1024)
#else
, m_nFrameBufferLength(0)
#endif
, m_pAudioPacket(NULL)
, m_nAudioFrameBufferLength(0)
, m_usAudioSequence(0)
, m_ulLastFrameTimestamp(0)
, m_ulLastPacketTimestamp(0)
, m_MediaServerIp("")
, m_uiPort(0)
, m_pVideoView(NULL)
, m_strUserID("")
, m_pAudioCapture(NULL)
, m_CameraCapture(NULL)
, m_IsSendVideoData(false)
, m_IsSendAudioData(false)
, m_IsOpenVideo(false)
, m_IsOpenAudio(false)
, m_pH264RTPFrame(NULL)
{
    NETEC_Setting::SetVideoProtocolType(NETEC_Setting::PT_TCP);
    NETEC_Setting::SetAudioProtocolType(NETEC_Setting::PT_TCP);
    //m_pAudioCapture = CteateAudioCapture(this);
//    m_pVideoCapture = CteateVideoCapture(this);
//      m_CameraCapture  = [CameraCapture shareCameraCapture];
#ifdef USER_SUBCONTRACTING
    m_pVideoPacket=(char*)malloc(m_nFrameBufferLength);
    if (m_pVideoPacket==NULL)
    {
        m_nFrameBufferLength=0;
    }
#endif
    m_pH264RTPFrame = new H264RTPFrame(*this);
    m_pH264RTPFrame->Open(97, 1100);
}

OpenLocalUser::~OpenLocalUser()
{
#if 0
    if(m_pAudioCapture)
        ReleaseAudioCapture();
    m_pAudioCapture = NULL;
#endif
    
    if(m_pH264RTPFrame)
    {
        m_pH264RTPFrame->Close();
        delete m_pH264RTPFrame;
    }
    
//    if(m_pVideoCapture)
//        ReleaseVideoCapture();
//    m_pVideoCapture = NULL;
    
    m_IsSendVideoData = false;
    m_IsSendAudioData = false;
    m_IsOpenVideo = false;
    m_IsOpenAudio = false;
}

bool OpenLocalUser::ConnectMediaServer(std::string strServerIp, unsigned int uiPort)
{
    m_MediaServerIp = strServerIp;
    m_uiPort = uiPort;
    if(!CreateScreenSender())
        return false;
    
    return true;
}

void OpenLocalUser::ReleaseMediaSever()
{
    ReleaseSender();
}

bool OpenLocalUser::OpenVideo(void* pView, unsigned long ulUserVideoId, unsigned int niWidth, unsigned int niHeight, unsigned int uiBitrate, unsigned int uiFramerate)
{
    if( ulUserVideoId == 0)
        return false;//m_pVideoCapture == NULL ||
    
    m_ulLocalVideoID = ulUserVideoId;
    m_IsOpenVideo = true;
    [[CameraCapture shareCameraCapture]setOpenLocalUser:this];
    [[CameraCapture shareCameraCapture]startup];
    AVCaptureVideoPreviewLayer* preview = [[CameraCapture shareCameraCapture] getPreviewLayer];
    [preview removeFromSuperlayer];
    
    preview.frame = ((UIView*)pView).bounds;
    [[preview connection] setVideoOrientation:UIInterfaceOrientationPortrait];
    
    [((UIView*)pView).layer addSublayer:preview];
//    m_pVideoCapture->SetLocalVideoWindow(pView);
//    m_pVideoCapture->SetResolution(niWidth, niHeight);
//    m_pVideoCapture->SetBitRate(uiBitrate);
//    m_pVideoCapture->SetVideoFps(uiFramerate);
//    m_pVideoCapture->StartCapture();
//    m_pVideoCapture->StartEncoding();
    return true;
}

bool OpenLocalUser::setVideoWindow(UIView*preview)
{
//    m_pVideoCapture->setPreview(preview);
    return  YES;
}

void OpenLocalUser::SetFrontAndRearCamera(bool isFront)
{
//    if(m_pVideoCapture == NULL)
//        return;
//    m_pVideoCapture->SetFrontAndRearCamera(isFront);
}

bool OpenLocalUser::SendVideoData()
{
    if(!StartVideo())
        return false;
    m_IsSendVideoData = true;
//    m_pVideoCapture->StartEncodingData();
    return true;
}

void OpenLocalUser::StopSendVideoData()
{
//    if(m_pVideoCapture == NULL)
//        return;
    m_IsSendVideoData = false;
//    m_pVideoCapture->StopEncodeingData();
        [[CameraCapture shareCameraCapture] shutdown];
    StopVideo();
}

void OpenLocalUser::CloseVideo()
{
//    if(m_pVideoCapture == NULL)
//        return;
    [[CameraCapture shareCameraCapture]shutdown];
//    m_IsOpenVideo = false;
//    m_pVideoCapture->StopCapture();
//    m_pVideoCapture->StopEncoding();
    StopVideo();
}

bool OpenLocalUser::OpenAudio(unsigned long ulUserAudioId, unsigned int uiAudioType)
{
    if(ulUserAudioId == 0)
        return false;
    
    m_ulLocalAudioID = ulUserAudioId;
    
    if(!StartAudio())
    {
        m_IsOpenAudio = true;
        return false;
    }
    m_IsOpenAudio = true;
    m_pAudioPacket = NULL;
#if 0
    m_pAudioCapture->SetAudioEncodingMode(uiAudioType);
    m_pAudioCapture->Start();
#endif
    return true;
}

void OpenLocalUser::On_MediaReceiverCallbackAudio(unsigned char*pData,int nLen)
{
    if(pData==NULL || nLen<=0)
        return;
    
    if(m_IsSendAudioData)
        ProcessAudioFrame((char*)pData, nLen, TimeGetTimestamp());
}

void OpenLocalUser::On_MediaReceiverCallbackVideo(unsigned char*pData,int nLen, bool bKeyFrame, int nWidth, int nHeight)
{
    if(pData==NULL || nLen<=0 )
        return;
    //if(m_IsSendVideoData)
//    {
//        if(m_pH264RTPFrame)
//            m_pH264RTPFrame->SendFrame(pData, nLen, nWidth, nHeight, bKeyFrame, TimeGetTimestamp(), bKeyFrame);
//    }
   ProcessVideoFrame((char*)pData, nLen, bKeyFrame, TimeGetTimestamp(), nWidth, nHeight);
}

void OpenLocalUser::OnBaseRTPFrameCallbackRTPPacket(void*pPacketData,int nPacketLen)
{
    ProcessVideoFrame((char*)pPacketData, nPacketLen, true, TimeGetTimestamp(), 320, 240);
}

void OpenLocalUser::OnBaseRTPFrameCallbackFramePacket(void*pPacketData,int nPacketLen)
{
    
}

bool OpenLocalUser::SendAudioData()
{
    LoginServer::OnGetLoginServer()->voe_manager()->StartSendAudio();
    m_IsSendAudioData = true;
    return true;
}

void OpenLocalUser::StopSendAudioData()
{
    LoginServer::OnGetLoginServer()->voe_manager()->StopSendAudio();
    m_IsSendAudioData = false;
}

void OpenLocalUser::CloseAudio()
{
#if 0
    if(m_pAudioCapture != NULL)
        m_pAudioCapture->Stop();
#endif
    m_IsOpenAudio = false;
    StopAudio();
    if(m_pAudioPacket!=NULL)
        free(m_pAudioPacket);
    m_pAudioPacket = NULL;
}

bool OpenLocalUser::CreateScreenSender()
{
	m_pMediaSender=NETEC_MediaSender::Create(*this);
	if (m_pMediaSender!=NULL)
	{
#if 1
		m_pMediaSender->SetLocalMCUID("MCU-001");
		m_pMediaSender->SetLocalMCIIP(m_MediaServerIp.c_str());
		m_pMediaSender->SetLocalMCUPort(m_uiPort);
		//m_pMediaSender->SetConnectStatus(m_ConnectStatus);
#endif
		if (0!=m_pMediaSender->Open())
		{
			m_pMediaSender->Close();
			delete m_pMediaSender;
			m_pMediaSender=NULL;
            
			return false;
		}
		return true;
	}
	return false;
}

bool OpenLocalUser::StartVideo()
{
    if(m_ulLocalVideoID == 0)
        return false;
    
	if (0!=m_pMediaSender->StartVideo(m_ulLocalVideoID))
	{
		return false;
	}
	return true;
}

bool OpenLocalUser::StopVideo()
{
	if (m_pMediaSender!=NULL)
	{
		m_pMediaSender->StopVideo();
		return true;
	}
	return false;
}

bool OpenLocalUser::StartAudio()
{
    if(m_ulLocalAudioID == 0)
    {
        assert(false);
        return false;
    }
    // LoginServer::OnGetLoginServer()->voe_manager()->StartLocalAudio(m_ulLocalAudioID);
#if 1
    LoginServer::OnGetLoginServer()->voe_manager()->StartLocalAudio(this);
	if (0!=m_pMediaSender->StartAudio(m_ulLocalAudioID))
	{
		return false;
	}
#endif
	return true;
}

bool OpenLocalUser::StopAudio()
{
    //LoginServer::OnGetLoginServer()->voe_manager()->StopLocalAudio();
    //return true;
#if 1
	if (m_pMediaSender!=NULL)
	{
        LoginServer::OnGetLoginServer()->voe_manager()->StopLocalAudio();
		m_pMediaSender->StopAudio();
		return true;
	}
	return false;
#endif
}

void OpenLocalUser::ReleaseSender()
{
	if (m_pMediaSender!=NULL)
	{
		m_pMediaSender->Close();
		delete m_pMediaSender;
		m_pMediaSender=NULL;
	}
}

void OpenLocalUser::ProcessVideoFrame(char*pData, int nLen, bool bKeyFrame, unsigned long ulTimestamp, int nWidth, int nHeight)
{
#ifdef USER_SUBCONTRACTING
	if (m_nFrameBufferLength<1024 && !m_pVideoPacket && !pData && nLen <= 0)
	{
        return;
	}
    
	if (m_bGotKeyFrameMain==false && bKeyFrame && m_pVideoPacket)
	{
		m_bGotKeyFrameMain=true;
	}
    
	if (m_bGotKeyFrameMain && m_pVideoPacket)
	{
        
        if(nLen < 1000)
        {
            VIDEC_HEADER_EXT_RESET(m_pVideoPacket);
            VIDEC_HEADER_EXT_SET_CODEC_ID(m_pVideoPacket,VIDEC_CODEC_H264);
            VIDEC_HEADER_EXT_SET_DOUBLE_FIELD(m_pVideoPacket,0);
            VIDEC_HEADER_EXT_SET_KEYFRAME(m_pVideoPacket,(bKeyFrame?1:0));
            VIDEC_HEADER_EXT_SET_SEQUENCE(m_pVideoPacket,m_usVideoSequence++);
            VIDEC_HEADER_EXT_SET_TIMESTAMP(m_pVideoPacket,ulTimestamp);
            
            if (bKeyFrame)
            {
                VIDEC_HEADER_EXT_SET_ACTUAL_WIDTH(m_pVideoPacket,nWidth);
                VIDEC_HEADER_EXT_SET_ACTUAL_HEIGHT(m_pVideoPacket,nHeight);
                VIDEC_HEADER_EXT_SET_VIRTUAL_WIDTH(m_pVideoPacket,nWidth);
                VIDEC_HEADER_EXT_SET_VIRTUAL_HEIGHT(m_pVideoPacket,nHeight);
            }
            
            int nHeaderLen=VIDEC_HEADER_EXT_GET_LEN(m_pVideoPacket);
            
            VIDEC_HEADER_EXT_SET_MAIN_FRAME(m_pVideoPacket,1);
            
            VIDEC_KEY_SUBCONTRACTING_RESET(m_pVideoPacket+nHeaderLen);
            VIDEC_KEY_SUBCONTRACTING_SET_BEGING(m_pVideoPacket+nHeaderLen,1);
            VIDEC_KEY_SUBCONTRACTING_SET_END(m_pVideoPacket+nHeaderLen,1);
            
            int nSUBHeaderLen = VIDEC_KEY_SUBCONTRACTING_GET_LEN(m_pVideoPacket+nHeaderLen);
            
            memcpy(m_pVideoPacket+(nHeaderLen+nSUBHeaderLen),pData,nLen);
            m_pMediaSender->SendVideo((unsigned char *)m_pVideoPacket, nLen+nHeaderLen+nSUBHeaderLen);
        }
        else
        {
            bool isbegin = true;
            int iLen = nLen;
            unsigned int uiVideoPacketSeek = 0;
            do
            {
                VIDEC_HEADER_EXT_RESET(m_pVideoPacket);
                VIDEC_HEADER_EXT_SET_CODEC_ID(m_pVideoPacket,VIDEC_CODEC_H264);
                VIDEC_HEADER_EXT_SET_DOUBLE_FIELD(m_pVideoPacket,0);
                VIDEC_HEADER_EXT_SET_KEYFRAME(m_pVideoPacket,(bKeyFrame?1:0));
                VIDEC_HEADER_EXT_SET_SEQUENCE(m_pVideoPacket,m_usVideoSequence++);
                VIDEC_HEADER_EXT_SET_TIMESTAMP(m_pVideoPacket,ulTimestamp);
                
                if (bKeyFrame)
                {
                    VIDEC_HEADER_EXT_SET_ACTUAL_WIDTH(m_pVideoPacket,nWidth);
                    VIDEC_HEADER_EXT_SET_ACTUAL_HEIGHT(m_pVideoPacket,nHeight);
                    VIDEC_HEADER_EXT_SET_VIRTUAL_WIDTH(m_pVideoPacket,nWidth);
                    VIDEC_HEADER_EXT_SET_VIRTUAL_HEIGHT(m_pVideoPacket,nHeight);
                }
                
                int nHeaderLen=VIDEC_HEADER_EXT_GET_LEN(m_pVideoPacket);
                
                VIDEC_HEADER_EXT_SET_MAIN_FRAME(m_pVideoPacket,1);
                
                VIDEC_KEY_SUBCONTRACTING_RESET(m_pVideoPacket+nHeaderLen);
                
                int nSUBHeaderLen = VIDEC_KEY_SUBCONTRACTING_GET_LEN(m_pVideoPacket+nHeaderLen);
                
                if(iLen > 1000)
                {
                    VIDEC_KEY_SUBCONTRACTING_SET_BEGING(m_pVideoPacket+nHeaderLen,isbegin?1:0);
                    VIDEC_KEY_SUBCONTRACTING_SET_END(m_pVideoPacket+nHeaderLen, 0);
                    
                    memcpy(m_pVideoPacket+(nHeaderLen+nSUBHeaderLen),pData + uiVideoPacketSeek,1000);
                    m_pMediaSender->SendVideo((unsigned char *)m_pVideoPacket, 1000+nHeaderLen+nSUBHeaderLen);
                    
                    iLen -= 1000;
                    uiVideoPacketSeek += 1000;
                }
                else
                {
                    VIDEC_KEY_SUBCONTRACTING_SET_BEGING(m_pVideoPacket+nHeaderLen,isbegin?1:0);
                    VIDEC_KEY_SUBCONTRACTING_SET_END(m_pVideoPacket+nHeaderLen,1);
                    
                    memcpy(m_pVideoPacket+(nHeaderLen+nSUBHeaderLen),pData + uiVideoPacketSeek,iLen);
                    m_pMediaSender->SendVideo((unsigned char *)m_pVideoPacket, iLen+nHeaderLen+nSUBHeaderLen);
                    
                    iLen -= iLen;
                }
                isbegin = false;
            }
            while( iLen > 0 );
        }
	}
#else
    
    if (m_nFrameBufferLength<nLen+1024)
	{
		m_nFrameBufferLength=nLen+2048;
		if (m_pVideoPacket)
		{
			free(m_pVideoPacket);
			m_pVideoPacket=NULL;
		}
		m_pVideoPacket=(char*)malloc(m_nFrameBufferLength);
		if (m_pVideoPacket==NULL)
		{
			m_nFrameBufferLength=0;
			return;
		}
	}
    
	if (m_bGotKeyFrameMain==false && bKeyFrame && m_pVideoPacket)
	{
		m_bGotKeyFrameMain=true;
	}
    
	if (m_bGotKeyFrameMain && m_pVideoPacket)
	{
		VIDEC_HEADER_EXT_RESET(m_pVideoPacket);
		VIDEC_HEADER_EXT_SET_CODEC_ID(m_pVideoPacket,VIDEC_CODEC_H264);
		VIDEC_HEADER_EXT_SET_DOUBLE_FIELD(m_pVideoPacket,0);
		VIDEC_HEADER_EXT_SET_KEYFRAME(m_pVideoPacket,(bKeyFrame?1:0));
		VIDEC_HEADER_EXT_SET_SEQUENCE(m_pVideoPacket,m_usVideoSequence++);
		VIDEC_HEADER_EXT_SET_TIMESTAMP(m_pVideoPacket,ulTimestamp);
		
		if (bKeyFrame)
		{
			VIDEC_HEADER_EXT_SET_ACTUAL_WIDTH(m_pVideoPacket,nWidth);
			VIDEC_HEADER_EXT_SET_ACTUAL_HEIGHT(m_pVideoPacket,nHeight);
			VIDEC_HEADER_EXT_SET_VIRTUAL_WIDTH(m_pVideoPacket,nWidth);
			VIDEC_HEADER_EXT_SET_VIRTUAL_HEIGHT(m_pVideoPacket,nHeight);
		}
        
		int nHeaderLen=VIDEC_HEADER_EXT_GET_LEN(m_pVideoPacket);
		
		memcpy(m_pVideoPacket+nHeaderLen,pData,nLen);
        
		VIDEC_HEADER_EXT_SET_MAIN_FRAME(m_pVideoPacket,1);
        
		m_pMediaSender->SendVideo((unsigned char *)m_pVideoPacket, nLen+nHeaderLen);
	}
#endif
}

void OpenLocalUser::ProcessAudioFrame(char*pData, int nLen, unsigned long ulTimestamp)
{
    if(m_pMediaSender!=NULL)
        m_pMediaSender->SendAudio((unsigned char*)pData, nLen);
    
#if 0
    if(!m_IsOpenAudio)
        return;
    
	if (m_nAudioFrameBufferLength<nLen+1024)
	{
		m_nAudioFrameBufferLength=nLen+2048;
		if (m_pAudioPacket)
		{
			free(m_pAudioPacket);
			m_pAudioPacket=NULL;
		}
		m_pAudioPacket=(char*)malloc(m_nAudioFrameBufferLength);
		if (m_pAudioPacket==NULL)
		{
			m_nAudioFrameBufferLength=0;
			return;
		}
	}
    
	if (m_pAudioPacket)
	{
		unsigned long ulCurTimestamp=TimeGetTimestamp();
		if (ulCurTimestamp-m_ulLastFrameTimestamp<120)
		{
			unsigned long ulDelta1=ulCurTimestamp-m_ulLastPacketTimestamp;
			unsigned long ulDelta2=m_ulLastPacketTimestamp-ulCurTimestamp;
			unsigned long ulDelta=(ulDelta1>ulDelta2?ulDelta2:ulDelta1);
			if (ulDelta==ulDelta2)
			{
				m_ulLastPacketTimestamp+=1;
			}
			else
			{
				m_ulLastPacketTimestamp=ulCurTimestamp;
			}
		}
		else
		{
			m_ulLastPacketTimestamp=ulCurTimestamp;
		}
		m_ulLastFrameTimestamp=ulCurTimestamp;
        
		AUDEC_HEADER_RESET(m_pAudioPacket);
		AUDEC_HEADER_SET_SEQUENCE(m_pAudioPacket, m_usAudioSequence++);
		AUDEC_HEADER_SET_TIMESTAMP(m_pAudioPacket, m_ulLastPacketTimestamp);
		AUDEC_HEADER_SET_CODEC_ID(m_pAudioPacket, X_AUDIO_CODEC_AMR_NB_475);
		int nHeaderSize=AUDEC_HEADER_GET_LEN(m_pAudioPacket);
		memcpy(m_pAudioPacket+nHeaderSize,pData,nLen);
        
        if(m_pMediaSender!=NULL)
            m_pMediaSender->SendAudio((unsigned char*)m_pAudioPacket, nHeaderSize+nLen);
	}
#endif
}

unsigned long OpenLocalUser::TimeGetTimestamp()
{
#ifdef WIN32
	return ::timeGetTime();
#else
	struct timeval now;
	gettimeofday(&now,NULL);
	return now.tv_sec*1000+now.tv_usec/1000;
#endif
}

bool OpenLocalUser::AddOpenMeVideoUser(std::string strUserID)
{
    m_OpenMeVideoUserList.push_back(strUserID);
    return true;
}

void OpenLocalUser::DeleteOpenMeVideoUser(std::string strUserID)
{
    OPENMEUSERLIST::iterator iter = m_OpenMeVideoUserList.begin();
    while(iter!=m_OpenMeVideoUserList.end())
    {
        if(*iter==strUserID)
        {
            iter = m_OpenMeVideoUserList.erase(iter);
        }
        else
            iter++;
    }
}

bool OpenLocalUser::AddOpenMeAudioUser(std::string strUserID)
{
    m_OpenMeAudioUserList.push_back(strUserID);
    return true;
}

void OpenLocalUser::DeleteOpenAudioUser(std::string strUserID)
{
    OPENMEUSERLIST::iterator iter = m_OpenMeAudioUserList.begin();
    while(iter!=m_OpenMeAudioUserList.end())
    {
        if(*iter == strUserID)
        {
            iter = m_OpenMeAudioUserList.erase(iter);
        }
        else
            iter++;
    }
}

unsigned int OpenLocalUser::OpenMeVideoCount()
{
    return m_OpenMeVideoUserList.size();
}
unsigned int OpenLocalUser::OpenMeAudioCount()
{
    return m_OpenMeAudioUserList.size();
}
