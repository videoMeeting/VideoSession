//VIDEC_DC.h
#ifndef __VIDEC_DC_H__
#define __VIDEC_DC_H__

#include "VIDEC_Export.h"
#include "VIDEC.h"

class VIDEC_API VIDEC_DC
	: public VIDEC_CapDev
{
public:
	VIDEC_DC(void){};
	virtual~VIDEC_DC(void){};
public:
	virtual int Open(HDC hDC,int x,int y,int cx,int cy)=0;
	virtual void Close(void)=0;

	virtual int RequestFrame(void)=0;

	static VIDEC_DC*Create(void);
};

#endif
