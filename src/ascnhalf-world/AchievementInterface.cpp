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

#include "StdAfx.h"

set<uint32> m_completedRealmFirstAchievements;

AchievementInterface::AchievementInterface(Player* plr)
{
	m_player = plr;
	m_achievementInspectPacket = NULL;
}

AchievementInterface::~AchievementInterface()
{
	m_player = NULLPLR;

	if( m_achivementDataMap.size() > 0 )
	{
		std::map<uint32,AchievementData*>::iterator itr = m_achivementDataMap.begin();
		for(; itr != m_achivementDataMap.end(); ++itr)
		{
			delete itr->second;
		}
	}

	if( m_achievementInspectPacket )
		delete m_achievementInspectPacket;
}

void AchievementInterface::LoadFromDB( QueryResult * pResult )
{

	// don't allow GMs to complete achievements
	if( m_player->GetSession()->HasGMPermissions() )
	{
		CharacterDatabase.Execute("DELETE FROM achievements WHERE player = %u;", m_player->GetGUID());
		return;
	}

	if( !pResult ) // We have no achievements yet. :)
		return;

	do 
	{
		Field * fields = pResult->Fetch();
		uint32 achievementid = fields[1].GetUInt32();
		string criteriaprogress = fields[2].GetString();
		bool completed = (fields[3].GetUInt32() > 0);

		AchievementEntry * ae = dbcAchievement.LookupEntry( achievementid );
		AchievementData * ad = new AchievementData;
		memset(ad, 0, sizeof(AchievementData));

		ad->id = achievementid;
		ad->num_criterias = ae->AssociatedCriteriaCount;
		ad->completed = completed;
		ad->date = fields[3].GetUInt32();
		
		if( ad->completed && string(ae->name).find("Realm First!") != string::npos )
			m_completedRealmFirstAchievements.insert( ae->ID );

		vector<string> Delim = StrSplit( criteriaprogress, "," );
		for( uint32 i = 0; i < 32; ++i)
		{
			if( i >= Delim.size() )
				continue;

			string posValue = Delim[i];
			if( !posValue.size() )
				continue;

			uint32 r = atoi(posValue.c_str());
			ad->counter[i] = r;

			//printf("Loaded achievement: %u, %s\n", ae->ID, ad->completed ? "completed" : "incomplete" );
		}

		m_achivementDataMap.insert( make_pair( achievementid, ad) );
	} while ( pResult->NextRow() );
}

void AchievementInterface::SaveToDB(QueryBuffer * buffer)
{
	// don't allow GMs to save achievements
	if( m_player->GetSession()->HasGMPermissions() )
		return;

	bool NewBuffer = false;
	if( !buffer )
	{
		buffer = new QueryBuffer;
		NewBuffer = true;
	}

	map<uint32,AchievementData*>::iterator itr = m_achivementDataMap.begin();
	for(; itr != m_achivementDataMap.end(); ++itr)
	{
		AchievementData * ad = itr->second;
		if( !ad->m_isDirty )
			continue;

		std::stringstream ss;
		ss << "REPLACE INTO achievements (player,achievementid,progress,completed) VALUES (";
		ss << m_player->GetLowGUID() << ",";
		ss << ad->id << ",";
		ss << "'";
		for(uint32 i = 0; i < ad->num_criterias; ++i)
		{
			ss << ad->counter[i] << ",";
		}
		ss << "',";
		ss << ad->date << ")";
		buffer->AddQueryStr( ss.str().c_str() );

		ad->m_isDirty = false;
	}

	if( NewBuffer )
		CharacterDatabase.AddQueryBuffer( buffer );
}

WorldPacket* AchievementInterface::BuildAchievementData(bool forInspect)
{
	if(forInspect && m_achievementInspectPacket)
		return m_achievementInspectPacket;

	WorldPacket * data = new WorldPacket(forInspect ? SMSG_RESPOND_INSPECT_ACHIEVEMENTS : SMSG_ALL_ACHIEVEMENT_DATA, 400);
	if(forInspect)
		*data << m_player->GetNewGUID();

	std::map<uint32,AchievementData*>::iterator itr = m_achivementDataMap.begin();
	for(; itr != m_achivementDataMap.end(); ++itr)
	{
		if( itr->second->completed )
		{
			*data << uint32(itr->first);
			*data << uint32( unixTimeToTimeBitfields(itr->second->date) );
		}
	}

	*data << int32(-1);
	itr = m_achivementDataMap.begin(); // Re-loop, luls
	for(; itr != m_achivementDataMap.end(); ++itr)
	{
		if( !itr->second->completed )
		{
			AchievementEntry * ae = dbcAchievement.LookupEntry( itr->second->id );
			// Loop over the associated criteria
			for(uint32 i = 0; i < ae->AssociatedCriteriaCount; ++i)
			{
				*data << uint32( ae->AssociatedCriteria[i] );
				uint32 counterVar = itr->second->counter[i];
				FastGUIDPack( *data, counterVar );
				*data << m_player->GetNewGUID();
				*data << uint32(0);
				*data << uint32( unixTimeToTimeBitfields( time(NULL) ) );
				*data << uint32(0);
				*data << uint32(0);
			}
		}
	}
	*data << int32(-1);

	if(forInspect)
		m_achievementInspectPacket = data;

	return data;
}

