// XDataBuffer.h: interface for the UDPPacket class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __XDATABUFFER_H__
#define __XDATABUFFER_H__

#include <NETEC/NETEC_Export.h>

class NETEC_API XDataBuffer  
{
public:
	XDataBuffer(int nExtraLen=0);
	virtual ~XDataBuffer(void);
public:
	void Release(void);
	bool StoreData(char*pData,int nLen);
	char*GetData(void){return m_pData;}
	int GetLen(void){return m_nLen;}
protected:
	char*				m_pData;
	int					m_nLen;
	int					m_nBufferSize;
	int					m_nExtraLen;
};

#endif 