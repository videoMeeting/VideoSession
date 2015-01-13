/* KThread base class. 
 * 
 *	Example:
 *	class TestThread:public KThread
 *	{
 *	public:
 *		TestThread(){m_bWantToStop=false;};
 *		virtual~TestThread(){};
 *	public:
 *		bool Start(void){return StartThread();};
 *		void Stop(void){m_bWantToStop=true;WaitForStop();};
 *	protected:
 *		void ThreadProcMain(void)
 *		{
 *			while(!m_bWantToStop)
 *			{
 *				//...
 *				Sleep(1000);
 *			}
 *		};
 *	protected:
 *		bool	m_bWantToStop;
 *	}; 
 */

#pragma once

#ifndef WIN32
  #include <pthread.h>
  #include <semaphore.h>
#endif

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KThread
{
public:
	KThread();
	virtual ~KThread();

	//启动线程，成功返回true,失败返回false,只有在该进程创建的线程数到达系统限制时才返回false
	bool StartThread(void);

	//等待线程退出，调用此函数前必须调用方法，以确保从主线程函数中退出，否则调用此函数会阻塞
	void WaitForStop(void);

	//获得线程ID
#ifdef WIN32
	DWORD GetThreadID(void){return m_dwThreadID;};
#else
	pthread_t GetThreadID(void){return m_thread;};
#endif

protected:
	// 主线程函数，您可以在此函数中实现线程要做的事
	virtual void ThreadProcMain(void)=0;

#ifdef WIN32
	DWORD	m_dwThreadID;		// 线程标识
	HANDLE	m_hThread;			// 线程句柄
	HANDLE	m_evStop;
#else
    pthread_t	m_thread;
    sem_t		m_semWaitForStop;
    bool		m_bThreadStopped;
#endif

private:
	unsigned long ThreadProc(void);
#ifdef WIN32
	static DWORD WINAPI InitThreadProc(PVOID pObj){
		return	((KThread*)pObj)->ThreadProc();
	}
#else
	static void* InitThreadProc(void*pObj){
		((KThread*)pObj)->ThreadProc();
		return 0;
	}
#endif
};

