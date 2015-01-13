#pragma once

#include "KNFSDefine.h"

//=======================================================================================
// 网络文件传输客户端接口类
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
// 网络文件上传接口类
//=======================================================================================

//---------------------------------------------------------
// KNFSUploadSessionEvent 事件接口类
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSUploadSessionEvent
{
public:
	KNFSUploadSessionEvent(void){};
	virtual ~KNFSUploadSessionEvent(void){};
	
	/* 连接成功  */
	virtual void OnConnected(void)=0;

	/* 连接断开  */
	virtual void OnDisconnected(int nErrCode)=0;

	/* 上传错误 */
	virtual void OnUploadError(int nErrCode)=0;

	/* 上传进程 */
	virtual void OnUploadProgress(double dPercent,double dSpeed)=0;

	/* 上传结束 */
	virtual void OnUploadEnd(void)=0;

	/* 删除 */
	virtual void OnDelete(int nErrCode)=0;
};

//---------------------------------------------------------
// KNFSUploadSession 接口类
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSUploadSession
{
public:
	KNFSUploadSession(void){};
	virtual ~KNFSUploadSession(void){};

	/* 连接服务器 */
	virtual bool Connect(const std::string& strServerAddr,unsigned short usServerPort)=0;

	/* 断开服务器连接 */
	virtual void Disconnect(void)=0;

	/* 上传文件:
	 * strLocalFileFullName:  本地上传文件全路径名(包含文件名)
	 * strUploadFilePath:     上传文件路径(服务器相对路径):/emaps/part01
	 * strUploadFileName:     上传文件名称: map0001.jpg
     * 说明:保存到服务器上的文件位置: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Upload(const std::string& strLocalFileFullName,const std::string& strUploadFilePath,const std::string& strUploadFileName)=0;

	/* 删除文件
	 * strUploadFilePath:     上传文件路径(服务器相对路径):/emaps/part01
	 * strUploadFileName:     上传文件名称: map0001.jpg
     * 说明:保存到服务器上的文件位置: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Delete(const std::string& strDeleteFilePath,const std::string& strDeleteFileName)=0;
};

//=======================================================================================
// 网络文件下载接口类
//=======================================================================================

//---------------------------------------------------------
// KNFSDownloadSessionEvent 事件接口类
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSDownloadSessionEvent
{
public:
	KNFSDownloadSessionEvent(void){};
	virtual ~KNFSDownloadSessionEvent(void){};
	
	/* 连接成功  */
	virtual void OnConnected(void)=0;

	/* 连接断开  */
	virtual void OnDisconnected(int nErrCode)=0;

	/* 下载开始 */
	virtual void OnDownloadStart(unsigned long ulFileSize)=0;

	/* 下载错误 */
	virtual void OnDownloadError(int nErrCode)=0;

	/* 下载进程 */
	virtual void OnDownloadProgress(double dPercent,double dSpeed)=0;

	/* 下载结束 */
	virtual void OnDownloadEnd(void)=0;

	/* 删除 */
	virtual void OnDelete(int nErrCode)=0;
};

//---------------------------------------------------------
// KNFSDownloadSession 接口类
//---------------------------------------------------------
class AFX_EXT_CLASS KNFSDownloadSession
{
public:
	KNFSDownloadSession(void){};
	virtual ~KNFSDownloadSession(void){};

	/* 连接服务器 */
	virtual bool Connect(const std::string& strServerAddr,unsigned short usServerPort)=0;

	/* 断开服务器连接 */
	virtual void Disconnect(void)=0;

	/* 上传文件:
	 * strLocalFileFullName: 本地文件全路径
	 * strDownloadFilePath:  下载文件路径(服务器相对路径):/emaps/part01
	 * strDownloadFileName:  下载文件名称: map0001.jpg
     * 说明:从服务器上下载文件/usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Download(const std::string& strLocalFileFullName,const std::string& strDownloadFilePath,const std::string& strDownloadFileName)=0;

	/* 删除文件
	 * strUploadFilePath:     上传文件路径(服务器相对路径):/emaps/part01
	 * strUploadFileName:     上传文件名称: map0001.jpg
     * 说明:保存到服务器上的文件位置: /usr/local/avcond/storage/emaps/part01/map0001.jpg */
	virtual bool Delete(const std::string& strDeleteFilePath,const std::string& strDeleteFileName)=0;
};

//---------------------------------------------------------------------------------------
AFX_EXT_CLASS KNFSUploadSession* CreateNFSUploadSession(KNFSUploadSessionEvent& rNFSUploadSessionEvent);

//---------------------------------------------------------------------------------------
AFX_EXT_CLASS KNFSDownloadSession* CreateNFSDownloadSession(KNFSDownloadSessionEvent& rNFSDownloadSessionEvent);
