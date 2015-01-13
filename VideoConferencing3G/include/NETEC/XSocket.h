// XSocket.h: interface for the XSocket class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __XSOCKET_H__
#define __XSOCKET_H__


#include "NETEC/NETEC_Export.h"

#ifdef WIN32


#include <winsock2.h>
#include <WS2TCPIP.H>
#include <errno.h>

#pragma comment(lib,"ws2_32.lib")

typedef int socklen_t;

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL	(0)
#endif

#define EWOULDBLOCK WSAEWOULDBLOCK
#define EINPROGRESS WSAEINPROGRESS
#define EALREADY WSAEALREADY
#define ENOTSOCK WSAENOTSOCK
#define EDESTADDRREQ WSAEDESTADDRREQ
#define EMSGSIZE WSAEMSGSIZE
#define EPROTOTYPE WSAEPROTOTYPE
#define ENOPROTOOPT WSAENOPROTOOPT
#define EPROTONOSUPPORT WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
#define EOPNOTSUPP WSAEOPNOTSUPP
#define EPFNOSUPPORT WSAEPFNOSUPPORT
#define EAFNOSUPPORT WSAEAFNOSUPPORT
#define EADDRINUSE WSAEADDRINUSE
#define EADDRNOTAVAIL WSAEADDRNOTAVAIL
#define ENETDOWN WSAENETDOWN
#define ENETUNREACH WSAENETUNREACH
#define ENETRESET WSAENETRESET
#define ECONNABORTED WSAECONNABORTED
#define ECONNRESET WSAECONNRESET
#define ENOBUFS WSAENOBUFS
#define EISCONN WSAEISCONN
#define ENOTCONN WSAENOTCONN
#define ESHUTDOWN WSAESHUTDOWN
#define ETOOMANYREFS WSAETOOMANYREFS
#define ETIMEDOUT WSAETIMEDOUT
#define ECONNREFUSED WSAECONNREFUSED
#define ELOOP WSAELOOP
#undef ENAMETOOLONG // remove errno.h's definition
#define ENAMETOOLONG WSAENAMETOOLONG
#define EHOSTDOWN WSAEHOSTDOWN
#define EHOSTUNREACH WSAEHOSTUNREACH
#undef ENOTEMPTY // remove errno.h's definition
#define ENOTEMPTY WSAENOTEMPTY
#define EPROCLIM WSAEPROCLIM
#define EUSERS WSAEUSERS
#define EDQUOT WSAEDQUOT
#define ESTALE WSAESTALE
#define EREMOTE WSAEREMOTE
#undef EACCES
#define SOCKET_EACCES WSAEACCES


class XSocketInitializer  
{
public:
	XSocketInitializer(void)
	{
		WORD wVersion; 
		WSADATA wsaData;
		wVersion = MAKEWORD(2,2);
		WSAStartup(wVersion,&wsaData);
	}
	virtual ~XSocketInitializer(void)
	{
		WSACleanup(); 
	}
};

#else 

#ifndef SOCKET
#define SOCKET int
#endif

#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
//#include <linux/rtc.h>
#include <errno.h>


#endif /* WIN32 */

class NETEC_API XSocket  
{
public:
	XSocket(void);
	virtual ~XSocket(void);
public:
	virtual void Attach(SOCKET hSocket);
	virtual void Detach(void);
	virtual void Close(void);
	virtual bool SetNoneBlocking(bool bNB);

	virtual unsigned short GetLocalPort(void);
	virtual unsigned long GetLocalIP(void);

	virtual operator SOCKET(void){return m_hSocket;};
	static bool SetTos(SOCKET hSocket,unsigned char nTos);

    static const char*GetLocalHostName(void);

	static const char*htoa(unsigned long nIP);
	static unsigned long atoh(const char*cszIP);

	static void SetLocalInterface(const char*cszLocalInterface);
	static const char*GetLocalInterface(void);
protected:
	SOCKET		m_hSocket;

	static char m_szLocalHostName[256];
	static char m_szLocalInterface[256];
};

#endif
