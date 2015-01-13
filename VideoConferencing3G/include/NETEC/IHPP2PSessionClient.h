//IHPP2PSessionClient.h
#ifndef __IHPP2PSESSIONCLIENT_H__
#define __IHPP2PSESSIONCLIENT_H__

#include <NETEC/NETEC_Export.h>

class IHPP2PSessionClient;
class IHPP2PSessionClientNotify
{
public:
	IHPP2PSessionClientNotify(void){};
	virtual~IHPP2PSessionClientNotify(void){};
public:
	virtual void OnIHPP2PSessionClientNotifyReceivedData(IHPP2PSessionClient*pIHPP2PSessionClient,const void*pData,int nLen)=0;
	virtual void OnIHPP2PSessionClientNotifyConnected(IHPP2PSessionClient*pIHPP2PSessionClient)=0;
	virtual void OnIHPP2PSessionClientNotifyDisconnected(IHPP2PSessionClient*pIHPP2PSessionClient)=0;
	virtual void OnIHPP2PSessionClientNotifyLocalAddress(IHPP2PSessionClient*pIHPP2PSessionClient,const char*cszIP,unsigned short usPort,int nPreference,bool bFirst)=0;
	virtual void OnIHPP2PSessionClientNotifyMTU(unsigned long ulMTU)=0;
	virtual void OnIHPP2PSessionClientNotifyRTT(unsigned long ulRTT)=0;
};

class IHPP2PSessionClient
{
public:
	IHPP2PSessionClient(void){};
	virtual~IHPP2PSessionClient(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual unsigned long GetP2PID(void)=0;
	virtual unsigned long GetSessionID(void)=0;
	virtual bool IsReadable(void)=0;
	virtual bool IsWritale(void)=0;
	virtual int SendData(const void*pData,int nLen)=0;
	virtual void AddPeerAddress(const char*cszIP,unsigned short usPort,int nPreference,bool bFirst)=0;
	virtual bool IsExpired(void)=0;
};

NETEC_API IHPP2PSessionClient*CreateIHPP2PSessionClient(IHPP2PSessionClientNotify&rIHPP2PSessionClientNotify,unsigned long ulP2PID,const char*cszStunServer,unsigned short usStunPort,bool bHost);

#endif