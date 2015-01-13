/* KLog.h */

#pragma once

#include "CritSec.h"
#include "Utils.h"
#include <string>

#ifdef WIN32
#define snprintf _snprintf
#endif

//日志级别
typedef	enum _LOG_LEVEL
{
	LL_NONE			= 0,	//不显示日志信息
	LL_ERROR		= 1,    //显示错误信息级别
	LL_INFO     	= 2,    //显示运行信息级别(同时显示错误信息)
	LL_DEBUG		= 3,    //显示调试信息级别(同时显示错误信息和运行信息)
}LOG_LEVEL;

//日志回调
typedef void (*KLoggerCallBack)(const char* cszText);

//---------------------------------------------------------------------------------------
// KLogger日志类定义
class AFX_EXT_CLASS KLogger
{
public:
    KLogger(void);
    virtual ~KLogger();
    
    bool Open(LOG_LEVEL nLevel=LL_NONE,const char* cszLogFileName=NULL,KLoggerCallBack fpLoggerCallBack=NULL);
    void Close(void);
    void Write(const char* fmt,va_list args);

	void SetLevel(LOG_LEVEL nLevel);
    LOG_LEVEL GetLevel(void);

private:
	int				m_nPipe;
	FILE*			m_pFile;
	LOG_LEVEL		m_nLevel;
	KLoggerCallBack	m_fpLoggerCallBack;
};

//---------------------------------------------------------------------------------------
// LOG类定义
class AFX_EXT_CLASS LOG
{
public:
    LOG(void){};
    virtual ~LOG(){};

    static bool START(LOG_LEVEL nLevel,const char* cszLogFileName=NULL,KLoggerCallBack fpLoggerCallBack=NULL);
    static void STOP(void);
	static void SETLEVEL(LOG_LEVEL nLevel);
    static void DBG(const char* fmt,...);
    static void INF(const char* fmt,...);
    static void ERR(const char* fmt,...); 
};