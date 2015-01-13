#pragma once

#include "Thread.h"
#include "CritSec.h"
#include <map>

//---------------------------------------------------------------------------------------
typedef struct _TIMER_EVENT
{
	unsigned long elapse;
	unsigned long timestamp;
	unsigned short flag;
}TIMER_EVENT,*PTIMER_EVENT;

//---------------------------------------------------------------------------------------
typedef std::map<unsigned int,PTIMER_EVENT>	TIMER_EVENT_MAP;

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KTimer : public KThread
{
public:
	KTimer(void);
	~KTimer(void);

	/* 启动计时器 */
	bool StartTimer(void);

	/* 停止计时器 */
	void StopTimer(void);

	/* 设置计时器事件: nEventID=事件ID; nElapse=事件间隔(ms) */
	void SetTimerEvent(unsigned int nEventID,unsigned long ulElapse);

	/* 删除计时器时间: nEvnetID=指定删除的事件ID */
	void KillTimerEvent(unsigned int nEventID);

protected:
	/* 事件触发回调,继承该方法处理事件(虚函数) */
	virtual void OnTimerEvent(unsigned int nEventID){};
	
private:
	bool				m_bWantToStop;
	KCritSec			m_secTimerEvent;
	TIMER_EVENT_MAP		m_mapTimerEvent;

	virtual void ThreadProcMain(void);
	bool ProcessTimerEvent(void);
};
