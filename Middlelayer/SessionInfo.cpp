//
//  SessionInfo.cpp
//  VideoSession
//
//  Created by zhangxm on 13-1-30.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#include "SessionInfo.h"
SessionInfo* g_sessionInfo = NULL;
SessionInfo::SessionInfo()
{
    
}

//---------------------------------------------------------------------------------------
SessionInfo::~SessionInfo()
{
    
}

//---------------------------------------------------------------------------------------
SessionInfo* SessionInfo::GetSessionInfo()
{
    if(g_sessionInfo == NULL)
        g_sessionInfo = new SessionInfo;
    
	return g_sessionInfo;
}