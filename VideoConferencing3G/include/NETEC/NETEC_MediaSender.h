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

//ý�巢����
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
	*��������
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int Open(void)=0;

	/******************************************************************************
	* Close
	*�������ر�
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* StartAudio
	*������������Ƶ
	*���룺	ulAudioID	-��Ƶ��ʶ
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int StartAudio(unsigned long ulAudioID)=0;

	/******************************************************************************
	* IsAudioStarted
	*��������ȡ�Ƿ���������Ƶ
	*���룺	��
	*����� ��
	*����ֵ���Ƿ���������Ƶ,��0Ϊ��,0Ϊ��
	*****************************************************************************/
	virtual int IsAudioStarted(void)=0;

	/******************************************************************************
	* StopAudio
	*������ֹͣ��Ƶ
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void StopAudio(void)=0;

	/******************************************************************************
	* GetAudioID
	*��������ȡ��Ƶ��ʶ
	*���룺	��
	*����� ulAudioID	-��Ƶ��ʶ
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetAudioID(unsigned long&ulAudioID)=0;

	/******************************************************************************
	* IsAudioEnable
	*��������ȡ��Ƶ�Ƿ����˽���
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����>=0��0:���˽��գ��������˽��ա���ʧ�ܷ���-1
	*****************************************************************************/
	virtual int IsAudioEnable(void)=0;

	/******************************************************************************
	* GetAudioPacketStatistics
	*��������ȡ��Ƶ�İ���ͳ������
	*���룺	��
	*����� ulTotalPackets		-�ܹ������˶��ٸ���
			ulLostPackets		-�ܹ������˶��ٸ���
			AvgPacketLossRate	-ƽ��������
			CurPacketLossRate	-��ǰ������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetAudioPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate)=0;

	/******************************************************************************
	* GetAudioNetworkStatus
	*��������ȡ��Ƶ������״̬
	*���룺	��
	*����� nNetworkStatus	-������[0-100]
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetAudioNetworkStatus(unsigned long&nNetworkStatus)=0;

	/******************************************************************************
	* SendAudio
	*������������Ƶ���ݰ�
	*���룺	pData			-���ݰ�ָ��
			nLen			-���ݰ�����
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int SendAudio(unsigned char*pData,int nLen)=0;

	/******************************************************************************
	* StartVideo
	*����������������Ƶ
	*���룺	ulVideoID	-������Ƶ��ʶ
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int StartVideo(unsigned long ulVideoID)=0;

	/******************************************************************************
	* IsVideoStarted
	*��������ȡ�Ƿ�������������Ƶ
	*���룺	��
	*����� ��
	*����ֵ���Ƿ�������������Ƶ��0Ϊ��,0Ϊ��
	*****************************************************************************/
	virtual int IsVideoStarted(void)=0;

	/******************************************************************************
	* StopVideo
	*������ֹͣ������Ƶ
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void StopVideo(void)=0;

	/******************************************************************************
	* GetVideoID
	*��������ȡ������Ƶ��ʶ
	*���룺	��
	*����� ulVideoID	-������Ƶ��ʶ
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetVideoID(unsigned long&ulVideoID)=0;

	/******************************************************************************
	* IsVideoRequestKeyFrame
	*��������ȡ������Ƶ�Ƿ���������ؼ�֡
	*���룺	nFrameType	-֡����[Main:0 Sub:1 QSub:2]
	*����� ��
	*����ֵ���ɹ�����>=0��0:��������ؼ�֡��������������ؼ�֡����ʧ�ܷ���-1
	*****************************************************************************/
	virtual int IsVideoRequestKeyFrame(int nFrameType)=0;

	/******************************************************************************
	* IsVideoBlocking
	*��������ȡ������Ƶ�����Ƿ�����
	*���룺	nFrameType	-֡����[Main:0 Sub:1 QSub:2]
	*����� ��
	*����ֵ���ɹ�����>=0��0:���Ͳ�����������������������������ʱ����Բ�ѹ����Ƶ����ʧ�ܷ���-1
	*****************************************************************************/
	virtual int IsVideoBlocking(int nFrameType)=0;

	/******************************************************************************
	* IsVideoEnable
	*��������ȡ��Ƶ�Ƿ����˽���
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����>=0��0:���˽��գ��������˽��ա���ʧ�ܷ���-1
	*****************************************************************************/
	virtual int IsVideoEnable(void)=0;

	/******************************************************************************
	* GetVideoPacketStatistics
	*��������ȡ������Ƶ�İ���ͳ������
	*���룺	��
	*����� ulTotalPackets		-�ܹ������˶��ٸ���
			ulLostPackets		-�ܹ������˶��ٸ���
			AvgPacketLossRate	-ƽ��������
			CurPacketLossRate	-��ǰ������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetVideoPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate)=0;

	/******************************************************************************
	* GetVideoNetworkStatus
	*��������ȡ������Ƶ������״̬
	*���룺	��
	*����� nNetworkStatus	-������[0-100]
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetVideoNetworkStatus(unsigned long&nNetworkStatus)=0;

	/******************************************************************************
	* SendVideo
	*������������Ƶ���ݰ�
	*���룺	pData			-���ݰ�ָ��
			nLen			-���ݰ�����
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int SendVideo(unsigned char*pData,int nLen)=0;

	/******************************************************************************
	* Create
	*����������NETEC_MediaSender
	*���룺	��
	*����� ��
	*����ֵ��NETEC_MediaSender����ָ��
	*****************************************************************************/
	static NETEC_MediaSender*Create(NETEC_MediaSenderCallback&rCallback);
};

#endif