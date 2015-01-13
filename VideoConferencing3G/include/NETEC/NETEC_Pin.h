//NETEC_Pin.h
#ifndef __NETEC_PIN_H__
#define __NETEC_PIN_H__

#include <NETEC/NETEC_Export.h>

class NETEC_PinCallback
{
public:
	NETEC_PinCallback(void){};
	virtual~NETEC_PinCallback(void){};
public:
	virtual void OnNETEC_PinCallbackRecvdData(const char*pData,int nLen)=0;
	virtual void OnNETEC_PinCallbackConnected(void)=0;
	virtual void OnNETEC_PinCallbackDisconnected(void)=0;
};

class NETEC_API NETEC_Pin
{
public:
	NETEC_Pin(void){};
	virtual~NETEC_Pin(void){};
public:
	virtual int Open(const char*cszPeerNodeID,unsigned long nPinID)=0;
	virtual int Open(const char*cszPeerNodeID,unsigned long nPinID,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort,const char*cszPeerMCUType)=0;
	virtual void Close(void)=0;
	virtual int SendData(const char*pData,int nLen)=0;
	static NETEC_Pin*Create(NETEC_PinCallback&rCallback);
};


#endif
