//NETEC.h
#ifndef __NETEC_H__
#define __NETEC_H__

#include "NETEC/NETEC_Export.h"

class NETEC
{
public:
	typedef enum{
		BROTHER=0,
		PARENT,
		CHILD,
	}DOMAIN_TYPE;

	typedef enum{
		ERR_OK=0,
		ERR_DOMAIN_TYPE_UNMATCHED,
		ERR_DOMAIN_LEVEL_UNMATCHED,
	}ERR_CODE;
public:
	static const char*GetVersion(void);
};

//帧率控制模式
typedef enum
{
	FRAME_RATE_CONTROL_MODE_FULL=0,	//全帧率控制
	FRAME_RATE_CONTROL_MODE_HALF,	//半帧率控制
	FRAME_RATE_CONTROL_MODE_AUTO,	//自动帧率控制
}FRAME_RATE_CONTROL_MODE;

typedef enum
{
	FRAME_TYPE_CONTROL_MODE_MAIN=0,	//主流
	FRAME_TYPE_CONTROL_MODE_SUB,	//子流
	FRAME_TYPE_CONTROL_MODE_QSUB,	//孙流
}FRAME_TYPE_CONTROL_MODE;

#endif
