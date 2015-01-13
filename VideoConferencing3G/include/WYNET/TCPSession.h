/**********************************************************
 * Name: KTCPSession.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include "TCPSocket.h"
#include "EventHandler.h"

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KTCPSessionEvent
{
public:
	KTCPSessionEvent(){};
	virtual ~KTCPSessionEvent(void){};

	virtual void OnTCPSessionReceived(char* pData,int nLen){};
	virtual void OnTCPSessionDisconnected(void){};
};

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KTCPSession : public KEventHandler
{
public:
	KTCPSession(KTCPSessionEvent& rTCPSessionEvent,SOCKET hSocket);
	virtual ~KTCPSession(void);

	virtual bool IsDisconnected(void);
	virtual void SendData(char* pData,int nLen);
	virtual void ProcessRecvData(void);

protected:
	KTCPSocket			m_TCPSocket;
	KTCPSessionEvent&	m_rTCPSessionEvent;
	KBufferPool			m_SendBufferPool;	
	KBufferPool			m_RecvBufferPool;

	virtual void OnRead(void);
	virtual void OnWrite(void);
	virtual void OnExcept(void);

private:
	bool m_bDisconnected;
};
