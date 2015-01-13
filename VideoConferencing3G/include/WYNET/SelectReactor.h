/**********************************************************
 * Name: SelectReactor.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#ifdef IO_SELECT

#include "Reactor.h"

struct win_fd_set
{
	unsigned int fd_count;
	SOCKET fd_array[1];
};

//---------------------------------------------------------------------------------------
// 网络处理反应器(SELECT模式)
class AFX_EXT_CLASS KSelectReactor : public KThread
                                   , public KReactor 
{
public:
	KSelectReactor(void);
	virtual ~KSelectReactor(void);
	
	virtual bool Start(void);
	virtual void Stop(void);

	virtual void RegisterEventHandler(KEventHandler* pEventHandler);
	virtual void UnRegisterEventHandler(KEventHandler* pEventHandler);
	virtual void ResetEventHandler(KEventHandler* pEventHandler);

protected:
	bool					m_bWantToStop;
	KCritSec				m_CritSec;
	KEventHandlerPool		m_EventHandlerPool;

	void ThreadProcMain(void);
	bool DispatchEvents(void);
	bool DispatchRecvData(void);

	void OnRead(SOCKET hSocket);
	void OnWrite(SOCKET hSocket);
	void OnException(SOCKET hSocket);

private:
	unsigned int	m_fd_size;
	win_fd_set*		m_read_in_set;
	win_fd_set*		m_write_in_set;
	win_fd_set*		m_read_out_set;
	win_fd_set*		m_write_out_set;
	win_fd_set*		m_except_out_set;

	bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool ModifyEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool RemoveEvent(SOCKET hSocket);

	int realloc_fd_sets(size_t newsize);
	int do_fd_set(struct win_fd_set* set, SOCKET hSocket);
	void do_fd_unset(struct win_fd_set* set, SOCKET hSocket);
	void fd_set_copy(struct win_fd_set* out, const struct win_fd_set* in);
};

#endif