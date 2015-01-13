// JitterBuffer.h: interface for the JBBase class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __JITTERBUFFER_H__
#define __JITTERBUFFER_H__

#include <NETEC/XAutoLock.h>
#include <NETEC/XListPtr.h>
#include <NETEC/XPacketStatistics.h>

#define JB_MAX_DELAY_VARIATION		1280//9600
#define JB_MIN_DELAY_VARIATION		60//120
		
class NETEC_API JBBase
	: public XPacketStatistics
{
public:
	JBBase(void);
	virtual~JBBase(void);
public:
	virtual int OnRecvdPacket(unsigned short usSeq,unsigned long ulRTPTimeMS,const unsigned char*pPacketData,int nPacketLen);

	virtual bool DoTick(void);

	virtual void SetDelayVariation(unsigned long nDelayVariation);

	virtual void OnLostPackets(unsigned short usLostPackets,unsigned short usFromSeqNo,unsigned short usToSeqNo);

	virtual void OnJBFilteredPacket(const unsigned char*pPacketData,int nPacketLen){};
	virtual bool IsPacketJB(void)=0;
	
protected:
	virtual void ClearPackets(void); 

	typedef struct NETEC_API tagPACKET
	{
		bool			bDiscontinous;
		unsigned short	usSeq;
		unsigned long	ulRTPTimeMS;
		unsigned long	ulTimestampNow;
		unsigned char*	pPacketData;
		int				nPacketLen;
	}PACKET,*PPACKET;

	virtual void OnStreamPacket(PPACKET pPacket){};
protected:
	unsigned long	m_nDelayVariation;
	unsigned long	m_nLastSentPacketRTPTimeMS;
	unsigned long	m_nNewRecvdPacketRTPTimeMS;


	XListPtr		m_listPacket;
	XCritSec		m_csListPacket;

	unsigned short	m_usLastGoodSequence;
	bool			m_bGotFirstFrame;

	unsigned long	m_nCurMaxDelayVariation;
	unsigned long	m_ulLastCurMaxDelayVariationTimestamp;
	bool			m_bResetDelayVariation;
	int				m_nCurMaxDelayVariationPacketCount;

	unsigned long	m_ulLastRecvdPacketTimestamp;
	unsigned long	m_ulLastRecvdPacketRTPTimeMS;
};


class NETEC_API JBFrame
	: public JBBase
{
public:
	JBFrame(void);
	virtual~JBFrame(void);
public:
	virtual int OnRecvdRepairedPacket(unsigned short usFromSeqNo,unsigned short usToSeqNo,const unsigned char*pPacketData,int nPacketLen);
	virtual void OnJBAckPackets(unsigned short usFromSeqNo,unsigned short usToSeqNo)=0;
	virtual void OnJBFrameData(unsigned char*pData,int nLen)=0;
protected:
	virtual bool IsPacketJB(void);
	virtual void OnStreamPacket(PPACKET pPacket);
protected:
	XListPtr		m_listStreamPackets;
	XCritSec		m_csListStreamPackets;
	unsigned char*	m_pFrameBuf;
	int				m_nFrameBufLen;

};

		
class NETEC_API JBPacket
	: public JBBase
{
public:
	JBPacket(void);
	virtual~JBPacket(void);
public:
	virtual int OnRecvdPacket(unsigned short usSeq,unsigned long ulRTPTimeMS,const unsigned char*pPacketData,int nPacketLen);
	virtual void ResetJBPacket(void);
protected:
	virtual bool IsPacketJB(void);
};

#endif