void AchievementInterface::GiveRewardsForAchievement(AchievementEntry * ae)
{
	AchievementReward * ar = AchievementRewardStorage.LookupEntry( ae->ID );
	if(!ar) return;

	// Reward: Item
	if( ar->ItemID )
	{
		m_player->GetGUID();
		Item* pItem = objmgr.CreateItem(ar->ItemID, m_player);
		m_player->GetItemInterface()->AddItemToFreeSlot(pItem);
		if( !m_player->GetItemInterface()->AddItemToFreeSlot(pItem) )
		{
			// Inventory full? Send it by mail.
			m_player->GetSession()->SendNotification("No free slots were found in your inventory, item has been mailed.");
			sMailSystem.DeliverMessage(MAILTYPE_NORMAL, m_player->GetGUID(), m_player->GetGUID(), "Achievement Reward", "Here is your reward.", 0, 0, ar->ItemID, 1, true);
			pItem->Destructor();
		}
	}

	// Define: Alliance Title
	if(m_player->GetTeam() == ALLIANCE)
	{
		if( ar->AllianceTitle )
		{
			m_player->SetKnownTitle(ar->AllianceTitle, true);
			// Set title to Alliance Reward, forced by Blizzard.
			m_player->SetUInt32Value( PLAYER_CHOSEN_TITLE, ar->AllianceTitle);
		}
	}

	// Define: Horde Title
	if(m_player->GetTeam() == HORDE)
	{
		if( ar->HordeTitle )
		{
			m_player->SetKnownTitle(ar->HordeTitle, true);
			// Set title to Horde Reward, forced by Blizzard.
			m_player->SetUInt32Value( PLAYER_CHOSEN_TITLE, ar->HordeTitle);
		}
	}
}

void AchievementInterface::EventAchievementEarned(AchievementData * pData)
{
	pData->completed = true;
	pData->date = (uint32)time(NULL);

	AchievementEntry * ae = dbcAchievement.LookupEntry(pData->id);

	GiveRewardsForAchievement(ae);

	WorldPacket * data = BuildAchievementEarned(pData);

	if( m_player->IsInWorld() )
		m_player->GetSession()->SendPacket( data );
	else
		m_player->CopyAndSendDelayedPacket( data );

	delete data;

	HandleAchievementCriteriaRequiresAchievement(pData->id);

	// Realm First Achievements
	if( string(ae->name).find("Realm First") != string::npos  ) // flags are wrong lol
	{
		m_completedRealmFirstAchievements.insert( ae->ID );

		// Send to my team
		WorldPacket data(SMSG_SERVER_FIRST_ACHIEVEMENT, 60);
		data << m_player->GetName();
		data << m_player->GetGUID();
		data << ae->ID;
		data << uint32(1);
		sWorld.SendFactionMessage(&data, m_player->GetTeam());

		// Send to the other team (no clickable link)
		WorldPacket data2(SMSG_SERVER_FIRST_ACHIEVEMENT, 60);
		data2 << m_player->GetName();
		data2 << m_player->GetGUID();
		data2 << ae->ID;
		data2 << uint32(0);
		sWorld.SendFactionMessage(&data2, m_player->GetTeam() ? 0 : 1);
	}
}



WorldPacket* AchievementInterface::BuildAchievementEarned(AchievementData * pData)
{
	pData->m_isDirty = true;
	WorldPacket * data = new WorldPacket(SMSG_ACHIEVEMENT_EARNED, 40);
	*data << m_player->GetNewGUID();
	*data << pData->id;
	*data << uint32( unixTimeToTimeBitfields(time(NULL)) );
	*data << uint32(0);

	if( m_achievementInspectPacket )
	{
		delete m_achievementInspectPacket;
		m_achievementInspectPacket = NULL;
	}

	return data;
}

AchievementData* AchievementInterface::CreateAchievementDataEntryForAchievement(AchievementEntry * ae)
{
	AchievementData * ad = new AchievementData;
	memset(ad, 0, sizeof(AchievementData));
	ad->id = ae->ID;
	ad->num_criterias = ae->AssociatedCriteriaCount;
	m_achivementDataMap.insert( make_pair( ad->id, ad ) );
	return ad;
}

