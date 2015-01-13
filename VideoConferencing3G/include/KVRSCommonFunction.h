
#pragma once
#include "KVRSDataDefine.h"
/************************************************************************/
/* 打包，解包                                                           */
/************************************************************************/
inline void DataPack( KDataOutPacket& outPacket, PTMONRECORDINFO ptMonRecordInfo)
{
    outPacket << ptMonRecordInfo->_ulID;
    outPacket << ptMonRecordInfo->_ulSize;
    outPacket << ptMonRecordInfo->_byType;
    outPacket << ptMonRecordInfo->_byChannelID;

    outPacket << ptMonRecordInfo->_strName.c_str();
    outPacket << ptMonRecordInfo->_strDVRID.c_str();
    outPacket << ptMonRecordInfo->_strServerIP.c_str();
    outPacket << ptMonRecordInfo->_strWriteDate.c_str();
    outPacket << ptMonRecordInfo->_strCompleteDate.c_str();
    outPacket << ptMonRecordInfo->_strStartTime.c_str();
    outPacket << ptMonRecordInfo->_strEndTime.c_str();
}

inline void DataUnpack( KDataInPacket& inPacket, PTMONRECORDINFO ptMonRecordInfo)
{
    char achName[LARGE_DB_VARCHAR_LEN] = {0};
    char achType[NORMAL_DB_VARCHAR_LEN] = {0};
    char achDVRID[NORMAL_DB_VARCHAR_LEN] = {0};
    char achChannelID[NORMAL_DB_VARCHAR_LEN] = {0};
    char achServerIP[NORMAL_DB_VARCHAR_LEN] = {0};
    char achWriteDate[NORMAL_DB_VARCHAR_LEN] = {0};
    char achCompleteDate[NORMAL_DB_VARCHAR_LEN] = {0};
    char achStartTime[NORMAL_DB_VARCHAR_LEN] = {0};
    char achEndTime[NORMAL_DB_VARCHAR_LEN] = {0};

    inPacket >> ptMonRecordInfo->_ulID;
    inPacket >> ptMonRecordInfo->_ulSize;
    inPacket >> ptMonRecordInfo->_byType;
    inPacket >> ptMonRecordInfo->_byChannelID;

    inPacket >> achName;
    inPacket >> achDVRID;
    inPacket >> achServerIP;
    inPacket >> achWriteDate;
    inPacket >> achCompleteDate;
    inPacket >> achStartTime;
    inPacket >> achEndTime;

    ptMonRecordInfo->_strName            = achName;
    ptMonRecordInfo->_strDVRID           = achDVRID;
    ptMonRecordInfo->_strServerIP        = achServerIP;
    ptMonRecordInfo->_strWriteDate       = achWriteDate;
    ptMonRecordInfo->_strCompleteDate    = achCompleteDate;
    ptMonRecordInfo->_strStartTime       = achStartTime;
    ptMonRecordInfo->_strEndTime         = achEndTime;
}




