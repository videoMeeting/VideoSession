// TestClient.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

#ifdef WIN32
#include <assert.h>
#endif

#include "cmdtcpclient.h"

class CClient
	: public NETEC_ClientCallback
{
public:
	CClient(void);
	virtual~CClient(void);
public:
	int Open(const char*cszIP,unsigned short usPort);
	void Close(void);
	void SetFunPointer(CmdTCPClientCallback* pCallback);
public:
	//收到连接状态
	virtual void OnNETEC_SessionConnectStatus(NETEC_Session::CONNECT_STATUS cs,int nErrorCode=0);

	//从其它网络应用收到的数据包回调
	virtual void OnNETEC_ClientReceivedFromServer(const char* pData,int nLen);

	virtual bool IsConnnected(void)
	{
		return m_bConnected;
	}

	virtual void SendData(const char*pData,int nLen)
	{
		if (m_pClient!=NULL)
		{
			m_pClient->SendDataToServer(pData,nLen);
		}
	}
protected:
	NETEC_Client*	m_pClient;
	bool			m_bConnected;
private:
	CmdTCPClientCallback* m_pCallback;
};

CmdTCPClient::CmdTCPClient():m_pTCPClient(NULL)
{

}
CmdTCPClient::~CmdTCPClient()
{
	if(m_pTCPClient != NULL)
	{
		((CClient*)m_pTCPClient)->Close();
		delete (CClient*)m_pTCPClient;
		m_pTCPClient = NULL;
	}
}

bool CmdTCPClient::startClient(const char* ip, unsigned int uiPort, CmdTCPClientCallback* pCallback)
{
	assert(ip);
	assert(pCallback);

	m_pTCPClient = (CClient*)new CClient;
	assert(m_pTCPClient);

	((CClient*)m_pTCPClient)->SetFunPointer(pCallback);
	((CClient*)m_pTCPClient)->Open(ip,uiPort);

	return true;
}
bool CmdTCPClient::stopClient()
{
	if(m_pTCPClient == NULL)
		return true;
	((CClient*)m_pTCPClient)->Close();
	delete (CClient*)m_pTCPClient;
	m_pTCPClient = NULL;
	return true;
}
bool CmdTCPClient::sendData( KCmdPacketEx& pPacket)
{
	std::string data = pPacket.GetString();
	((CClient*)m_pTCPClient)->SendData(data.c_str(),data.length()+1);
	return true;
}

CClient::CClient(void)
{
	m_pClient=NULL;
	m_bConnected=false;
	m_pCallback = NULL;
}

CClient::~CClient(void)
{
}

void CClient::SetFunPointer(CmdTCPClientCallback* pCallback)
{
	assert(pCallback);
	m_pCallback = pCallback;
}

int CClient::Open(const char*cszIP,unsigned short usPort)
{
	//NETEC_Core::Start(0);
	m_bConnected=false;
	m_pClient=NETEC_Client::Create(*this);
	m_pClient->Connect(10,cszIP,usPort,"");
	return 0;
}

void CClient::Close(void)
{
	if (NULL != m_pClient)
	{
		m_pClient->Disconnect();
		delete m_pClient;
		m_pClient=NULL;
	}
	//NETEC_Core::Stop();
}

//收到连接状态
void CClient::OnNETEC_SessionConnectStatus(NETEC_Session::CONNECT_STATUS cs,int nErrorCode)
{
	char szText[1024]="";
	switch (cs)
	{
	case NETEC_Session::CS_CONNECTING:
		strcpy(szText,"Connecting...");
		break;
	case NETEC_Session::CS_FAILED:
		strcpy(szText,"Failed");
		break;
	case NETEC_Session::CS_DISCONNECTED:
		strcpy(szText,"Disconnected");
		break;
	case NETEC_Session::CS_CONNECTED:
		strcpy(szText,"Connected");
		break;
	case NETEC_Session::CS_BUSY:
		strcpy(szText,"Busy");
		break;
	case NETEC_Session::CS_RECONNECTED:
		strcpy(szText,"Reconnected");
		break;
	case NETEC_Session::CS_RESTARTED:
		strcpy(szText,"Restarted");
		break;
	default:
		strcpy(szText,"Unkown");
		break;
	}
	printf("%s\n",szText);
		
	m_bConnected=(NETEC_Session::CS_CONNECTED==cs || NETEC_Session::CS_RECONNECTED==cs);

	m_pCallback->On_SessionConnectStatus((CONNECT_STATUS)cs);
}

//从其它网络应用收到的数据包回调
void CClient::OnNETEC_ClientReceivedFromServer(const char* pData,int nLen)
{
	KCmdPacketEx rPacket(pData,nLen);
	rPacket.SetDomain("");
	rPacket.SetSourceType(0);
	rPacket.SetSourceID("");

	m_pCallback->OnDispatchCmd(rPacket);
}

