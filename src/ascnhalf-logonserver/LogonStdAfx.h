/* AscNHalf */

#pragma once

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "Common.h"
#include <Network/Network.h>

#include "../ascnhalf-shared/Log.h"
#include "../ascnhalf-shared/Util.h"
#include "../ascnhalf-shared/ByteBuffer.h"
#include "../ascnhalf-shared/Config/ConfigEnv.h"
#include <zlib.h>

#include "../ascnhalf-shared/Database/DatabaseEnv.h"
#include "../ascnhalf-shared/Database/DBCStores.h"
#include "../ascnhalf-shared/Database/dbcfile.h"

#include "../ascnhalf-shared/Auth/BigNumber.h"
#include "../ascnhalf-shared/Auth/Sha1.h"
#include "../ascnhalf-shared/Auth/WowCrypt.h"
#include "../ascnhalf-shared/CrashHandler.h"

#include "LogonOpcodes.h"
#include "../ascnhalf-logonserver/Main.h"
#include "../ascnhalf-world/NameTables.h"
#include "AccountCache.h"
#include "PeriodicFunctionCall_Thread.h"
#include "../ascnhalf-logonserver/AutoPatcher.h"
#include "../ascnhalf-logonserver/AuthSocket.h"
#include "../ascnhalf-logonserver/AuthStructs.h"
#include "../ascnhalf-logonserver/LogonOpcodes.h"
#include "../ascnhalf-logonserver/LogonCommServer.h"
#include "../ascnhalf-logonserver/LogonConsole.h"
#include "../ascnhalf-shared/WorldPacket.h"

// database decl
extern Database* sLogonSQL;
