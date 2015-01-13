
#pragma once

/************************************************************************/
/* ��Ϣ����                                                             */
/************************************************************************/
#define VRS_UPLOAD_START                0x1000  // ��ʼ�ϴ�
#define VRS_UPLOAD_START_ACK            0x1001
#define VRS_UPLOAD_START_NACK           0x1002

#define VRS_UPLOAD_DATA                 0x1003  // �ϴ�����
#define VRS_UPLOAD_DATA_ACK             0x1004
#define VRS_UPLOAD_DATA_NACK            0x1005

#define VRS_UPLOAD_END                  0x1006  // �ϴ�����
#define VRS_UPLOAD_END_ACK              0x1007
#define VRS_UPLOAD_END_NACK             0x1008

#define VRS_DISK_SPACE_FULL_NOTIFY      0x1009  // ֪ͨ�ͻ��˴�����
/************************************************************************/
/* ����Ŷ���                                                           */
/************************************************************************/
// ����˷��صĴ���
#define  ERR_DISK_FULL                  1       // ������
#define  ERR_FILE_OPERATION             2       // �ļ�����ʧ��(��/д/seek)
#define  ERR_NOW_UPLOADING              3       // Ŀǰ�����ϴ�
#define  ERR_MD5_CHECK                  4       // MD5��֤ʧ��

// �ͻ����������
#define  ERR_LOCAL_FILE_OPEN            101     // �����ļ���ʧ��
#define  ERR_LOCAL_FILE_SEEK            102     // �����ļ�Seek����
#define  ERR_LOCAL_DISCONNECT           103     // �����˶�����

/************************************************************************/
/* ��������                                                             */
/************************************************************************/
//#define IO_CONNECT_TYPE_CLIENT_VRS      1                 // VRS ��������

const unsigned short MAX_PACKET_SIZE        = 8192;         // ������

const unsigned short NORMAL_DB_VARCHAR_LEN  = 64;           // ��ͨ���ݿ��ֶγ���
const unsigned short LARGE_DB_VARCHAR_LEN   = 256;          // �ϳ����ݿ��ֶγ���
const unsigned short HUGE_DB_VARCHAR_LEN    = 1024;         // �������ݿ��ֶγ���


const unsigned long MIN_ALAMR1_SPACE        = 50;           // ¼�������С�����ռ�
const unsigned long MIN_ALAMR2_SPACE        = 50;           // ¼�������С�����ռ�
const unsigned long MIN_RESERVE_SPACE       = 1000;         // ¼�������С�����ռ�

const unsigned long MAX_RECORD_RESERVE_DAYS = 3 * 30;       // �¼�񱣴�����

const unsigned long RECORD_FILE_HEADER_MODIFY_LEN = 24 + 12 + 4;    // ¼���ļ������󣬻��޸��ļ�ͷ
                                                                    // 24 : ͷ�ṹ����
                                                                    // 12 : ����֡���ȱ��� framenum ����λ��
                                                                    // 4  : ����֡���� framenum ��ռ�ֽ���

#ifdef WIN32
#define PATH_SPLIT_CHAR		"\\"                    // ·���ָ���
#else
#define PATH_SPLIT_CHAR		"/"
#endif

/************************************************************************/
/* ���ݿ�ṹ����                                                       */
/************************************************************************/

typedef unsigned char byte;

typedef struct tagMonRecordInfo
{
    tagMonRecordInfo()
    {
        _ulID        = 0;
        _ulSize      = 0;
        _byType       = 0;
        _byChannelID  = 0;
    }
    unsigned long   _ulID;              // ��ţ������ݿ�����
    unsigned long   _ulSize;            // �ļ���С
    unsigned char   _byType;            // ¼������
    unsigned char   _byChannelID;       // ͨ����

    string          _strDVRID;          // DVR ID
    string          _strName;           // ¼������
    string          _strServerIP;       // ������IP
    string          _strWriteDate;      // ����ʱ��
    string          _strCompleteDate;   // ���ʱ��
    string          _strStartTime;      // ��ʼʱ��
    string          _strEndTime;        // ����ʱ��
}
TMONRECORDINFO, *PTMONRECORDINFO;