bool AchievementInterface::CanCompleteAchievement(AchievementData * ad)
{
	// don't allow GMs to complete achievements
	if( m_player->GetSession()->HasGMPermissions() )
		return false;

	if( ad->completed )
		return false;

	bool hasCompleted = false;
	AchievementEntry * ach = dbcAchievement.LookupEntry(ad->id);
	if( ach->categoryId == 1 ) // We cannot complete statistics
		return false;

	// realm first achievements
	if( m_completedRealmFirstAchievements.find(ad->id) != m_completedRealmFirstAchievements.end() )
		return false;

	bool failedOne = false;
	for(uint32 i = 0; i < ad->num_criterias; ++i)
	{
		bool thisFail = false;
		AchievementCriteriaEntry * ace = dbcAchivementCriteria.LookupEntry(ach->AssociatedCriteria[i]);
		uint32 ReqCount = ace->raw.field4 ? ace->raw.field4 : 1;

		if( ace->groupFlag & ACHIEVEMENT_CRITERIA_GROUP_NOT_IN_GROUP && m_player->GetGroup() )
			return false;

		if( ace->timeLimit && ace->timeLimit < ad->completionTimeLast )
			thisFail = true;

		if( ad->counter[i] < ReqCount )
			thisFail = true;

		if( ach->factionFlag == ACHIEVEMENT_FACTION_ALLIANCE && m_player->GetTeam() == 1 )
			thisFail = true;

		if( ach->factionFlag == ACHIEVEMENT_FACTION_HORDE && m_player->GetTeam() == 0 )
			thisFail = true;

		if( thisFail && ace->completionFlag & ACHIEVEMENT_CRITERIA_COMPLETE_ONE_FLAG )
			failedOne = true;
		else if(thisFail)
			return false;

		if( !thisFail && ace->completionFlag & ACHIEVEMENT_CRITERIA_COMPLETE_ONE_FLAG )
			hasCompleted = true;
	}

	if( failedOne && !hasCompleted )
		return false;

	return true;
}

AchievementData* AchievementInterface::GetAchievementDataByAchievementID(uint32 ID)
{
	map<uint32,AchievementData*>::iterator itr = m_achivementDataMap.find( ID );
	if( itr != m_achivementDataMap.end() )
		return itr->second;
	else
	{
		AchievementEntry * ae = dbcAchievement.LookupEntryForced(ID);
		if(!ae)
		{
			printf("No achievement for %u!\n", ID);
		}
		return CreateAchievementDataEntryForAchievement(ae);
	}
}

void AchievementInterface::SendCriteriaUpdate(AchievementData * ad, uint32 idx)
{
	ad->m_isDirty = true;
	ad->date = (uint32)time(NULL);
	WorldPacket data(SMSG_CRITERIA_UPDATE, 50);
	AchievementEntry * ae = dbcAchievement.LookupEntry(ad->id);
	data << uint32(ae->AssociatedCriteria[idx]);
	FastGUIDPack( data, (uint64)ad->counter[idx] );
	data << m_player->GetNewGUID();   
	data << uint32(0);
	data << uint32(unixTimeToTimeBitfields(time(NULL)));
	data << uint32(0);
	data << uint32(0); 

	if( !m_player->IsInWorld() )
		m_player->CopyAndSendDelayedPacket(&data);
	else
		m_player->GetSession()->SendPacket(&data);

	if( m_achievementInspectPacket )
	{
		delete m_achievementInspectPacket;
		m_achievementInspectPacket = NULL;
	}
}

void AchievementInterface::HandleAchievementCriteriaConditionDeath()
{
	// We died, so reset all our achievements that have ACHIEVEMENT_CRITERIA_CONDITION_NO_DEATH
	if( !m_achivementDataMap.size() )
		return;

	map<uint32,AchievementData*>::iterator itr = m_achivementDataMap.begin();
	for(; itr != m_achivementDataMap.end(); ++itr)
	{
		AchievementData * ad = itr->second;
		if(ad->completed) continue;
		AchievementEntry * ae = dbcAchievement.LookupEntry( ad->id );
		for(uint32 i = 0; i < ad->num_criterias; ++i)
		{
			uint32 CriteriaID = ae->AssociatedCriteria[i];
			AchievementCriteriaEntry * ace = dbcAchivementCriteria.LookupEntry( CriteriaID );
			if( ad->counter[i] && ace->raw.additionalRequirement1_type & ACHIEVEMENT_CRITERIA_CONDITION_NO_DEATH )
			{
				ad->counter[i] = 0;
				SendCriteriaUpdate(ad, i); break;
			}
		}
	}
}

