#pragma once
#include "WYBASE/CmdPacket.h"
#include "NETEC_Core.h"
#include "NETEC_Setting.h"
#include "NETEC_Client.h"
#include "NETEC_Server.h"
#include "Middlelayer.h"

class CmdTCPClientCallback
{
public:
	//返回连接服务端状态
	virtual void On_SessionConnectStatus(CONNECT_STATUS cs) = 0;
	//返回服务端数据
	virtual void OnDispatchCmd(KCmdPacketEx& pPacket) = 0;
};

class CmdTCPClient
{
public:
	CmdTCPClient();
	~CmdTCPClient();
public:
	bool startClient(const char* ip, unsigned int uiPort, CmdTCPClientCallback* pCallback);
	bool stopClient();
	bool sendData(KCmdPacketEx& pPacket);
private:
	void* m_pTCPClient;
};


