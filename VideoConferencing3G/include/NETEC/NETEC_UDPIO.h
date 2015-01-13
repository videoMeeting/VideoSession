//NETEC_UDPIO.h
#ifndef __NETEC_UDPIO_H__
#define __NETEC_UDPIO_H__

#include <NETEC/XSocket.h>
#include <NETEC/XPacketUDP.h>

class NETEC_UDPIONotify
{
public:
	NETEC_UDPIONotify(void){};
	virtual~NETEC_UDPIONotify(void){};
public:
	virtual bool OnNETEC_UDPIONotifyRecvdPacket(XPacketUDP*pXPacketUDP)=0;
};

class NETEC_UDPIO
{
public:
	NETEC_UDPIO(void){};
	virtual~NETEC_UDPIO(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual SOCKET GetSocketHandle(unsigned long ulIP)=0;
	virtual unsigned short GetUDPPort(void)=0;
	virtual int GetSocketHandleCount(void)=0;
	virtual SOCKET GetSocketHandleByIndex(int nIndex)=0;
};

NETEC_UDPIO*NETEC_UDPIOCreate(NETEC_UDPIONotify&rNETEC_UDPIONotify,unsigned short usUDPPort,unsigned char nTos=160);


#endif