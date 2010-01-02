/* AscNHalf */

#include "StdAfx.h"


// gameobject faction
	static uint32 g_gameObjectFactions[IOC_NUM_CONTROL_POINTS] = {
	35,				// neutral
	2,				// alliance assault
	2,				// alliance	controlled
	1,				// horde assault
	1,				// horde controlled
	};

// Graveyard locations
	static float GraveyardLocations[IOC_NUM_CONTROL_POINTS][4] = {
		{ 0.0f, 0.0f, 0.0f },													// The Oil Derrick 
		{ 0.0f, 0.0f, 0.0f },													// The Cobalt Mine
		{ 0.0f, 0.0f, 0.0f },													// The Docks
		{ 0.0f, 0.0f, 0.0f },													// The Airship Hangar
		{ 0.0f, 0.0f, 0.0f },													// The Siege Workshop
	};

	
	static float NoBaseGYLocations[2][4] = {
		{ 278.28f, -883.65f, 49.92f, 1.57f },												// ALLIANCE
		{ 1301.30f, -839.38f, 48.91f, 1.48f },												// HORDE
	};

	static const char * ControlPointNames[IOC_NUM_CONTROL_POINTS] = {
		"Oil Derrick",																			// The Oil Derrick
		"Cobalt Mine",																			// The Cobalt Mine
		"Docks",																				// The Docks
		"Airship Hangar",																		// The Airship Hangar
		"Siege Workshop",																		// The Siege Workshop
	};
	
	static uint32 ControlPointGoIds[IOC_NUM_CONTROL_POINTS][AB_NUM_SPAWN_TYPES] = {
		  // NEUTRAL    ALLIANCE-ATTACK    HORDE-ATTACK    ALLIANCE-CONTROLLED    HORDE_CONTROLLED
		{ 180087,       180085,            180086,         180076,                180078 },			// The Oil Derrick	
		{ 180089,       180085,            180086,         180076,                180078 },			// The Cobalt Mine
		{ 180088,       180085,            180086,         180076,                180078 },			// The Docks
		{ 180091,       180085,            180086,         180076,                180078 },			// The Airship Hangar
		{ 180090,       180085,            180086,         180076,                180078 },			// The Siege Workshop
	};

	static float ControlPointCoordinates[IOC_NUM_CONTROL_POINTS][4] = {
		{ 1266.01f, -400.78f, 37.62f, 0.16f },						// The Oil Derrick
		{ 225.29f, -1189.01f, 8.05f, 0.86f },						// The Cobalt Mine
		{ 782.88f, -371.84f, 12.37f, 5.45f },						// The Docks
		{ 691.70f, -1121.04f, 133.70f, 2.147f },					// The Airship Hangar
		{ 751.29f, -818.18f, 7.40f, 0.75f },						// The Siege Workshop
	};

	
IsleOfConquest::IsleOfConquest(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t) : CBattleground(mgr,id,lgroup,t)
{

	m_playerCountPerTeam = 40;
	m_reinforcements[0] = IOC_NUM_REINFORCEMENTS;
	m_reinforcements[1] = IOC_NUM_REINFORCEMENTS;
	m_LiveCaptain[0] = true;
	m_LiveCaptain[1] = true;
	m_bonusHonor = HonorHandler::CalculateHonorPointsFormula(lgroup*10,lgroup*10);

	memset(m_nodes, 0, sizeof(m_nodes));

}

IsleOfConquest::~IsleOfConquest()
{

}

void IsleOfConquest::Init()
{
	CBattleground::Init();
}

bool IsleOfConquest::HookHandleRepop(Player* plr)
{
	/*uint32 x;*/
	float dist = 999999.0f;
	/*float dt;*/
	LocationVector dest_pos;
	if( plr->GetTeam() == 1 )
		dest_pos.ChangeCoords(NoBaseGYLocations[1][0], NoBaseGYLocations[1][1], NoBaseGYLocations[1][2], NoBaseGYLocations[1][3]);
	else
		dest_pos.ChangeCoords(NoBaseGYLocations[0][0], NoBaseGYLocations[0][1], NoBaseGYLocations[0][2], NoBaseGYLocations[0][3]);

	/*if(m_started)
	{
		for(x = 0; x < IOC_NUM_CONTROL_POINTS; ++x)
		{
			// skip non-graveyards
			if( !m_nodes[x]->m_template->m_isGraveyard )
				continue;

			// make sure they're owned by us
			if( ( plr->GetTeam() == 0 && m_nodes[x]->m_state == IOC_NODE_STATE_ALLIANCE_CONTROLLED ) ||
				( plr->GetTeam() == 1 && m_nodes[x]->m_state == IOC_NODE_STATE_HORDE_CONTROLLED ) )
			{
				dt = plr->GetPositionNC().Distance2DSq(m_nodes[x]->m_template->m_graveyardLocation.x, m_nodes[x]->m_template->m_graveyardLocation.y);
				if( dt < dist )
				{
					// new one
					dest_pos.ChangeCoords(m_nodes[x]->m_template->m_graveyardLocation.x, m_nodes[x]->m_template->m_graveyardLocation.y, m_nodes[x]->m_template->m_graveyardLocation.z);
					dist = dt;
				}
			}
		}
	}*/

	// port to it
	plr->SafeTeleport(plr->GetMapId(), plr->GetInstanceID(), dest_pos);
	return false;
}

