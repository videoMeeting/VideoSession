#pragma once

#ifndef WIN32
#include <pthread.h>
#endif

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KEvent
{
public:
	KEvent(bool bManualReset = false);
	virtual ~KEvent(void);

	//对于任何等待的线程设置事件可用(有信号)或不可用(无信号)。
	void Set(void);

	//等待事件有信号或超时，ulTimeout是毫秒，如果返回true，事件被设置，否则超时。
	bool Wait(unsigned long ulTimeout);

	//设置事件不可用(无信号)。
	void Reset(void);

protected:

#ifdef WIN32
	HANDLE m_hEvent;
#else
	pthread_mutex_t m_mutex;
	pthread_cond_t	m_cond;
	int				m_nEvent;
	bool			m_bManualReset;
#endif
};

