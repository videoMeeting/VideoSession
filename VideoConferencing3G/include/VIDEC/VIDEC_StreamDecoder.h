//VIDEC_StreamDecoder.h
#ifndef __VIDEC_STREAMDECODER_H__
#define __VIDEC_STREAMDECODER_H__

#include "VIDEC_Export.h"

class VIDEC_API VIDEC_StreamDecoder
{
public:
	VIDEC_StreamDecoder(void){};
	virtual~VIDEC_StreamDecoder(void){};
public:
	//打开解码器
	//成功返回0，否则返回-1
	virtual int Open(void)=0;
	//关闭解码器
	virtual void Close(void)=0;
	//解码，输入的PacketData是含有VIDEC数据头的数据
	//输出YUV[4:2:0]的图象和图象的宽和高
	//成功返回0，否则返回-1
	virtual int Decode(void*pPacketData,int nPacketLen,void**ppYUVData,int&nWidth,int&nHeight)=0;
	//创建解码器
	static VIDEC_StreamDecoder*Create(void);
};

#endif