void AchievementInterface::HandleAchievementCriteriaKillCreature(uint32 killedMonster)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
	{
		return;
	}
	
	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqKill = ace->kill_creature.creatureID;
		uint32 ReqCount = ace->kill_creature.creatureCount;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;


		// Wrong monster, continue on, kids.
		if( ReqKill != killedMonster )
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaWinBattleground(uint32 bgMapId, uint32 scoreMargin, uint32 time, CBattleground* bg)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_WIN_BG );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqBGMap = ace->win_bg.bgMapID;
		uint32 ReqCount = ace->win_bg.winCount;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;
		// Wrong BG, continue on, kids.
		if( ReqBGMap != bgMapId )
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		ad->completionTimeLast = time;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				if( compareCriteria->raw.additionalRequirement1_type && scoreMargin < compareCriteria->raw.additionalRequirement1_type ) // BG Score Requirement.
					continue;

				// AV stuff :P
				if( bg->GetType() == BATTLEGROUND_ALTERAC_VALLEY )
				{
					AlteracValley* pAV(TO_ALTERACVALLEY(bg));
					if( pAchievementEntry->ID == 225 ||  pAchievementEntry->ID == 1164) // AV: Everything Counts
					{
						continue; // We do not support mines yet in AV
					}

					if( pAchievementEntry->ID == 220 ) // AV: Stormpike Perfection
					{
						bool failure = false;
						// We must control all Alliance nodes and Horde nodes (towers only)
						for(uint32 i = 0; i < AV_NUM_CONTROL_POINTS; ++i)
						{
							if( pAV->GetNode(i)->IsGraveyard() )
								continue;

							if( pAV->GetNode(i)->GetState() != AV_NODE_STATE_ALLIANCE_CONTROLLED )
								failure = true;
						}
						if( failure ) continue;
					}

					if( pAchievementEntry->ID == 873 ) // AV: Frostwolf Perfection
					{
						bool failure = false;
						// We must control all Alliance nodes and Horde nodes (towers only)
						for(uint32 i = 0; i < AV_NUM_CONTROL_POINTS; ++i)
						{
							if( pAV->GetNode(i)->IsGraveyard() )
								continue;

							if( pAV->GetNode(i)->GetState() != AV_NODE_STATE_HORDE_CONTROLLED )
								failure = true;
						}
						if( failure ) continue;
					}
				}

				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaRequiresAchievement(uint32 achievementId)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqAchievement = ace->complete_achievement.linkedAchievement;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		if( ReqAchievement != achievementId )
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;

		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaLevelUp(uint32 level)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqLevel = ace->reach_level.level;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		if( level < ReqLevel )
			continue;

		// Realm first to 80 stuff has race and class requirements. Let the hacking begin.
		if( string(pAchievementEntry->name).find("Realm First!") != string::npos )
		{
			static const char* classNames[] = { "", "Warrior", "Paladin", "Hunter", "Rogue", "Priest", "Death Knight", "Shaman", "Mage", "Warlock", "", "Druid" };
			static const char* raceNames[] = { "", "Human", "Orc", "Dwarf", "Night Elf", "Forsaken", "Tauren", "Gnome", "Troll", "", "Blood Elf", "Draenei" };

			uint32 ReqClass = 0;
			uint32 ReqRace = 0;
			for(uint32 i = 0; i < 12; ++i)
			{
				if(strlen(classNames[i]) > 0 && string(pAchievementEntry->name).find(classNames[i]) != string::npos )
				{
					// We require this class
					ReqClass = i;
					break;
				}
			}
			for(uint32 i = 0; i < 12; ++i)
			{
				if(strlen(raceNames[i]) > 0 && string(pAchievementEntry->name).find(raceNames[i]) != string::npos )
				{
					// We require this race
					ReqRace = i;
					break;
				}
			}

			if( ReqClass && m_player->getClass() != ReqClass )
				continue;

			if( ReqRace && m_player->getRace() != ReqRace )
				continue;
		}

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;

		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = m_player->getLevel() > ReqLevel ? ReqLevel : m_player->getLevel();
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaOwnItem(uint32 itemId, uint32 stack)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqItemId = ace->own_item.itemID;
		uint32 ReqItemCount = ace->own_item.itemCount;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		if( itemId != ReqItemId )
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if( ad->completed )
			continue;

		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + stack;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}

	HandleAchievementCriteriaLootItem(itemId, stack);
}

