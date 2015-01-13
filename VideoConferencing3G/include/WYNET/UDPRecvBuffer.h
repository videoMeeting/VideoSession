/**********************************************************
 * Name: UDPRecvBuffer.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-11-23
 **********************************************************/

#pragma once

#include "UDPPacket.h"

//class KUDPRecvSession;
//
////---------------------------------------------------------------------------------------
//class AFX_EXT_CLASS KUDPRecvBuffer : public KThread
//{
//public:
//	KUDPRecvBuffer(KUDPRecvSession& rUDPRecvSession);
//	virtual ~KUDPRecvBuffer(void);
//	
//	bool Create(void);
//	void Close(void);
//	void PushPacket(KUDPPacket* pUDPPacket);
//
//protected:
//	KUDPRecvSession& m_rUDPRecvSession;
//	virtual void ThreadProcMain(void);
//	void AssembleFrame(KUDPPacket* pUDPPacket);
//
//private:
//	bool			m_bWantToStop;
//	KCritSec		m_secWinPacketPool;
//	KList			m_lstWinPacketPool;
//	char*			m_pRecvFrameData;
//	int				m_nRecvFrameLen;
//};
