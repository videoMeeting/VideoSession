//VIDEC_AH2K.h
#ifndef __VIDEC_AH2K_H__
#define __VIDEC_AH2K_H__

#include "VIDEC.h"


class VIDEC_AH2KCallback
{
public:
	VIDEC_AH2KCallback(void){};
	virtual~VIDEC_AH2KCallback(void){};
public:
	virtual void OnVIDEC_AH2KCallbackImage(VIDEC_Image*pImage)=0;
	virtual void OnVIDEC_AH2KCallbackAudioData(short*pSamples,int nSamples,int nSampleRate)=0;
	virtual void OnVIDEC_AH2KCallbackVideoStreamData(unsigned char*pData,int nLen,int nWidth,int nHeight,int nHeaderLen)=0;
};

class VIDEC_AH2K
{
public:
	VIDEC_AH2K(void){};
	virtual~VIDEC_AH2K(void){};
public:
	virtual int Open(int nDevID,int nWidth,int nHeight,int nFrameRate)=0;
	virtual void Close(void)=0;
	virtual int StartVideoStream(int nBitrate,int nBitrateControlType,int qmin,int qmax)=0;
	virtual int RequestKeyFrame(void)=0;
	virtual int StopVideoStream(void)=0;

	static int Init(void);
	static void Terminate(void);

	static int GetDevCount(void);
	static int GetDevName(int nDevID,char*szName,int nMaxCount);
	static int GetDevType(int nDevID,VIDEC_DEV_TYPE&nDevType);//SD HD VGA
	static bool HasAudioInput(int nDevID);
	static bool SupportHardwareEncoding(int nDevID);

	static VIDEC_AH2K*Create(VIDEC_AH2KCallback&rCallback);
};


#endif