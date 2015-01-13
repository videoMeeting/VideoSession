/**********************************************************
 * Name: EventHandler.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include <string>
#include <map>
#include "WYNET/SocketDef.h"
#include "WYNET/SocketAddr.h"

// IO事件MASK
 enum NET_EVENT
{
	EVENT_READ		= 0x01,
	EVENT_WRITE		= 0x02,
};

class KReactor;

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KEventHandler
{
public:
	KEventHandler();
	virtual ~KEventHandler();

	virtual SOCKET GetSocketHandle(void);

	/* Add this socket handler to the sockets map of the I/O reactor */
	virtual void RegisterEventHandler(void);

	/* Remove this socket handler from sockets map of the I/O reactor */
	virtual void UnRegisterEventHandler(void);

	/* Enable file descriptor read event */
	virtual void EnableRead(bool bEnable);

	/* Enable file descriptor write event */
	virtual void EnableWrite(bool bEnable);

	/* Get events of read/write/exception file descriptor set for a socket. */
	virtual unsigned long GetEvents(void);

	virtual void OnRead(void);
	virtual void OnWrite(void);
	virtual void OnException(void);

	/* 处理接收数据 */
	virtual void ProcessRecvData(void){};

protected:
	KReactor&		m_rReactor;
	SOCKET			m_hSocket;
	unsigned long   m_ulEvents;
};

//---------------------------------------------------------------------------------------
// KEventHandlerPool类型定义
typedef std::map<SOCKET,KEventHandler*> KEventHandlerPool;