void AchievementInterface::HandleAchievementCriteriaLootItem(uint32 itemId, uint32 stack)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqItemId = ace->loot_item.itemID;
		uint32 ReqItemCount = ace->loot_item.itemCount;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		if( itemId != ReqItemId )
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;

		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + stack;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaQuestCount(uint32 questCount)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqQuestCount = ace->complete_quest_count.totalQuestCount;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;

		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = questCount;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaHonorableKillClass(uint32 classId)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqClass = ace->hk_class.classID;
		uint32 ReqCount = ace->hk_class.count;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		if( ReqClass != classId )
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaHonorableKillRace(uint32 raceId)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_HK_RACE );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqRace = ace->hk_race.raceID;
		uint32 ReqCount = ace->hk_race.count;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		if( ReqRace != raceId )
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaTalentResetCostTotal(uint32 cost)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TALENTS );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + cost;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaTalentResetCount()
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_NUMBER_OF_TALENT_RESETS );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaBuyBankSlot(bool retroactive)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqSlots = ace->buy_bank_slot.numberOfSlots; // We don't actually use this. :P

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				if( retroactive )
				{
					uint32 bytes = m_player->GetUInt32Value(PLAYER_BYTES_2);
					uint32 slots = (uint8)(bytes >> 16);
					ad->counter[i] = slots > ReqSlots ? ReqSlots : slots;
				}
				else
					ad->counter[i] = ad->counter[i] + 1;

				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaFlightPathsTaken()
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_FLIGHT_PATHS_TAKEN );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaExploreArea(uint32 areaId, uint32 explorationFlags)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqFlags = ace->explore_area.areaReference;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		WorldMapOverlayEntry * wmoe = dbcWorldMapOverlay.LookupEntryForced( ReqFlags );
		if(!wmoe) continue;

		AreaTable * at = dbcArea.LookupEntryForced(wmoe->AreaTableID);
		if(!at || !(ReqFlags & at->explorationFlag) )
			continue;

		uint32 offset = at->explorationFlag / 32;
		offset += PLAYER_EXPLORED_ZONES_1;

		uint32 val = (uint32)(1 << (at->explorationFlag % 32));
		uint32 currFields = m_player->GetUInt32Value(offset);

		// Not explored /sadface
		if( !(currFields & val) )
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;

		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaHonorableKill()
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqKills = ace->honorable_kill.killCount;

		if( m_player->m_killsLifetime < ReqKills )
			continue;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

#define SCRIPTOK_FALSE { scriptOk = false; break; }
void AchievementInterface::HandleAchievementCriteriaDoEmote(uint32 emoteId, Unit* pTarget)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqEmote = ace->do_emote.emoteID;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		if(ReqEmote != emoteId)
			continue; // Wrong emote, newb!

		// Target information is not stored, so we'll have to do this one by one...
		// --unless the target's name is the description of the criteria! Bahahaha
		bool scriptOk = false;
		if( pTarget && pTarget->IsCreature() )
		{
			Creature* pCreature = TO_CREATURE(pTarget);
			if( !(!ace->name || strlen(ace->name) == 0 || !pCreature->GetCreatureInfo() || stricmp(pCreature->GetCreatureInfo()->Name, ace->name) != 0) )
			{
				scriptOk = true;
			}
		}

		string name = string(pAchievementEntry->name);
		if( name.find("Total") != string::npos )
		{
			// It's a statistic, like: "Total Times /Lol'd"
			scriptOk = true;
		}

		// Script individual ones here...
		if( ace->ID == 2379 ) // Make Love, Not Warcraft
		{
			if( !pTarget || !pTarget->IsPlayer() || !pTarget->isDead() || !isHostile(pTarget, m_player) )
				SCRIPTOK_FALSE

			scriptOk = true;
		}
		else if( ace->ID == 6261 ) // Winter Veil: A Frosty Shake 
		{
			if( m_player->GetZoneId() != 4395 ) // Not in Dalaran
				SCRIPTOK_FALSE
			
			if( !pTarget || !pTarget->HasAura(21848) ) // Not a Snowman
				SCRIPTOK_FALSE

			scriptOk = true;
		}

		if( !scriptOk ) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaCompleteQuestsInZone(uint32 zoneId)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqZone = ace->complete_quests_in_zone.zoneID;
		uint32 ReqCount = ace->complete_quests_in_zone.questCount;

		if( ReqZone != zoneId )
			continue;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;

		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaReachSkillLevel(uint32 skillId, uint32 skillLevel)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqSkill = ace->reach_skill_level.skillID;
		uint32 ReqLevel = ace->reach_skill_level.skillLevel;

		if( ReqSkill != skillId )
			continue;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry)
			continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;

		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = skillLevel;
				SendCriteriaUpdate(ad, i);
				break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaWinDuel()
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		//uint32 ReqDuels = ace->win_duel.duelCount;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaLoseDuel()
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_LOSE_DUEL );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		//uint32 ReqDuels = ace->win_duel.duelCount;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i] = ad->counter[i] + 1;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaKilledByCreature(uint32 killedMonster)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE );
	if( itr == objmgr.m_achievementCriteriaMap.end() )
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 ReqCreature = ace->killed_by_creature.creatureEntry;

		if( ReqCreature != killedMonster )
			continue;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i]++;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaKilledByPlayer()
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_PLAYER );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i]++;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}
}

