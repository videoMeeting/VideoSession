//VIDEC_DCRecord.h
#ifndef __VIDEC_DCRECORD_H__
#define __VIDEC_DCRECORD_H__

#include "VIDEC_Export.h"

class VIDEC_API VIDEC_DCRecord
{
public:
	VIDEC_DCRecord(void){};
	virtual~VIDEC_DCRecord(void){};
public:
	//打开
	//HDC hDC:要采集的DC
	//int x,int y,int cx,int cy:要采集的区域，x,y是位移，cx,xy是宽高
	virtual int Open(HDC hDC,int x,int y,int cx,int cy,const char*cszPathName,int nFrameRate=5,int nQuality=3,int nBitrateControlType=VIDEC_BITRATE_CONTROL_CQP)=0;
	//关闭
	virtual void Close(void)=0;
	//采集一帧
	virtual void CaptureFrame(void)=0;
	//是否压缩完成
	virtual bool IsDone(void)=0;

	//创建对象
	static VIDEC_DCRecord*Create(void);
};

#endif