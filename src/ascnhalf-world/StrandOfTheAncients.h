/* AscNHalf */

#ifndef _SOTA_H
#define _SOTA_H

static const float SOTAStartLocations[2][3] = {
	{ 1601.004395f, -105.182663f, 8.873691f }, //attackers
	{ 1209.1f, -65.562363f, 70.2f }, //defenders
};

enum SOTA_SPAWNTYPES
{
	SOTA_SPAWN_TYPE_ALLIANCE_CONTROLLED	= 3,
	SOTA_SPAWN_TYPE_HORDE_CONTROLLED		= 4,
};

enum SOTA_GAMEOBJECTS
{
	SOTA_GAMEOBJECT_GATE					= 192549
};

enum SOTA_FACTION
{
	SOTA_GAMEOBJECT_FACTION_1					= 1,		// alliance
	SOTA_GAMEOBJECT_FACTION_2					= 2,		// horde
	SOTA_GAMEOBJECT_FACTION_3					= 35,		// netural
	SOTA_GAMEOBJECT_FLAG						= 6553632
};

#define SOTA_CANNON					27894
#define SOTA_RELIC					192834
#define BG_DEMOLISHER				28781

class StrandOfTheAncients : public CBattleground
{
public:
	StrandOfTheAncients(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t);
	~StrandOfTheAncients();

	void HookOnPlayerDeath(Player* plr);
	void HookFlagDrop(Player* plr, GameObject* obj);
	void HookFlagStand(Player* plr, GameObject* obj);
	void HookOnMount(Player* plr);
	void HookOnAreaTrigger(Player* plr, uint32 id);
	bool HookHandleRepop(Player* plr);
	void OnAddPlayer(Player* plr);
	void OnRemovePlayer(Player* plr);
	void OnCreate();
	void HookOnPlayerKill(Player* plr, Unit* pVictim);
	void HookOnHK(Player* plr);
	void HookOnShadowSight();
	void SpawnControlPoint(uint32 Id, uint32 Type);
	void CaptureControlPoint(uint32 Id, uint32 Team);
	void SOTARebuild(bool m_reliccaptured);
	void OnPlatformTeleport(Player* plr);
	void Respawn();
	LocationVector GetStartingCoords(uint32 Team);

	static CBattleground* Create(MapMgr* m, uint32 i, uint32 l, uint32 t) { return (new StrandOfTheAncients(m, i, l, t)); }

	const char * GetName() { return "Strand of the Ancients"; }
	void OnStart();

	bool SupportsPlayerLoot() { return true; }
	bool HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell);

	void HookGenerateLoot(Player* plr, Corpse* pCorpse);

	void SetIsWeekend(bool isweekend);
	void HookOnUnitKill(Player* plr, Unit* pVictim);
	/*void HookOnGobjectDestroy(Player* plr, Gameobject* pGO);*/
	void SetTime(uint32 secs, uint32 WorldState);
	uint32 GetRoundTime(){ return RoundTime; };
	void SetRoundTime(uint32 secs){ RoundTime = secs; };
	void TimeTick();
	void PrepareRound();
	void EndGame();
protected:
	uint32 Attackers; // 0 - horde / 1 - alliance
	uint32 BattleRound;
	uint32 RoundTime;
	Creature* m_cannons[10];
	Creature* m_npcs[2];
	Creature* m_demolisher[6];
	Creature* m_spiritGuides[3];
	GameObject* m_relic;
	GameObject* m_endgate;
	GameObject* m_gates[5];
	GameObject* m_gateSigils[5];
	GameObject* m_gateTransporters[5];
	GameObject* m_boats[2];
	GameObject* m_controlPoint[3];
	uint8 hordewins;
	uint8 allywins;
	int32 m_basesOwnedBy[3];
};

#endif		// _SOTA_H