void AchievementInterface::HandleAchievementCriteriaDeath()
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_DEATH );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
				ad->counter[i]++;
				SendCriteriaUpdate(ad, i); break;
			}
		}

		if( CanCompleteAchievement(ad) )
			EventAchievementEarned(ad);
	}

	HandleAchievementCriteriaDeathAtMap(m_player->GetMapId());
}

void AchievementInterface::HandleAchievementCriteriaDeathAtMap(uint32 mapId)
{
	AchievementCriteriaMap::iterator itr = objmgr.m_achievementCriteriaMap.find( ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP );
	if(itr == objmgr.m_achievementCriteriaMap.end())
		return;

	AchievementCriteriaSet * acs = itr->second;
	if( !acs ) // We have no achievements for this criteria :(
		return;

	AchievementCriteriaSet::iterator citr = acs->begin();
	for(; citr != acs->end(); ++citr)
	{
		AchievementCriteriaEntry * ace = (*citr);
		uint32 AchievementID = ace->referredAchievement;
		uint32 MapID = ace->death_at_map.mapID;

		if( mapId != MapID )
			continue;

		AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(AchievementID);
		if(!pAchievementEntry) continue;

		AchievementCriteriaEntry * compareCriteria = NULL;
		AchievementData * ad = GetAchievementDataByAchievementID(AchievementID);
		if(ad->completed)
			continue;
		// Figure out our associative ID.
		for(uint32 i = 0; i < pAchievementEntry->AssociatedCriteriaCount; ++i)
		{
			compareCriteria = dbcAchivementCriteria.LookupEntry( pAchievementEntry->AssociatedCriteria[i] );			
			if( compareCriteria == ace )
			{
			ad->counter[i]++;
			SendCriteriaUpdate(ad, i); break;
		}
	}
	if( CanCompleteAchievement(ad) )
		EventAchievementEarned(ad);
  }
}

