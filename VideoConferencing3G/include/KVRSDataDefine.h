
#pragma once

/************************************************************************/
/* 消息定义                                                             */
/************************************************************************/
#define VRS_UPLOAD_START                0x1000  // 开始上传
#define VRS_UPLOAD_START_ACK            0x1001
#define VRS_UPLOAD_START_NACK           0x1002

#define VRS_UPLOAD_DATA                 0x1003  // 上传数据
#define VRS_UPLOAD_DATA_ACK             0x1004
#define VRS_UPLOAD_DATA_NACK            0x1005

#define VRS_UPLOAD_END                  0x1006  // 上传结束
#define VRS_UPLOAD_END_ACK              0x1007
#define VRS_UPLOAD_END_NACK             0x1008

#define VRS_DISK_SPACE_FULL_NOTIFY      0x1009  // 通知客户端磁盘满
/************************************************************************/
/* 错误号定义                                                           */
/************************************************************************/
// 服务端返回的错误
#define  ERR_DISK_FULL                  1       // 磁盘满
#define  ERR_FILE_OPERATION             2       // 文件操作失败(读/写/seek)
#define  ERR_NOW_UPLOADING              3       // 目前正在上传
#define  ERR_MD5_CHECK                  4       // MD5验证失败

// 客户端自身出错
#define  ERR_LOCAL_FILE_OPEN            101     // 本地文件打开失败
#define  ERR_LOCAL_FILE_SEEK            102     // 本地文件Seek出错
#define  ERR_LOCAL_DISCONNECT           103     // 与服务端断链了

/************************************************************************/
/* 常量定义                                                             */
/************************************************************************/
//#define IO_CONNECT_TYPE_CLIENT_VRS      1                 // VRS 连接类型

const unsigned short MAX_PACKET_SIZE        = 8192;         // 最大传输包

const unsigned short NORMAL_DB_VARCHAR_LEN  = 64;           // 普通数据库字段长度
const unsigned short LARGE_DB_VARCHAR_LEN   = 256;          // 较长数据库字段长度
const unsigned short HUGE_DB_VARCHAR_LEN    = 1024;         // 超长数据库字段长度


const unsigned long MIN_ALAMR1_SPACE        = 50;           // 录像磁盘最小保留空间
const unsigned long MIN_ALAMR2_SPACE        = 50;           // 录像磁盘最小保留空间
const unsigned long MIN_RESERVE_SPACE       = 1000;         // 录像磁盘最小保留空间

const unsigned long MAX_RECORD_RESERVE_DAYS = 3 * 30;       // 最长录像保存天数

const unsigned long RECORD_FILE_HEADER_MODIFY_LEN = 24 + 12 + 4;    // 录像文件结束后，会修改文件头
                                                                    // 24 : 头结构长度
                                                                    // 12 : 数据帧长度变量 framenum 保存位置
                                                                    // 4  : 数据帧长度 framenum 所占字节数

#ifdef WIN32
#define PATH_SPLIT_CHAR		"\\"                    // 路径分隔符
#else
#define PATH_SPLIT_CHAR		"/"
#endif

/************************************************************************/
/* 数据库结构定义                                                       */
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
    unsigned long   _ulID;              // 标号，由数据库生成
    unsigned long   _ulSize;            // 文件大小
    unsigned char   _byType;            // 录像类型
    unsigned char   _byChannelID;       // 通道号

    string          _strDVRID;          // DVR ID
    string          _strName;           // 录像名称
    string          _strServerIP;       // 服务器IP
    string          _strWriteDate;      // 创建时间
    string          _strCompleteDate;   // 完成时间
    string          _strStartTime;      // 开始时间
    string          _strEndTime;        // 结束时间
}
TMONRECORDINFO, *PTMONRECORDINFO;

