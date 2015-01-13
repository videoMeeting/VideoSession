//NETEC_Stream.h
#ifndef __NETEC_STREAM_H__
#define __NETEC_STREAM_H__

#include <NETEC/NETEC_Export.h>

class NETEC_StreamCallback
{
public:
	NETEC_StreamCallback(void){};
	virtual~NETEC_StreamCallback(void){};
public:
	virtual void OnNETEC_StreamCallbackRecvdData(const char*pData,int nLen)=0;
	virtual void OnNETEC_StreamCallbackConnected(void)=0;
	virtual void OnNETEC_StreamCallbackDisconnected(void)=0;
};

class NETEC_API NETEC_Stream
{
public:
	NETEC_Stream(void){};
	virtual~NETEC_Stream(void){};
public:
	virtual int Open(const char*cszIP,unsigned short usPort)=0;
	virtual void Close(void)=0;
	virtual int SendData(const char*pData,int nLen)=0;

	static NETEC_Stream*Create(NETEC_StreamCallback&rCallback);
};

#endif
