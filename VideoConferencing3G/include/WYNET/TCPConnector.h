/**********************************************************
 * Name: TCPConnector.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include "TCPSocket.h"

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KTCPConnectorEvent
{
public:
	KTCPConnectorEvent(void){};
	virtual ~KTCPConnectorEvent(void){};

	/* 连接成功事件 */
	virtual void OnTCPConnectorConnected(SOCKET hSocket){};

	/* 连接断开事件 */
	virtual void OnTCPConnectorDisconnected(void){};
};

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KTCPConnector : public KThread
{
public:
	KTCPConnector(KTCPConnectorEvent& rTCPConnectorEvent);
	virtual ~KTCPConnector(void);

	virtual bool Connect(const std::string& strRemoteHost,unsigned short usRemotePort);
	virtual void Disconnect(void);

protected:
	KTCPSocket			m_TCPSocket;
	KTCPConnectorEvent&	m_rTCPConnectorEvent;
	bool				m_bWantToStop;
	std::string			m_strRemoteAddr;
	unsigned short		m_usRemotePort;

	virtual void ThreadProcMain(void);
};
