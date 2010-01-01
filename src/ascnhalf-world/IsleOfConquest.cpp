/* AscNHalf */

#include "StdAfx.h"

IsleOfConquest::IsleOfConquest(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t) : CBattleground(mgr,id,lgroup,t)
{
/*    m_StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_BG_WS_START_TWO_MINUTES;
    m_StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_BG_WS_START_ONE_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_BG_WS_START_HALF_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_BG_WS_HAS_BEGUN;*/
}

IsleOfConquest::~IsleOfConquest()
{
	delete m_mapMgr;
}

void IsleOfConquest::Init()
{
	CBattleground::Init();
}

bool IsleOfConquest::HookHandleRepop(Player* plr)
{
	return false;
}

void IsleOfConquest::HookOnAreaTrigger(Player* plr, uint32 id)
{
}

void IsleOfConquest::HookOnPlayerDeath(Player* plr)
{
 plr->m_bgScore.Deaths++;
 UpdatePvPData();
}

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

LocationVector IsleOfConquest::GetStartingCoords(uint32 Team)
{
	return LocationVector( SOTAStartLocations[Team][0], 
		SOTAStartLocations[Team][1],
		SOTAStartLocations[Team][2] );
}

void IsleOfConquest::OnStart()
{

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

void IsleOfConquest::SetTime(uint32 secs, uint32 WorldState)
{
}

void IsleOfConquest::PrepareRound()
{

};

void IsleOfConquest::TimeTick()
{

};