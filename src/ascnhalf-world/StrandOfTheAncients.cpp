/* AscNHalf */


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
	{190763},
	{191575},		// the same as the first one, but not needed
	{192819},		// the same as the first one, but not needed
};

const float m_gatesLocations[5][5] = {
	{190722, 1411.57f, 108.163f, 28.692f, 5.441f},
	{190727, 1055.452f, -108.1f, 82.134f, 0.034f},
	{190724, 1431.3413f, -219.437f, 30.893f, 0.9736f},
	{190726, 1227.667f, -212.555f, 55.372f, 0.5023f},
	{190723, 1214.681f, 81.21f,53.413f, 5.745f},
};

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
	{ 962.52f, -184.76f, 91.47f, 0.9f },	
	{ 1446.87f, -54.35f, 5.88f, 0.25f },	// Attackers
	{ 1347.20f, -161.15f, 31.24f, 2.56f },	// east graveyard
	{ 1316.39f, 11.36f, 31.19f, 2.91f },	// west graveyard
	{ 1221.38f, -69.61f, 70.08f, 3.16f },	// south graveyard
	
};

const float sotaBoatids[4][4] = {	/*[boatids][captinids(on boats)] */
	{193183, 32660},	// The Blightbringer, Dread Captain
	{193185, 32657},	// The Frostbreaker, Privateer Stonemantle
	{193184, 32659},	// The Coffin Carrier, Dread Captain Winge
	{193182, 32658},	// The Graceful Maiden, Privateer Zierhut
};

const float sotaBoats[2][4] = {
	{ 1623.34f, 37.0f, 1.0f, 3.65f },
	{ 2439.4f, 845.38f, 1.0f, 3.35f },
	/*{ 1623.34f, 37.0f, 1.0f, 3.65f },
	{ 2439.4f, 845.38f, 1.0f, 3.35f },*/
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
	{29260, 1355.71f, -320.68f, 36.83f, 2.01f},		// Rigger Sparkligh
	{29262, 1367.82f, 220.55f, 37.06f, 4.45f},		// Gorgril Rigspark
};

