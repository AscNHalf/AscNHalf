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

#define ROUND_LENGTH 600 // This takes seconds.

const float m_gateSigilsLocations[5][5] = {
	{192687,1414.054f,106.72f,41.442f,5.441f},
	{192685,1060.63f,-107.8f,94.7f,0.034f},
	{192689,1433.383f,-216.4f,43.642f,0.9736f},
	{192690,1230.75f,-210.724f,67.611f,0.5023f},
	{192691,1217.8f,79.532f,66.58f,5.745f},
};

const uint32 m_gatetransgos[3] = {
	190763,
	191575,		// the same as the first one, but not needed
	192819,		// the same as the first one, but not needed
};

const float m_gatesLocations[5][5] = {
	{190722, 1411.57f, 108.163f, 28.692f, 5.441f},
	{190727, 1055.452f, -108.1f, 82.134f, 0.034f},
	{190724, 1431.3413f, -219.437f, 30.893f, 0.9736f},
	{190726, 1227.667f, -212.555f, 55.372f, 0.5023f},
	{190723, 1214.681f, 81.21f,53.413f, 5.745f},
};
/*
static const char * m_gatesname[5][1] = {
};*/

//Location : Cannons
const float m_cannonsLocations[10][4] = {
	{1436.429f, 110.05f, 41.407f, 5.4f},
	{1404.9023f, 84.758f, 41.183f, 5.46f},
	{1068.693f, -86.951f, 93.81f, 0.02f},
	{1068.83f, -127.56f, 96.45f, 0.0912f},
	{1422.115f, -196.433f, 42.1825f, 1.0222f},
	{1454.887f, -220.454f, 41.956f, 0.9627f},
	{1232.345f, -187.517f, 66.945f, 0.45f},
	{1249.634f, -224.189f, 66.72f, 0.635f},
	{1236.213f, 92.287f, 64.965f, 5.751f},
	{1215.11f, 57.772f, 64.739f, 5.78f},
};

//Location : Transporters ( Teleporters.)
const float m_gateTransportersLocations[5][4] = {
	{1394.0444f, 72.586f, 31.0535f, 0.0f},
	{1065.0f, -89.7f, 81.08f, 0.0f},
	{1467.95f, -225.67f, 30.9f, 0.0f},
	{1255.93f, -233.382f, 56.44f, 0.0f},
	{1215.679f, 47.47f, 54.281f, 0.0f},
};

// Defender Trans Dest: Locations you end up.
const float sotaTransporterDestination[5][4] = {
	{ 1388.94f, 103.067f, 34.49f, 5.4571f },
	{ 1043.69f, -87.95f, 87.12f, 0.003f },
	{ 1441.0411f, -240.974f, 35.264f, 0.949f },
	{ 1228.342f, -235.234f, 60.03f, 0.4584f },
	{ 1193.857f, 69.9f, 58.046f, 5.7245f },
};
const float sotaRepop[5][4] = {
	{ 1109.52f, 6.13f, 69.38f, 5.94f, },	// South graveyard
	{ 1405.45f, -301.34f, 32.18f, 2.21f },	// East graveyard
	{ 1390.89f, 204.84f, 32.12f, 5.65f },	// West graveyard
	{ 962.52f, -184.76f, 91.47f, 0.9f },	
	{ 1446.87f, -54.35f, 5.88f, 0.25f },
	
};

const float sotaBoatids[4][2] = {	/*[boatids][captinids(on boats)] */
	{193182, 32658},	// The Graceful Maiden, Privateer Zierhut
	{193185, 32657},	// The Frostbreaker, Privateer Stonemantle
	{193183, 32660},	// The Blightbringer, Dread Captain
	{193184, 32659},	// The Coffin Carrier, Dread Captain Winge
};

const float sotaBoats[4][4] = {
    { 2679.696777f, -826.891235f, 3.712860f, 5.78367f},	// ally
    { 2574.003662f, 981.261475f, 2.603424f, 0.807696f},		// ally
	{ 2679.696777f, -826.891235f, 3.712860f, 5.78367f},	// horde
    { 2574.003662f, 981.261475f, 2.603424f, 0.807696f},		// horde
};

const float sotaStopBoats[2][4] = {
	{ 1623.34f, 37.0f, 1.0f, 3.9f },
	{ 1623.34f, 37.0f, 1.0f, 3.9f },
};

const float sotaStopBoatsPlayer[2][4] = {
	{ 1624.7f, 42.93f, 12.0f, 2.63f },
	{ 1624.7f, 42.93f, 12.0f, 2.63f },
};

const float demolisherSalesman[2][5] = {
	{29260, 1360.54f, -320.08f, 36.83f, 0.18f},		// Rigger Sparkligh
	{29262, 1363.08f, 219.07f, 37.07f, 2.71f},		// Gorgril Rigspark
};

const float demolisherLocations[8][4] = {
	{1353.65f, 224.56f, 35.20f, 4.31f},
	{1347.26f, 205.47f, 33.04f, 4.44f},
	{1371.41f, -317.01f, 34.99f, 1.92f},
	{1363.59f, -300.13f, 33.19f, 1.87f},
	{1564.84f, 112.20f, 2.90f, 3.59f},
	{1569.93f, -168.21f, 5.46f, 3.40f},
	{1610.25f, -116.32f, 8.81f, 2.44f},
	{1617.97f, 62.39f, 7.17f, 3.85f},
};

static uint32 ControlPointGoIds[3][2] = { /* ALLIANCE-CONTROLLED    HORDE_CONTROLLED*/
		{ 180076,    180078 },	
		{ 180076,    180078 },
		{ 180076,    180078 },
};

const uint8 m_banners[3] = { 0, 1, 2 };

const float ControlPointFlagpole[3][4] = {
	{1217.88f, -68.01f, 70.08f, 0.01f},			// South Graveyard
	{1341.15f, -154.83f, 30.90f, 0.01f},		// East Graveyard
	{1315.13f, 11.74f, 31.12f, 0.01f},			// West Graveyard
};

const float ControlPointCoordinates[3][4] = {
	{1217.88f, -68.01f, 70.08f, 0.01f},			// South Graveyard
	{1341.15f, -154.83f, 30.90f, 0.01f},		// East Graveyard
	{1315.13f, 11.74f, 31.12f, 0.01f},			// West Graveyard
};

const uint32 capturedStates[3][2] = {		/* [alliance][horde]*/
	{ WORLDSTATE_SOTA_WEST_GRAVEYARD_ALLIANCE_CONTROLLED, WORLDSTATE_SOTA_WEST_GRAVEYARD_HORDE_CONTROLLED},
	{ WORLDSTATE_SOTA_EAST_GRAVEYARD_ALLIANCE_CONTROLLED, WORLDSTATE_SOTA_EAST_GRAVEYARD_HORDE_CONTROLLED},
	{ WORLDSTATE_SOTA_SOUTH_GRAVEYARD_ALLIANCE_CONTROLLED, WORLDSTATE_SOTA_SOUTH_GRAVEYARD_HORDE_CONTROLLED},
};

