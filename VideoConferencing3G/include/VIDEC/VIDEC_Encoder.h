//VIDEC_Encoder.h
#ifndef __VIDEC_ENCODER_H__
#define __VIDEC_ENCODER_H__

#include "VIDEC_Export.h"
#include "VIDEC_CodecDef.h"
#include "VIDEC.h"


class VIDEC_EncoderStreamCallback
{
public:
	VIDEC_EncoderStreamCallback(void){};
	virtual~VIDEC_EncoderStreamCallback(void){};
public:
	//输出AVCON的视频包
	virtual void OnVIDEC_EncoderStreamCallbackFramePacket(void*pPacketData,int nPacketSize,int nWidth,int nHeight)=0;
	virtual void OnVIDEC_EncoderStreamCallbackRTPPacket(void*pPacketData,int nPacketSize,int nWidth,int nHeight)=0;
};

class VIDEC_EncoderStream
{
public:
	VIDEC_EncoderStream(void){};
	virtual~VIDEC_EncoderStream(void){};
public:
	virtual void Close(void)=0;
	virtual int EncodeFrame(VIDEC_Image*pImage,int nBitrate,int nMinQP,int nMaxQP,int nBitrateControlType,VIDEC_CODEC_TYPE codecType)=0;
	virtual void RequestKeyFrame(void)=0;
};

VIDEC_API VIDEC_EncoderStream*VIDEC_EncoderStreamCreate(VIDEC_EncoderStreamCallback&rCallback,bool bRTPPacket);

#endif
