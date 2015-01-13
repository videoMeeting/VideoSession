//VIDEC_Codec.h
#ifndef __VIDEC_CODEC_H__
#define __VIDEC_CODEC_H__

#include "VIDEC_Export.h"
#include "VIDEC_CodecDef.h"
#include "VIDEC.h"

VIDEC_API void VIDEC_SetMaxKeyFrameInterval(unsigned long ulMS);
VIDEC_API unsigned long VIDEC_GetMaxKeyFrameInterval(void);

//
class VIDEC_EncoderCallback
{
public:
	VIDEC_EncoderCallback(void){};
	virtual~VIDEC_EncoderCallback(void){};
public:
	//输出AVCON的视频包
	virtual void OnVIDEC_EncoderCallbackFramePacket(void*pPacketData,int nPacketLen)=0;
	virtual void OnVIDEC_EncoderCallbackRTPPacket(void*pPacketData,int nPacketSize)=0;
};

class VIDEC_Encoder
{
public:
	VIDEC_Encoder(void){};
	virtual~VIDEC_Encoder(void){};
public:
	virtual void Close(void)=0;
	virtual int EncodeFrame(void*pFrameData,int nFrameSize,int nVirtualWidth,int nVirtualHeight,bool bEventFieldFirst,bool bHardware)=0;
	virtual void RequestKeyFrame(void)=0;
	virtual bool DoRTPPacket(void)=0;
};

VIDEC_API VIDEC_Encoder*VIDEC_EncoderCreate(VIDEC_EncoderCallback&rCallback,int nWidth,int nHeight,int nFrameRate,VIDEC_CODEC_TYPE codecType,bool bDoubleField,int nBitrate,int nMinQP,int nMaxQP,int nBitrateControlType,bool bRTPPacket);

class VIDEC_Decoder;
class VIDEC_DecoderCallback
{
public:
	VIDEC_DecoderCallback(void){};
	virtual~VIDEC_DecoderCallback(void){};
public:
	virtual void OnVIDEC_DecoderCallbackFrame(VIDEC_Decoder*pDecoderFrame,VIDEC_Image*pImage)=0;
	virtual void OnVIDEC_DecoderCallbackFramePacket(VIDEC_Decoder*pDecoderFrame,void*pPacketData,int nPacketLen,int nWidth,int nHeight){};
};

class VIDEC_Decoder
{
public:
	VIDEC_Decoder(void){};
	virtual~VIDEC_Decoder(void){};
public:
	virtual void Close(void)=0;
	virtual int DecodeFramePacket(void*pPacketData,int nPacketSize)=0;
	virtual int DecodeRTPPacket(void*pPacketData,int nPacketSize)=0;
};

VIDEC_API VIDEC_Decoder*VIDEC_DecoderCreate(VIDEC_DecoderCallback&rCallback,VIDEC_CODEC_TYPE codecType,int nWidth,int nHeight);



#endif