static const char * ControlPointNames[3] = {
	"West Graveyard",
	"East Graveyard",
	"South Graveyard",
};

float CalculateDistance(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	float dz = z1 - z2;
	return sqrt(dx*dx + dy*dy + dz*dz);
}
StrandOfTheAncients::StrandOfTheAncients(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t) : CBattleground(mgr,id,lgroup,t)
{
	Attackers = RandomUInt(2)-1;
	BattleRound = 1;
	hordewins = 0;
	allywins = 0;
	m_started = false;
	m_ended = false;
	m_playerCountPerTeam = 15;

	for(uint8 i = 0; i < 3; ++i)
	{
		m_sotacontrolPointAuras[i] = NULLGOB;
		m_sotacontrolPoint[i] = NULLGOB;
		m_spiritGuides[i] = NULLCREATURE;
		m_basesAssaultedBy[i] = -1;
		m_basesOwnedBy[i] = -1;
		m_basesLastOwnedBy[i] = -1;
		m_flagIsVirgin[i] = true;
	}
}

StrandOfTheAncients::~StrandOfTheAncients()
{
	for(uint8 i = 0; i < 3; ++i)
	{
		if(m_sotacontrolPoint[i] != NULL)
		{
			m_sotacontrolPoint[i]->m_battleground = NULLBATTLEGROUND;
			if( !m_sotacontrolPoint[i]->IsInWorld() )
			{
				m_sotacontrolPoint[i]->Destructor();
			}
		}

		if(m_sotacontrolPointAuras[i])
		{
			m_sotacontrolPointAuras[i]->m_battleground = NULLBATTLEGROUND;
			if( !m_sotacontrolPointAuras[i]->IsInWorld() )
			{
				m_sotacontrolPointAuras[i]->Destructor();
			}
		}
		
		if(m_flagpole[i])
		{
			m_flagpole[i]->m_battleground = NULLBATTLEGROUND;
			if( !m_flagpole[i]->IsInWorld() )
			{
				m_flagpole[i]->Destructor();
			}
		}
	}
	for(uint8 i = 0; i < 5; i++)
	{
		if(m_gates[i] != NULL)
		{
			m_gates[i]->m_battleground = NULLBATTLEGROUND;
			if( !m_gates[i]->IsInWorld() )
			{
				m_gates[i]->Destructor();
			}
		}
		
		if(m_gateSigils[i] != NULL)
		{
			m_gateSigils[i]->m_battleground = NULLBATTLEGROUND;
			if( !m_gateSigils[i]->IsInWorld() )
			{
				m_gateSigils[i]->Destructor();
			}
		}
		
		if(m_gateTransporters[i] != NULL)
		{
			m_gateTransporters[i]->m_battleground = NULLBATTLEGROUND;
			if( !m_gateTransporters[i]->IsInWorld() )
			{
				m_gateTransporters[i]->Destructor();
			}
		}
	}
	
	if(m_relic != NULL)
	{
		m_relic->m_battleground = NULLBATTLEGROUND;
		if( !m_relic->IsInWorld() )
		{
			m_relic->Destructor();
		}
	}
	
	if(m_endgate != NULL)
	{
		m_endgate->m_battleground = NULLBATTLEGROUND;
		if( !m_endgate->IsInWorld() )
		{
			m_endgate->Destructor();
		}
	}
}

bool StrandOfTheAncients::HookHandleRepop(Player* plr)
{
	LocationVector dest;
	uint32 x;
	
	if(plr->GetTeam() == 1 && Attackers == HORDE)
	{	
		x = 0;
	}
	else if(plr->GetTeam() == 1 && Attackers == ALLIANCE)
	{
		x = 1;
	}
	else if(plr->GetTeam() == 0 && Attackers == HORDE)
	{
		x = 1;
	}
	else if(plr->GetTeam() == 0 && Attackers == ALLIANCE)
	{
		x = 0;
	}
	else { x = 0; }		// shouldnt happen
	
	dest.ChangeCoords(sotaRepop[x][0], sotaRepop[x][1],
			sotaRepop[x][2], sotaRepop[x][3]);

	plr->SafeTeleport(plr->GetMapId(), plr->GetInstanceID(), dest);
	return true;
}

void StrandOfTheAncients::SpawnControlPoint(uint32 Id, uint32 Type)
{
	GameObjectInfo * gi, * gi_aura;
	gi = GameObjectNameStorage.LookupEntry(ControlPointGoIds[Id][Type]);
	if(gi == NULL)
		return;

	gi_aura = gi->sound3 ? GameObjectNameStorage.LookupEntry(gi->sound3) : NULL;

	if(m_sotacontrolPoint[Id] == NULL)
	{
		m_sotacontrolPoint[Id] = SpawnGameObject(gi->ID, ControlPointCoordinates[Id][0], ControlPointCoordinates[Id][1],
			ControlPointCoordinates[Id][2], ControlPointCoordinates[Id][3], 0, 35, 1.0f);

		m_sotacontrolPoint[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_STATE, 1);
		m_sotacontrolPoint[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_TYPE_ID, gi->Type);
		m_sotacontrolPoint[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_ANIMPROGRESS, 100);
		m_sotacontrolPoint[Id]->SetUInt32Value(GAMEOBJECT_DYNAMIC, 1);
		m_sotacontrolPoint[Id]->SetUInt32Value(GAMEOBJECT_DISPLAYID, gi->DisplayID);

		switch(Type)
		{
		case SOTA_SPAWN_TYPE_ALLIANCE_CONTROLLED:
			m_sotacontrolPoint[Id]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);
			break;
			
		case SOTA_SPAWN_TYPE_HORDE_CONTROLLED:
			m_sotacontrolPoint[Id]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);
			break;
		}

		m_sotacontrolPoint[Id]->bannerslot = Id;
		m_sotacontrolPoint[Id]->PushToWorld(m_mapMgr);
	}
	else
	{
		if(m_sotacontrolPoint[Id]->IsInWorld())
			m_sotacontrolPoint[Id]->RemoveFromWorld(false);

		// assign it a new guid (client needs this to see the entry change?)
		m_sotacontrolPoint[Id]->SetNewGuid(m_mapMgr->GenerateGameobjectGuid());
		m_sotacontrolPoint[Id]->SetUInt32Value(OBJECT_FIELD_ENTRY, gi->ID);
		m_sotacontrolPoint[Id]->SetUInt32Value(GAMEOBJECT_DISPLAYID, gi->DisplayID);
		m_sotacontrolPoint[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_TYPE_ID, gi->Type);

		switch(Type)
		{
		case SOTA_SPAWN_TYPE_HORDE_CONTROLLED:
		case SOTA_SPAWN_TYPE_ALLIANCE_CONTROLLED:
			m_sotacontrolPoint[Id]->SetUInt32Value(GAMEOBJECT_FACTION, 14);
			break;
		}

		m_sotacontrolPoint[Id]->SetInfo(gi);
		m_sotacontrolPoint[Id]->PushToWorld(m_mapMgr);
	}

	if(gi_aura==NULL)
	{
		// remove it if it exists
		if(m_sotacontrolPointAuras[Id]!=NULL && m_sotacontrolPointAuras[Id]->IsInWorld())
			m_sotacontrolPointAuras[Id]->RemoveFromWorld(false);
			
		return;
	}

	if(m_sotacontrolPointAuras[Id] == NULL)
	{
		m_sotacontrolPointAuras[Id] = SpawnGameObject(gi_aura->ID, ControlPointCoordinates[Id][0], ControlPointCoordinates[Id][1],
			ControlPointCoordinates[Id][2], ControlPointCoordinates[Id][3], 0, 35, 5.0f);

		m_sotacontrolPointAuras[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_STATE, 1);
		m_sotacontrolPointAuras[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_TYPE_ID, 6);
		m_sotacontrolPointAuras[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_ANIMPROGRESS, 100);
		m_sotacontrolPointAuras[Id]->bannerauraslot = Id;
		m_sotacontrolPointAuras[Id]->PushToWorld(m_mapMgr);
	}
	else
	{
		if(m_sotacontrolPointAuras[Id]->IsInWorld())
			m_sotacontrolPointAuras[Id]->RemoveFromWorld(false);

		// re-spawn the aura
		m_sotacontrolPointAuras[Id]->SetNewGuid(m_mapMgr->GenerateGameobjectGuid());
		m_sotacontrolPointAuras[Id]->SetUInt32Value(OBJECT_FIELD_ENTRY, gi_aura->ID);
		m_sotacontrolPointAuras[Id]->SetUInt32Value(GAMEOBJECT_DISPLAYID, gi_aura->DisplayID);
		m_sotacontrolPointAuras[Id]->SetInfo(gi_aura);
		m_sotacontrolPointAuras[Id]->PushToWorld(m_mapMgr);
	}	
}

