//NETEC_RTPSession.h
#ifndef __NETEC_RTPSESSION_H__
#define __NETEC_RTPSESSION_H__

#include "NETEC_Export.h"

class NETEC_API NETEC_RTPSession;
class NETEC_RTPSessionCallback
{
public:
	NETEC_RTPSessionCallback(void){};
	virtual~NETEC_RTPSessionCallback(void){};
public:
	virtual void OnNETEC_RTPSessionCallbackRecvdRTPPacket(NETEC_RTPSession*pRTPSession,unsigned char*pRTPPacketData,int nRTPPacketLen)=0;
};

class NETEC_API NETEC_RTPSession
{
public:
	NETEC_RTPSession(void){};
	virtual~NETEC_RTPSession(void){};
public:
	virtual int Open(const char*cszLocalIP,unsigned short&usLocalPort,const char*cszRemoteIP,unsigned short usRemotePort)=0;
	virtual void Close(void)=0;

	virtual int Send(unsigned char*pRTPPacketData,int nRTPPacketLen)=0;

	static NETEC_RTPSession*Create(NETEC_RTPSessionCallback&rCallback);
};

#endif
