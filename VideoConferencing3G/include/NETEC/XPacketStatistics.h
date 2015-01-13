//XPacketStatistics.h
#ifndef __XPACKETSTATISTICS_H__
#define __XPACKETSTATISTICS_H__

#include <NETEC/XAutoLock.h>

class NETEC_API XPacketStatistics
{
public:
	XPacketStatistics(void);
	virtual~XPacketStatistics(void);
public:
	void GetStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate);
	
	void IncreaseTotalPackets(unsigned long ulPackets);
	void IncreaseLostPackets(unsigned long ulPackets);

	unsigned long GetLostPackets(void);
protected:
	typedef struct NETEC_API PACKET_ITEM
	{
		PACKET_ITEM(void)
		:m_ulTotalPackets(0)
		,m_ulLostPackets(0)
		{
		};
		
		unsigned long	m_ulTotalPackets;
		unsigned long	m_ulLostPackets;
	}PACKET_ITEM;
	
	PACKET_ITEM			m_PacketItem;		
	PACKET_ITEM			m_PacketItems[2];
	unsigned long		m_ulCurIndex;
	unsigned long		m_ulNextIndex;
	unsigned long		m_ulLastIndexTimestamp;

	XCritSec			m_csPacketItem;
};	

#endif