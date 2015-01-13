//NETEC_TCPIO.h
#ifndef __NETEC_TCPIO_H__
#define __NETEC_TCPIO_H__

#include <NETEC/XSocket.h>

class NETEC_TCPIONotify
{
public:
	NETEC_TCPIONotify(void){};
	virtual~NETEC_TCPIONotify(void){};
public:
	virtual bool OnNETEC_TCPIONotifyConnected(unsigned long ulType,const void*pData,int nLen,SOCKET hSocket)=0;
};

class NETEC_TCPIO
{
public:
	NETEC_TCPIO(void){};
	virtual~NETEC_TCPIO(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual unsigned short GetTCPPort(void)=0;
};

NETEC_TCPIO*NETEC_TCPIOCreate(NETEC_TCPIONotify&rNETEC_TCPIONotify,unsigned short usTCPPort);

#endif