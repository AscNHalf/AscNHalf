/*
  * AscNHalf MMORPG Server
  * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
  * Copyright (C) 2010 AscNHalf Team <http://ascnhalf.scymex.info/>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Affero General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Affero General Public License for more details.
  *
  * You should have received a copy of the GNU Affero General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

#ifndef LOGONSTDAFX_H
#define LOGONSTDAFX_H

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

#endif
