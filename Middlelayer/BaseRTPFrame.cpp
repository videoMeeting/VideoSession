

#include "BaseRTPFrame.h"
#include <NETEC/XUtil.h>

BaseRTPFrame::BaseRTPFrame(BaseRTPFrameCallback&rCallback)
:m_nPayloadType(34)
,m_nMaxRTPFrameSize(1400)
,m_nMaxRTPPayloadBufLen(m_nMaxRTPFrameSize-RTP_HEADER_LEN)

,m_nRTPTimestamp(0)
,m_ulSSRC(XGenerateSSRC())
,m_usSeqNo(0)

,m_rCallback(rCallback)
{
	m_pFrameBuf=NULL;
	m_nFrameBufLen=0;

	m_nHeaderMargin=0;

	m_nLastRecvdRTPTime=0;
	m_bGotFrame=false;

	m_nBufferedFrameCount=0;
	m_nMaxPacketsToSend=3;
	m_nLastSentPacketTimestamp=0;
}

BaseRTPFrame::~BaseRTPFrame(void)
{

}

int BaseRTPFrame::Open(int nPayloadType,int nMaxRTPFrameSize,int nHeaderMargin)
{
	m_nHeaderMargin=nHeaderMargin;
	m_nPayloadType=nPayloadType;
	m_nMaxRTPFrameSize=nMaxRTPFrameSize;
	m_nMaxRTPPayloadBufLen=m_nMaxRTPFrameSize-RTP_HEADER_LEN-get_codec_header_len();
	return 0;
}

void BaseRTPFrame::Close(void)
{
	FlushRTPPackets();

	if (m_pFrameBuf!=NULL)
	{
		free(m_pFrameBuf);
		m_pFrameBuf=NULL;
	}
	m_nFrameBufLen=0;
}

void BaseRTPFrame::FlushRTPPackets(void)
{
	XAutoLock l(m_csListRTPPacket);
	while (m_ListRTPPacket.size()>0)
	{
		RTPFrame*pRTPFrame=(RTPFrame*)m_ListRTPPacket.front();
		m_ListRTPPacket.pop_front();
		pRTPFrame->Release();
		pRTPFrame=NULL;
	}
}


int BaseRTPFrame::CalculateFrameSize(void)
{
	int nFrameLen=0;
	XAutoLock l(m_csListRTPPacket);
	XListPtr::iterator iter=m_ListRTPPacket.begin();
	while (iter!=m_ListRTPPacket.end())
	{
		RTPFrame*pRTPFrame=(RTPFrame*)*iter;
		nFrameLen+=pRTPFrame->nLen;
		++iter;
	}
	return nFrameLen;
}

int BaseRTPFrame::GetFrame(unsigned char*pFrameBuf,int nBufLen)
{
	int nFrameLen=0;
	XAutoLock l(m_csListRTPPacket);
	while (m_ListRTPPacket.size()>0)
	{
		RTPFrame*pRTPFrame=(RTPFrame*)m_ListRTPPacket.front();
		m_ListRTPPacket.pop_front();

		int nTemp=handle_rtp_packet((unsigned char*)pRTPFrame->pBuffer+RTP_HEADER_LEN,pRTPFrame->nLen-RTP_HEADER_LEN,pFrameBuf,nBufLen);
		nFrameLen+=nTemp;

		pFrameBuf+=nTemp;
		nBufLen-=nBufLen;

		pRTPFrame->Release();
		pRTPFrame=NULL;
	}

	return nFrameLen;
}


void BaseRTPFrame::SendFrame(const unsigned char*pFrameData,int nFrameLen,int nWidth,int nHeight,int nKeyFrame,unsigned long ulTimestamp)
{
	m_nRTPTimestamp=ulTimestamp;

	DoSendFrame(pFrameData,nFrameLen,nWidth,nHeight,nKeyFrame,ulTimestamp);
}

void BaseRTPFrame::SendFrameHeader(unsigned char*pRTPPacket,int nPacketLen)
{
	//m_rCallback.OnBaseRTPFrameCallbackRTPPacket(pRTPPacket,nPacketLen);

	RTPFrame*pRTPFrame=new RTPFrame;
	if (pRTPFrame==NULL)
	{
		return;
	}
	pRTPFrame->pBuffer=malloc(nPacketLen);
	if (pRTPFrame->pBuffer!=NULL)
	{
		memcpy(pRTPFrame->pBuffer,pRTPPacket,nPacketLen);
		pRTPFrame->nLen=nPacketLen;

		XAutoLock l(m_csListRTPPacket);

		pRTPFrame->bFirstPacket=true;

		m_nBufferedFrameCount++;

		m_ListRTPPacket.push_back(pRTPFrame);
	}
	else
	{
		pRTPFrame->Release();
		pRTPFrame=NULL;
		return;
	}
}

void BaseRTPFrame::set_rtp_header(unsigned char*pHeader,bool bMarker)
{
	PRTP_HEADER pRTPHeader=(PRTP_HEADER)pHeader;
	memset(pRTPHeader,0,RTP_HEADER_LEN);
	pRTPHeader->version=RTP_VERSION;
	pRTPHeader->marker=(bMarker?1:0);
	pRTPHeader->type=m_nPayloadType;
	pRTPHeader->sequence=htons(m_usSeqNo++);
	pRTPHeader->timestamp=htonl(m_nRTPTimestamp);
	pRTPHeader->ssrc=htonl(m_ulSSRC);

	//if (bMarker)
	//{
		//m_nRTPTimestamp+=3003;
	//}
	//char szDebug[1024];
	//sprintf(szDebug,"nRTPTime=%u m_nLastRecvdRTPTime=%u\n",nRTPTime,m_nLastRecvdRTPTime);
	//OutputDebugString(szDebug);
}

