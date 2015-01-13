//IXMsgQueue.h

#ifndef __IXMSGQUEUE_H__
#define __IXMSGQUEUE_H__

#include <map>

#include <NETEC/XUtil.h>
#include <NETEC/XAutoLock.h>

class IXMsgHandle
{
public:
	IXMsgHandle(void);
	virtual~IXMsgHandle(void);
public:
	virtual void RegisterHandle(void);
	virtual void UnRegisterHandle(void);

	virtual void HandleMsg(unsigned long ulMsgID)=0;
	virtual void PostMsg(unsigned long ulMsgID,bool bOnce=true,unsigned long ulDelay=0);
	virtual void ClearMsg(void);
	virtual void RemoveMsg(unsigned long ulMsgID);

	virtual bool CheckMsg(void);
protected:
	struct XMsg
	{
		XMsg(unsigned long ulMsgID,bool bOnce,unsigned long ulDelay)
		:m_ulMsgID(ulMsgID)
		,m_bOnce(bOnce)
		,m_ulDelay(ulDelay)
		,m_ulTimestamp(XGetTimestamp())
		{
		}
		
		XMsg(void)
		:m_ulMsgID(0)
		,m_bOnce(true)
		,m_ulDelay(0)
		,m_ulTimestamp(XGetTimestamp())
		{
		}

		virtual~XMsg(void)
		{
		}
		
		XMsg operator=(const XMsg&tXMsg)
		{
			m_ulMsgID=tXMsg.m_ulMsgID;
			m_bOnce=tXMsg.m_bOnce;
			m_ulDelay=tXMsg.m_ulDelay;
			m_ulTimestamp=tXMsg.m_ulTimestamp;
			return *this;
		}
		
		unsigned long	m_ulMsgID;
		bool			m_bOnce;
		unsigned long	m_ulDelay;
		unsigned long	m_ulTimestamp;
	};

	typedef std::map<unsigned long,XMsg>	MapXMsg;
protected:
	MapXMsg				m_MapXMsg;
	XCritSec			m_csMapXMsg;
};

class  IXMsgQueue
{
public:
	IXMsgQueue(void){};
	virtual ~IXMsgQueue(void){};
public:
	static void Start(void);
	static void Stop(void);
};

#endif