#ifndef __IXEVENTSPUMP_H__
#define __IXEVENTSPUMP_H__

#include <NETEC/NETEC_Export.h>

class NETEC_API IXEventsQueue
{
public:
	IXEventsQueue(void){};
	virtual~IXEventsQueue(void){};
public:
	virtual bool PumpEvents(void)=0;
};

class NETEC_API IXEventsPump
{
public:
	IXEventsPump(void){};
	virtual ~IXEventsPump(void){};
public:
	static void Start(void);
	static void Stop(void);

	static void AddIXEventsQueue(IXEventsQueue*pIXEventsQueue);
	static void RemoveIXEventsQueue(IXEventsQueue*pIXEventsQueue);
	static bool PumpEvents(void);
};

#endif