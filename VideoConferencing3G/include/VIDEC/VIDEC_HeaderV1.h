//VIDEC_HeaderV1.h
#ifndef __VIDEC_HEADER_V1_H__
#define __VIDEC_HEADER_V1_H__

#ifdef _WIN32
#include <winsock2.h>
#define __INLINE__	_inline
#else
#define __INLINE__	inline
#endif


#define VIDEC_HEADER_VER_01						0x01
#define VIDEC_HEADER_LEN						16
#define VIDEC_HEADER_KEY_FRAME_LEN				24


typedef struct tagVIDEC_HEADER
{
	unsigned short ver:2;
	unsigned short codecid:6;
	unsigned short even_field_first:1;	//even_field_first 
	unsigned short double_field:1;		//double field 
	unsigned short even_keyframe:1;		//even field has keyframe
	unsigned short odd_keyframe:1;		//odd field has keyframe
	unsigned short sub_keyframe0:1;		//sub keyframe 
	unsigned short sub_keyframe1:1;		//sub keyframe 
	unsigned short sub_keyframe2:1;		//sub keyframe 
	unsigned short sub_keyframe3:1;		//sub keyframe 

	unsigned short seq;
	unsigned int   ts;
	unsigned int   even_size;			//duration
	unsigned int   odd_size;			//audio packet len

	unsigned short actual_width;
	unsigned short actual_height;
	unsigned short virtual_width;
	unsigned short virtual_height;
}VIDEC_HEADER,*PVIDEC_HEADER;

__INLINE__ void VIDEC_HEADER_RESET(void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->ver=VIDEC_HEADER_VER_01;
	pHeader->codecid=0;
	pHeader->even_field_first=1;
	pHeader->double_field=0;
	pHeader->even_keyframe=0;
	pHeader->odd_keyframe=0;
	pHeader->sub_keyframe0=0;
	pHeader->sub_keyframe1=0;
	pHeader->sub_keyframe2=0;
	pHeader->sub_keyframe3=0;
	pHeader->seq=0;
	pHeader->ts=0;
	pHeader->even_size=0;
	pHeader->odd_size=0;
}

__INLINE__ unsigned short VIDEC_HEADER_IS_VALID(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	if (pHeader->ver==VIDEC_HEADER_VER_01)
	{
		return 1;
	}
	return 0;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_CODEC_ID(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->codecid;
}

__INLINE__ void VIDEC_HEADER_SET_CODEC_ID(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->codecid=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_EVEN_FIELD_FIRST(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->even_field_first;
}

__INLINE__ void VIDEC_HEADER_SET_EVEN_FIELD_FIRST(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->even_field_first=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_DOUBLE_FIELD(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->double_field;
}

__INLINE__ void VIDEC_HEADER_SET_DOUBLE_FIELD(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->double_field=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_EVEN_KEYFRAME(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->even_keyframe;
}

__INLINE__ void VIDEC_HEADER_SET_EVEN_KEYFRAME(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->even_keyframe=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_ODD_KEYFRAME(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->odd_keyframe;
}

__INLINE__ void VIDEC_HEADER_SET_ODD_KEYFRAME(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->odd_keyframe=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_SUB_KEYFRAME0(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->sub_keyframe0;
}

__INLINE__ void VIDEC_HEADER_SET_SUB_KEYFRAME0(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->sub_keyframe0=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_SUB_KEYFRAME1(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->sub_keyframe1;
}

__INLINE__ void VIDEC_HEADER_SET_SUB_KEYFRAME1(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->sub_keyframe1=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_SUB_KEYFRAME2(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->sub_keyframe2;
}

__INLINE__ void VIDEC_HEADER_SET_SUB_KEYFRAME2(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->sub_keyframe2=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_SUB_KEYFRAME3(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return pHeader->sub_keyframe3;
}

__INLINE__ void VIDEC_HEADER_SET_SUB_KEYFRAME3(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->sub_keyframe3=v;
}

__INLINE__ unsigned short VIDEC_HEADER_GET_KEY_FRAME(void*p)
{
	return (VIDEC_HEADER_GET_EVEN_KEYFRAME(p)| VIDEC_HEADER_GET_ODD_KEYFRAME(p));
}

__INLINE__ unsigned short VIDEC_HEADER_GET_SEQUENCE(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return ntohs(pHeader->seq);
}

__INLINE__ void VIDEC_HEADER_SET_SEQUENCE(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->seq=htons(v);
}

__INLINE__ unsigned int VIDEC_HEADER_GET_TIMESTAMP(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return ntohl(pHeader->ts);
}

__INLINE__ void VIDEC_HEADER_SET_TIMESTAMP(void*p,unsigned int v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->ts=htonl(v);
}

__INLINE__ unsigned int VIDEC_HEADER_GET_EVEN_SIZE(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return ntohl(pHeader->even_size);
}

__INLINE__ void VIDEC_HEADER_SET_EVEN_SIZE(void*p,unsigned int v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->even_size=htonl(v);
}

__INLINE__ unsigned int VIDEC_HEADER_GET_ODD_SIZE(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return ntohl(pHeader->odd_size);
}

__INLINE__ void VIDEC_HEADER_SET_ODD_SIZE(void*p,unsigned int v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->odd_size=htonl(v);
}

__INLINE__ unsigned short VIDEC_HEADER_GET_ACTUAL_WIDTH(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return ntohs(pHeader->actual_width);
}

__INLINE__ void VIDEC_HEADER_SET_ACTUAL_WIDTH(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->actual_width=htons(v);
}

__INLINE__ unsigned short VIDEC_HEADER_GET_ACTUAL_HEIGHT(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return ntohs(pHeader->actual_height);
}

__INLINE__ void VIDEC_HEADER_SET_ACTUAL_HEIGHT(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->actual_height=htons(v);
}

__INLINE__ unsigned short VIDEC_HEADER_GET_VIRTUAL_WIDTH(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return ntohs(pHeader->virtual_width);
}

__INLINE__ void VIDEC_HEADER_SET_VIRTUAL_WIDTH(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->virtual_width=htons(v);
}

__INLINE__ unsigned short VIDEC_HEADER_GET_VIRTUAL_HEIGHT(const void*p)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	return ntohs(pHeader->virtual_height);
}

__INLINE__ void VIDEC_HEADER_SET_VIRTUAL_HEIGHT(void*p,unsigned short v)
{
	PVIDEC_HEADER pHeader=(PVIDEC_HEADER)p;
	pHeader->virtual_height=htons(v);
}

__INLINE__ unsigned short VIDEC_HEADER_GET_LEN(const void*p)
{
	if ((VIDEC_HEADER_GET_EVEN_KEYFRAME(p) || VIDEC_HEADER_GET_ODD_KEYFRAME(p)))
	{
		return VIDEC_HEADER_KEY_FRAME_LEN;
	}
	
	return VIDEC_HEADER_LEN;
}



#endif