void IsleOfConquest::HookOnAreaTrigger(Player* plr, uint32 id)
{
}

void IsleOfConquest::HookOnPlayerDeath(Player* plr)
{
 plr->m_bgScore.Deaths++;
 UpdatePvPData();
 RemoveReinforcements(plr->GetTeam(), IOC_POINTS_ON_KILL);
}
// we don't have flag in ioc
void IsleOfConquest::HookFlagDrop(Player* plr, GameObject* obj)
{
}

void IsleOfConquest::HookFlagStand(Player* plr, GameObject* obj)
{
}

bool IsleOfConquest::HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell)
{
	return true;
}

void IsleOfConquest::HookOnMount(Player* plr)
{
}

void IsleOfConquest::OnAddPlayer(Player* plr)
{
	if(!m_started)
		plr->CastSpell(plr, BG_PREPARATION, true);
}

void IsleOfConquest::OnRemovePlayer(Player* plr)
{
  plr->RemoveAura(BG_PREPARATION);
}

void IsleOfConquest::OnCreate()
{
	WorldStateManager &sm = m_mapMgr->GetStateManager();
	/*sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_SCORE_DISPLAY, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_SCORE_DISPLAY, 1);

	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_SCORE, 600);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_SCORE, 600);*/
	
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_EAST_GATE, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_1, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_2, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_3, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_WEST_GATE, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_FRONT_GATE, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_KEEP_ALLIANCE_CONTROLLED, 0);	
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_KEEP_HORDE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_KEEP_ALLIANCE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_KEEP_HORDE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_ALLIANCE_KEEP_NETURAL, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_KEEP_ALLIANCE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_KEEP_HORDE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_KEEP_ALLIANCE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_KEEP_HORDE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_KEEP_NETURAL, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_DOCKS_ALLIANCE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_DOCKS_HORDE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_DOCKS_ALLIANCE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_DOCKS_HORDE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_DOCKS_NETURAL, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_HANGAR_ALLIANCE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HANGAR_HORDE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HANGAR_ALLIANCE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HANGAR_HORDE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HANGAR_NETURAL, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_QUARRY_ALLIANCE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_QUARRY_HORDE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_QUARRY_ALLIANCE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_QUARRY_HORDE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_QUARRY_NETURAL, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_REFINERY_ALLIANCE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_REFINERY_HORDE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_REFINERY_ALLIANCE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_REFINERY_HORDE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_REFINERY_NETURAL, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_WORKSHOP_ALLIANCE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_WORKSHOP_HORDE_CONTROLLED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_WORKSHOP_ALLIANCE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_WORKSHOP_HORDE_ASSAULTED, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_WORKSHOP_NETURAL, 1);		
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_EAST_GATE, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_GATE_DESTROYED_1, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_GATE_DESTROYED_2, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_GATE_DESTROYED_3, 0);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_WEST_GATE, 1);
	sm.CreateWorldState(WORLDSTATE_IOC_HORDE_FRONT_GATE, 1);
	
	// generals/leaders!
	SpawnCreature(34924, 214.77f, -830.73f, 60.81f, 0.07f);	// High Commander Halford Wyrmbane (ALLIANCE)
	SpawnCreature(34922, 1296.57f, -765.78f, 69.98f, 6.22f);	// Overlord Agmar (not sure this is the good general) (HORDE)
}

void IsleOfConquest::HookOnPlayerKill(Player* plr, Unit* pVictim)
{
   if(pVictim->IsPlayer())
	{
		plr->m_bgScore.KillingBlows++;
		UpdatePvPData();
	}
}

void IsleOfConquest::HookOnHK(Player* plr)
{
    plr->m_bgScore.HonorableKills++;
	UpdatePvPData();
}

