//AUDEC_Header.h
#ifndef __AUDEC_HEADER_H__
#define __AUDEC_HEADER_H__


#ifdef _WIN32
#include <winsock2.h>
#define __INLINE__	_inline
#else
#define __INLINE__	inline

#ifndef _WIN32_WCE
#include <netinet/in.h>
#endif

#endif





#define AUDEC_HEADER_VER_01					0x01
#define AUDEC_HEADER_VER_01_LEN				8


typedef struct tagAUDEC_HEADER
{
	unsigned short ver:2;
	unsigned short tcp:1;
	unsigned short dual:1;	
	unsigned short fec:1;
	unsigned short syn_point:1;
	unsigned short reserved:2;
	unsigned short codecid:8;

	unsigned short seq;
	unsigned int   ts;
}AUDEC_HEADER,*PAUDEC_HEADER;

__INLINE__ void AUDEC_HEADER_RESET(void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	pHeader->ver=AUDEC_HEADER_VER_01;
	pHeader->tcp=0;
	pHeader->dual=0;
	pHeader->fec=0;
	pHeader->syn_point=0;
	pHeader->codecid=0;
	pHeader->reserved=0;
	pHeader->seq=0;
	pHeader->ts=0;
}

__INLINE__ unsigned short AUDEC_HEADER_IS_VALID(const void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	if (pHeader->ver==AUDEC_HEADER_VER_01)
	{
		return 1;
	}
	return 0;
}

__INLINE__ unsigned short AUDEC_HEADER_GET_TCP(const void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	return pHeader->tcp;
}

__INLINE__ void AUDEC_HEADER_SET_TCP(void*p,unsigned short v)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	pHeader->tcp=v;
}

__INLINE__ unsigned short AUDEC_HEADER_GET_DUAL(const void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	return pHeader->dual;
}

__INLINE__ void AUDEC_HEADER_SET_DUAL(void*p,unsigned short v)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	pHeader->dual=v;
}

__INLINE__ unsigned short AUDEC_HEADER_GET_FEC(const void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	return pHeader->fec;
}

__INLINE__ void AUDEC_HEADER_SET_FEC(void*p,unsigned short v)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	pHeader->fec=v;
}

__INLINE__ unsigned short AUDEC_HEADER_GET_SYN_POINT(const void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	return pHeader->syn_point;
}

__INLINE__ void AUDEC_HEADER_SET_SYN_POINT(void*p,unsigned short v)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	pHeader->syn_point=v;
}

__INLINE__ unsigned short AUDEC_HEADER_GET_CODEC_ID(const void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	return pHeader->codecid;
}

__INLINE__ void AUDEC_HEADER_SET_CODEC_ID(void*p,unsigned short v)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	pHeader->codecid=v;
}

__INLINE__ unsigned short AUDEC_HEADER_GET_SEQUENCE(const void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	return ntohs(pHeader->seq);
}

__INLINE__ void AUDEC_HEADER_SET_SEQUENCE(void*p,unsigned short v)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	pHeader->seq=htons(v);
}

__INLINE__ unsigned int AUDEC_HEADER_GET_TIMESTAMP(const void*p)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	return ntohl(pHeader->ts);
}

__INLINE__ void AUDEC_HEADER_SET_TIMESTAMP(void*p,unsigned int v)
{
	PAUDEC_HEADER pHeader=(PAUDEC_HEADER)p;
	pHeader->ts=htonl(v);
}

__INLINE__ unsigned short AUDEC_HEADER_GET_LEN(const void*p)
{
	return AUDEC_HEADER_VER_01_LEN;
}


#endif