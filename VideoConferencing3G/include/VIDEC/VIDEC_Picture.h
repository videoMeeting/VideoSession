#ifndef __VIDEC_PICTURE_H__
#define __VIDEC_PICTURE_H__

#include "VIDEC.h"

class VIDEC_API VIDEC_Picture
{
public:
	VIDEC_Picture(void){};
	virtual~VIDEC_Picture(void){};
public:
	virtual int Open(HWND hWnd,const char*cszPathName)=0;
	virtual void Close(void)=0;
	virtual void ShowWindow(bool bShow)=0;
	virtual bool IsWindowVisible(void)=0;
	virtual void SetWindowPosition(int x,int y,int cx,int cy)=0;
	virtual int GetWidth(void)=0;
	virtual int GetHeight(void)=0;

	static VIDEC_Picture*Create(void);
};

#endif