void StrandOfTheAncients::CaptureControlPoint(uint32 Id, uint32 Team)
{
	if(m_basesOwnedBy[Id] != -1)
	{
		// there is a very slim chance of this happening, 2 teams evnets could clash..
		// just in case...
		return;
	}

	// anticheat, not really necessary because this is a server method but anyway
	if(m_basesAssaultedBy[Id] != (int32)Team)
		return;

	
	m_basesLastOwnedBy[Id] = Team;

	m_flagIsVirgin[Id] = false;

	m_basesOwnedBy[Id] = Team;
	m_basesAssaultedBy[Id]=-1;

	if(m_spiritGuides[Id] != NULL)
	{
		RemoveSpiritGuide(m_spiritGuides[Id]);
		m_spiritGuides[Id]->Despawn(0,0);
	}

	// spawn the spirit guide for our faction
	m_spiritGuides[Id] = SpawnSpiritGuide(sotaRepop[Id][0], sotaRepop[Id][1], sotaRepop[Id][2], 0.0f, Team);
	AddSpiritGuide(m_spiritGuides[Id]);

	// send the chat message/sounds out
	PlaySoundToAll(Team ? SOUND_HORDE_SCORES : SOUND_ALLIANCE_SCORES);
	SendChatMessage(CHAT_MSG_SYSTEM, 0, "The %s has been captured by the %s!", ControlPointNames[Id], Team ? "Horde" : "Alliance");
	
	SpawnControlPoint(Id, Team ? SOTA_SPAWN_TYPE_HORDE_CONTROLLED : SOTA_SPAWN_TYPE_ALLIANCE_CONTROLLED);
	
	if(Team == ALLIANCE)
	{
		m_mapMgr->GetStateManager().UpdateWorldState(capturedStates[Id][HORDE], 0);
		m_mapMgr->GetStateManager().UpdateWorldState(capturedStates[Id][Team], 1);
	}
	else
	{
		m_mapMgr->GetStateManager().UpdateWorldState(capturedStates[Id][ALLIANCE], 0);
		m_mapMgr->GetStateManager().UpdateWorldState(capturedStates[Id][Team], 1);
	}
	
	if( Id == 0 )	// west
		Updateworkshop(Team, Id);
	else if( Id == 1)	// east
		Updateworkshop(Team, Id);
}

