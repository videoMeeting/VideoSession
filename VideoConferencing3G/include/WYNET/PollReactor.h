/**********************************************************
 * Name: KPollReactor.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#ifdef IO_POLL

#include "KReactor.h"
#include <poll.h>

//---------------------------------------------------------------------------------------
// 网络处理反应器(POLL模式)
class AFX_EXT_CLASS KPollReactor : public KThread
                                 , public KReactor 
{
public:
	KPollReactor(void);
	virtual ~KPollReactor(void);
	
	virtual bool Start(void);
	virtual void Stop(void);

	virtual void RegisterEventHandler(KEventHandler* pEventHandler);
	virtual void UnRegisterEventHandler(KEventHandler* pEventHandler);
	virtual void ResetEventHandler(KEventHandler* pEventHandler);

protected:
	bool					m_bWantToStop;
	KCritSec					m_CritSec;
	KEventHandlerPool		m_EventHandlerPool;

	void ThreadProcMain(void);
	bool DispatchEvents(void);
	bool DispatchRecvData(void);

	void OnRead(SOCKET hSocket);
	void OnWrite(SOCKET hSocket);
	void OnException(SOCKET hSocket);

private:
	struct pollfd*	m_event_set;
	int				m_num_fds;
	int				m_event_count;

	bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool ModifyEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool RemoveEvent(SOCKET hSocket);
};

#endif