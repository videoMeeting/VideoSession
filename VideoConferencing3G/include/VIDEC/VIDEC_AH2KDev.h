//VIDEC_AH2KDev.h
#ifndef __VIDEC_AH2KDEV_H__
#define __VIDEC_AH2KDEV_H__

#include "VIDEC.h"

//AH2K采集源
class VIDEC_API VIDEC_AH2KDev
	: public VIDEC_CapDev
	, public VIDEC_StreamSource
{
public:
	VIDEC_AH2KDev(void){}
	virtual~VIDEC_AH2KDev(void){};
public:
	//打开设备
	//nDevID设备号，从0开始
	//nWidth,图象宽度
	//nHeight,图象高度
	//nFrameRate,帧率，1-30
	//bInterlaced,是否隔行扫描
	//成功返回0，失败返回-1
	virtual int Open(int nDevID,int nWidth,int nHeight,int nFrameRate,bool bDenoise=true)=0;
	//关闭设置
	virtual void Close(void)=0;
	//重置设备
	//nDevID设备号，从0开始
	//nWidth,图象宽度
	//nHeight,图象高度
	//nFrameRate,帧率，1-30
	//bInterlaced,是否隔行扫描
	//成功返回0，失败返回-1
	virtual int Reset(int nDevID,int nWidth,int nHeight,int nFrameRate,bool bDenoise=true)=0;

	virtual int SetVideoParam(int nBrightness=128/*亮度值0-255*/, int nContrast=64/*对比度0-127*/, int nSaturation=64/*饱和度0-127*/, int nHue=0/*色调0-255*/,int nGamma=100/*伽马1-400*/,int nSharpen=0/*锐化0-127*/)=0;
 	
	virtual int StartVideoStream(int nBitrate,int nBitrateControlType,int qmin,int qmax)=0;
	virtual int RequestKeyFrame(void)=0;
	virtual int StopVideoStream(void)=0;

	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;
 
	//创建接口
	static VIDEC_AH2KDev*Create(void);

	//取设备个数
	static int GetDevCount(void);
	//取设备名称
	static int GetDevName(unsigned int nDevIndex,char*szName,int nMaxCount);
	static int GetDevType(unsigned int nDevIndex,VIDEC_DEV_TYPE&nDevType);
	static bool HasAudioInput(unsigned int nDevIndex);
	static bool SupportHardwareEncoding(unsigned int nDevIndex);


	//列出可裁剪的格式的个数
	static int GetFormatCount(void);
	//取格式名称
	static int GetFormatName(int nIndex,char*szName,int nMaxCount);
	//取格式大小
	static int GetFormatSize(int nIndex,int&nWidth,int&nHeight);
	//example
	//int nCount=VIDEC_AH2KDev::GetFormatCount();
	//for (int i=0;i<nCount;i++)
	//{
	//	char szName[128];
	//	VIDEC_AH2KDev::GetFormatName(i,szName,127);
	//	int nWidth=0;
	//	int nHeight=0;
	//	VIDEC_AH2KDev::GetFormatSize(i,nWidth,nHeight);
	//}
};

#endif