void StrandOfTheAncients::AssaultControlPoint(Player* pPlayer, uint32 Id)
{
#if defined(BG_ANTI_CHEAT) && !defined(_DEBUG)
	if(!m_started)
	{
		SendChatMessage(CHAT_MSG_BG_SYSTEM_NEUTRAL, pPlayer->GetGUID(), "%s has been removed from the game for cheating.", pPlayer->GetName());
		pPlayer->SoftDisconnect();
		return;
	}
#endif

	bool isVirgin = false;

	uint32 Team = pPlayer->m_bgTeam;
	uint32 Owner;

	if(m_basesOwnedBy[Id] != -1)
	{
		Owner = m_basesOwnedBy[Id];

		// set it to uncontrolled for now
		m_basesOwnedBy[Id] = -1;

		// this control point just got taken over by someone! oh noes!
		if( m_spiritGuides[Id] != NULL )
		{
			map<Creature*,set<uint32> >::iterator itr = m_resurrectMap.find(m_spiritGuides[Id]);
			if( itr != m_resurrectMap.end() )
			{
				for( set<uint32>::iterator it2 = itr->second.begin(); it2 != itr->second.end(); ++it2 )
				{
					Player* r_plr = m_mapMgr->GetPlayer( *it2 );
					if( r_plr != NULL && r_plr->isDead() )
					{
						HookHandleRepop( r_plr );
						QueueAtNearestSpiritGuide(r_plr, itr->first);
					}
				}
			}
			m_resurrectMap.erase( itr );
			m_spiritGuides[Id]->Despawn( 0, 0 );
			m_spiritGuides[Id] = NULLCREATURE;
		}

		// reset the world states
		m_mapMgr->GetStateManager().UpdateWorldState(capturedStates[Id][Owner], 0);

		// modify the resource update time period
		if(m_capturedBases[Owner]==0)
			this->event_RemoveEvents(EVENT_SOTA_RESOURCES_UPDATE_TEAM_0+Owner);
	}

	// nigga stole my flag!
	if(m_basesAssaultedBy[Id] != -1)
	{
		Owner = m_basesAssaultedBy[Id];

		// woah! vehicle hijack!
		m_basesAssaultedBy[Id] = Team;
		m_mapMgr->GetStateManager().UpdateWorldState(capturedStates[Id][Owner], 0);

		// make sure the event does not trigger
		sEventMgr.RemoveEvents(this, EVENT_SOTA_CAPTURE_CP_1 + Id);

		// no need to remove the spawn, SpawnControlPoint will do this.
	}

	m_basesAssaultedBy[Id] = Team;

	// guessed
	PlaySoundToAll(Team ? SOUND_ALLIANCE_CAPTURE : SOUND_HORDE_CAPTURE);

	// update the client's map with the new assaulting field
	m_mapMgr->GetStateManager().UpdateWorldState(capturedStates[Id][Team], 1);

	// create the 0 second event.
	sEventMgr.AddEvent(TO_SOTA(this), &StrandOfTheAncients::CaptureControlPoint, Id, Team, EVENT_SOTA_CAPTURE_CP_1 + Id, 0, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

	// update players info
	pPlayer->m_bgScore.MiscData[BG_SCORE_SOTA_BASE_ASSAULTED]++;
	UpdatePvPData();
}

void StrandOfTheAncients::HookOnAreaTrigger(Player* plr, uint32 id)
{
}

void StrandOfTheAncients::HookOnPlayerDeath(Player* plr)
{
	plr->m_bgScore.Deaths++;
	UpdatePvPData();
}
void StrandOfTheAncients::OnPlatformTeleport(Player* plr)
{
	LocationVector dest;
	uint32 closest_platform = 0;

	for (uint32 i = 0; i < 5; i++)
	{
		float distance = CalculateDistance(plr->GetPositionX(),
			plr->GetPositionY(), plr->GetPositionZ(),
			sotaTransporterDestination[i][0],
			sotaTransporterDestination[i][1],
			sotaTransporterDestination[i][2]);
		if (distance < 75)
		{
			closest_platform = i;
			break;
		}
	}
	dest.ChangeCoords(sotaTransporterDestination[closest_platform][0],
		sotaTransporterDestination[closest_platform][1],
		sotaTransporterDestination[closest_platform][2],
		sotaTransporterDestination[closest_platform][3]);

	plr->SafeTeleport(plr->GetMapId(), plr->GetInstanceID(), dest);
}

void StrandOfTheAncients::HookFlagDrop(Player* plr, GameObject* obj)
{
}

void StrandOfTheAncients::HookFlagStand(Player* plr, GameObject* obj)
{
}

// Rebuild the whole shit for the second round 
void StrandOfTheAncients::SOTARebuild(bool m_reliccaptured)
{
	if(m_ended)
		return;
		
	if(m_reliccaptured)		// Attackers won the round
	{
		if(Attackers == ALLIANCE)
			allywins++;
		else
			hordewins++;
	}
	else
	{
		if(Attackers == ALLIANCE)
			hordewins++;
		else
			allywins++;
	}
	
	if(BattleRound == 2 )	// Game Over
	{
		m_ended = true;
		EndGame();
	}
	else if(BattleRound == 1)	// Prepare second round
	{
		if(Attackers == ALLIANCE)
		{
			Attackers = HORDE;
		}
		else
		{
			Attackers = ALLIANCE;
		}
		
		PrepareRound();
		Respawn();
		sEventMgr.RemoveEvents(this, EVENT_SOTA_TIMER);
		PlaySoundToAll( 8212 );
		for(uint32 i = 0; i < 2; ++i)
		{
			for(set<Player*>::iterator itr = m_players[i].begin(); itr != m_players[i].end(); ++itr)
			{
				uint8 n = RandomUInt(2)-1;
				(*itr)->CastSpell((*itr),52459,true);
				if(Attackers == ALLIANCE)
				{	
					if((*itr)->GetTeam() == ALLIANCE)
						(*itr)->SafeTeleport((*itr)->GetMapId(),(*itr)->GetInstanceID(),SOTAStartLocations[n][0],SOTAStartLocations[n][1],SOTAStartLocations[n][2],0.0f);
					else
						(*itr)->SafeTeleport((*itr)->GetMapId(),(*itr)->GetInstanceID(),SOTAStartLocations[2][0],SOTAStartLocations[2][1],SOTAStartLocations[2][2],0.0f);
				}
				else
				{
					if((*itr)->GetTeam() == HORDE)
						(*itr)->SafeTeleport((*itr)->GetMapId(),(*itr)->GetInstanceID(),SOTAStartLocations[n][0],SOTAStartLocations[n][1],SOTAStartLocations[n][2],0.0f);
					else
						(*itr)->SafeTeleport((*itr)->GetMapId(),(*itr)->GetInstanceID(),SOTAStartLocations[2][0],SOTAStartLocations[2][1],SOTAStartLocations[2][2],0.0f);
				}
			}
		}
		BattleRound = 2;
		OnStart();
	}
}	

bool StrandOfTheAncients::HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell)
{
	if( pPlayer->m_bgFlagIneligible )
		return false;

	// burlex todo: find a cleaner way to do this that doesnt waste memory.
	if(pGo->bannerslot >= 0 && pGo->bannerslot < 3)
	{
		// TODO: anticheat here
		AssaultControlPoint(pPlayer,pGo->bannerslot);
		return true;
	}

	return true;
}

