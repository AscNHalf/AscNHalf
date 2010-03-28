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

#ifndef __WORLDCREATOR_H
#define __WORLDCREATOR_H

#ifdef CLUSTERING
	#include "../ascnhalf-realmserver/Structures.h"
#endif

enum INSTANCE_TYPE
{
	INSTANCE_NULL,
	INSTANCE_RAID,
	INSTANCE_NONRAID,
	INSTANCE_PVP,
	INSTANCE_MULTIMODE,
};

enum MAPENTRY_TYPE
{
	BATTLEGROUND	= 0,
	INSTANCE		= 1,
	RAID			= 2,
	ARENA			= 4,
};

enum INSTANCE_MODE
{
	MODE_5PLAYER_NORMAL	= 0,
	MODE_5PLAYER_HEROIC	= 1,
	MODE_5PLAYER_EPIC	= 2
};

enum RAID_MODE
{
	MODE_10PLAYER_NORMAL	=	0,
	MODE_25PLAYER_NORMAL	=	1,
	MODE_10PLAYER_HEROIC	=	2,
	MODE_25PLAYER_HEROIC	=	3
};

enum INSTANCE_ABORT_ERROR
{
	INSTANCE_ABORT_ERROR_ERROR					= 0x01,
	INSTANCE_ABORT_FULL							= 0x02,
	INSTANCE_ABORT_NOT_FOUND					= 0x03,
	INSTANCE_ABORT_TOO_MANY						= 0x04,
	INSTANCE_ABORT_ENCOUNTER					= 0x05,
	INSTANCE_ABORT_NON_CLIENT_TYPE				= 0x06,
	INSTANCE_ABORT_HEROIC_MODE_NOT_AVAILABLE	= 0x07,
	INSTANCE_ABORT_NOT_IN_RAID_GROUP			= 0x08,
	INSTANCE_OK	= 0x10,
};

enum OWNER_CHECK
{
	OWNER_CHECK_ERROR		= 0,
	OWNER_CHECK_EXPIRED		= 1,
	OWNER_CHECK_NOT_EXIST	= 2,
	OWNER_CHECK_NO_GROUP	= 3,
	OWNER_CHECK_DIFFICULT	= 4,
	OWNER_CHECK_MAX_LIMIT	= 5,
	OWNER_CHECK_MIN_LEVEL	= 6,
	OWNER_CHECK_WRONG_GROUP	= 7,
	OWNER_CHECK_OK			= 10,
	OWNER_CHECK_GROUP_OK	= 11,
	OWNER_CHECK_SAVED_OK	= 12,
	OWNER_CHECK_TRIGGERPASS = 13,
	OWNER_CHECK_GM_INSIDE	= 14,
};

extern const char * InstanceAbortMessages[];

class Map;
class MapMgr;

class Object;
class Group;
class Player;
class MapUpdaterThread;
class Battleground;

class SERVER_DECL FormationMgr : public Singleton < FormationMgr >
{
	map<uint32, Formation*> m_formations;
public:
	typedef std::map<uint32, Formation*> FormationMap;
    FormationMgr();
	~FormationMgr();

	Formation * GetFormation(uint32 sqlid)
	{
		FormationMap::iterator itr = m_formations.find(sqlid);
		return (itr == m_formations.end()) ? 0 : itr->second;
	}
};

class Instance
{
public:
	uint32 m_instanceId;
	uint32 m_mapId;
	MapMgr* m_mapMgr;
	uint32 m_creatorGuid;
	uint32 m_creatorGroup;
	uint32 m_difficulty;
	UNORDERED_SET<uint32> m_killedNpcs;
	UNORDERED_SET<uint32> m_SavedPlayers;
	Mutex m_SavedLock;
	time_t m_creation;
	time_t m_expiration;
	MapInfo * m_mapInfo;
	bool m_isBattleground;

	void LoadFromDB(Field * fields);
	void SaveToDB();
	void DeleteFromDB();
};

typedef HM_NAMESPACE::hash_map<uint32, Instance*> InstanceMap; 

class SERVER_DECL InstanceMgr
{
	friend class MapMgr;
public:
	InstanceMgr();	
	~InstanceMgr();

	INLINE Map* GetMap(uint32 mapid)
	{
		if(mapid>NUM_MAPS)
			return NULL;
		else
			return m_maps[mapid];
	}

	uint32 PreTeleport(uint32 mapid, Player* plr, uint32 instanceid);
	MapMgr* GetInstance(Object* obj);
	MapMgr* GetInstance(uint32 MapId, uint32 InstanceId);
	MapMgr* ClusterCreateInstance(uint32 mapid, uint32 instanceid);

	uint32 GenerateInstanceID();
	void BuildXMLStats(char * m_file);
	void Load(TaskList * l);

	// deletes all instances owned by this player.
	void ResetSavedInstances(Player* plr);

