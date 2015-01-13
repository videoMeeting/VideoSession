/**********************************************************
 * Name: SocketDef.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#ifdef WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#define ErrorNo		WSAGetLastError()
	#define ErrorText	strerror(ErrorNo)
	#ifndef MSG_NOSIGNAL
		#define MSG_NOSIGNAL 0
	#endif
#else
	#include <sys/socket.h>
	#include <sys/select.h> 
	#include <sys/types.h>
	#include <unistd.h>
	#define SOCKET	int
	#define SOCKET_ERROR	-1
	#define INVALID_SOCKET	-1
	#ifndef INADDR_NONE
		#define INADDR_NONE ((unsigned long) -1)
	#endif
	#define closesocket(s) shutdown(s,SHUT_RDWR);close(s)
	#define ErrorNo		errno
	#define ErrorText	strerror(ErrorNo)
#endif