void StrandOfTheAncients::Respawn()
{
	for(uint32 y = 0; y < 4; y++)
	{
		if(y == 0)
		{
			for(uint32 z = 0; z < 9; z++)
				m_cannons[z]->Delete();
			for(uint32 z = 0; z < 2; z++)
			{
				/*m_boats[z]->Delete();*/
				m_npcs[z]->Delete();
			}
			for(uint32 s = 0; s < 8; s++)
			{
				m_demolisher[s]->Delete();
			}
			/*for(uint32 gcp = 0; gcp < 3; gcp++)
			{
				m_banners[gcp]->Delete();
			}*/
			for(uint32 i = 0; i < 3; ++i)
			{
				m_flagpole[i]->Delete();
			}
		}
	
		m_gates[y]->Delete();
		m_gateSigils[y]->Delete();
		m_gateTransporters[y]->Delete();
	}

	m_endgate->Delete();
	m_relic->Delete();
	
	// spawn the boats
	if(Attackers == ALLIANCE)
	{
		for(uint8 boats = 0; boats < 2; boats++)
		{
			m_boats[boats] = m_mapMgr->CreateGameObject(sotaBoatids[boats][0]);
			if(m_boats[boats] == NULL || !m_boats[boats]->CreateFromProto(sotaBoatids[boats][0], m_mapMgr->GetMapId() ,sotaBoats[boats][0], sotaBoats[boats][1], sotaBoats[boats][2], sotaBoats[boats][3], 0, 0, 0, 0))
			{
				Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
				abort();
				return;
			}
			m_boats[boats]->PushToWorld(m_mapMgr);
 		}
	}
	else
	{
		for(uint8 boats = 2; boats < 4; boats++)
		{
			m_boats[boats] = m_mapMgr->CreateGameObject(sotaBoatids[boats][0]);
			if(m_boats[boats] == NULL || !m_boats[boats]->CreateFromProto(sotaBoatids[boats][0], m_mapMgr->GetMapId() ,sotaBoats[boats][0], sotaBoats[boats][1], sotaBoats[boats][2], sotaBoats[boats][3], 0, 0, 0, 0))
			{
				Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
				abort();
				return;
			}
			m_boats[boats]->PushToWorld(m_mapMgr);
		}
	}
	
	//Spawn the Cannons
	for(uint8 x = 0; x < 10; x++)
	{
		m_cannons[x] = SpawnVehicle(SOTA_CANNON,m_cannonsLocations[x][0], m_cannonsLocations[x][1], m_cannonsLocations[x][2], m_cannonsLocations[x][3]);
		
		//Change Factions Of Cannons.
		if(Attackers == ALLIANCE)
			m_cannons[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_CREATURE_FACTION_1);
		else if(Attackers == HORDE)
			m_cannons[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_CREATURE_FACTION_2);
	}

	//Spawn Teleporters
	for(uint8 i = 0; i < 5; i++)
	{
		m_gateTransporters[i] = m_mapMgr->CreateGameObject(m_gatetransgos[0]);
		if(m_gateTransporters[i] == NULL || !m_gateTransporters[i]->CreateFromProto(m_gatetransgos[0], m_mapMgr->GetMapId() , m_gateTransportersLocations[i][0] ,m_gateTransportersLocations[i][1], m_gateTransportersLocations[i][2], m_gateTransportersLocations[i][3], 0, 0, 0, 0 ))
		{
			Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}

		// Faction Change Two.
		if(Attackers == ALLIANCE)
			m_gateTransporters[i]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);
		else
			m_gateTransporters[i]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);

		m_gateTransporters[i]->PushToWorld(m_mapMgr);
	}

	//Spawn Gates
	for(uint8 gates = 0; gates < 5; gates++)
	{
		m_gates[gates] = m_mapMgr->CreateGameObject(m_gatesLocations[gates][0]);
		if(m_gates[gates] == NULL || !m_gates[gates]->CreateFromProto(m_gatesLocations[gates][0], m_mapMgr->GetMapId() , m_gatesLocations[gates][1] ,m_gatesLocations[gates][2], m_gatesLocations[gates][3], m_gatesLocations[gates][4], 0, 0, 0, 0 ))
		{
			Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}

		if(Attackers == ALLIANCE)
		{
			m_gates[gates]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);
			m_gates[gates]->SetUInt32Value(GAMEOBJECT_FLAGS, SOTA_GAMEOBJECT_FLAG);
		}
		else
		{
			m_gates[gates]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);
			m_gates[gates]->SetUInt32Value(GAMEOBJECT_FLAGS, SOTA_GAMEOBJECT_FLAG);
		}
		m_gates[gates]->PushToWorld(m_mapMgr);
	}

	m_endgate = m_mapMgr->CreateGameObject(SOTA_GAMEOBJECT_GATE);
	if(m_endgate == NULL || !m_endgate->CreateFromProto(SOTA_GAMEOBJECT_GATE, m_mapMgr->GetMapId() ,878.555f, -108.989f, 119.835f, 0.0565f, 0, 0, 0, 0 ))
	{
		Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
		abort();
		return;
	}

	if(Attackers == ALLIANCE)
	{
		m_endgate->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);
		m_endgate->SetUInt32Value(GAMEOBJECT_FLAGS, SOTA_GAMEOBJECT_FLAG);
	}
	else
	{
		m_endgate->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);
		m_endgate->SetUInt32Value(GAMEOBJECT_FLAGS, SOTA_GAMEOBJECT_FLAG);
	}
	m_endgate->PushToWorld(m_mapMgr);

	//Spawn Gate Sigils
	for(uint8 sigils = 0; sigils < 5; sigils++)
	{
		m_gateSigils[sigils] = m_mapMgr->CreateGameObject(m_gateSigilsLocations[sigils][0]);
		if(m_gateSigils[sigils] == NULL || !m_gateSigils[sigils]->CreateFromProto(m_gateSigilsLocations[sigils][0], m_mapMgr->GetMapId() , m_gateSigilsLocations[sigils][1] , m_gateSigilsLocations[sigils][2] , m_gateSigilsLocations[sigils][3], m_gateSigilsLocations[sigils][4], 0, 0, 0, 0 ))
		{
			Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}
		m_gateSigils[sigils]->PushToWorld(m_mapMgr);
	}
	
	// Spawn Relic
	m_relic = m_mapMgr->CreateGameObject(SOTA_RELIC);
	if(m_relic == NULL || !m_relic->CreateFromProto(SOTA_RELIC, m_mapMgr->GetMapId() , 836.5f , -108.8f , 150.0f , 0.0f , 0 , 0 , 0 , 0))
	{
		Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
		abort();
		return;
	}
	// No suecide
	if(Attackers == ALLIANCE)
		m_relic->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);
	else
		m_relic->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);

	m_relic->PushToWorld(m_mapMgr);
	
	// Spawn demolishers
	for(uint8 dem = 0; dem < 8; dem++)
	{
		m_demolisher[dem] = SpawnVehicle(BG_DEMOLISHER, demolisherLocations[dem][0], demolisherLocations[dem][1], demolisherLocations[dem][2], demolisherLocations[dem][3]);

		if(Attackers == ALLIANCE)
			m_demolisher[dem]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_CREATURE_FACTION_2);
		else if(Attackers == HORDE)
			m_demolisher[dem]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_CREATURE_FACTION_1);
	}
	
	// Spawn spirit guids
	if(Attackers == ALLIANCE)
	{
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[4][0], sotaRepop[4][1], sotaRepop[4][2], sotaRepop[4][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[3][0], sotaRepop[3][1], sotaRepop[3][2], sotaRepop[3][3], 0));
		for(uint32 repop = 0; repop < 3; repop++)
		{
			AddSpiritGuide(m_spiritGuides[repop] = SpawnSpiritGuide(sotaRepop[repop][0], sotaRepop[repop][1], sotaRepop[repop][2], sotaRepop[repop][3], 0));
		}
	}
	else
	{
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[4][0], sotaRepop[4][1], sotaRepop[4][2], sotaRepop[4][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[3][0], sotaRepop[3][1], sotaRepop[3][2], sotaRepop[3][3], 1));
		for(uint32 repop = 0; repop < 3; repop++)
		{
			AddSpiritGuide(m_spiritGuides[repop] = SpawnSpiritGuide(sotaRepop[repop][0], sotaRepop[repop][1], sotaRepop[repop][2], sotaRepop[repop][3], 1));
		}
	}
	
	// Spawn controlpoints
	for(uint8 gcp = 0; gcp < 3; gcp++)
	{
		if(Attackers == ALLIANCE)
			SpawnControlPoint(m_banners[gcp], 0);
		else
			SpawnControlPoint(m_banners[gcp], 1);
	}

	// Flagpole
	for(uint8 i = 0; i < 3; ++i)
	{
		m_flagpole[i] = SpawnGameObject(SOTA_FLAGPOLE, ControlPointFlagpole[i][0], ControlPointFlagpole[i][1], ControlPointFlagpole[i][2], ControlPointFlagpole[i][3], 0, 35, 1.0f);
		m_flagpole[i]->PushToWorld(m_mapMgr);
	}
}

