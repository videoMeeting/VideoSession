//NETEC_MediaReceiver.h
#ifndef __NETEC_MEDIARECEIVER_H__
#define __NETEC_MEDIARECEIVER_H__

#include <NETEC/NETEC_Export.h>
#include <NETEC/NETEC.h>

#define MEDIA_RECEIVER_NOT_STARTED			0x00000001
#define MEDIA_RECEIVER_CONNECTING			0x00000002
#define MEDIA_RECEIVER_CONNECTED			0x00000004
#define MEDIA_RECEIVER_DISCONNECTED			0x00000008

//媒体接收类
class NETEC_MediaReceiverCallback
{
public:
	NETEC_MediaReceiverCallback(void){};
	virtual~NETEC_MediaReceiverCallback(void){};
public:
	/******************************************************************************
	* OnNETEC_MediaReceiverCallbackAudioPacket
	*描述：接收到音频数据包的回调
	*输入：	pData			-数据包指针
			nLen			-数据包长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MediaReceiverCallbackAudioPacket(unsigned char*pData,int nLen)=0;

	/******************************************************************************
	* OnNETEC_MediaReceiverCallbackVideoPacket
	*描述：接收到视频数据包的回调
	*输入：	pData			-数据包指针
			nLen			-数据包长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MediaReceiverCallbackVideoPacket(unsigned char*pData,int nLen)=0;
};

class NETEC_API NETEC_MediaReceiver
{
public:
	NETEC_MediaReceiver(void){};
	virtual~NETEC_MediaReceiver(void){};
public:
	//add by wanggj
	virtual void SetLocalMCUID(const char* cszLocalMCUID)=0;
	virtual void SetLocalMCIIP(const char* cszLocalMCUIP)=0;
	virtual void SetLocalMCUPort(unsigned short usLocalMCUPort)=0;
	//end.
	/******************************************************************************
	* Open
	*描述：打开
	*输入：	cszPeerNodeID	-对端节点标识
			cszPeerNATIP	-对端外网IP
			cszPeerLocalIP	-对端本机IP
			nPeerLocalPort	-对端本机端口
			cszPeerMCUID	-对端MCU标识
			cszPeerMCUIP	-对端MCU地址
			usPeerMCUPort	-对端MCU端口
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Open(const char*cszPeerNodeID,const char*cszPeerNATIP,const char*cszPeerLocalIP,unsigned short nPeerLocalPort,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort)=0;

	/******************************************************************************
	* Close
	*描述：关闭
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* SetAudioID
	*描述：设置音频标识
	*输入：	ulAudioID	-音频标识
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetAudioID(unsigned long ulAudioID)=0;

	/******************************************************************************
	* StartAudio
	*描述：启动音频
	*输入：	无
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int StartAudio(void)=0;

	/******************************************************************************
	* StopAudio
	*描述：停止音频
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void StopAudio(void)=0;

	/******************************************************************************
	* IsAudioStarted
	*描述：获取是否启动了音频
	*输入：	无
	*输出： 无
	*返回值：成功返回>=0【0:未启动，否则已经启动了】，失败返回-1
	*****************************************************************************/
	virtual int IsAudioStarted(void)=0;

	/******************************************************************************
	* EnableAudio
	*描述：设置是否开始接收音频
	*输入：	nEnable			-是否开始接收音频【0：停止接收音频，否则开始接收音频】
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual int EnableAudio(int nEnable)=0;

	/******************************************************************************
	* IsAudioEnable
	*描述：获取是否开始接收主流音频
	*输入：	无
	*输出： 无
	*返回值：成功返回>=0【0:已经开始接收，已经停止接收】，失败返回-1
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
	* SetVideoID
	*描述：设置主流视频标识
	*输入：	ulVideoID	-主流视频标识
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetVideoID(unsigned long ulVideoID)=0;

	/******************************************************************************
	* StartVideo
	*描述：启动主流视频
	*输入：	无
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int StartVideo(void)=0;

	/******************************************************************************
	* StopVideo
	*描述：停止主流视频
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void StopVideo(void)=0;

	/******************************************************************************
	* IsVideoStarted
	*描述：获取是否启动了主流视频
	*输入：	无
	*输出： 无
	*返回值：成功返回>=0【0:未启动，否则已经启动了】，失败返回-1
	*****************************************************************************/
	virtual int IsVideoStarted(void)=0;

	/******************************************************************************
	* EnableVideo
	*描述：设置是否开始接收视频
	*输入：	nEnable			-是否开始接收视频【0：停止接收视频，否则开始接收视频】
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual int EnableVideo(int nEnable)=0;

	/******************************************************************************
	* IsVideoEnable
	*描述：获取是否开始接收主流视频
	*输入：	无
	*输出： 无
	*返回值：成功返回>=0【0:已经开始接收，已经停止接收】，失败返回-1
	*****************************************************************************/
	virtual int IsVideoEnable(void)=0;

	virtual int SendCtrl(void*pData,int nLen)=0;
	virtual int SendPTZ(void*pData,int nLen)=0;

	/******************************************************************************
	* GetVideoPacketStatistics
	*描述：获取视频的包的统计数据
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
	*描述：获取视频的网络状态
	*输入：	无
	*输出： nNetworkStatus	-丢包率[0-100]
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetVideoNetworkStatus(unsigned long&nNetworkStatus)=0;

	/******************************************************************************
	* RequestKeyFrame
	*描述：请求关键帧
	*输入：	无
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int RequestKeyFrame(void)=0;

	/******************************************************************************
	* SetFrameRateControlMode
	*描述：设置帧率控制模式
	*输入：	nMode			-帧率控制模式
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetFrameRateControlMode(FRAME_RATE_CONTROL_MODE nMode)=0;

	/******************************************************************************
	* SetFrameTypeControlMode
	*描述：设置帧类型控制模式
	*输入：	nMode			-帧类型控制模式
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetFrameTypeControlMode(FRAME_TYPE_CONTROL_MODE nMode)=0;


	static NETEC_MediaReceiver*Create(NETEC_MediaReceiverCallback&rCallback);
};

#endif