//VIDEC_AVIWriter.h
#ifndef __VIDEC_AVIWRITER_H__
#define __VIDEC_AVIWRITER_H__

#include "VIDEC_Export.h"

//AVI录像对象
class VIDEC_API VIDEC_AVIWriter
{
public:
	VIDEC_AVIWriter(void){};
	virtual~VIDEC_AVIWriter(void){};
public:
	/******************************************************************************
	* Open
	*描述：打开录像文件
	*输入：	cszFileName			-文件名称
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Open(const char*cszFileName,int nStandardFormat)=0;

	/******************************************************************************
	* Close
	*描述：关闭录像文件
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* WriteVideo
	*描述：写视频到录像文件
	*输入：	pPacketData			-视频包数据
			nPacketLen			-视频包数据长度
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int WriteVideo(unsigned char*pPacketData,int nPacketLen)=0;

	/******************************************************************************
	* WriteAudio
	*描述：写音频到录像文件
	*输入：	pSampleData			-样本数据
			nSampleDataLen		-样本数据长度
			nSampleRate			-样本率
			nSynTimestamp		-同步时间戳
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int WriteAudio(unsigned char*pSampleData,int nSampleDataLen,int nSampleRate,unsigned long nSynTimestamp)=0;

	/******************************************************************************
	* Create
	*描述：创建录像文件对象
	*输入：	无
	*输出： 无
	*返回值：成功返回VIDEC_AVIWriter的指针，失败返回NULL
	*****************************************************************************/
	static VIDEC_AVIWriter*Create(void);
};


#endif