void StrandOfTheAncients::HookOnMount(Player* plr)
{
}

void StrandOfTheAncients::OnAddPlayer(Player* plr)
{
	if(!m_started)
		plr->CastSpell(plr, BG_PREPARATION, true);
}

void StrandOfTheAncients::OnRemovePlayer(Player* plr)
{
	plr->RemoveAura(BG_PREPARATION);
}

void StrandOfTheAncients::OnCreate()
{
	// spawn the boats
	if(Attackers == ALLIANCE)
	{
		for(uint8 boats = 0; boats < 2; boats++)
		{
			m_boats[boats] = m_mapMgr->CreateGameObject(sotaBoatids[boats][0]);
			if(m_boats[boats] == NULL || !m_boats[boats]->CreateFromProto(sotaBoatids[boats][0], m_mapMgr->GetMapId() ,sotaBoats[boats][0], sotaBoats[boats][1], sotaBoats[boats][2], sotaBoats[boats][3], 0, 0, 0, 0))
			{
				Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
				abort();
				return;
			}
			m_boats[boats]->PushToWorld(m_mapMgr);
 		}
	}
	else
	{
		for(uint8 boats = 2; boats < 4; boats++)
		{
			m_boats[boats] = m_mapMgr->CreateGameObject(sotaBoatids[boats][0]);
			if(m_boats[boats] == NULL || !m_boats[boats]->CreateFromProto(sotaBoatids[boats][0], m_mapMgr->GetMapId() ,sotaBoats[boats][0], sotaBoats[boats][1], sotaBoats[boats][2], sotaBoats[boats][3], 0, 0, 0, 0))
			{
				Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
				abort();
				return;
			}
			m_boats[boats]->PushToWorld(m_mapMgr);
		}
	}

	//Begin Gate Spawning.
	for(uint8 gates = 0; gates < 5; gates++)
	{
		m_gates[gates] = m_mapMgr->CreateGameObject(m_gatesLocations[gates][0]);
		if(m_gates[gates] == NULL || !m_gates[gates]->CreateFromProto(m_gatesLocations[gates][0], m_mapMgr->GetMapId() , m_gatesLocations[gates][1] ,m_gatesLocations[gates][2], m_gatesLocations[gates][3], m_gatesLocations[gates][4], 0 , 0 , 0 , 0 ))
		{
			Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}

		if(Attackers == ALLIANCE)
		{
			m_gates[gates]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);
			m_gates[gates]->SetUInt32Value(GAMEOBJECT_FLAGS, SOTA_GAMEOBJECT_FLAG);
		}
		else
		{
			m_gates[gates]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);
			m_gates[gates]->SetUInt32Value(GAMEOBJECT_FLAGS, SOTA_GAMEOBJECT_FLAG);
		}

		m_gates[gates]->PushToWorld(m_mapMgr);
	}

	m_endgate = m_mapMgr->CreateGameObject(SOTA_GAMEOBJECT_GATE);
	if(m_endgate == NULL || !m_endgate->CreateFromProto(SOTA_GAMEOBJECT_GATE, m_mapMgr->GetMapId() ,878.555f, -108.989f, 119.835f, 0.0565f, 0, 0, 0, 0))
	{
		Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
		abort();
		return;
	}
	if(Attackers == ALLIANCE)
	{
		m_endgate->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);
		m_endgate->SetUInt32Value(GAMEOBJECT_FLAGS, SOTA_GAMEOBJECT_FLAG);
	}
	else
	{
		m_endgate->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);
		m_endgate->SetUInt32Value(GAMEOBJECT_FLAGS, SOTA_GAMEOBJECT_FLAG);
	}
	
	m_endgate->PushToWorld(m_mapMgr);
	

	//Spawn Gate Sigils
	for(uint8 sigils = 0; sigils < 5; sigils++)
	{
		m_gateSigils[sigils] = m_mapMgr->CreateGameObject(m_gateSigilsLocations[sigils][0]);
		if(m_gateSigils[sigils] == NULL || !m_gateSigils[sigils]->CreateFromProto(m_gateSigilsLocations[sigils][0], m_mapMgr->GetMapId() , m_gateSigilsLocations[sigils][1] , m_gateSigilsLocations[sigils][2] , m_gateSigilsLocations[sigils][3], m_gateSigilsLocations[sigils][4], 0, 0, 0, 0 ))
		{
			Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}
		m_gateSigils[sigils]->PushToWorld(m_mapMgr);
	}

	//Spawn the Relic
	m_relic = m_mapMgr->CreateGameObject(SOTA_RELIC);
	if(m_relic == NULL || !m_relic->CreateFromProto(SOTA_RELIC, m_mapMgr->GetMapId() , 836.5f , -108.8f , 150.0f , 0.0f , 0 , 0 , 0 , 0))
	{
		Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects. Terminating.");
		abort();
		return;
	}
	// No suecide
	if(Attackers == ALLIANCE)
		m_relic->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);
	else
		m_relic->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);

	m_relic->PushToWorld(m_mapMgr);

	//Spawn the Cannons
	for(uint8 x = 0; x < 10; x++)
	{
		m_cannons[x] = SpawnVehicle(SOTA_CANNON,m_cannonsLocations[x][0], m_cannonsLocations[x][1], m_cannonsLocations[x][2], m_cannonsLocations[x][3]);

		//Change Factions Of Cannons.
		if(Attackers == ALLIANCE)
			m_cannons[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_CREATURE_FACTION_1);
		else if(Attackers == HORDE)
			m_cannons[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_CREATURE_FACTION_2);
	}
	
	//Spawn Teleporters
	for(uint8 i = 0; i < 5; i++)
	{
		m_gateTransporters[i] = m_mapMgr->CreateGameObject(m_gatetransgos[0]);
		if(m_gateTransporters[i] == NULL || !m_gateTransporters[i]->CreateFromProto(m_gatetransgos[0], m_mapMgr->GetMapId() , m_gateTransportersLocations[i][0] ,m_gateTransportersLocations[i][1], m_gateTransportersLocations[i][2], m_gateTransportersLocations[i][3], 0, 0, 0, 0 ))
		{
			Log.Notice("Battleground: ", "SOTA is being created and you are missing gameobjects.");
			abort();
			return;
		}

		// Faction Change Two. wrong faction ids.....
		if(Attackers == ALLIANCE)
			m_gateTransporters[i]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_1);
		else
			m_gateTransporters[i]->SetUInt32Value(GAMEOBJECT_FACTION, SOTA_GAMEOBJECT_FACTION_2);

		m_gateTransporters[i]->PushToWorld(m_mapMgr);
	}
	
	// Spawn npcs
	for(uint8 npcs = 0; npcs < 2; npcs++)
	{
		m_npcs[npcs] = SpawnCreature(demolisherSalesman[npcs][0], demolisherSalesman[npcs][1], demolisherSalesman[npcs][2], demolisherSalesman[npcs][3], demolisherSalesman[npcs][4]);
	}
	
	// Spawn demolishers
	for(uint8 dem = 0; dem < 8; dem++)
	{
		m_demolisher[dem] = SpawnVehicle(BG_DEMOLISHER, demolisherLocations[dem][0], demolisherLocations[dem][1], demolisherLocations[dem][2], demolisherLocations[dem][3]);

		if(Attackers == ALLIANCE)
			m_demolisher[dem]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_CREATURE_FACTION_2);
		else if(Attackers == HORDE)
			m_demolisher[dem]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_CREATURE_FACTION_1);
	}
	
	// Spawn spirit guids
	if(Attackers == ALLIANCE)
	{
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[4][0], sotaRepop[4][1], sotaRepop[4][2], sotaRepop[4][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[3][0], sotaRepop[3][1], sotaRepop[3][2], sotaRepop[3][3], 0));
		for(uint32 repop = 0; repop < 3; repop++)
		{
			AddSpiritGuide(m_spiritGuides[repop] = SpawnSpiritGuide(sotaRepop[repop][0], sotaRepop[repop][1], sotaRepop[repop][2], sotaRepop[repop][3], 0));
		}
	}
	else
	{
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[4][0], sotaRepop[4][1], sotaRepop[4][2], sotaRepop[4][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[3][0], sotaRepop[3][1], sotaRepop[3][2], sotaRepop[3][3], 1));
		for(uint32 repop = 0; repop < 3; repop++)
		{
			AddSpiritGuide(m_spiritGuides[repop] = SpawnSpiritGuide(sotaRepop[repop][0], sotaRepop[repop][1], sotaRepop[repop][2], sotaRepop[repop][3], 1));
		}
	}
	
	// Spawn graveyards controlpoints
	for(uint8 gcp = 0; gcp < 3; gcp++)
	{
		if(Attackers == ALLIANCE)
			SpawnControlPoint(m_banners[gcp], 0);
		else
			SpawnControlPoint(m_banners[gcp], 1);
	}

	// Flagpole
	for(uint8 i = 0; i < 3; ++i)
	{
		m_flagpole[i] = SpawnGameObject(SOTA_FLAGPOLE, ControlPointFlagpole[i][0], ControlPointFlagpole[i][1], ControlPointFlagpole[i][2], ControlPointFlagpole[i][3], 0, 35, 1.0f);
		m_flagpole[i]->PushToWorld(m_mapMgr);
	}
	
	WorldStateManager& sm = m_mapMgr->GetStateManager();
	sm.CreateWorldState( WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_HORDE_ATTACKER, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_CAPTURE_BAR_DISPLAY, 0 );
	sm.CreateWorldState( WORLDSTATE_SOTA_CAPTURE_BAR_VALUE, 0 );
	// gates
	sm.CreateWorldState( WORLDSTATE_SOTA_CHAMBER_OF_THE_ANCIENT_RELICS, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_BLUE_SAPPHIRE, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_GREEN_EMERALD, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_PURPLE_AMETHYST, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_RED_SUN, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_YELLOW_MOON, 1);
	
	sm.CreateWorldState( WORLDSTATE_SOTA_THE_FROSTBREAKER, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_THE_GRACEFUL_MAIDEN, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_EAST_GRAVEYARD_HORDE_CONTROLLED, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_SOUTH_GRAVEYARD_HORDE_CONTROLLED, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_WEST_GRAVEYARD_HORDE_CONTROLLED, 0);
	
	sm.CreateWorldState( WORLDSTATE_SOTA_THE_BLIGHTBRINGER, 0);	
	sm.CreateWorldState( WORLDSTATE_SOTA_THE_CASKET_CARRIER, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_SOUTH_GRAVEYARD_ALLIANCE_CONTROLLED, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_EAST_GRAVEYARD_ALLIANCE_CONTROLLED, 0);
	sm.CreateWorldState( WORLDSTATE_SOTA_WEST_GRAVEYARD_ALLIANCE_CONTROLLED, 0);
	
	PrepareRound();
	sm.CreateWorldState( WORLDSTATE_SOTA_BONUS_TIME, 0 );
	sm.CreateWorldState( WORLDSTATE_SOTA_TIMER_1, 0 );
	sm.CreateWorldState( WORLDSTATE_SOTA_TIMER_2, 0 );
	sm.CreateWorldState( WORLDSTATE_SOTA_TIMER_3, 0 );	
}

