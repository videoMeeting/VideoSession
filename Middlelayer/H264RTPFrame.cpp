
#include "H264RTPFrame.h"
#include <NETEC/XUtil.h>

const unsigned char *avc_find_startcode(const unsigned char *p, const unsigned char *end)
{
    const unsigned char *a = p + 4 - ((long)p & 3);

    for( end -= 3; p < a && p < end; p++ ) {
        if( p[0] == 0 && p[1] == 0 && p[2] == 1 )
            return p;
    }

    for( end -= 3; p < end; p += 4 ) {
        unsigned long x = *(const unsigned long*)p;
//      if( (x - 0x01000100) & (~x) & 0x80008000 ) // little endian
//      if( (x - 0x00010001) & (~x) & 0x00800080 ) // big endian
        if( (x - 0x01010101) & (~x) & 0x80808080 ) { // generic
            if( p[1] == 0 ) {
                if( p[0] == 0 && p[2] == 1 )
                    return p-1;
                if( p[2] == 0 && p[3] == 1 )
                    return p;
            }
            if( p[3] == 0 ) {
                if( p[2] == 0 && p[4] == 1 )
                    return p+1;
                if( p[4] == 0 && p[5] == 1 )
                    return p+2;
            }
        }
    }

    for( end += 3; p < end; p++ ) {
        if( p[0] == 0 && p[1] == 0 && p[2] == 1 )
            return p;
    }

    return end + 3;
}


H264RTPFrame::H264RTPFrame(BaseRTPFrameCallback&rCallback)
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

H264RTPFrame::~H264RTPFrame(void)
{

}

int H264RTPFrame::get_codec_header_len(void)
{
	return 0;
}


int H264RTPFrame::handle_rtp_packet(unsigned char*buf,int len,unsigned char*pFrameBuf,int nBufLen)
{
    unsigned char nal = buf[0];
    unsigned char type = (nal & 0x1f);
    int result= 0;
    unsigned char start_sequence[]= {0, 0, 0, 1};

    if (type >= 1 && type <= 23)
        type = 1;              // simplify the case. (these are all the nal types used internally by the h264 codec)
    switch (type) 
	{
    case 1:
        memcpy(pFrameBuf, start_sequence, sizeof(start_sequence));
        memcpy(pFrameBuf+sizeof(start_sequence), buf, len);
		result=sizeof(start_sequence)+len;
        break;
    case 28:                   // FU-A (fragmented nal)
        buf++;
        len--;                  // skip the fu_indicator
        {
            // these are the same as above, we just redo them here for clarity...
            unsigned char fu_indicator = nal;
            unsigned char fu_header = *buf;   // read the fu_header.
            unsigned char start_bit = fu_header >> 7;
//            unsigned char end_bit = (fu_header & 0x40) >> 6;
            unsigned char nal_type = (fu_header & 0x1f);
            unsigned char reconstructed_nal;

            // reconstruct this packet's true nal; only the data follows..
            reconstructed_nal = fu_indicator & (0xe0);  // the original nal forbidden bit and NRI are stored in this packet's nal;
            reconstructed_nal |= nal_type;

            // skip the fu_header...
            buf++;
            len--;

            if(start_bit) 
			{
                // copy in the start sequence, and the reconstructed nal....
                memcpy(pFrameBuf, start_sequence, sizeof(start_sequence));
                pFrameBuf[sizeof(start_sequence)]= reconstructed_nal;
                memcpy(pFrameBuf+sizeof(start_sequence)+sizeof(nal), buf, len);
				result=sizeof(start_sequence)+sizeof(nal)+len;
            } 
			else 
			{
                memcpy(pFrameBuf, buf, len);
				result=len;
            }
        }
        break;
    default:
        result= 0;
        break;
    }

    return result;
}

void H264RTPFrame::DoSendFrame(const unsigned char*pFrameData,int nFrameLen,int nWidth,int nHeight,int nKeyFrame,unsigned long ulTimestamp, int last)
{
#if 0
	const unsigned char *buf1=pFrameData;
	int size=nFrameLen;
    const unsigned char *r;
    r = avc_find_startcode(buf1, buf1 + size);
    while (r < buf1 + size) 
	{
        const unsigned char *r1;

        while(!*(r++));
        r1 = avc_find_startcode(r, buf1 + size);
        nal_send(r, r1 - r, (r1 == buf1 + size));
        r = r1;
    }
#endif
    nal_send(pFrameData, nFrameLen, last);
}


