/**********************************************************
 * Name: Socket.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include "SocketDef.h"

//---------------------------------------------------------------------------------------
// KSocket ¿‡∂®“Â
class AFX_EXT_CLASS KSocket
{
public:
	KSocket(void);
	virtual ~KSocket(void);
	virtual operator SOCKET(void){return m_hSocket;};

	virtual void Attach(SOCKET hSocket);
	virtual void Detach(void);
	bool SetNoneBlocking(bool bNoneBlocking);
	unsigned short GetLocalPort(void);

	static int SetOptions(SOCKET hSocket,int nLevel,int nOptName,void* szOptVal,int nOptLen);

protected:
	SOCKET m_hSocket;
};