void StrandOfTheAncients::HookOnPlayerKill(Player* plr, Unit* pVictim)
{
	plr->m_bgScore.KillingBlows++;
	UpdatePvPData();
}

void StrandOfTheAncients::HookOnHK(Player* plr)
{
	plr->m_bgScore.HonorableKills++;
	UpdatePvPData();
}

LocationVector StrandOfTheAncients::GetStartingCoords(uint32 Team)
{
	uint32 sTeam;
	if(Team == Attackers)
		sTeam = RandomUInt(2)-1;
	else
		sTeam = 2;

	return LocationVector( SOTAStartLocations[sTeam][0], 
		SOTAStartLocations[sTeam][1],
		SOTAStartLocations[sTeam][2] );
}

void StrandOfTheAncients::OnStart()
{
	SetTime(ROUND_LENGTH, 0);
	PlaySoundToAll(SOUND_BATTLEGROUND_BEGIN);

	m_started = true;
	sEventMgr.AddEvent( this, &StrandOfTheAncients::TimeTick, EVENT_SOTA_TIMER, MSTIME_SECOND , 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
	for(uint32 i = 0; i < 2; ++i)
	{
		for(set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); ++itr)
		{
			(*itr)->RemoveAura(BG_PREPARATION);
		}
	}
}

void StrandOfTheAncients::HookGenerateLoot(Player* plr, Corpse* pCorpse)
{
	// add some money
	float gold = ((float(plr->getLevel()) / 2.5f)+1) * 100.0f;			// fix this later
	gold *= sWorld.getRate(RATE_MONEY);

	// set it
	pCorpse->m_loot.gold = float2int32(gold);
}

void StrandOfTheAncients::HookOnShadowSight() 
{
}

void StrandOfTheAncients::SetIsWeekend(bool isweekend) 
{
	m_isWeekend = isweekend;
}

void StrandOfTheAncients::HookOnUnitKill(Player* plr, Unit* pVictim)
{
	if(pVictim->IsPlayer())
		return;

	if(pVictim->GetEntry() == BG_DEMOLISHER)
	{
		plr->m_bgScore.MiscData[BG_SCORE_SOTA_DESTROY_DEMOLISHER]++;
		UpdatePvPData();
	}
	else return;
}

// Prometheusz: ToDo: finish it....
/*void StrandOfTheAncients::OnDestroyBuilding(GameObject* go);
{
	for(uint8 x = 0;x < 5; x++)
	{
		if(go->GetEntry() == m_gatesLocations[x][0])
		{
			plr->m_bgScore.MiscData[BG_SCORE_SOTA_DESTROY_GATE]++;
			UpdatePvPData();
			break;
		}
	}
	
	if(go->GetEntry() == SOTA_GAMEOBJECT_GATE)
	{
		plr->m_bgScore.MiscData[BG_SCORE_SOTA_DESTROY_GATE]++;
		UpdatePvPData();
	}
}*/

