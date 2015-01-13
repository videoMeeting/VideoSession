#ifndef __XBUFFERPOOL_H__
#define __XBUFFERPOOL_H__

#include <NETEC/XListPtr.h>
#include <NETEC/XDataBuffer.h>
#include <NETEC/XAutoLock.h>

class NETEC_API XBufferPool
{
public:
	XBufferPool(void);
	virtual ~XBufferPool(void);
public:
	virtual void SetDataBuffer(XDataBuffer*pXDataBuffer);
	virtual XDataBuffer*GetDataBuffer(void);
	virtual int GetCount(void);
	virtual void Flush(void);
protected:
	XCritSec			m_csListDataBuffer;
	XListPtr			m_listDataBuffer;
};

#endif
