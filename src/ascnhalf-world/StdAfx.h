/* AscNHalf */

#ifndef __STDAFX_H
#define __STDAFX_H

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define _GAME

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "../ascnhalf-shared/Common.h"
#include "../ascnhalf-shared/SharedPtr.h"
#include "../ascnhalf-shared/MersenneTwister.h"
#include "../ascnhalf-shared/WorldPacket.h"
#include "../ascnhalf-shared/Log.h"
#include "../ascnhalf-shared/NGLog.h"
#include "../ascnhalf-shared/ByteBuffer.h"
#include "../ascnhalf-shared/StackBuffer.h"
#include "../ascnhalf-shared/Config/ConfigEnv.h"
#include "../ascnhalf-shared/crc32.h"
#include "../ascnhalf-shared/LocationVector.h"
#include "../ascnhalf-shared/hashmap.h"

#include "../ascnhalf-shared/Collision/vmap/IVMapManager.h"
#include "../ascnhalf-shared/Collision/vmap/VMapManager.h"

#include <zlib.h>

#include "../ascnhalf-shared/Database/DatabaseEnv.h"
#include "../ascnhalf-shared/Database/DBCStores.h"
#include "../ascnhalf-shared/Database/dbcfile.h"

#include <Network/Network.h>

#include "../ascnhalf-shared/Auth/MD5.h"
#include "../ascnhalf-shared/Auth/BigNumber.h"
#include "../ascnhalf-shared/Auth/Sha1.h"
#include "../ascnhalf-shared/Auth/WowCrypt.h"
#include "../ascnhalf-shared/CrashHandler.h"
#include "../ascnhalf-shared/FastQueue.h"
#include "../ascnhalf-shared/CircularQueue.h"
#include "../ascnhalf-shared/Threading/RWLock.h"
#include "../ascnhalf-shared/Threading/Condition.h"
#include "../ascnhalf-shared/ascnhalf_getopt.h"
#include "../ascnhalf-shared/BufferPool.h"

#include "Const.h"
#include "NameTables.h"
#include "UpdateFields.h"
#include "UpdateMask.h"
#include "Opcodes.h"
#include "WorldStates.h"

#ifdef CLUSTERING
	#include "../ascnhalf-realmserver/WorkerOpcodes.h"
#endif

#include "Packets.h"

#include "../ascnhalf-shared/CallBack.h"
#include "SharedDefines.h"
#include "SpellAuraDefines.h"
#include "ObjectDefines.h"
#include "DBCEnums.h"
#include "WordFilter.h"
#include "EventMgr.h"
#include "EventableObject.h"
#include "Object.h"
#include "LootMgr.h"
#include "Unit.h"

#include "AddonMgr.h"
#include "AIInterface.h"
#include "AreaTrigger.h"
#include "BattlegroundMgr.h"
#include "AlteracValley.h"
#include "ArathiBasin.h"
#include "EyeOfTheStorm.h"
#include "Arenas.h"
#include "CellHandler.h"
#include "Chat.h"
#include "Corpse.h"
#include "Quest.h"
#include "QuestMgr.h"
#include "Creature.h"
#include "DynamicObject.h"
#include "GameObject.h"
#include "Group.h"
#include "Guild.h"
#include "HonorHandler.h"
#include "ItemPrototype.h"
#include "Item.h"
#include "Container.h"
#include "AuctionHouse.h"
#include "AuctionMgr.h"
#include "LfgMgr.h"
#include "MailSystem.h"
#include "Map.h"
#include "MapCell.h"
#include "TerrainMgr.h"
#include "MiscHandler.h"
#include "NPCHandler.h"
#include "Pet.h"
#include "WorldSocket.h"
#include "World.h"
#include "WorldSession.h"
#include "WorldStateManager.h"
#include "MapMgr.h"
#include "MapScriptInterface.h"
#include "Player.h"
#include "faction.h"
#include "Skill.h"
#include "SkillNameMgr.h"
#include "SpellNameHashes.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "TaxiMgr.h"
#include "TransporterHandler.h"
#include "WarsongGulch.h"
#include "WeatherMgr.h"
#include "ItemInterface.h"
#include "Stats.h"
#include "ObjectMgr.h"
#include "WorldCreator.h"
#include "ScriptMgr.h"
#include "Channel.h"
#include "ChannelMgr.h"
#include "ArenaTeam.h"
#include "LogonCommClient.h"
#include "LogonCommHandler.h"
#include "MainServerDefines.h"
#include "WorldRunnable.h"
#include "../ascnhalf-shared/Storage.h"
#include "ObjectStorage.h"
#include "DayWatcherThread.h"
#include "VoiceChatHandler.h"
#include "LocalizationMgr.h"
#include "Vehicle.h"
#include "AchievementInterface.h"
#include "ChainAggroEntity.h"
#include "StrandOfTheAncients.h"
#include "IsleOfConquest.h"

#ifdef CLUSTERING
	#include "WorkerServerClient.h"
	#include "ClusterInterface.h"
#endif

#include "CollideInterface.h"

#include "Master.h"
#include "BaseConsole.h"
#include "CConsole.h"
//#define COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS 1

#endif