void AchievementInterface::HandleAchievementsFromAchievements(AchievementData * pData, uint32 mapId, uint32 classId, uint32 raceId, uint32 itemId, uint32 killedMonster, uint32 ID, uint32 stack)
 {
	AchievementEntry * pAchievementEntry = dbcAchievement.LookupEntryForced(ID);
	{
		switch(ID)
		{
		case 913: // To Honor One's Elders
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (912 && 911 && 910 && 914 && 915 && 1396 && 609 && 626 && 1281 && 1552 && 937))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1693: // Fool For Love
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (260 && 1188 && 1280 && 1291 && 1695 && 1696 && 1698 && 1699 && 1702 && 1701 && 1703 && 1704))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1707: // Fool For Love
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (260 && 1188 && 1279 && 1291 && 1695 && 1697 && 1696 && 1699 && 1702 && 1701 && 1703 && 1704))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2798: // Noble Gardener
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (2676 && 2418 && 2436 && 2576 && 2416 && 2497 && 2420 && 2422))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2797: // Noble Gardener
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (2676 && 2418 && 2416 && 2419 && 2421 && 2422 && 2436 && 2576))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1793: // FOR THE CHILDREN!!!
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1791 && 1788 && 1789 && 1792 && 1786 && 1790))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1039: // The Flame Keeper
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1036 && 1037 && 271 && 263 && 1145 && 272))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1038: // The Flame Warden
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1034 && 1035 && 263 && 271 && 1145 && 272))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1683: // Brewmaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1203 && 1185 && 2796 && 1260 && 295 && 1186 && 293 && 303 && 1936))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1684: // Brewmaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1184 && 1185 && 2796 && 1260 && 295 && 1186 && 293 && 1936 && 303))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1657: // Hallowed be thy Name
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (972 && 288 && 255 && 289 && 981 && 1041 && 1261 && 291 && 283 && 292 && 971))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1656: // Hallowed be thy Name
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (972 && 288 && 255 && 289 && 981 && 1040 && 1261 && 291 && 283 && 292 && 970))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1691: // Merrymaker
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (273 && 252 && 259 && 1282 && 277 && 1295 && 279 && 1687 && 1685 && 1688 && 1689 && 1690))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1692: // Merrymaker
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (273 && 252 && 1255 && 1282 && 277 && 1295 && 279 && 1687 && 1686 && 1688 && 1689 && 1690))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2145: // What a Long, Strange Trip Its Been.
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (913 && 1693 && 2798 && 1793 && 1039 && 1683 && 1657 && 1691))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
					m_player->addSpell(60024);
			}break;
		case 2144: // What a Long, Strange Trip Its Been.
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (913 && 1707 && 2797 && 1793 && 1038 && 1684 && 1656 && 1692))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
					m_player->addSpell(60024);
			}break;
		case 1036: // The Fires of Azeroth
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1025 && 1026 && 1027))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1034: // The Fires of Azeroth
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1022 && 1023 && 1024))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1037: // Desecration of the Alliance
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1031 && 1032 && 1033))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1035: // Desecration of the Horde
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1028 && 1029 && 1030))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 971: // Tricks and Treats of Azeroth
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (965 && 967 && 968))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 970: // Tricks and Treats of Azeroth
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (963 && 966 && 969))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 730: // Skills to pay the Bills
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (130 && 135 && 125))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1784: // Hail to the Chef
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (125 && 877 && 906 && 1779 && 1780 && 1781 && 1783 && 1798 && 1801 && 1800))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1563: // Hail to the Chef
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (125 && 877 && 906 && 1779 && 1780 && 1781 && 1782 && 1798 && 1801 && 1800))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2096: // The Coin Master
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (2094 && 2095 && 1957))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1516: // Accomplished Angler
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (130 && 153 && 1257 && 150 && 306 && 726 && 878 && 905 && 560 && 144 && 1225 && 1517 && 1243 && 1561 && 2096))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 945: // The Argent Champion
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (946 && 947))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 952: // Mercenary of Sholazar
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (951 && 950))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1010: // Northrend Vanguard
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (947 && 1007 && 1008 && 1009))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1283: // Classic DungeonMaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (628 && 629 && 630 && 631 && 632 && 633 && 634 && 635 && 636 && 637 && 638 && 639 && 640 && 641 && 642 && 643 && 644 && 645 && 646))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1285: // Classic Raider
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (684 && 685 && 686 && 687 && 688 && 689))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1284: // Outland DungeonMaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (647 && 648 && 649 && 650 && 651 && 652 && 653 && 654 && 655 && 656 && 657 && 658 && 659 && 660 && 661 && 666))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1287: // Outland Dungeon Hero
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (667 && 668 && 669 && 670 && 671 && 673 && 674 && 675 && 676 && 677 && 678 && 679 && 680 && 681 && 682 && 672))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1286: // Outland Raider
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (690 && 691 && 692 && 693 && 694 && 695 && 696 && 697 && 698))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1288: // Northrend DungeonMaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (477 && 478 && 479 && 480 && 481 && 482 && 483 && 484 && 485 && 486 && 487 && 488))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1289: // Northrend Dungeon Hero
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (489 && 490 && 500 && 491 && 492 && 493 && 494 && 495 && 496 && 497 && 498 && 499))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2136: // Glory of the Hero
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1919 && 2150 && 2036 && 2037 && 1296 && 1297 && 1860 && 1861 && 1862 && 2038 && 2056 && 2151 && 2039 && 2057 && 1816 && 1865 && 2041 && 2153 && 1864 && 2152 && 2040 && 2058 && 1866 && 2154 && 2155 && 1867 && 1834 && 2042 && 1817 && 1872 && 2043 && 1873 && 2156 && 2157 && 1871 && 1868 && 2044 && 2045 && 2046))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2137: // Glory of the Raider
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (578 && 1858 && 1856 && 1996 && 1997 && 2178 && 2180 && 622 && 1874 && 1869 && 2047 && 2051 && 2146 && 2176 && 2148 && 2187 && 2184))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2138: // Glory of the Raider
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (579 && 1859 && 1857 && 2139 && 2140 && 2186 && 2179 && 2177 && 2181 && 623 && 1875 && 1870 && 2048 && 2149 && 2054 && 2147 && 2185))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2957: // Glory of the Ulduar Raider
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (3056 && 2930 && 2923 && 3058 && 2941 && 2953 && 3006 && 3182 && 3176 && 3179 && 3180 && 3181 && 3158))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2958: // Glory of the Ulduar Raider
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (3057 && 2929 && 2924 && 3059 && 2944 && 2954 && 3007 && 3184 && 3183 && 3187 && 3189 && 3188 && 3163))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 714: // The Conqueror
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (708 && 710 && 712))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1175: // The Battlemaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1168 && 1170 && 1173 && 1171 && 2195))
				&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1174: // The Arena Master
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (699 && 876 && 1159 && 1160 && 1161 && 408 && 1162 && 409))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1168: // Master of Alterac Valley
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (219 && 221 && 222 && 224 && 1164 && 226 && 223 && 873 && 582 && 706 && 708 && 1166))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1170: // Master of Arathi Basin
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (155 && 165 && 158 && 73 && 1153 && 157 && 161 && 156 && 159 && 162 && 710 && 583 && 584))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1171: // Master of Eye of the Storm
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (209 && 783 && 784 && 214 && 213 && 212 && 216 && 233))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1173: // Master of Warsong Gulch
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (167 && 199 && 200 && 872 && 168 && 201 && 204 && 712 && 1251 && 1502 && 1252 && 207))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2195: // Master of Stand of the Ancients
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1309 && 1310 && 1765 && 1761 && 2193 && 2192 && 1763 && 2189 && 1764 && 2190 && 1766 && 2191 && 2200))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2776: // Master of Wintergrasp
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1718 && 1755 && 2199 && 2080 && 2089 && 1722 && 1721 && 2476 && 1723 && 1727 && 1751))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 3957: // Master of Isle of ConQuest
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (3777 && 4177 && 3847 && 3848 && 3849 && 3850 && 3852 && 3853 && 3854 && 4256 && 3855))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 907: // The Justicar
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (709 && 711 && 713))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 230: // The Battlemaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1167 && 1169 && 1172 && 1171 && 2194))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1167: // Master of Alterac Valley
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (219 && 221 && 222 && 1151 && 225 && 226 && 223 && 220 && 582 && 707 && 709 && 1166))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1169: // Master of Arathi Basin
		{
				if(m_player->GetAchievementInterface()->HasAchievements() == (155 && 165 && 158 && 73 && 1153 && 157 && 161 && 156 && 159 && 162 && 711 && 583 && 584))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
		}break;
		case 1172: // Master of Warsong Gulch
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (167 && 199 && 200 && 872 && 168 && 201 && 204 && 713 && 203 && 202 && 206 && 207))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2194: // Master of Stand of the Ancients
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1309 && 1310 && 1765 && 1761 && 2193 && 1762 && 1763 && 2189 && 1764 && 2190 && 1766 && 2191 && 1757))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1752: // Master of Wintergrasp
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1718 && 1755 && 2199 && 2080 && 2089 && 1722 && 1721 && 1737 && 1723 && 1727 && 1751))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 3857: // Master of Isle of ConQuest
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (3777 && 3851 && 3847 && 3848 && 3849 && 3850 && 3852 && 3853 && 3854 && 3856 && 3855))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 42: // Explore Eastern Kingdoms
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (776 && 760 && 761 && 765 && 766 && 775 && 627 && 778 && 772 && 779 && 780 && 768 && 859 && 774 && 769 && 858 && 781 && 782 && 773 && 802 && 841 && 777 && 770 && 771 && 868))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 43: // Explore Kalimdor
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (728 && 736 && 842 && 860 && 750 && 844 && 861 && 845 && 846 && 847 && 848 && 850 && 849 && 851 && 852 && 853 && 854 && 855 && 856 && 857))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 44: // Explore Outland
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (862 && 863 && 867 && 866 && 865 && 843 && 864))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 45: // Explore Northrend
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1264 && 1263 && 1265 && 1266 && 1267 && 1268 && 1457 && 1269 && 1270))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 46: // World Explorer
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (42 && 43 && 44 && 45))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1682: // The Loremaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1360 && 1274 && 1677 && 1680))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1681: // The Loremaster
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (41 && 1262 && 1676 && 1678))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1274: // Loremaster of Outland
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1271 && 1272 && 1273 && 1190 && 1193 && 1194 && 1195))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1262: // Loremaster of Outland
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (1189 && 1190 && 1191 && 1192 && 1193 && 1194 && 1195))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 1360: // Loremaster of Northrend
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (36 && 38 && 39 && 40 && 1356 && 1357 && 1358 && 1359))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 41: // Loremaster of Northrend
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (33 && 34 && 35 && 36 && 37 && 38 && 39 && 40))
					&AchievementInterface::EventAchievementEarned;
				pData->completed = true;
			}break;
		case 941: // Hemet Nesingwary: The Collected Quests
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (938 && 939 && 940))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 614: // For The Alliance!
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (610 && 611 && 612 && 613))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 619: // For The Horde!
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (615 && 616 && 617 && 618))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 3656: // Horde Pilgrim
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (3579 && 3557 && 3597 && 3582 && 3559 && 3577 && 3581 && 3558 && 3578))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
					m_player->addSpell(61773);
			}break;
		case 3478: // Alliance Pilgrim
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (3579 && 3556 && 3596 && 3582 && 3559 && 3576 && 3580 && 3558 && 3578))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
					m_player->addSpell(61773);
			}break;
		case 2788: // Champion of the Horde
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (2783 && 2784 && 2785 && 2786 && 2787))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2771: // Exalted Champion of the Horde
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (2765 && 2766 && 2767 && 2768 && 2769))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2816: // Exalted Argent Champion of the Horde
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (947 && 2765 && 2766 && 2767 && 2768 && 2769))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2782: // Champion of the Alliance
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (2777 && 2778 && 2779 && 2780 && 2781))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2770: // Exalted Champion of the Alliance
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (2760 && 2761 && 2762 && 2763 && 2764))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		case 2817: // Exalted Argent Champion of the Alliance
			{
				if(m_player->GetAchievementInterface()->HasAchievements() == (947 && 2760 && 2761 && 2762 && 2763 && 2764))
					&AchievementInterface::EventAchievementEarned;
					pData->completed = true;
			}break;
		}
	}
}