void BaseRTPFrame::SendRTPPacket(RTPFrame*pRTPFrame)
{
	m_rCallback.OnBaseRTPFrameCallbackRTPPacket(pRTPFrame->pBuffer,pRTPFrame->nLen);

	pRTPFrame->Release();
	pRTPFrame=NULL;

	//XAutoLock l(m_csListRTPPacket);
	//m_ListRTPPacket.push_back(pRTPFrame);
}


void BaseRTPFrame::OnRecvdRTPPacket(void*pPacketData,int nPacketLen)
{
	unsigned char*pFrameData=(unsigned char*)pPacketData;
	if (pFrameData!=NULL && nPacketLen>=12)
	{
		PRTP_HEADER pRTPHeader=(PRTP_HEADER)pFrameData;
		unsigned long nRTPTime=ntohl(pRTPHeader->timestamp);

		//char szDebug[1024];
		//sprintf(szDebug,"nRTPTime=%u m_nLastRecvdRTPTime=%u\n",nRTPTime,m_nLastRecvdRTPTime);
		//OutputDebugString(szDebug);

		if (m_bGotFrame && m_nLastRecvdRTPTime!=nRTPTime)
		{
			PacketsToFrame();
			m_bGotFrame=false;
		}

		RTPFrame*pRTPFrame=new RTPFrame;
		if (pRTPFrame==NULL)
		{
			return;
		}

		pRTPFrame->pBuffer=malloc(nPacketLen);
		if (pRTPFrame->pBuffer!=NULL)
		{
			memcpy(pRTPFrame->pBuffer,pPacketData,nPacketLen);
			pRTPFrame->nLen=nPacketLen;

			XAutoLock l(m_csListRTPPacket);
			m_ListRTPPacket.push_back(pRTPFrame);
		}
		else
		{
			pRTPFrame->Release();
			pRTPFrame=NULL;
			return;
		}

		m_bGotFrame=true;
		m_nLastRecvdRTPTime=nRTPTime;

		if (pRTPHeader->marker)//Marker
		{
			PacketsToFrame();
			m_bGotFrame=false;
		}
	}
}

int BaseRTPFrame::GetFrameTestOnly(unsigned char*pFrameBuf,int nBufLen)
{
	int nFrameLen=CalculateFrameSize();
	if (nFrameLen>0)
	{
		if (m_pFrameBuf==NULL || m_nFrameBufLen<nFrameLen)
		{
			if (m_pFrameBuf!=NULL)
			{
				free(m_pFrameBuf);
				m_pFrameBuf=NULL;
			}
			m_nFrameBufLen=m_nHeaderMargin+nFrameLen;
			m_pFrameBuf=(unsigned char*)malloc(m_nFrameBufLen);
		}

		if (m_pFrameBuf==NULL)
		{
			FlushRTPPackets();
			return 0;
		}

		nFrameLen=GetFrame(m_pFrameBuf+m_nHeaderMargin,m_nFrameBufLen-m_nHeaderMargin);

		memcpy(pFrameBuf,m_pFrameBuf+m_nHeaderMargin,nFrameLen);

		return nFrameLen;
	}
	return 0;
}

void BaseRTPFrame::PacketsToFrame(void)
{
	int nFrameLen=CalculateFrameSize()*2;
	if (nFrameLen>0)
	{
		if (m_pFrameBuf==NULL || m_nFrameBufLen<nFrameLen)
		{
			if (m_pFrameBuf!=NULL)
			{
				free(m_pFrameBuf);
				m_pFrameBuf=NULL;
			}
			m_nFrameBufLen=m_nHeaderMargin+nFrameLen;
			m_pFrameBuf=(unsigned char*)malloc(m_nFrameBufLen);
		}

		if (m_pFrameBuf==NULL)
		{
			FlushRTPPackets();
			return;
		}

		nFrameLen=GetFrame(m_pFrameBuf+m_nHeaderMargin,m_nFrameBufLen-m_nHeaderMargin);
		m_rCallback.OnBaseRTPFrameCallbackFramePacket(m_pFrameBuf+m_nHeaderMargin,nFrameLen);
	}
}

bool BaseRTPFrame::DoSendData(void)
{
	bool bRet=false;
	int nSentPackets=0;
	unsigned long ulTimestamp=XGetTimestamp();
	if (ulTimestamp==m_nLastSentPacketTimestamp)
	{
		return bRet;
	}
	m_nLastSentPacketTimestamp=ulTimestamp;
	int nMaxPacketsToSend=m_nMaxPacketsToSend;
	if (m_nBufferedFrameCount>0)
		nMaxPacketsToSend+=1;

	RTPFrame*pRTPFrame=NULL;
	while (nSentPackets<nMaxPacketsToSend)
	{
		{
			XAutoLock l(m_csListRTPPacket);
			if (m_ListRTPPacket.size()>0)
			{
				pRTPFrame=(RTPFrame*)m_ListRTPPacket.front();
				m_ListRTPPacket.pop_front();

				if (pRTPFrame->bFirstPacket)
				{
					m_nBufferedFrameCount--;
				}

				bRet=true;
			}
			else
			{
				break;
			}
		}

		m_rCallback.OnBaseRTPFrameCallbackRTPPacket(pRTPFrame->pBuffer,pRTPFrame->nLen);

		nSentPackets++;

		pRTPFrame->Release();
		pRTPFrame=NULL;

		bRet=true;
	}


	return bRet;
}
