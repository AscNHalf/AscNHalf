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

//HEADER GUARDS!
#ifndef __RSTDAFX_H
#define __RSTDAFX_H

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "../ascnhalf-shared/Common.h"
#include "../ascnhalf-shared/MersenneTwister.h"
#include "../ascnhalf-shared/WorldPacket.h"
#include "../ascnhalf-shared/Log.h"
#include "../ascnhalf-shared/NGLog.h"
#include "../ascnhalf-shared/ByteBuffer.h"
#include "../ascnhalf-shared/StackBuffer.h"
#include "../ascnhalf-shared/Config/ConfigEnv.h"
#include "../ascnhalf-shared/crc32.h"
#include "../ascnhalf-shared/LocationVector.h"

#include <zlib.h>

#include "../ascnhalf-shared/Database/DatabaseEnv.h"
#include "../ascnhalf-shared/Database/DBCStores.h"
#include "../ascnhalf-shared/Database/dbcfile.h"
#include "../ascnhalf-shared/FastQueue.h"
#include "../ascnhalf-shared/Threading/RWLock.h"

#include <Network/Network.h>

#include "../ascnhalf-shared/Auth/MD5.h"
#include "../ascnhalf-shared/Auth/BigNumber.h"
#include "../ascnhalf-shared/Auth/Sha1.h"
#include "../ascnhalf-shared/Auth/WowCrypt.h"
#include "../ascnhalf-shared/CrashHandler.h"

#include "../ascnhalf-world/NameTables.h"
#include "../ascnhalf-world/Opcodes.h"
#include "../ascnhalf-shared/CallBack.h"

#include "Master.h"
#include "WorkerOpcodes.h"
#include "WorkerServerSocket.h"
#include "Structures.h"
#include "WorldSocket.h"
#include "Session.h"
#include "WorkerServer.h"
#include "ClusterManager.h"
#include "ClientManager.h"
#include "LogonCommClient.h"
#include "LogonCommHandler.h"
#include "../ascnhalf-shared/Storage.h"
#include "ObjectStorage.h"
#include "LocalizationMgr.h"
#include "Chat.h"
#include "Channel.h"
#include "ChannelMgr.h"
#include "ClusterServerDefines.h"

#endif