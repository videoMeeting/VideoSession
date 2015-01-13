//NETEC_Core.h
#ifndef __NETEC_CORE_H__
#define __NETEC_CORE_H__

#include "NETEC/NETEC_Export.h"
#include "NETEC/XSocket.h"

class NETEC_API NETEC_Core
{
public:
	NETEC_Core(void);
	virtual~NETEC_Core(void);
public:
	//启动网络服务内核
	//成功返回0，失败返回错误码
	static int Start(unsigned short usPort=0,bool bHTTPPort=false,bool bAnyUDPPort=false,bool bHasMCU=true);
	//停止网络服务内核
	static void Stop(void);

	static unsigned short GetUDPPort(void);
	static const char*GetLocalIP(void);
	static SOCKET GetSocketHandle(unsigned long ulIP);

	static void SetUpdateFilePath(const char*cszFilePath);
	static bool HasMCU(void);
	static bool IsMCUClient(void);
	static bool IsMCUServer(void);
};

#endif
