//VIDEC_Camera.h
#ifndef __VIDEC_CAMERA_H__
#define __VIDEC_CAMERA_H__

#include "VIDEC.h"
 
class VIDEC_CameraCallback
{
public:
	VIDEC_CameraCallback(void){};
	virtual~VIDEC_CameraCallback(void){};
public:
	virtual void OnVIDEC_CameraCallbackImageData(VIDEC_Image*pImage)=0;
};

class VIDEC_Camera
{
public:
	VIDEC_Camera(void){};
	virtual~VIDEC_Camera(void){};
public:
	virtual int Open(int nDevIndex,int& nWidth,int& nHeight,int nFrameRate)=0;
	virtual void Close(void)=0;

	virtual void ShowAdjustVideoWnd(HWND hWnd)=0;
	virtual void ShowVideoInputWnd(HWND hWnd)=0;
	virtual bool HasVideoInputWnd(void)=0;
	virtual bool TVTunerPutChannel(long lChannel)=0;

	static int GetDeviceCount(void);
	static int GetDeviceName(int nDevice,char*szName);

	static VIDEC_Camera*Create(VIDEC_CameraCallback&rCallback,int nType/*0:Old,1:New*/);
};

#endif