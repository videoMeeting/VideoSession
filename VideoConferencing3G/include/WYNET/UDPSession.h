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
//// UDP����Session�¼���
//class AFX_EXT_CLASS KUDPSessionEvent
//{
//public:
//	KUDPSessionEvent(void);
//	virtual ~KUDPSessionEvent(void);
//
//public:
//	///* ��������:�յ� */
//	//virtual void OnUDPSessionReceivedData(char* pData,int nLen)=0;
//
//	///* �յ����� */
//	//virtual void OnUDPSessionNetworkError(int nErrCode)=0;
//};

////---------------------------------------------------------------------------------------
//// UDP����Session��
//class AFX_EXT_CLASS KUDPSession : public KThread
//{
//public:
//	KUDPSession(KUDPSessionEvent& rUDPSessionEvent);
//	virtual ~KUDPSession(void);
//
//public:
//	/* ����SESSION */
//	bool Create(const std::string& strLocalAddr,unsigned short usLocalPort,const std::string& strRemoteAddr,unsigned short usRemotePort);
//
//	/* �ر�SESSION */
//	void Close(void);
//
//	/* �������� */
//	void SendData(char* pData,int nLen);
//
//	/* ֱ�ӷ������� */
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
