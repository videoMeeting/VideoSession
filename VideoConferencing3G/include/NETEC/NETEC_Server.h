//NETEC_Server.h
#ifndef __NETEC_SERVER_H__
#define __NETEC_SERVER_H__

#include "NETEC_Session.h"

//网络Server
class NETEC_ServerCallback
{
public:
	NETEC_ServerCallback(void){};
	virtual~NETEC_ServerCallback(void){};
public:
	virtual void OnNETEC_ServerClientConnected(unsigned long ulClientID,unsigned long ulClientRemoteIP)=0;
	virtual void OnNETEC_ServerClientDisconnected(unsigned long ulClientID)=0;
	virtual void OnNETEC_ServerReceivedFromClient(unsigned long ulClientID,const char*pData,int nLen)=0;

};

class NETEC_API NETEC_Server
{
public:
	NETEC_Server(void){};
	virtual ~NETEC_Server(void){};
public:
	//启动本地服务
	virtual int Start(void)=0;
	
	//停止本地服务
	virtual void Stop(void)=0;

	//获得客户SESSION数目
	virtual unsigned int GetClientCount(void)=0;

	//发送数据给指定的网络客户端
	virtual int SendDataToClient(unsigned int nClientID,const char*pData,int nLen)=0;

	//强制断开客户端
	virtual void DisconnectClient(unsigned int nClientID)=0;

	static NETEC_Server*Create(NETEC_ServerCallback&rCallback,unsigned short usServerType);
};

#endif