const float demolisherLocations[4][4] = {
	{1327.34f, -257.86f, 32.61f, 0.26f},
	{1318.58f, 181.75f, 32.07f, 5.69f},
	{1564.84f, 112.20f, 2.90f, 3.59f},
	{1569.93f, -168.21, 5.46f, 3.40f},
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

	// spawn the boats
	/*for(uint32 boats = 0; boats < 2; boats++)
	{
		m_boats[boats] = m_mapMgr->CreateGameObject(sotaBoatids[boats][0]);
		if(m_boats[boats] == NULL || !m_boats[boats]->CreateFromProto(sotaBoatids[boats][0], m_mapMgr->GetMapId() ,sotaBoats[boats][0], sotaBoats[boats][1], sotaBoats[boats][2], sotaBoats[boats][3], 0, 0, 0, 0))
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}
		m_boats[boats]->PushToWorld(m_mapMgr);

	}*/		// removed because boats arent working well
	
	//Begin Gate Spawning.
	for(uint32 gates = 0; gates < 5; gates++)
	{
		m_gates[gates] = m_mapMgr->CreateGameObject(m_gatesLocations[gates][0]);
		if(m_gates[gates] == NULL || !m_gates[gates]->CreateFromProto(m_gatesLocations[gates][0], m_mapMgr->GetMapId() , m_gatesLocations[gates][1] ,m_gatesLocations[gates][2], m_gatesLocations[gates][3], m_gatesLocations[gates][4], 0 , 0 , 0 , 0 ))
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
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
		Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
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
	for(uint32 sigils = 0; sigils < 5; sigils++)
	{
		m_gateSigils[sigils] = m_mapMgr->CreateGameObject(m_gateSigilsLocations[sigils][0]);
		if(m_gateSigils[sigils] == NULL || !m_gateSigils[sigils]->CreateFromProto(m_gateSigilsLocations[sigils][0], m_mapMgr->GetMapId() , m_gateSigilsLocations[sigils][1] , m_gateSigilsLocations[sigils][2] , m_gateSigilsLocations[sigils][3], m_gateSigilsLocations[sigils][4], 0, 0, 0, 0 ))
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}
		m_gateSigils[sigils]->PushToWorld(m_mapMgr);
	}

	//Spawn the Relic
	m_relic = m_mapMgr->CreateGameObject(SOTA_RELIC);
	if(m_relic == NULL || !m_relic->CreateFromProto(SOTA_RELIC, m_mapMgr->GetMapId() , 836.5f , -108.8f , 150.0f , 0.0f , 0 , 0 , 0 , 0))
	{
		Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
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
	for(uint32 x = 0; x < 10; x++)
	{
		m_cannons[x] = SpawnCreature(SOTA_CANNON,m_cannonsLocations[x][0], m_cannonsLocations[x][1], m_cannonsLocations[x][2], m_cannonsLocations[x][3]);
		
		//Change Factions Of Cannons.
		if(Attackers == ALLIANCE)
			m_cannons[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_GAMEOBJECT_FACTION_1);
		else if(Attackers == HORDE)
			m_cannons[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_GAMEOBJECT_FACTION_2);
	}
	
	//Spawn Teleporters
	for(uint32 i = 0; i < 5; i++)
	{
		m_gateTransporters[i] = m_mapMgr->CreateGameObject(m_gatetransgos[0]);
		if(m_gateTransporters[i] == NULL || !m_gateTransporters[i]->CreateFromProto(m_gatetransgos[0], m_mapMgr->GetMapId() , m_gateTransportersLocations[i][0] ,m_gateTransportersLocations[i][1], m_gateTransportersLocations[i][2], m_gateTransportersLocations[i][3], 0, 0, 0, 0 ))
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
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
	for(uint32 npcs = 0; npcs < 2; npcs++)
	{
		m_npcs[npcs] = SpawnCreature(demolisherSalesman[npcs][0], demolisherSalesman[npcs][1], demolisherSalesman[npcs][2], demolisherSalesman[npcs][3], demolisherSalesman[npcs][4]);
	}
	
	// Spawn demolishers
	for(uint32 dem =0; dem < 4; dem++)
	{
		m_demolisher[dem] = SpawnCreature(BG_DEMOLISHER, demolisherLocations[dem][0], demolisherLocations[dem][1], demolisherLocations[dem][2], demolisherLocations[dem][3]);
	}
	
	// Spawn spirit guids
	if(Attackers == ALLIANCE)
	{
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[1][0], sotaRepop[1][1], sotaRepop[1][2], sotaRepop[1][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[0][0], sotaRepop[0][1], sotaRepop[0][2], sotaRepop[0][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[2][0], sotaRepop[2][1], sotaRepop[2][2], sotaRepop[2][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[3][0], sotaRepop[3][1], sotaRepop[3][2], sotaRepop[3][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[4][0], sotaRepop[4][1], sotaRepop[4][2], sotaRepop[4][3], 0));
	}
	else
	{
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[1][0], sotaRepop[1][1], sotaRepop[1][2], sotaRepop[1][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[0][0], sotaRepop[0][1], sotaRepop[0][2], sotaRepop[0][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[2][0], sotaRepop[2][1], sotaRepop[2][2], sotaRepop[2][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[3][0], sotaRepop[3][1], sotaRepop[3][2], sotaRepop[3][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[4][0], sotaRepop[4][1], sotaRepop[4][2], sotaRepop[4][3], 1));
	}
}

StrandOfTheAncients::~StrandOfTheAncients()
{
	delete m_mapMgr;
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

bool StrandOfTheAncients::HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell)
{	
	Respawn();
	OnStart();
	if(BattleRound == 1)
	{
		sEventMgr.RemoveEvents(this, EVENT_SOTA_TIMER);
		PlaySoundToAll( 8212 );
		pPlayer->CastSpell(pPlayer,52459,true);
		if(pPlayer->GetTeam() == Attackers)
		{
			pPlayer->SetTeam(1);
			pPlayer->SafeTeleport(pPlayer->GetMapId(),pPlayer->GetInstanceID(),SOTAStartLocations[0][0],SOTAStartLocations[0][1],SOTAStartLocations[0][2],0.0f);
		}
		else
		{
			pPlayer->SetTeam(0);
			pPlayer->SafeTeleport(pPlayer->GetMapId(),pPlayer->GetInstanceID(),SOTAStartLocations[1][0],SOTAStartLocations[1][1],SOTAStartLocations[1][2],0.0f);
		}
		if(Attackers == ALLIANCE)
		{
			m_mapMgr->GetStateManager().UpdateWorldState(WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 1 );
			m_mapMgr->GetStateManager().UpdateWorldState(WORLDSTATE_SOTA_ALLIANCE_DEFENDER, 0 );
			hordewins++;
			Attackers = HORDE;
		}
		else if(Attackers == HORDE)
		{
			m_mapMgr->GetStateManager().UpdateWorldState(WORLDSTATE_SOTA_ALLIANCE_DEFENDER, 1 );
			m_mapMgr->GetStateManager().UpdateWorldState(WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 0 );
			allywins++;
			Attackers = ALLIANCE;
		}
		BattleRound = 2;
		OnStart();
	}
	else if(BattleRound == 2)
	{
		EndGame();
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
		}
	
		m_gates[y]->Delete();
		m_gateSigils[y]->Delete();
		m_gateTransporters[y]->Delete();
		m_demolisher[y]->Delete();
	}

	m_endgate->Delete();
	
	// spawn the boats
	/*for(uint32 boats = 0; boats < 2; boats++)
	{
		m_boats[boats] = m_mapMgr->CreateGameObject(sotaBoatids[boats][0]);
		if(m_boats[boats] == NULL || !m_boats[boats]->CreateFromProto(sotaBoatids[boats][0], m_mapMgr->GetMapId() ,sotaBoats[boats][0], sotaBoats[boats][1], sotaBoats[boats][2], sotaBoats[boats][3], 0, 0, 0, 0))
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}
		m_boats[boats]->PushToWorld(m_mapMgr);

	}*/ // removed because boats arent working well
	
	//Spawn the Cannons
	for(uint32 x = 0; x < 10; x++)
	{
		m_cannons[x] = SpawnCreature(SOTA_CANNON,m_cannonsLocations[x][0], m_cannonsLocations[x][1], m_cannonsLocations[x][2], m_cannonsLocations[x][3]);
		
		//Change Factions Of Cannons.
		if(Attackers == ALLIANCE)
			m_cannons[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_GAMEOBJECT_FACTION_1);
		else if(Attackers == HORDE)
			m_cannons[x]->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, SOTA_GAMEOBJECT_FACTION_2);
	}

	//Spawn Teleporters
	for(uint32 i = 0; i < 5; i++)
	{
		m_gateTransporters[i] = m_mapMgr->CreateGameObject(m_gatetransgos[0]);
		if(m_gateTransporters[i] == NULL || !m_gateTransporters[i]->CreateFromProto(m_gatetransgos[0], m_mapMgr->GetMapId() , m_gateTransportersLocations[i][0] ,m_gateTransportersLocations[i][1], m_gateTransportersLocations[i][2], m_gateTransportersLocations[i][3], 0, 0, 0, 0 ))
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
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
	for(uint32 gates = 0; gates < 5; gates++)
	{
		m_gates[gates] = m_mapMgr->CreateGameObject(m_gatesLocations[gates][0]);
		if(m_gates[gates] == NULL || !m_gates[gates]->CreateFromProto(m_gatesLocations[gates][0], m_mapMgr->GetMapId() , m_gatesLocations[gates][1] ,m_gatesLocations[gates][2], m_gatesLocations[gates][3], m_gatesLocations[gates][4], 0, 0, 0, 0 ))
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
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
	
	// Spawn npcs
	for(uint32 npcs = 0; npcs < 2; npcs++)
	{
		m_npcs[npcs] = SpawnCreature(demolisherSalesman[npcs][0], demolisherSalesman[npcs][1], demolisherSalesman[npcs][2], demolisherSalesman[npcs][3], demolisherSalesman[npcs][4]);
	}

	m_endgate = m_mapMgr->CreateGameObject(SOTA_GAMEOBJECT_GATE);
	if(m_endgate == NULL || !m_endgate->CreateFromProto(SOTA_GAMEOBJECT_GATE, m_mapMgr->GetMapId() ,878.555f, -108.989f, 119.835f, 0.0565f, 0, 0, 0, 0 ))
	{
		Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
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
	for(uint32 sigils = 0; sigils < 5; sigils++)
	{
		m_gateSigils[sigils] = m_mapMgr->CreateGameObject(m_gateSigilsLocations[sigils][0]);
		if(m_gateSigils[sigils] == NULL || !m_gateSigils[sigils]->CreateFromProto(m_gateSigilsLocations[sigils][0], m_mapMgr->GetMapId() , m_gateSigilsLocations[sigils][1] , m_gateSigilsLocations[sigils][2] , m_gateSigilsLocations[sigils][3], m_gateSigilsLocations[sigils][4], 0, 0, 0, 0 ))
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_ERROR, "SOTA is being created and you are missing gameobjects. Terminating.");
			abort();
			return;
		}
		m_gateSigils[sigils]->PushToWorld(m_mapMgr);
	}
	
	// Spawn demolishers
	for(uint32 dem =0; dem < 4; dem++)
	{
		m_demolisher[dem] = SpawnCreature(BG_DEMOLISHER, demolisherLocations[dem][0], demolisherLocations[dem][1], demolisherLocations[dem][2], demolisherLocations[dem][3]);
	}
	
	// Spawn spirit guids
	if(Attackers == ALLIANCE)
	{
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[1][0], sotaRepop[1][1], sotaRepop[1][2], sotaRepop[1][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[0][0], sotaRepop[0][1], sotaRepop[0][2], sotaRepop[0][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[2][0], sotaRepop[2][1], sotaRepop[2][2], sotaRepop[2][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[3][0], sotaRepop[3][1], sotaRepop[3][2], sotaRepop[3][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[4][0], sotaRepop[4][1], sotaRepop[4][2], sotaRepop[4][3], 0));
	}
	else
	{
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[1][0], sotaRepop[1][1], sotaRepop[1][2], sotaRepop[1][3], 0));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[0][0], sotaRepop[0][1], sotaRepop[0][2], sotaRepop[0][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[2][0], sotaRepop[2][1], sotaRepop[2][2], sotaRepop[2][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[3][0], sotaRepop[3][1], sotaRepop[3][2], sotaRepop[3][3], 1));
		AddSpiritGuide(SpawnSpiritGuide(sotaRepop[4][0], sotaRepop[4][1], sotaRepop[4][2], sotaRepop[4][3], 1));
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
	WorldStateManager& sm = m_mapMgr->GetStateManager();
	sm.CreateWorldState( WORLDSTATE_SOTA_CAPTURE_BAR_DISPLAY, 0 );
	sm.CreateWorldState( WORLDSTATE_SOTA_CAPTURE_BAR_VALUE, 0 );
	// gates
	sm.CreateWorldState( WORLDSTATE_SOTA_CHAMBER_OF_THE_ANCIENT_RELICS, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_BLUE_SAPPHIRE, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_GREEN_EMERALD, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_PURPLE_AMETHYST, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_RED_SUN, 1);
	sm.CreateWorldState( WORLDSTATE_SOTA_GATES_OF_THE_YELLOW_MOON, 1);
	if(Attackers == ALLIANCE)
	{
		// boats
		sm.CreateWorldState( WORLDSTATE_SOTA_THE_BLIGHTBRINGER, 1);	
		sm.CreateWorldState( WORLDSTATE_SOTA_THE_CASKET_CARRIER, 1);
		// graveyards
		sm.CreateWorldState( WORLDSTATE_SOTA_SOUTH_GRAVEYARD_ALLIANCE_CONTROLLED, 1);
		sm.CreateWorldState( WORLDSTATE_SOTA_EAST_GRAVEYARD_ALLIANCE_CONTROLLED, 1);
		sm.CreateWorldState( WORLDSTATE_SOTA_WEST_GRAVEYARD_ALLIANCE_CONTROLLED, 1);
	}
	else
	{
		// boats
		sm.CreateWorldState( WORLDSTATE_SOTA_THE_FROSTBREAKER, 1);
		sm.CreateWorldState( WORLDSTATE_SOTA_THE_GRACEFUL_MAIDEN, 1);
		// graveyards
		sm.CreateWorldState( WORLDSTATE_SOTA_EAST_GRAVEYARD_HORDE_CONTROLLED, 1);
		sm.CreateWorldState( WORLDSTATE_SOTA_SOUTH_GRAVEYARD_HORDE_CONTROLLED, 1);
		sm.CreateWorldState( WORLDSTATE_SOTA_WEST_GRAVEYARD_HORDE_CONTROLLED, 1);
	}
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
	uint32 sTeam = ( Team == Attackers ? 1 : 0 );
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
}

void StrandOfTheAncients::HookGenerateLoot(Player* plr, Corpse* pCorpse)
{
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

// Prometheusz: ToDo: finish it...., and add the graveyard faction changes
/*void StrandOfTheAncients::HookOnGobjectDestroy(Player* plr, Gameobject* pGO)
{
	for(uint32 x = 0;x < 5; x++)
	{
		if(pGO->GetEntry() == m_gatesLocations[x][0])
		{
			plr->m_bgScore.MiscData[BG_SCORE_SOTA_DESTROY_GATE]++;
			UpdatePvPData();
		}
	}
	
	if(pGO->GetEntry() == SOTA_GAMEOBJECT_GATE)
	{
		plr->m_bgScore.MiscData[BG_SCORE_SOTA_DESTROY_GATE]++;
		UpdatePvPData();
	}
}*/

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
	if(Attackers == ALLIANCE)
	{
		m_mapMgr->GetStateManager().CreateWorldState( WORLDSTATE_SOTA_ALLIANCE_DEFENDER, 1 );
		m_mapMgr->GetStateManager().CreateWorldState( WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 0 );
	}
	else if(Attackers == HORDE)
	{
		m_mapMgr->GetStateManager().CreateWorldState( WORLDSTATE_SOTA_ALLIANCE_DEFENDER, 0 );
		m_mapMgr->GetStateManager().CreateWorldState( WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 1 );
	}
	else
	{
		Attackers = RandomUInt(2)-1;
		PrepareRound();
	}
};

void StrandOfTheAncients::TimeTick()
{
	SetTime(GetRoundTime() - 1, NULL);
	if(GetRoundTime() == 0)
	{
		sEventMgr.RemoveEvents(this, EVENT_SOTA_TIMER);
		if(BattleRound == 1)
		{
			for(uint32 i = 0; i < 2; ++i)
			{
				for(std::set<Player*>::iterator itr = m_players[i].begin(); itr != m_players[i].end(); ++itr)
				{
					//Player* pPlayer;
					
					PlaySoundToAll( 8212 );
					(*itr)->CastSpell((*itr), 52459, true);
					if((*itr)->GetTeam() == Attackers)
					{
						(*itr)->SetTeam(1);
						(*itr)->SafeTeleport((*itr)->GetMapId(),(*itr)->GetInstanceID(),SOTAStartLocations[0][0],SOTAStartLocations[0][1],SOTAStartLocations[0][2],0.0f);
					}
					else
					{
						(*itr)->SetTeam(0);
						(*itr)->SafeTeleport((*itr)->GetMapId(),(*itr)->GetInstanceID(),SOTAStartLocations[1][0],SOTAStartLocations[1][1],SOTAStartLocations[1][2],0.0f);
					}
					Respawn();
					OnStart();
					if(Attackers == ALLIANCE)
					{
						m_mapMgr->GetStateManager().UpdateWorldState(WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 1 );
						m_mapMgr->GetStateManager().UpdateWorldState(WORLDSTATE_SOTA_ALLIANCE_DEFENDER, 0 );
						Attackers = HORDE;
					}
					else if(Attackers == HORDE)
					{
						m_mapMgr->GetStateManager().UpdateWorldState(WORLDSTATE_SOTA_ALLIANCE_DEFENDER, 1 );
						m_mapMgr->GetStateManager().UpdateWorldState(WORLDSTATE_SOTA_ALLIANCE_ATTACKER, 0 );
						Attackers = ALLIANCE;
					}
					BattleRound = 2;
					OnStart();
				}
			}
		}
		else if(BattleRound == 2)
		{
			EndGame();
		}
	}
};

void StrandOfTheAncients::EndGame()
{
	m_ended = true;
	if(hordewins > allywins)
		m_losingteam = HORDE;
	else if(allywins > hordewins)
		m_losingteam = ALLIANCE;
	else if(allywins = hordewins)
		m_losingteam = 2;
	m_nextPvPUpdateTime = 0;

	sEventMgr.RemoveEvents(this);
	sEventMgr.AddEvent( (CBattleground*)this, &CBattleground::Close, EVENT_BATTLEGROUND_CLOSE, 120000, 1,0);

	m_mainLock.Acquire();
	// Honor is added?
	SpellEntry * winner_spell = dbcSpell.LookupEntry(61160);
	SpellEntry * loser_spell = dbcSpell.LookupEntry(61159);
	for(uint32 i = 0; i < 2; ++i)
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
