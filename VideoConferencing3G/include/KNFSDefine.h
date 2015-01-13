#pragma once

//---------------------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------------------
#define NFS_UPLOAD_START		100
#define NFS_UPLOAD_START_ACK	101
#define NFS_UPLOAD_DATA			102
#define NFS_UPLOAD_DATA_ACK		103
#define NFS_UPLOAD_END			104
#define NFS_UPLOAD_END_ACK		105

#define NFS_DOWNLOAD_START		200
#define NFS_DOWNLOAD_START_ACK	201
#define NFS_DOWNLOAD_DATA		202
#define NFS_DOWNLOAD_DATA_ACK	203
#define NFS_DOWNLOAD_END		204

#define NFS_DELETE				300
#define NFS_DELETE_ACK			301

//---------------------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------------------
#define  ERR_UPLOAD_FILE		401		//�ϴ��ļ������������ļ���������
#define  ERR_DOWNLOAD_FILE		402		//�����ļ���������ȡ�ļ���������
#define  ERR_DELETE_FILE		403		//�����ļ���������ȡ�ļ���������