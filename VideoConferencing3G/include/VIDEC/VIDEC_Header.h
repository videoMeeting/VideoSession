//VIDEC_Header.h
#ifndef __VIDEC_HEADER_H__
#define __VIDEC_HEADER_H__

#ifdef _WIN32
#include <winsock2.h>
#define __INLINE__	_inline
#else
#define __INLINE__	inline
#endif

//#define USER_SUBCONTRACTING

#define VIDEC_KEY_SUBCONTRACTING_LEN			4

typedef struct tagVIDEC_KEY_SUBCONTRACTING {
    unsigned short ubeing;
    unsigned short uend;
}VIDEC_KEY_SUBCONTRACTING, *pVIDEC_KEY_SUBCONTRACTING;

__INLINE__ void VIDEC_KEY_SUBCONTRACTING_RESET(void*p)
{
	pVIDEC_KEY_SUBCONTRACTING pHeader=(pVIDEC_KEY_SUBCONTRACTING)p;
	pHeader->ubeing=0;
	pHeader->uend=0;
}

__INLINE__ void VIDEC_KEY_SUBCONTRACTING_SET_BEGING(const void*p, unsigned short v)
{
	pVIDEC_KEY_SUBCONTRACTING pHeader=(pVIDEC_KEY_SUBCONTRACTING)p;
    pHeader->ubeing = v;
}

__INLINE__ unsigned short VIDEC_KEY_SUBCONTRACTING_GET_BEGING(const void*p)
{
	pVIDEC_KEY_SUBCONTRACTING pHeader=(pVIDEC_KEY_SUBCONTRACTING)p;
	return pHeader->ubeing;
}

__INLINE__ void VIDEC_KEY_SUBCONTRACTING_SET_END(const void*p, unsigned short v)
{
	pVIDEC_KEY_SUBCONTRACTING pHeader=(pVIDEC_KEY_SUBCONTRACTING)p;
    pHeader->uend = v;
}

__INLINE__ unsigned short VIDEC_KEY_SUBCONTRACTING_GET_END(const void*p)
{
	pVIDEC_KEY_SUBCONTRACTING pHeader=(pVIDEC_KEY_SUBCONTRACTING)p;
	return pHeader->uend;
}

__INLINE__ unsigned short VIDEC_KEY_SUBCONTRACTING_GET_LEN(const void*p)
{
    return VIDEC_KEY_SUBCONTRACTING_LEN;
}

#define VIDEC_HEADER_EXT_VER_02					0x02
#define VIDEC_HEADER_EXT_LEN					8
#define VIDEC_HEADER_EXT_KEY_FRAME_LEN			16

typedef struct tagVIDEC_HEADER_EXT
{
	unsigned short ver:2;
	unsigned short codecid:6;
	unsigned short even_field_first:1;	//even_field_first 
	unsigned short double_field:1;		//double field 
	unsigned short keyframe:1;			//has keyframe
	unsigned short hardware:1;			//hardware
	unsigned short bframe:1;			//has bframe
	unsigned short main_frame:1;		//has main_frame
	unsigned short sub_frame:1;			//has sub_frame
	unsigned short qsub_frame:1;		//has qsub_frame

	unsigned short seq;
	unsigned int   ts;

	unsigned short actual_width;
	unsigned short actual_height;
	unsigned short virtual_width;
	unsigned short virtual_height;
}VIDEC_HEADER_EXT,*PVIDEC_HEADER_EXT;


__INLINE__ void VIDEC_HEADER_EXT_RESET(void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->ver=VIDEC_HEADER_EXT_VER_02;
	pHeader->codecid=0;
	pHeader->even_field_first=1;
	pHeader->double_field=0;
	pHeader->keyframe=0;
	pHeader->bframe=0;
	pHeader->hardware=0;
	pHeader->main_frame=0;
	pHeader->sub_frame=0;
	pHeader->qsub_frame=0;
	pHeader->seq=0;
	pHeader->ts=0;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_IS_VALID(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	if (pHeader->ver==VIDEC_HEADER_EXT_VER_02)
	{
		return 1;
	}
	return 0;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_CODEC_ID(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->codecid;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_CODEC_ID(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->codecid=v;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_EVEN_FIELD_FIRST(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->even_field_first;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_EVEN_FIELD_FIRST(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->even_field_first=v;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_DOUBLE_FIELD(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->double_field;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_DOUBLE_FIELD(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->double_field=v;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_KEYFRAME(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->keyframe;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_KEYFRAME(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->keyframe=v;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_MAIN_FRAME(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->main_frame;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_MAIN_FRAME(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->main_frame=v;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_SUB_FRAME(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->sub_frame;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_SUB_FRAME(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->sub_frame=v;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_QSUB_FRAME(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->qsub_frame;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_QSUB_FRAME(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->qsub_frame=v;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_BFRAME(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->bframe;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_BFRAME(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->bframe=v;
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_HARDWARE(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return pHeader->hardware;
}

__INLINE__ void VIDEC_HEADER_EXT_SET_HARDWARE(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->hardware=v;
}


__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_SEQUENCE(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return ntohs(pHeader->seq);
}

__INLINE__ void VIDEC_HEADER_EXT_SET_SEQUENCE(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->seq=htons(v);
}

__INLINE__ unsigned int VIDEC_HEADER_EXT_GET_TIMESTAMP(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return ntohl(pHeader->ts);
}

__INLINE__ void VIDEC_HEADER_EXT_SET_TIMESTAMP(void*p,unsigned int v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->ts=htonl(v);
}


__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_ACTUAL_WIDTH(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return ntohs(pHeader->actual_width);
}

__INLINE__ void VIDEC_HEADER_EXT_SET_ACTUAL_WIDTH(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->actual_width=htons(v);
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_ACTUAL_HEIGHT(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return ntohs(pHeader->actual_height);
}

__INLINE__ void VIDEC_HEADER_EXT_SET_ACTUAL_HEIGHT(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->actual_height=htons(v);
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_VIRTUAL_WIDTH(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return ntohs(pHeader->virtual_width);
}

__INLINE__ void VIDEC_HEADER_EXT_SET_VIRTUAL_WIDTH(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->virtual_width=htons(v);
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_VIRTUAL_HEIGHT(const void*p)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	return ntohs(pHeader->virtual_height);
}

__INLINE__ void VIDEC_HEADER_EXT_SET_VIRTUAL_HEIGHT(void*p,unsigned short v)
{
	PVIDEC_HEADER_EXT pHeader=(PVIDEC_HEADER_EXT)p;
	pHeader->virtual_height=htons(v);
}

__INLINE__ unsigned short VIDEC_HEADER_EXT_GET_LEN(const void*p)
{
	if (VIDEC_HEADER_EXT_GET_KEYFRAME(p))
	{
		return VIDEC_HEADER_EXT_KEY_FRAME_LEN;
	}
	
	return VIDEC_HEADER_EXT_LEN;
}



#endif


