
#include "H264RTPFrame.h"


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
:BaseRTPFrame(rCallback)
{
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

void H264RTPFrame::DoSendFrame(const unsigned char*pFrameData,int nFrameLen,int nWidth,int nHeight,int nKeyFrame,unsigned long ulTimestamp)
{
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
