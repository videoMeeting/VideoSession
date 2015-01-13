/**********************************************************
 * Name: SocketAddr.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include "SocketDef.h"
#include <string>

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KSocketAddr
{
public:
	KSocketAddr(){};
	virtual ~KSocketAddr(){};

	static std::string GetLocalHostName(void);
	static std::string GetLocalAddr(void);
	static std::string GetAddrByHostName(const std::string& strHostName);
	static std::string GetAddrByIP(unsigned long ulIP);
	static unsigned long GetIPByAddr(const std::string& strAddr);

	static std::string GetLocalAddr(SOCKET hSocket);
	static std::string GetRemoteAddr(SOCKET hSocket);
	static unsigned short GetRemotePort(SOCKET hSocket);
};

