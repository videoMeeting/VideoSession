//VIDEC_Decoder.h
#ifndef __VIDEC_DECODER_H__
#define __VIDEC_DECODER_H__

#include "VIDEC_Export.h"
#include "VIDEC_CodecDef.h"
#include "VIDEC.h"


//自动识别视频大小，帧率和编码
class VIDEC_DecoderStreamCallback
{
public:
	VIDEC_DecoderStreamCallback(void){};
	virtual~VIDEC_DecoderStreamCallback(void){};
public:
	virtual void OnVIDEC_DecoderStreamCallbackFrame(VIDEC_Image*pImage)=0;
	virtual void OnVIDEC_DecoderStreamCallbackFramePacket(void*pPacketData,int nPacketSize,int nWidth,int nHeight){};
};

class VIDEC_DecoderStream
{
public:
	VIDEC_DecoderStream(void){};
	virtual~VIDEC_DecoderStream(void){};
public:
	virtual void Close(void)=0;
	virtual int DecodeFramePacket(void*pPacketData,int nPacketSize)=0;
	virtual int DecodeRTPPacket(void*pPacketData,int nPacketSize)=0;
};

VIDEC_API VIDEC_DecoderStream*VIDEC_DecoderStreamCreate(VIDEC_DecoderStreamCallback&rCallback);
VIDEC_API VIDEC_DecoderStream*VIDEC_DecoderStreamCreate(VIDEC_DecoderStreamCallback&rCallback,int nWidth,int nHeight,VIDEC_CODEC_TYPE CodecType);


#endif


