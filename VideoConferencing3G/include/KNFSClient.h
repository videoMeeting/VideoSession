#pragma once

#include "KNFSDefine.h"

//=======================================================================================
// �����ļ�����ͻ��˽ӿ���
//=======================================================================================
class AFX_EXT_CLASS KNFSClient
{
public:
	KNFSClient(void);
	virtual ~KNFSClient(void);

	static bool Start(void);
	static void Stop(void);
};

//=======================================================================================
// �����ļ��ϴ��ӿ���
//=======================================================================================

//---------------------------------------------------------
// KNFSUploadSessionEvent �¼��ӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSUploadSessionEvent
{
public:
	KNFSUploadSessionEvent(void){};
	virtual ~KNFSUploadSessionEvent(void){};
	
	/* ���ӳɹ�  */
	virtual void OnConnected(void)=0;

	/* ���ӶϿ�  */
	virtual void OnDisconnected(int nErrCode)=0;

	/* �ϴ����� */
	virtual void OnUploadError(int nErrCode)=0;

	/* �ϴ����� */
	virtual void OnUploadProgress(double dPercent,double dSpeed)=0;

	/* �ϴ����� */
	virtual void OnUploadEnd(void)=0;

	/* ɾ�� */
	virtual void OnDelete(int nErrCode)=0;
};

//---------------------------------------------------------
// KNFSUploadSession �ӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSUploadSession
{
public:
	KNFSUploadSession(void){};
	virtual ~KNFSUploadSession(void){};

	/* ���ӷ����� */
	virtual bool Connect(const std::string& strServerAddr,unsigned short usServerPort)=0;

	/* �Ͽ����������� */
	virtual void Disconnect(void)=0;

	/* �ϴ��ļ�:
	 * strLocalFileFullName:  �����ϴ��ļ�ȫ·����(�����ļ���)
	 * strUploadFilePath:     �ϴ��ļ�·��(���������·��):/emaps/part01
	 * strUploadFileName:     �ϴ��ļ�����: map0001.jpg
     * ˵��:���浽�������ϵ��ļ�λ��: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Upload(const std::string& strLocalFileFullName,const std::string& strUploadFilePath,const std::string& strUploadFileName)=0;

	/* ɾ���ļ�
	 * strUploadFilePath:     �ϴ��ļ�·��(���������·��):/emaps/part01
	 * strUploadFileName:     �ϴ��ļ�����: map0001.jpg
     * ˵��:���浽�������ϵ��ļ�λ��: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Delete(const std::string& strDeleteFilePath,const std::string& strDeleteFileName)=0;
};

//=======================================================================================
// �����ļ����ؽӿ���
//=======================================================================================

//---------------------------------------------------------
// KNFSDownloadSessionEvent �¼��ӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSDownloadSessionEvent
{
public:
	KNFSDownloadSessionEvent(void){};
	virtual ~KNFSDownloadSessionEvent(void){};
	
	/* ���ӳɹ�  */
	virtual void OnConnected(void)=0;

	/* ���ӶϿ�  */
	virtual void OnDisconnected(int nErrCode)=0;

	/* ���ؿ�ʼ */
	virtual void OnDownloadStart(unsigned long ulFileSize)=0;

	/* ���ش��� */
	virtual void OnDownloadError(int nErrCode)=0;

	/* ���ؽ��� */
	virtual void OnDownloadProgress(double dPercent,double dSpeed)=0;

	/* ���ؽ��� */
	virtual void OnDownloadEnd(void)=0;

	/* ɾ�� */
	virtual void OnDelete(int nErrCode)=0;
};

//---------------------------------------------------------
// KNFSDownloadSession �ӿ���
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSDownloadSession
{
public:
	KNFSDownloadSession(void){};
	virtual ~KNFSDownloadSession(void){};

	/* ���ӷ����� */
	virtual bool Connect(const std::string& strServerAddr,unsigned short usServerPort)=0;

	/* �Ͽ����������� */
	virtual void Disconnect(void)=0;

	/* �ϴ��ļ�:
	 * strLocalFileFullName: �����ļ�ȫ·��
	 * strDownloadFilePath:  �����ļ�·��(���������·��):/emaps/part01
	 * strDownloadFileName:  �����ļ�����: map0001.jpg
     * ˵��:�ӷ������������ļ�/usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Download(const std::string& strLocalFileFullName,const std::string& strDownloadFilePath,const std::string& strDownloadFileName)=0;

	/* ɾ���ļ�
	 * strUploadFilePath:     �ϴ��ļ�·��(���������·��):/emaps/part01
	 * strUploadFileName:     �ϴ��ļ�����: map0001.jpg
     * ˵��:���浽�������ϵ��ļ�λ��: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Delete(const std::string& strDeleteFilePath,const std::string& strDeleteFileName)=0;
};

//---------------------------------------------------------------------------------------
AFX_EXT_CLASS KNFSUploadSession* CreateNFSUploadSession(KNFSUploadSessionEvent& rNFSUploadSessionEvent);

//---------------------------------------------------------------------------------------
AFX_EXT_CLASS KNFSDownloadSession* CreateNFSDownloadSession(KNFSDownloadSessionEvent& rNFSDownloadSessionEvent);
