//NETEC_App.h
#ifndef __NETEC_APP_H__
#define __NETEC_APP_H__

#include <NETEC/NETEC_Export.h>

#include <NETEC/NETEC_TCPIO.h>
#include <NETEC/NETEC_UDPIO.h>

class NETEC_API NETEC_App
{
public:
	NETEC_App(unsigned long ulAppType);
	virtual~NETEC_App(void);
public:
	virtual int Open(void);
	virtual void Close(void);

	virtual unsigned long GetAppType(void);

	virtual int OnNETEC_TCPIONotifyConnected(unsigned long ulType,const void*pData,int nLen,SOCKET hSocket);
	virtual int OnNETEC_UDPIONotifyRecvdPacket(XPacketUDP*pXPacketUDP);
protected:
	unsigned long	m_ulAppType;
};


#endif