void H264RTPFrame::nal_send(const unsigned char *buf, int size, int last)
{
	unsigned char*pRTPPacketBuf=NULL;
    if (size <= m_nMaxRTPPayloadBufLen) 
	{
		RTPFrame*pRTPFrame=new RTPFrame;
		if (pRTPFrame==NULL)
		{
			return;
		}

		pRTPFrame->nLen=RTP_HEADER_LEN+size;
		pRTPPacketBuf=(unsigned char*)malloc(pRTPFrame->nLen);
		if (pRTPPacketBuf==NULL)
		{
			pRTPFrame->Release();
			pRTPFrame=NULL;
			return;
		}

		pRTPFrame->pBuffer=pRTPPacketBuf;
		memcpy(pRTPPacketBuf+RTP_HEADER_LEN,buf,size);

		set_rtp_header(pRTPPacketBuf,last!=0);
		SendRTPPacket(pRTPFrame);
	} 
	else 
	{
		RTPFrame*pRTPFrame=new RTPFrame;
		if (pRTPFrame==NULL)
		{
			return;
		}

		pRTPFrame->nLen=m_nMaxRTPFrameSize;
		pRTPPacketBuf=(unsigned char*)malloc(pRTPFrame->nLen);
		if (pRTPPacketBuf==NULL)
		{
			pRTPFrame->Release();
			pRTPFrame=NULL;
			return;
		}

		pRTPFrame->pBuffer=pRTPPacketBuf;
		unsigned char*rtp_payload_buf=pRTPPacketBuf+RTP_HEADER_LEN;

		unsigned char type = buf[0] & 0x1F;
		unsigned char nri = buf[0] & 0x60;

		rtp_payload_buf[0] = 28;        
		rtp_payload_buf[0] |= nri;
		rtp_payload_buf[1] = type;
		rtp_payload_buf[1] |= 1 << 7;
		buf += 1;
		size -= 1;
		while (size + 2 > m_nMaxRTPPayloadBufLen) 
		{
			memcpy(&rtp_payload_buf[2], buf, m_nMaxRTPPayloadBufLen - 2);

			{
				set_rtp_header(pRTPPacketBuf,0);

				SendRTPPacket(pRTPFrame);
			}

			pRTPFrame=new RTPFrame;
			if (pRTPFrame==NULL)
			{
				return;
			}

			pRTPFrame->nLen=m_nMaxRTPFrameSize;
			pRTPPacketBuf=(unsigned char*)malloc(pRTPFrame->nLen);
			if (pRTPPacketBuf==NULL)
			{
				pRTPFrame->Release();
				pRTPFrame=NULL;
				return;
			}

			pRTPFrame->pBuffer=pRTPPacketBuf;
			rtp_payload_buf=pRTPPacketBuf+RTP_HEADER_LEN;

			rtp_payload_buf[0] = 28;        
			rtp_payload_buf[0] |= nri;
			rtp_payload_buf[1] = type;
			rtp_payload_buf[1] |= 1 << 7;

			buf += m_nMaxRTPPayloadBufLen - 2;
			size -= m_nMaxRTPPayloadBufLen - 2;
			rtp_payload_buf[1] &= ~(1 << 7);
		}
		rtp_payload_buf[1] |= 1 << 6;
		memcpy(&rtp_payload_buf[2], buf, size);

		{
			pRTPFrame->nLen=RTP_HEADER_LEN + size + 2;	

			//char szDebug[1024];
			//sprintf(szDebug,"1 size=%d pRTPFrame->nLen=%d\n",size,pRTPFrame->nLen);
			//OutputDebugString(szDebug);

			set_rtp_header(pRTPPacketBuf,last!=0);

			//sprintf(szDebug,"2 size=%d pRTPFrame->nLen=%d\n",size,pRTPFrame->nLen);
			//OutputDebugString(szDebug);

			SendRTPPacket(pRTPFrame);
		}
    }
}

int H264RTPFrame::Open(int nPayloadType,int nMaxRTPFrameSize,int nHeaderMargin)
{
    m_nHeaderMargin=nHeaderMargin;
    m_nPayloadType=nPayloadType;
    m_nMaxRTPFrameSize=nMaxRTPFrameSize;
    m_nMaxRTPPayloadBufLen=m_nMaxRTPFrameSize-RTP_HEADER_LEN-get_codec_header_len();
    return 0;
}

void H264RTPFrame::Close(void)
{
    FlushRTPPackets();
    
    if (m_pFrameBuf!=NULL)
    {
        free(m_pFrameBuf);
        m_pFrameBuf=NULL;
    }
    m_nFrameBufLen=0;
}

void H264RTPFrame::FlushRTPPackets(void)
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


int H264RTPFrame::CalculateFrameSize(void)
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

int H264RTPFrame::GetFrame(unsigned char*pFrameBuf,int nBufLen)
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


void H264RTPFrame::SendFrame(const unsigned char*pFrameData,int nFrameLen,int nWidth,int nHeight,int nKeyFrame,unsigned long ulTimestamp, int last)
{
    m_nRTPTimestamp=ulTimestamp;
    
    DoSendFrame(pFrameData,nFrameLen,nWidth,nHeight,nKeyFrame,ulTimestamp, last);
}

void H264RTPFrame::SendFrameHeader(unsigned char*pRTPPacket,int nPacketLen)
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

void H264RTPFrame::set_rtp_header(unsigned char*pHeader,bool bMarker)
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

void H264RTPFrame::SendRTPPacket(RTPFrame*pRTPFrame)
{
    m_rCallback.OnBaseRTPFrameCallbackRTPPacket(pRTPFrame->pBuffer,pRTPFrame->nLen);
    
    pRTPFrame->Release();
    pRTPFrame=NULL;
    
    //XAutoLock l(m_csListRTPPacket);
    //m_ListRTPPacket.push_back(pRTPFrame);
}


void H264RTPFrame::OnRecvdRTPPacket(void*pPacketData,int nPacketLen)
{
    unsigned char*pFrameData=(unsigned char*)pPacketData;
    if (pFrameData!=NULL && nPacketLen>=12)
    {
        PRTP_HEADER pRTPHeader=(PRTP_HEADER)pFrameData;
        unsigned long nRTPTime=ntohl(pRTPHeader->timestamp);
        
        //char szDebug[1024];
        //sprintf(szDebug,"nRTPTime=%u m_nLastRecvdRTPTime=%u\n",nRTPTime,m_nLastRecvdRTPTime);
        //OutputDebugString(szDebug);
#if 0
        if (m_bGotFrame && m_nLastRecvdRTPTime!=nRTPTime)
        {
            PacketsToFrame();
            m_bGotFrame=false;
        }
#endif
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

int H264RTPFrame::GetFrameTestOnly(unsigned char*pFrameBuf,int nBufLen)
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

void H264RTPFrame::PacketsToFrame(void)
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

bool H264RTPFrame::DoSendData(void)
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

