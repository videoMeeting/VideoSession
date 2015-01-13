#pragma once

#ifdef WIN32
#else
#include <dlfcn.h>
#endif

//---------------------------------------------------------------------------------------
// 动态链接库管理类
class AFX_EXT_CLASS KDLLManager
{
public:
	KDLLManager(void);
	virtual ~KDLLManager(void);

	//加载动态连接库
	virtual bool Load(const char* pDllName);

	//卸载动态连接库
	virtual void UnLoad(void);

	//获得函数入口
	virtual void* GetFunction(const char* pFunctionName);

private:
#ifdef WIN32
	HMODULE m_hDLL;
#else
	void* m_hDLL;
#endif
};
