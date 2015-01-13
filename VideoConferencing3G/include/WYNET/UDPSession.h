/**********************************************************
 * Name: UDPSession.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-11-21
 **********************************************************/

#pragma once

#include "UDPSendBuffer.h"
#include "UDPRecvBuffer.h"
#include "UDPSocket.h"

////---------------------------------------------------------------------------------------
//// UDP发送Session事件类
//class AFX_EXT_CLASS KUDPSessionEvent
//{
//public:
//	KUDPSessionEvent(void);
//	virtual ~KUDPSessionEvent(void);
//
//public:
//	///* 接受数据:收到 */
//	//virtual void OnUDPSessionReceivedData(char* pData,int nLen)=0;
//
//	///* 收到错误 */
//	//virtual void OnUDPSessionNetworkError(int nErrCode)=0;
//};

////---------------------------------------------------------------------------------------
//// UDP发送Session类
//class AFX_EXT_CLASS KUDPSession : public KThread
//{
//public:
//	KUDPSession(KUDPSessionEvent& rUDPSessionEvent);
//	virtual ~KUDPSession(void);
//
//public:
//	/* 创建SESSION */
//	bool Create(const std::string& strLocalAddr,unsigned short usLocalPort,const std::string& strRemoteAddr,unsigned short usRemotePort);
//
//	/* 关闭SESSION */
//	void Close(void);
//
//	/* 发送数据 */
//	void SendData(char* pData,int nLen);
//
//	/* 直接发送数据 */
//	int SendDataToNetwork(char* pData,int nLen);
//
//protected:
//	KUDPSessionEvent&	m_rUDPSessionEvent;
//	KUDPSocket			m_UDPSocket;
//	std::string			m_strRemoteAddr;
//	unsigned short		m_usRemotePort;
//	KUDPSendBuffer*		m_pUDPSendBuffer;
//	KUDPRecvBuffer*		m_pUDPRecvBuffer;
//	bool				m_bWantToStop;
//
//	virtual void ThreadProcMain(void);
//
//private:
//	unsigned long		m_ulPacketSequence;
//};
