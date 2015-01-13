/**********************************************************
 * Name: TCPAcceptor.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include "TCPSocket.h"

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KTCPAcceptorEvent
{
public:
	KTCPAcceptorEvent(void){};
	virtual ~KTCPAcceptorEvent(void){};
	virtual void OnTCPAcceptorAccepted(SOCKET hSocket)=0;
};

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KTCPAcceptor : public KThread
{
public:
	KTCPAcceptor(KTCPAcceptorEvent& rTCPAcceptorEvent);
	virtual ~KTCPAcceptor(void);

	bool Create(const std::string& strLocalAddr,unsigned short usLocalPort);
	void Close(void);
	
protected:
	KTCPSocket			m_TCPSocket;
	KTCPAcceptorEvent&	m_rTCPAcceptorEvent;
	bool				m_bWantToStop;

	virtual void ThreadProcMain(void);
	virtual void OnAcceptConnection(SOCKET hSocket);
};
