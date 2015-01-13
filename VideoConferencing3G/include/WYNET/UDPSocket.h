/**********************************************************
 * Name: UDPSocket.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include <string>
#include "Socket.h"

//---------------------------------------------------------------------------------------
// UDP SOCKET¿‡
class AFX_EXT_CLASS KUDPSocket : public KSocket
{
public:
	KUDPSocket(void);
	virtual ~KUDPSocket(void);

	virtual bool Create(const std::string& strLocalAddr,unsigned short usLocalPort);
	virtual void Close(void);
	virtual bool Connect(const std::string& strRemoteAddr,unsigned short usRemotePort);

	virtual int SendTo(const std::string& strRemoteAddr,unsigned short usRemotePort,char* pData,int nLen);
	virtual int ReceiveFrom(std::string& strRemoteIP,unsigned short& usRemotePort,char* pData,int nLen);

	virtual bool SetBroadcast(bool bBroadcast);
	virtual bool IsBroadcast();
	virtual bool SetMulticastTTL(int nTTL);
	virtual int GetMulticastTTL();
	virtual bool SetMulticastLoop(bool bMulticastLoop);
	virtual bool IsMulticastLoop();
	virtual bool JoinMulticastGroup(const char* cszMulticastGroup);
	virtual bool LeaveMulticastGroup(const char* cszMulticastGroup);

private:
	void SetOptions(SOCKET hSocket);
};
