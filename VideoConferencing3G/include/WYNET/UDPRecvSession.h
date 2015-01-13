/**********************************************************
 * Name: UDPRecvSession.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-11-22
 **********************************************************/

#pragma once

//---------------------------------------------------------------------------------------
// UDP接收Session事件接口类
class AFX_EXT_CLASS IUDPRecvSessionEvent
{
public:
	IUDPRecvSessionEvent(void){};
	virtual ~IUDPRecvSessionEvent(void){};

public:
	virtual void OnReceivedData(char* pData,int nLen)=0;
	virtual void OnSendAckData(char* pData,int nLen)=0;
};

//---------------------------------------------------------------------------------------
// UDP接收Session接口类
class AFX_EXT_CLASS IUDPRecvSession
{
public:
	IUDPRecvSession(void){};
	virtual ~IUDPRecvSession(void){};

public:
	virtual bool Create(void)=0;
	virtual void Close(void)=0;
	virtual void OnRecvData(char* pData,int nLen)=0;
};

AFX_EXT_CLASS IUDPRecvSession* CreateUDPRecvSession(IUDPRecvSessionEvent& rUDPRecvSessionEvent);

#include "UDPRecvBuffer.h"

////---------------------------------------------------------------------------------------
//class KUDPRecvSession : public IUDPRecvSession
//                      , public KThread
//{
//public:
//	KUDPRecvSession(IUDPRecvSessionEvent& rUDPRecvSessionEvent);
//	virtual ~KUDPRecvSession(void);
//
//public:
//	virtual bool Create(void);
//	virtual void Close(void);
//	virtual void OnRecvData(char* pData,int nLen);
//	virtual void OnRecvFrame(char* pData,int nLen);
//
//protected:
//	IUDPRecvSessionEvent& m_rUDPRecvSessionEvent;
//	virtual void ThreadProcMain(void);
//
//private:
//	bool			m_bWantToStop;
//	KCritSec		m_secWinPacketPool;
//	KList			m_lstWinPacketPool;
//	KUDPRecvBuffer*	m_pUDPRecvBuffer;
//	unsigned long	m_ulNextSentSequence;
//};
