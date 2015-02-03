//H264RTPFrame.h
#ifndef __H264RTPFRAME_H__
#define __H264RTPFRAME_H__

#include "BaseRTPFrame.h"

//RFC3984


class H264RTPFrame
	: public BaseRTPFrame
{
public:
	H264RTPFrame(BaseRTPFrameCallback&rCallback);
	virtual~H264RTPFrame(void);
public:
	virtual void DoSendFrame(const unsigned char*pFrameData,int nFrameLen,int nWidth,int nHeight,int nKeyFrame,unsigned long ulTimestamp);
protected:
	void nal_send(const unsigned char *buf, int size, int last);
	int handle_rtp_packet( unsigned char*pPayloadData,int nPayloadLen,unsigned char*pFrameBuf,int nBufLen);
	int get_codec_header_len(void);
};

#endif