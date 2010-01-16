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

#ifndef _ACHIEVEMENT_INTERFACE_H
#define _ACHIEVEMENT_INTERFACE_H

#include "StdAfx.h"
#include "DBCEnums.h"

struct AchievementData
{
	uint32 id;
	uint32 counter[32];

	uint32 date;
	bool completed;

	uint32 num_criterias;
	uint32 completionTimeLast;
	
	bool m_isDirty;
};

inline uint32 unixTimeToTimeBitfields(time_t secs)
{
	tm* lt = localtime(&secs);
	return (lt->tm_year - 100) << 24 | lt->tm_mon  << 20 | (lt->tm_mday - 1) << 14 | lt->tm_wday << 11 | lt->tm_hour << 6 | lt->tm_min;
}

typedef std::set<AchievementCriteriaEntry*>							AchievementCriteriaSet;
typedef std::map<uint32, AchievementCriteriaSet*>					AchievementCriteriaMap;

class SERVER_DECL AchievementInterface
{
	Player* m_player;
	map<uint32,AchievementData*> m_achivementDataMap;
private:
	void GiveRewardsForAchievement(AchievementEntry * ae);
	void EventAchievementEarned(AchievementData * pData);
	void SendCriteriaUpdate(AchievementData * ad, uint32 idx);
	bool CanCompleteAchievement(AchievementData * ad);
	AchievementData* CreateAchievementDataEntryForAchievement(AchievementEntry * ae);

	// Gets AchievementData struct. If there is none, one will be created.
	AchievementData* GetAchievementDataByAchievementID(uint32 ID);

	WorldPacket* m_achievementInspectPacket;

public:
	AchievementInterface(Player* plr);
	~AchievementInterface();

	void LoadFromDB( QueryResult * pResult );
	void SaveToDB(QueryBuffer * buffer);

	
	WorldPacket* BuildAchievementEarned(AchievementData * pData);
	WorldPacket* BuildAchievementData(bool forInspect = false);

	bool HasAchievements() { return m_achivementDataMap.size() > 0; }

	//----------------------------------------------------------------
	void HandleAchievementCriteriaConditionDeath();

	// Handlers for misc events
	//-----------------------------------------------------------------
	void HandleAchievementCriteriaKillCreature(uint32 killedMonster);
	void HandleAchievementCriteriaWinBattleground(uint32 bgMapId, uint32 scoreMargin, uint32 time, CBattleground* bg);
	void HandleAchievementCriteriaRequiresAchievement(uint32 achievementId);
	void HandleAchievementCriteriaLevelUp(uint32 level);
	void HandleAchievementCriteriaOwnItem(uint32 itemId, uint32 stack = 1);
	void HandleAchievementCriteriaLootItem(uint32 itemId, uint32 stack = 1);
	void HandleAchievementCriteriaQuestCount(uint32 questCount);
	void HandleAchievementCriteriaHonorableKillClass(uint32 classId);
	void HandleAchievementCriteriaHonorableKillRace(uint32 raceId);
	void HandleAchievementCriteriaHonorableKill();
	void HandleAchievementCriteriaTalentResetCount();
	void HandleAchievementCriteriaTalentResetCostTotal(uint32 cost);
	void HandleAchievementCriteriaBuyBankSlot(bool retroactive = false);
	void HandleAchievementCriteriaFlightPathsTaken();
	void HandleAchievementCriteriaExploreArea(uint32 areaId, uint32 explorationFlags);
	void HandleAchievementCriteriaDoEmote(uint32 emoteId, Unit* pTarget);
	void HandleAchievementCriteriaCompleteQuestsInZone(uint32 zoneId);
	void HandleAchievementCriteriaReachSkillLevel(uint32 skillId, uint32 skillLevel);
	void HandleAchievementCriteriaWinDuel();
	void HandleAchievementCriteriaLoseDuel();
	void HandleAchievementCriteriaKilledByCreature(uint32 creatureEntry);
	void HandleAchievementCriteriaKilledByPlayer();
	void HandleAchievementCriteriaDeath();
	void HandleAchievementCriteriaDeathAtMap(uint32 mapId);
	void HandleAchievementsFromAchievements(AchievementData * pData, uint32 mapId, uint32 classId, uint32 raceId, uint32 itemId, uint32 killedMonster, uint32 ID, uint32 stack);

	//-----------------------------------------------------------------
};
#endif
