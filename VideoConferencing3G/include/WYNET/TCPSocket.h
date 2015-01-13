/**********************************************************
 * Name: TCPSocket.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include <string>
#include "Socket.h"

//---------------------------------------------------------------------------------------
typedef struct _TCPSOCKET_KEEPALIVE
{
	unsigned long ulOnOff;
    unsigned long ulKeepAliveTime;
    unsigned long ulKeepAliveInterval;
}TCPSOCKET_KEEPALIVE;

#define SIO_KEEPALIVE_VALS   _WSAIOW(IOC_VENDOR,4)

//---------------------------------------------------------------------------------------
// KTCPSocket ¿‡∂®“Â
class AFX_EXT_CLASS KTCPSocket : public KSocket
{
public:
	KTCPSocket(void);
	virtual ~KTCPSocket(void);

	bool Create(const std::string& strLocalAddr="",unsigned short usLocalPort=0);
	void Close(void);
	bool Connect(const std::string& strRemoteAddr,unsigned short usRemotePort);
	bool Listen(int nBackLog=SOMAXCONN);
	bool Accept(SOCKET& hSocket,std::string& strRemoteAddr,unsigned short& usRemotePort);
	
	int Send(char* pData,int nLen);
	int Receive(char* pData,int nLen);

	std::string GetRemoteAddr(void);
	unsigned short GetRemotePort(void);

	void SetOptions(SOCKET hSocket);
};