// Prometheusz: ToDo: Send warning to the defender team....
/*void StrandOfTheAncients::OnDamageBuilding(GameObject* go);
{
	uint8 x;
	for( x = 0 ;x < 5; x++)
	{
		if(go->GetEntry() == m_gatesLocations[x][0])
		{
			m_gatesname[x]
			break;
		}
	}
}*/

void StrandOfTheAncients::Updateworkshop(uint32 Team, uint32 Id)
{
	if(m_npcs[Id] != NULL)
		m_npcs[Id]->Despawn(0,0);
		
	uint8 faction;
	if(Team)
		faction = 2;
	else
		faction = 1;
		
	m_npcs[Id] = SpawnCreature(demolisherSalesman[Id][0], demolisherSalesman[Id][1], demolisherSalesman[Id][2], demolisherSalesman[Id][3], demolisherSalesman[Id][4]);
	m_npcs[Id]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, faction);
	m_npcs[Id]->PushToWorld(m_mapMgr);
	
	uint8 start,end;
	if(Id == 0)
	{
		start = 0;
		end = 2;
	}
	else
	{
		start = 2;
		end = 4;
	}
	
	for(uint8 i = start; i < end; i++)
	{
		m_wsveh[i] = SpawnVehicle(BG_DEMOLISHER, demolisherLocations[i][0], demolisherLocations[i][1], demolisherLocations[i][2], demolisherLocations[i][3]);
		m_wsveh[i]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, faction);
		m_wsveh[i]->PushToWorld(m_mapMgr);
	}
}

// For Gossip script
void StrandOfTheAncients::SpawnWSVehicle(uint32 Team, uint32 Id)
{
	uint32 faction;
	int x;
	x = -1;
	
	if(Team)
		faction = 2;
	else
		faction = 1;
		
	for(uint8 i = 0; i < 8; i++)
	{
		if(m_wsveh[i] == NULL)
		{
			x = i;
			break;
		}			
	}
	if(x > -1)
	{
		m_wsveh[x] = SpawnVehicle(BG_DEMOLISHER, demolisherLocations[Id][0], demolisherLocations[Id][1], demolisherLocations[Id][2], demolisherLocations[Id][3]);
		m_wsveh[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, faction);
		m_wsveh[x]->PushToWorld(m_mapMgr);
	}
	else return;
}

// Time Goes Through Seconds
void StrandOfTheAncients::SetTime(uint32 secs, uint32 WorldState)
{
	uint32 minutes = secs / TIME_MINUTE;
	uint32 seconds = secs % TIME_MINUTE;
	uint32 digits[3];
	digits[0] = minutes;
	digits[1] = seconds / 10;
	digits[2] = seconds % 10;

	//m_mapMgr->GetStateManager().UpdateWorldState( WorldState, 1 ); // This can be good.
	m_mapMgr->GetStateManager().UpdateWorldState( WORLDSTATE_SOTA_TIMER_1, digits[0] );
	m_mapMgr->GetStateManager().UpdateWorldState( WORLDSTATE_SOTA_TIMER_2, digits[1] );
	m_mapMgr->GetStateManager().UpdateWorldState( WORLDSTATE_SOTA_TIMER_3, digits[2] );
	SetRoundTime( secs );
}

void StrandOfTheAncients::PrepareRound()
{
	WorldStateManager& sm = m_mapMgr->GetStateManager();
	if(Attackers == ALLIANCE)
	{
		sm.UpdateWorldState( WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_HORDE_ATTACKER, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_THE_BLIGHTBRINGER, 1);	
		sm.UpdateWorldState( WORLDSTATE_SOTA_THE_CASKET_CARRIER, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_SOUTH_GRAVEYARD_ALLIANCE_CONTROLLED, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_EAST_GRAVEYARD_ALLIANCE_CONTROLLED, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_WEST_GRAVEYARD_ALLIANCE_CONTROLLED, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_THE_FROSTBREAKER, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_THE_GRACEFUL_MAIDEN, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_EAST_GRAVEYARD_HORDE_CONTROLLED, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_SOUTH_GRAVEYARD_HORDE_CONTROLLED, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_WEST_GRAVEYARD_HORDE_CONTROLLED, 0);
	}
	else
	{
		sm.UpdateWorldState( WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_HORDE_ATTACKER, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_THE_FROSTBREAKER, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_THE_GRACEFUL_MAIDEN, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_EAST_GRAVEYARD_HORDE_CONTROLLED, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_SOUTH_GRAVEYARD_HORDE_CONTROLLED, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_WEST_GRAVEYARD_HORDE_CONTROLLED, 1);
		sm.UpdateWorldState( WORLDSTATE_SOTA_THE_BLIGHTBRINGER, 0);	
		sm.UpdateWorldState( WORLDSTATE_SOTA_THE_CASKET_CARRIER, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_SOUTH_GRAVEYARD_ALLIANCE_CONTROLLED, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_EAST_GRAVEYARD_ALLIANCE_CONTROLLED, 0);
		sm.UpdateWorldState( WORLDSTATE_SOTA_WEST_GRAVEYARD_ALLIANCE_CONTROLLED, 0);
	}
};

void StrandOfTheAncients::TimeTick()
{
	SetTime(GetRoundTime() - 1, NULL);
	if(GetRoundTime() == 0)
	{
		bool captured = false;
		SOTARebuild(captured);
	}
};

void StrandOfTheAncients::EndGame()
{
	if(hordewins > allywins)
		m_losingteam = HORDE;
	else if(allywins > hordewins)
		m_losingteam = ALLIANCE;
	else if(allywins = hordewins)
		m_losingteam = 2;
	m_nextPvPUpdateTime = 0;

	sEventMgr.RemoveEvents(this);
	sEventMgr.AddEvent( (CBattleground*)this, &CBattleground::Close, EVENT_BATTLEGROUND_CLOSE, 120000, 1, 0);

	m_mainLock.Acquire();
	// Honor is added?
	SpellEntry * winner_spell = dbcSpell.LookupEntry(61160);
	SpellEntry * loser_spell = dbcSpell.LookupEntry(61159);
	for(uint8 i = 0; i < 2; ++i)
	{
		for(set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); ++itr)
		{
			(*itr)->Root();

			if( (*itr)->HasFlag(PLAYER_FLAGS, 0x2) )
				continue;

			if(m_losingteam = 2)
				(*itr)->CastSpell((*itr), loser_spell, true);
			else if(i == m_losingteam)
				(*itr)->CastSpell((*itr), loser_spell, true);
			else
			{
				(*itr)->CastSpell((*itr), winner_spell, true);
			}
		}
	}

	UpdatePvPData();
	m_mainLock.Release();
};
