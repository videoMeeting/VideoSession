/*	WYBASE.h	Kenny Base Classes Library */

#pragma once

//---------------------------------------------------------------------------------------
// 预包含STL常用库
//---------------------------------------------------------------------------------------
#include <set>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <string>

using namespace std;

#ifdef WIN32
#include <winsock2.h>
#endif

//---------------------------------------------------------------------------------------
// 包含头文件
//---------------------------------------------------------------------------------------

#include "WYBASE/Utils.h"
#include "WYBASE/CmdLine.h"
#include "WYBASE/Guid.h"
#include "WYBASE/KUID.h"
#include "WYBASE/File.h"
#include "WYBASE/IniFile.h"
#include "WYBASE/DLLManager.h"

#include "WYBASE/String.h"
#include "WYBASE/CritSec.h"
#include "WYBASE/Event.h"
#include "WYBASE/AutoLock.h"
#include "WYBASE/Thread.h"
#include "WYBASE/Timer.h"
#include "WYBASE/List.h"
#include "WYBASE/Logger.h"
#include "WYBASE/DateTime.h"
#include "WYBASE/Buffer.h"
#include "WYBASE/BufferPool.h"

#include "WYBASE/XMLParser.h"
#include "WYBASE/MD5.h"
#include "WYBASE/Zip.h"
#include "WYBASE/ZipEx.h"

#include "WYBASE/CmdBuffer.h"
#include "WYBASE/CmdPacket.h"

#include "WYBASE/KXMLNode.h"
#include "WYBASE/KXMLCData.h"
#include "WYBASE/KXMLAccumulator.h"
#include "WYBASE/KXMLElement.h"
#include "WYBASE/KXMLElementStream.h"
#include "WYBASE/KXMLPacket.h"

#include "WYBASE/DataPacket.h"
