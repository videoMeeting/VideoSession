//
//  SessionInfo.h
//  VideoSession
//
//  Created by zhangxm on 13-1-30.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#ifndef __VideoSession__SessionInfo__
#define __VideoSession__SessionInfo__

#include <iostream>
#include "Middlelayer.h"
class SessionInfo
{
public:
    ENTERMEETINGUSER  lEnterUser;
    SessionInfo();
	virtual ~SessionInfo();
public:
   static SessionInfo* GetSessionInfo();
};
#endif /* defined(__VideoSession__SessionInfo__) */
