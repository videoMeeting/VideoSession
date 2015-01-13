/**********************************************************
 * Name: Reactor.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include "WYNET/EventHandler.h"

//---------------------------------------------------------------------------------------
// 异步I/O反应器: 提供socket的异步I/O处理
class AFX_EXT_CLASS KReactor
{
public:
	KReactor(void);
	virtual ~KReactor(void);

	/* 创建反应堆实例 */
	static bool CreateInstance(void);

	/* 销毁反应堆实例 */
	static void DestoryInstance(void);

	/* 获取反应堆实例 */
	static KReactor* GetInstance(void);

	/* 注册KEventHandler */
	virtual void RegisterEventHandler(KEventHandler* pEventHandler)=0;

	/* 注销KEventHandler */
	virtual void UnRegisterEventHandler(KEventHandler* pEventHandler)=0;

	/* 重置KEventHandler的IO状态 */
	virtual void ResetEventHandler(KEventHandler* pEventHandler)=0;

protected:
	/* 启动反应堆 */
	virtual bool Start(void)=0;

	/* 停止反应堆 */
	virtual void Stop(void)=0;
};
