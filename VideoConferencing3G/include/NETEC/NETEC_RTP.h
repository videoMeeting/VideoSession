//NETEC_RTP.h
#ifndef __NETEC_RTP_H__
#define __NETEC_RTP_H__

#include "NETEC_Export.h"

class NETEC_API NETEC_RTP
{
public:
	NETEC_RTP(void);
	virtual~NETEC_RTP(void);
public:
	virtual int AddRTPChan(const char*cszChanID,const char*cszLocalIP,unsigned short&usLocalPort);
	virtual void RemoveRTPChan(const char*cszChanID);

	virtual int AddRTPChanDst(const char*cszChanID,const char*cszDstIP,unsigned short usDstPort);
	virtual void RemoveRTPChanDst(const char*cszChanID,const char*cszDstIP,unsigned short usDstPort);
};

#endif
