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

#ifndef WOWSERVER_GAMEOBJECT_H
#define WOWSERVER_GAMEOBJECT_H

#include "ObjectDefines.h"

class Player;
class GameObjectAIScript;
class GameObjectTemplate;

#pragma pack(push,1)
struct GameObjectInfo
{
	uint32 ID;
	uint32 Type;
	uint32 DisplayID;
	char * Name;
	uint32 SpellFocus;
	uint32 sound1;
	uint32 sound2;
	uint32 sound3;
	uint32 sound4;
	uint32 sound5;
	uint32 sound6;
	uint32 sound7;
	uint32 sound8;
	uint32 sound9;
	uint32 Unknown1;
	uint32 Unknown2;
	uint32 Unknown3;
	uint32 Unknown4;
	uint32 Unknown5;
	uint32 Unknown6;
	uint32 Unknown7;
	uint32 Unknown8;
	uint32 Unknown9;
	uint32 Unknown10;
	uint32 Unknown11;
	uint32 Unknown12;
	uint32 Unknown13;
	uint32 Unknown14;
	uint32 *InvolvedQuestIds;
	uint32 InvolvedQuestCount;
	GossipScript * gossip_script;
};
#pragma pack(pop)

#define CALL_GO_SCRIPT_EVENT(obj, func) if(obj->GetTypeId() == TYPEID_GAMEOBJECT && obj->GetScript() != NULL) obj->GetScript()->func

class SERVER_DECL GameObject : public Object
{
public:
	/************************************************************************/
	/* 						LUA Stuff						     */
	/************************************************************************/
/*	typedef struct { const char *name; int(*mfunc)(lua_State*,GameObject* ); } RegType;
	static const char className[];
	static RegType methods[];

	// a lua script cannot create a unit.
	GameObject(lua_State * L) { ASSERT(false); }*/

	GameObject(uint64 guid);
	~GameObject( );
	virtual void Init();
	virtual void Destructor();

	INLINE GameObjectInfo* GetInfo() { return pInfo; }
	INLINE void SetInfo(GameObjectInfo * goi) { pInfo = goi; }

	bool CreateFromProto(uint32 entry, uint32 mapid, float x, float y, float z, float ang, float orientation1, float orientation2, float orientation3, float orientation4);
   
	bool Load(GOSpawn *spawn);

	virtual void Update(uint32 p_time);

	void Spawn( MapMgr* m);
	void Despawn(uint32 time);

	//void _EnvironmentalDamageUpdate();
	void UpdateTrapState();
	// Serialization
	void SaveToDB();
	void SaveToFile(std::stringstream & name);
	//bool LoadFromDB(uint32 guid);
	//void LoadFromDB(GameObjectTemplate *t);
	void DeleteFromDB();
	void EventCloseDoor();
	uint64 m_rotation;
	void UpdateRotation(float orientation3 = 0.0f, float orientation4 = 0.0f);

	//Fishing stuff
	void UseFishingNode(Player* player);
	void EndFishing(Player* player,bool abort);
	void FishHooked(Player* player);
	
	// Quests
	void _LoadQuests();
	bool HasQuests() { return m_quests != NULL; };
	void AddQuest(QuestRelation *Q);
	void DeleteQuest(QuestRelation *Q);
	Quest *FindQuest(uint32 quest_id, uint8 quest_relation);
	uint16 GetQuestRelation(uint32 quest_id);
	uint32 NumOfQuests();
	std::list<QuestRelation *>::iterator QuestsBegin() { return m_quests->begin(); };
	std::list<QuestRelation *>::iterator QuestsEnd() { return m_quests->end(); };
	void SetQuestList(std::list<QuestRelation *>* qst_lst) { m_quests = qst_lst; };

	void SetSummoned(Unit* mob)
	{
		m_summoner = mob;
		m_summonedGo = true;
	}
	Unit* CreateTemporaryGuardian(uint32 guardian_entry, uint32 duration, float angle, Unit* u_caster, uint8 Slot);
	void _Expire();
	
	void ExpireAndDelete(uint32 delay = 1);

	INLINE bool isQuestGiver()
	{
		if( GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPE_ID) == 2)
			return true;
		else
			return false;
	};

	/// Quest data
	std::list<QuestRelation *>* m_quests;

	uint32 *m_ritualmembers;
	uint32 m_ritualcaster, m_ritualtarget;
	uint16 m_ritualspell;

	void InitAI();
	SpellEntry* spell;
	
	float range;
	uint8 checkrate;
	uint16 counter;
	int32 charges;//used for type==22,to limit number of usages.
	bool invisible;//invisible
	uint8 invisibilityFlag;
	Unit* m_summoner;
	int8 bannerslot;
	int8 bannerauraslot;
	CBattleground* m_battleground;

	void CallScriptUpdate();

	INLINE GameObjectAIScript* GetScript() { return myScript; }

	void TrapSearchTarget();	// Traps need to find targets faster :P

	INLINE bool HasAI() { return spell != 0; }
	GOSpawn * m_spawn;
	void OnPushToWorld();
	void OnRemoveInRangeObject(Object* pObj);
	void RemoveFromWorld(bool free_guid);

	INLINE bool CanMine(){return (mines_remaining > 0);}
	INLINE void UseMine(){ if(mines_remaining) mines_remaining--;}
	void CalcMineRemaining(bool force)
	{
		mines_remaining = 0;//3.0.9
	}

	uint32 GetGOReqSkill();
	MapCell * m_respawnCell;

	INLINE void SetScript(GameObjectAIScript *pScript) { myScript = pScript; }

	// loooot
	void GenerateLoot();

//	custom functions for scripting
	void SetState(uint8 state);
	uint8 GetState();

	//Destructable Building 
 	uint32 Health; 
 	void TakeDamage(uint32 ammount); 
 	void Rebuild(); 

protected:

	bool m_summonedGo;
	bool m_deleted;
	GameObjectInfo *pInfo;
	GameObjectAIScript * myScript;
	uint32 _fields[GAMEOBJECT_END];
	uint32 mines_remaining; //used for mining to mark times it can be mined

};

#endif

