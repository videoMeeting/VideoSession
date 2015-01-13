//NETEC_Client.h
#ifndef __NETEC_CLIENT_H__
#define __NETEC_CLIENT_H__

#include "NETEC_Session.h"

//网络应用服务
class NETEC_API NETEC_ClientCallback
{
public:
	NETEC_ClientCallback(void){};
	virtual~NETEC_ClientCallback(void){};
public:
	//收到连接状态
	virtual void OnNETEC_SessionConnectStatus(NETEC_Session::CONNECT_STATUS cs,int nErrorCode=0){};

	//从其它网络应用收到的数据包回调
	virtual void OnNETEC_ClientReceivedFromServer(const char* pData,int nLen){};
};

class NETEC_API NETEC_Client
{
public:
	NETEC_Client(void){};
	virtual~NETEC_Client(void){};
public:
	//连接服务器
	virtual int Connect(unsigned short nServerType,const char*cszIP,unsigned short usPort,const char*cszInterface)=0;
	//断开连接
	virtual void Disconnect(void)=0;

	//发送数据给指定的网络Server
	virtual int SendDataToServer(const char*pData,int nLen)=0;

	virtual unsigned int GetClientID(void)=0;

	//取本地地址
	virtual const char*GetLocalIP(void)=0;

	//取外网地址
	virtual const char*GetNATIP(void)=0;

	static NETEC_Client*Create(NETEC_ClientCallback&rCallback);
};

#endif