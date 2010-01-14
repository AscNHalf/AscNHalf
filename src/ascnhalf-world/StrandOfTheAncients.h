/* AscNHalf */

#ifndef _SOTA_H
#define _SOTA_H

static const float SOTAStartLocations[3][3] = {
	{ 1601.004395f, -105.182663f, 8.873691f },	//attackers
	{ 1607.7517f, 48.6505f, 7.5799f }, 			//attackers
	{ 1209.1f, -65.562363f, 70.2f },			//defenders
};

enum SOTA_SPAWNTYPES
{
	SOTA_SPAWN_TYPE_ALLIANCE_CONTROLLED		= 0,
	SOTA_SPAWN_TYPE_HORDE_CONTROLLED		= 1,
};

enum SOTA_GAMEOBJECTS
{
	SOTA_GAMEOBJECT_GATE					= 192549
};

enum SOTA_FACTION
{
	SOTA_CREATURE_FACTION_1						= 1,		// alliance
	SOTA_CREATURE_FACTION_2						= 2,		// horde
	SOTA_GAMEOBJECT_FACTION_1					= 1,		// alliance
	SOTA_GAMEOBJECT_FACTION_2					= 2,		// horde
	SOTA_GAMEOBJECT_FACTION_3					= 35,		// netural
	SOTA_GAMEOBJECT_FLAG						= 6553632
};

#define SOTA_CANNON					27894
#define SOTA_RELIC					192829
#define BG_DEMOLISHER				28781
#define SOTA_FLAGPOLE				191311

class SERVER_DECL StrandOfTheAncients : public CBattleground
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
	void AssaultControlPoint(Player* pPlayer, uint32 Id);
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
	//void SpawnSalesman(uint8 Id);
	void SetTime(uint32 secs, uint32 WorldState);
	uint32 GetRoundTime(){ return RoundTime; };
	void SetRoundTime(uint32 secs){ RoundTime = secs; };
	void TimeTick();
	void PrepareRound();
	void EndGame();

protected:
	uint32 Attackers; // 1 - horde / 0 - alliance
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
	GameObject* m_flagpole[3];
	uint8 hordewins;
	uint8 allywins;
	int32 m_basesOwnedBy[3];
	int32 m_basesLastOwnedBy[3];
	uint32 m_capturedBases[2];
	int32 m_basesAssaultedBy[3];
	bool m_flagIsVirgin[3];

public:
	GameObject* m_sotacontrolPoint[3];
	GameObject* m_sotacontrolPointAuras[3];

private:

};

#endif		// _SOTA_H
