//NETEC_XNCPTrans.h
#ifndef __NETEC_XNCPTRANS_H__
#define __NETEC_XNCPTRANS_H__

#include <NETEC/NETEC_Export.h>
#include <NETEC/XSocket.h>

class XNCPTransNotify
{
public:
	XNCPTransNotify(void)
	{
	}
	virtual~XNCPTransNotify(void)
	{
	}
public:
	virtual void OnXNCPTransNotifyReceivedFrame(void*pFrameData,int nFrameLen)=0;
	virtual bool OnXNCPTransNotifyHasPendingData(void)=0;
	virtual void OnXNCPTransNotifyGetPendingData(void)=0;
	virtual bool OnXNCPTransNotifyPreConnected(unsigned long ulType,void*pData,int nLen){return false;};
	virtual void OnXNCPTransNotifyConnected(void){};
};

class NETEC_API XNCPTrans
{
public:
	XNCPTrans(void){}
	virtual~XNCPTrans(void){}
public:
	virtual void ReleaseConnections(void)=0;
	virtual bool IsDisconnected(void)=0;
	virtual bool SendFrame(void*pFrameData,int nFrameLen)=0;
	virtual bool SendPendingData(void*pData,int nLen)=0;
	virtual void ActivateSending(void)=0;
	virtual const char*GetLocalIP(void)=0;
	virtual const char*GetPeerIP(void)=0;

	static XNCPTrans*Create(XNCPTransNotify&rNotify,SOCKET hSocket,void*pHeaderData,int nHeaderLen);
	static XNCPTrans*Create(XNCPTransNotify&rNotify,const char*cszIP,unsigned short usPort,const char*cszInterface,unsigned long ulType,void*pData,int nLen,bool bDontUseProxy=false);
};

// 

#endif