	// player left a group, boot him out of any instances he's not supposed to be in.
	void PlayerLeftGroup(Group * pGroup, Player* pPlayer);

	// Has instance expired? Can player join?
	INLINE uint8 PlayerOwnsInstance(Instance * pInstance, Player* pPlayer)
	{
		// expired?
		if( HasInstanceExpired( pInstance) )
		{
			_DeleteInstance(pInstance, false);
			return OWNER_CHECK_EXPIRED;
		}

		// Valid map?
		if( !pInstance->m_mapInfo || !dbcMap.LookupEntry(pInstance->m_mapId)) // ITS A TARP!
			return OWNER_CHECK_NOT_EXIST;

		// Triggercheat in use?
		if( pPlayer->triggerpass_cheat )
			return OWNER_CHECK_TRIGGERPASS;

		// Matching the requested mode?
		if( pInstance->m_difficulty != (dbcMap.LookupEntry(pInstance->m_mapId)->israid() ? pPlayer->iRaidType : pPlayer->iInstanceType) )
			return OWNER_CHECK_DIFFICULT;

		//Reached player limit?
		if( pInstance->m_mapMgr && pInstance->m_mapInfo->playerlimit < uint32(pInstance->m_mapMgr->GetPlayerCount()))
			return OWNER_CHECK_MAX_LIMIT;

		//Meet level requirements?
		if( pInstance->m_mapMgr && pPlayer->getLevel() < pInstance->m_mapInfo->minlevel )
			return OWNER_CHECK_MIN_LEVEL;

		//Need to be in group?
		if(!pPlayer->GetGroup() && pInstance->m_mapInfo->type == INSTANCE_RAID )
			return OWNER_CHECK_NO_GROUP;

		// Are we on the saved list?
		pInstance->m_SavedLock.Acquire();
		if( pInstance->m_SavedPlayers.find(pPlayer->GetLowGUID()) != pInstance->m_SavedPlayers.end() )
		{
			pInstance->m_SavedLock.Release();
			return OWNER_CHECK_SAVED_OK;
		}
		pInstance->m_SavedLock.Release();

		// Active raid?
		if( pInstance->m_mapMgr && pInstance->m_mapMgr->HasPlayers() )
		{
			//we have ensured the groupid is valid when it was created.
			if( pPlayer->GetGroup() && pPlayer->GetGroupID() != pInstance->m_creatorGroup )
				return OWNER_CHECK_WRONG_GROUP;
		}

		// if we are not the creator, check if we are in same creator group.
		// First player in should have set the correct instance_id.
		if( pInstance->m_creatorGuid != pPlayer->GetLowGUID() )
		{
			if(pInstance->m_creatorGroup)
			{
				 if( pPlayer->GetGroupID() != pInstance->m_creatorGroup)
					return OWNER_CHECK_WRONG_GROUP;
			}
		}
		//nothing left to check, should be OK then
		return OWNER_CHECK_OK;
	}

	// has an instance expired?
	INLINE bool HasInstanceExpired(Instance * pInstance)
	{
		MapEntry* map = dbcMap.LookupEntry(pInstance->m_mapId);
		if(map && map->israid())
			return false;

		// expired? (heroic instances never expire, they are reset every day at 05:00).
		if( pInstance->m_difficulty == 0 && pInstance->m_expiration && (UNIXTIME+20) >= pInstance->m_expiration)
			return true;

		return false;
	}
	void ResetHeroicInstances();

	// check for expired instances
	void CheckForExpiredInstances();

	// delete all instances
	void Shutdown();

	// packets, w000t! we all love packets!
	void BuildSavedRaidInstancesForPlayer(Player* plr);
	void BuildSavedInstancesForPlayer(Player* plr);
	MapMgr* CreateBattlegroundInstance(uint32 mapid);

	// this only frees the instance pointer, not the mapmgr itself
	void DeleteBattlegroundInstance(uint32 mapid, uint32 instanceid);
	MapMgr* GetMapMgr(uint32 mapId);

	//Find saved instance for player at given mapid
	Instance* GetSavedInstance(uint32 map_id, uint32 guid, uint32 difficulty);
	InstanceMap * GetInstancesForMap(uint32 map_id) {return m_instances[map_id];}

private:
	void _LoadInstances();
	void _CreateMap(uint32 mapid);
	MapMgr* _CreateInstance(Instance * in);
	MapMgr* _CreateInstance(uint32 mapid, uint32 instanceid);		// only used on main maps!
	bool _DeleteInstance(Instance * in, bool ForcePlayersOut);

	uint32 m_InstanceHigh;

	Mutex m_mapLock;
	Map * m_maps[NUM_MAPS];
	InstanceMap* m_instances[NUM_MAPS];
	MapMgr* m_singleMaps[NUM_MAPS];
};

extern SERVER_DECL InstanceMgr sInstanceMgr;

#endif
