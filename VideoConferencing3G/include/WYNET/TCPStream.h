#pragma once

#include "TCPSocket.h"

#define MAX_TCP_BUFFER_SIZE_READ	16400

//---------------------------------------------------------------------------------------
// TCP流类定义
class AFX_EXT_CLASS KTCPStream : public KThread
{
public:
	KTCPStream(void);
	virtual ~KTCPStream(void);

	virtual bool Connect(const char* cszServerAddr,unsigned short usServerPort,const char* cszLocalAddr="",unsigned short usLocalPort=0);
	virtual void Disconnect(void);

	virtual void SendData(char* pData,int nLen);
	virtual SOCKET GetSocketHandle(void);

	virtual void OnConnected(void)=0;
	virtual void OnReceivedData(char* pData,int nLen)=0;
	virtual void OnDisconnected(void)=0;

protected:
	KTCPSocket			m_TCPSocket;

	char				m_szServerAddr[64];
	unsigned short		m_usServerPort;
	char				m_szLocalAddr[64];
	unsigned short		m_usLocalPort;
	bool				m_bWantToStop;

	void ThreadProcMain(void);
};
