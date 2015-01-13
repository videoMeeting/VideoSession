/* KAutoLock.h */

#pragma once

#include "CritSec.h"

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KAutoLock  
{
public:
	KAutoLock(KCritSec &rCritSec);
	~KAutoLock();

protected:
    KCritSec& m_rCritSec;
};

