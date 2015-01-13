/**********************************************************
 * Name: Reactor.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-08-03
 **********************************************************/

#pragma once

#include "WYNET/EventHandler.h"

//---------------------------------------------------------------------------------------
// �첽I/O��Ӧ��: �ṩsocket���첽I/O����
class AFX_EXT_CLASS KReactor
{
public:
	KReactor(void);
	virtual ~KReactor(void);

	/* ������Ӧ��ʵ�� */
	static bool CreateInstance(void);

	/* ���ٷ�Ӧ��ʵ�� */
	static void DestoryInstance(void);

	/* ��ȡ��Ӧ��ʵ�� */
	static KReactor* GetInstance(void);

	/* ע��KEventHandler */
	virtual void RegisterEventHandler(KEventHandler* pEventHandler)=0;

	/* ע��KEventHandler */
	virtual void UnRegisterEventHandler(KEventHandler* pEventHandler)=0;

	/* ����KEventHandler��IO״̬ */
	virtual void ResetEventHandler(KEventHandler* pEventHandler)=0;

protected:
	/* ������Ӧ�� */
	virtual bool Start(void)=0;

	/* ֹͣ��Ӧ�� */
	virtual void Stop(void)=0;
};
