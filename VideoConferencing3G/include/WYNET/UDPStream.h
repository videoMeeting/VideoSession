#pragma once

#include "UDPSocket.h"
#include "UDPPacket.h"

#define MAX_UDP_BUFFER_SIZE_READ	1024

//---------------------------------------------------------------------------------------
// UDP流类定义
class AFX_EXT_CLASS KUDPStream : public KThread
{
public:
	KUDPStream(void);
	virtual ~KUDPStream(void);

	virtual bool Create(const char* cszLocalAddr,unsigned short usLocalPort);
	virtual void Close(void);
	virtual bool Connect(const char* cszRemoteAddr,unsigned short usRemotePort);

	virtual void SendPacket(KUDPOutPacket& OutPacket);
	virtual void OnReceivedData(KUDPInPacket& InPacket)=0;

protected:
	KUDPSocket			m_UDPSocket;
	bool				m_bWantToStop;
	void ThreadProcMain(void);
};
