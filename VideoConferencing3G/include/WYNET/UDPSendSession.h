/**********************************************************
 * Name: UDPSendSession.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-11-21
 **********************************************************/

#pragma once

////---------------------------------------------------------------------------------------
//// UDP发送Session事件接口类
//class AFX_EXT_CLASS IUDPSendSessionEvent
//{
//public:
//	IUDPSendSessionEvent(void){};
//	virtual ~IUDPSendSessionEvent(void){};
//
//public:
//	virtual void OnSendData(char* pData,int nLen)=0;
//};
//
////---------------------------------------------------------------------------------------
//// UDP发送Session接口类
//class AFX_EXT_CLASS IUDPSendSession
//{
//public:
//	IUDPSendSession(void){};
//	virtual ~IUDPSendSession(void){};
//
//public:
//	virtual bool Create(void)=0;
//	virtual void Close(void)=0;
//	virtual bool SendData(char* pData,int nLen)=0;
//	virtual void OnReceivedAckData(char* pData,int nLen)=0;
//
//	virtual void SetWindowSize(int nWindowSize)=0;
//	virtual int GetWindowSize(void)=0;
//};
//
//AFX_EXT_CLASS IUDPSendSession* CreateUDPSendSession(IUDPSendSessionEvent& rUDPSendSessionEvent);
//
//#include "UDPSendBuffer.h"
//
////---------------------------------------------------------------------------------------
//// UDP发送Session类
//class AFX_EXT_CLASS KUDPSendSession : public IUDPSendSession
//                                    , public KThread
//{
//public:
//	KUDPSendSession(IUDPSendSessionEvent& rUDPSendSessionEvent);
//	virtual ~KUDPSendSession(void);
//
//public:
//	virtual bool Create(void);
//	virtual void Close(void);
//
//	virtual bool SendData(char* pData,int nLen);
//	virtual void OnReceivedAckData(char* pData,int nLen);
//
//	virtual void SetWindowSize(int nWindowSize);
//	virtual int GetWindowSize(void);
//
//	void OnSendData(char* pData,int nLen);
//
//protected:
//	IUDPSendSessionEvent& m_rUDPSendSessionEvent;
//	KUDPSendBuffer*	m_pUDPSendBuffer;
//	virtual void ThreadProcMain(void);
//	bool ProcessSplitPacket(void);
//
//private:
//	unsigned short	m_usPacketSequence;
//	bool			m_bWantToStop;
//	int		    	m_nWindowSize;
//	KCritSec		m_secRawPacketPool;
//	KList			m_lstRawPacketPool;
//};
