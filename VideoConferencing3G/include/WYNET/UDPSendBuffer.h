/**********************************************************
 * Name: UDPSendBuffer.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-11-21
 **********************************************************/

#pragma once

#include "UDPPacket.h"

//typedef std::set<unsigned short> UDP_ACK_PACKET_SET;
//
//class KUDPSession;
//
////---------------------------------------------------------------------------------------
//// ·¢ËÍ°ü³ØÀà
//class AFX_EXT_CLASS KUDPSendBuffer : public KThread
//{
//public:
//	KUDPSendBuffer(KUDPSession& rUDPSession);
//	virtual ~KUDPSendBuffer(void);
//
//	bool Create(void);
//	void Close(void);
//	void PushIntoRawBufferPool(KUDPPacket UDPPacket);
//	//void PushIntoWinBufferPool(KUDPPacket UDPPacket);
//
//protected:
//	KUDPSession& m_rUDPSession;
//	virtual void ThreadProcMain(void);
//	bool ProcessBufferPool(void);
//
//private:
//	unsigned long	m_ulLastTimeStamp;
//	unsigned long	m_ulRTT;
//	bool			m_bWantToStop;
//	KCritSec		m_secRawBufferPool;
//	KList			m_lstRawBufferPool;
//	KCritSec		m_secWinPacketPool;
//	KList			m_lstWinPacketPool;
//
//	bool IsWinBufferPoolEmpty(void);
//	bool MoveBufferPacket(void);
//	//bool FindAndDeleteAckPacket(unsigned short usSequence);
//};