void IsleOfConquest::AddReinforcements(uint32 teamId, uint32 amt)
{
	WorldStateManager &sm = m_mapMgr->GetStateManager();
	if( ((int32)( m_reinforcements[teamId] + amt )) > IOC_NUM_REINFORCEMENTS )
		m_reinforcements[teamId] = IOC_NUM_REINFORCEMENTS;
	else
		m_reinforcements[teamId] += amt;

	/*sm.UpdateWorldState(WORLDSTATE_IOC_ALLIANCE_SCORE + teamId, m_reinforcements[teamId]);*/
}

void IsleOfConquest::RemoveReinforcements(uint32 teamId, uint32 amt)
{
	WorldStateManager &sm = m_mapMgr->GetStateManager();
	if( ((int32)( m_reinforcements[teamId] - amt )) < 0 )
		m_reinforcements[teamId] = 0;
	else
		m_reinforcements[teamId] -= amt;

	/*sm.UpdateWorldState(WORLDSTATE_IOC_ALLIANCE_SCORE + teamId, m_reinforcements[teamId]);*/

	// We've lost. :(
	/*if( m_reinforcements[teamId] == 0 )
	{
		Finish( teamId );
	}*/
}

LocationVector IsleOfConquest::GetStartingCoords(uint32 Team)
{
	if(Team)		// Horde
		return LocationVector(1264.06f, -736.73f, 48.91f, 3.07f);
	else			// Alliance
		return LocationVector(303.22f, -857.02f, 48.91f, 5.99f);
}

void IsleOfConquest::OnStart()
{
	for(uint32 i = 0; i < 2; ++i) {
		for(set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); ++itr) {
			(*itr)->RemoveAura(BG_PREPARATION);
		}
	}

	// open gates
	for(list< GameObject* >::iterator itr = m_gates.begin(); itr != m_gates.end(); ++itr)
	{
		(*itr)->SetUInt32Value(GAMEOBJECT_FLAGS, 64);
		(*itr)->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_STATE, 0);
	}

	/* correct? - burlex */
	PlaySoundToAll(SOUND_BATTLEGROUND_BEGIN);

	m_started = true;

	//sEventMgr.AddEvent(TO_ISLEOFCONQUEST(this), &IsleOfconquest::EventUpdateResources, EVENT_BATTLEGROUND_RESOURCEUPDATE, IOC_REINFORCEMENT_ADD_INTERVAL, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

}

void IsleOfConquest::HookGenerateLoot(Player* plr, Corpse* pCorpse)
{
	// add some money
	float gold = ((float(plr->getLevel()) / 2.5f)+1) * 100.0f;			// fix this later
	gold *= sWorld.getRate(RATE_MONEY);

	// set it
	pCorpse->m_loot.gold = float2int32(gold);
}

void IsleOfConquest::HookOnShadowSight() 
{
}

void IsleOfConquest::SetIsWeekend(bool isweekend) 
{
}

void IsleOfConquest::HookOnUnitKill(Player* plr, Unit* pVictim)
{
	if(pVictim->IsPlayer())
		return;

	WorldStateManager &sm = m_mapMgr->GetStateManager();

	if(pVictim->GetEntry() == 34924)	// High Commander Halford Wyrmbane 
	{
		Herald("The 7th Legion General is dead!");
		RemoveReinforcements( 0, IOC_NUM_REINFORCEMENTS );	// Horde Win
		GiveHonorToTeam(1, m_bonusHonor * 4);
	}
	else if(pVictim->GetEntry() == 34922)	// Overlord Agmar (not sure this is the right general)
	{
		Herald("The Scarshield Legion General is dead!");
		RemoveReinforcements( 1, IOC_NUM_REINFORCEMENTS );	// Alliance Win
		GiveHonorToTeam(0, m_bonusHonor * 4);
	}
}

void IsleOfConquest::Herald(const char *format, ...)
{
	char msgbuf[200];
	uint8 databuf[500];
	va_list ap;
	size_t msglen;
	StackPacket data(SMSG_MESSAGECHAT, databuf, 500);

	va_start(ap, format);
	vsnprintf(msgbuf, 100, format, ap);
	va_end(ap);
	msglen = strlen(msgbuf);

	data << uint8(CHAT_MSG_MONSTER_YELL);
	data << uint32(LANG_UNIVERSAL);
	data << uint64(0);
	data << uint32(0);			// new in 2.1.0
	data << uint32(7);			// Herald
	data << "Herald";			// Herald
	data << uint64(0);
	data << uint32(msglen+1);
	data << msgbuf;
	data << uint8(0x00);
	m_mapMgr->SendPacketToPlayers(ZONE_MASK_ALL, FACTION_MASK_ALL, &data);
}