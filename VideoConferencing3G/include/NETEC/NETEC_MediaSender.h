//NETEC_MediaSender.h
#ifndef __NETEC_MEDIASENDER_H__
#define __NETEC_MEDIASENDER_H__

#include <NETEC/NETEC_Export.h>

#define MEDIA_SENDER_NOT_STARTED		0x00000001
#define MEDIA_SENDER_CONNECTING			0x00000002
#define MEDIA_SENDER_CONNECTED			0x00000004
#define MEDIA_SENDER_DISCONNECTED		0x00000008

class NETEC_MediaSenderCallback
{
public:
	NETEC_MediaSenderCallback(void){};
	virtual~NETEC_MediaSenderCallback(void){};
public:
	virtual void OnNETEC_MediaSenderCallbackRecvdPTZ(void*pData,int nLen){};
	virtual void OnNETEC_MediaSenderCallbackRecvdCtrl(void*pData,int nLen){};
};

//媒体发送类
class NETEC_API NETEC_MediaSender
{
public:
	NETEC_MediaSender(void){};
	virtual~NETEC_MediaSender(void){};
public:
	//add by wanggj
	virtual void SetLocalMCUID(const char* cszLocalMCUID)=0;
	virtual void SetLocalMCIIP(const char* cszLocalMCUIP)=0;
	virtual void SetLocalMCUPort(unsigned short usLocalMCUPort)=0;
	virtual void SetConnectStatus(int nConnectStatus)=0;
	//end.
	/******************************************************************************
	* Open
	*描述：打开
	*输入：	无
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Open(void)=0;

	/******************************************************************************
	* Close
	*描述：关闭
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* StartAudio
	*描述：启动音频
	*输入：	ulAudioID	-音频标识
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int StartAudio(unsigned long ulAudioID)=0;

	/******************************************************************************
	* IsAudioStarted
	*描述：获取是否启动了音频
	*输入：	无
	*输出： 无
	*返回值：是否启动了音频,非0为是,0为否
	*****************************************************************************/
	virtual int IsAudioStarted(void)=0;

	/******************************************************************************
	* StopAudio
	*描述：停止音频
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void StopAudio(void)=0;

	/******************************************************************************
	* GetAudioID
	*描述：获取音频标识
	*输入：	无
	*输出： ulAudioID	-音频标识
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetAudioID(unsigned long&ulAudioID)=0;

	/******************************************************************************
	* IsAudioEnable
	*描述：获取音频是否有人接收
	*输入：	无
	*输出： 无
	*返回值：成功返回>=0【0:无人接收，否则有人接收】，失败返回-1
	*****************************************************************************/
	virtual int IsAudioEnable(void)=0;

	/******************************************************************************
	* GetAudioPacketStatistics
	*描述：获取音频的包的统计数据
	*输入：	无
	*输出： ulTotalPackets		-总共发送了多少个包
			ulLostPackets		-总共丢弃了多少个包
			AvgPacketLossRate	-平均丢包率
			CurPacketLossRate	-当前丢包率
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetAudioPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate)=0;

	/******************************************************************************
	* GetAudioNetworkStatus
	*描述：获取音频的网络状态
	*输入：	无
	*输出： nNetworkStatus	-丢包率[0-100]
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetAudioNetworkStatus(unsigned long&nNetworkStatus)=0;

	/******************************************************************************
	* SendAudio
	*描述：发送音频数据包
	*输入：	pData			-数据包指针
			nLen			-数据包长度
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SendAudio(unsigned char*pData,int nLen)=0;

	/******************************************************************************
	* StartVideo
	*描述：启动主流视频
	*输入：	ulVideoID	-主流视频标识
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int StartVideo(unsigned long ulVideoID)=0;

	/******************************************************************************
	* IsVideoStarted
	*描述：获取是否启动了主流视频
	*输入：	无
	*输出： 无
	*返回值：是否启动了主流视频非0为是,0为否
	*****************************************************************************/
	virtual int IsVideoStarted(void)=0;

	/******************************************************************************
	* StopVideo
	*描述：停止主流视频
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void StopVideo(void)=0;

	/******************************************************************************
	* GetVideoID
	*描述：获取主流视频标识
	*输入：	无
	*输出： ulVideoID	-主流视频标识
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetVideoID(unsigned long&ulVideoID)=0;

	/******************************************************************************
	* IsVideoRequestKeyFrame
	*描述：获取主流视频是否有人请求关键帧
	*输入：	nFrameType	-帧类型[Main:0 Sub:1 QSub:2]
	*输出： 无
	*返回值：成功返回>=0【0:无人请求关键帧，否则有人请求关键帧】，失败返回-1
	*****************************************************************************/
	virtual int IsVideoRequestKeyFrame(int nFrameType)=0;

	/******************************************************************************
	* IsVideoBlocking
	*描述：获取主流视频发送是否阻塞
	*输入：	nFrameType	-帧类型[Main:0 Sub:1 QSub:2]
	*输出： 无
	*返回值：成功返回>=0【0:发送不阻塞，否则发送阻塞，发送阻塞的时候可以不压缩视频】，失败返回-1
	*****************************************************************************/
	virtual int IsVideoBlocking(int nFrameType)=0;

	/******************************************************************************
	* IsVideoEnable
	*描述：获取视频是否有人接收
	*输入：	无
	*输出： 无
	*返回值：成功返回>=0【0:无人接收，否则有人接收】，失败返回-1
	*****************************************************************************/
	virtual int IsVideoEnable(void)=0;

	/******************************************************************************
	* GetVideoPacketStatistics
	*描述：获取主流视频的包的统计数据
	*输入：	无
	*输出： ulTotalPackets		-总共发送了多少个包
			ulLostPackets		-总共丢弃了多少个包
			AvgPacketLossRate	-平均丢包率
			CurPacketLossRate	-当前丢包率
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetVideoPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate)=0;

	/******************************************************************************
	* GetVideoNetworkStatus
	*描述：获取主流视频的网络状态
	*输入：	无
	*输出： nNetworkStatus	-丢包率[0-100]
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetVideoNetworkStatus(unsigned long&nNetworkStatus)=0;

	/******************************************************************************
	* SendVideo
	*描述：发送视频数据包
	*输入：	pData			-数据包指针
			nLen			-数据包长度
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SendVideo(unsigned char*pData,int nLen)=0;

	/******************************************************************************
	* Create
	*描述：创建NETEC_MediaSender
	*输入：	无
	*输出： 无
	*返回值：NETEC_MediaSender对象指针
	*****************************************************************************/
	static NETEC_MediaSender*Create(NETEC_MediaSenderCallback&rCallback);
};

#endif