/* AscNHalf */

#ifndef _IOC_H
#define _IOC_H

enum IOCControlPoints
{
	IOC_CONTROL_POINT_OILDERRICK				= 0,
	IOC_CONTROL_POINT_COBALTMINE				= 1,
	IOC_CONTROL_POINT_DOCKS						= 2,
	IOC_CONTROL_POINT_AIRSHIPHANGAR				= 3,
	IOC_CONTROL_POINT_SIEGEWORKSHOP				= 4,
	IOC_NUM_CONTROL_POINTS				= 5,
};

enum IOCNodeStates
{
	IOC_NODE_STATE_NEUTRAL_CONTROLLED		= 0,
	IOC_NODE_STATE_ALLIANCE_ASSAULTING		= 1,
	IOC_NODE_STATE_ALLIANCE_CONTROLLED		= 2,
	IOC_NODE_STATE_HORDE_ASSAULTING			= 3,
	IOC_NODE_STATE_HORDE_CONTROLLED			= 4,
	IOC_NODE_STATE_COUNT						= 5,
};

struct IOCLocation { float x; float y; float z; };
struct IOCSpawnLocation { float x; float y; float z; float o; };
struct IOCGameObject { uint32 id[IOC_NODE_STATE_COUNT]; float x; float y; float z; float o; float rot1; float rot2; };
struct IOCNodeTemplate
{
	const char *m_name;										// Stormpike Aid Station
	const bool m_isGraveyard;								// Is this a graveyard?
	const bool m_capturable;								// Is this capturable?
	const IOCLocation m_graveyardLocation;					// Revive location, also location of spirit guide
	const IOCGameObject m_flagLocation;						// Flag location (need to add GO id/properties here)
	const IOCGameObject m_auraLocation;						// Aura location
	const IOCGameObject m_glowLocation;						// Aura glow location
	const uint32 m_guardId[3];								// Horde/alliance guard ids
	const uint32 m_guardCount;								// Count of guards to spawn
	const uint32 m_bossId[3];								// Boss ID (e.g. Balinda), 0 = A, 1 = H, 2 = Neutral
	const IOCLocation *m_peonLocations;						// Used by mines.
	const IOCLocation m_bossLocation;						// Location of boss if there is one
	const uint32 m_initialSpawnId;							// Initial spawn (Bowmen) ID
	const uint32 m_worldStateFields[IOC_NODE_STATE_COUNT];	// State fields
	const uint32 m_defaultState;							// State of the node when battleground is spawned
};

class IsleOfConquest;
class IOCNode
{
	IsleOfConquest* m_bg;
	IOCNodeTemplate *m_template;

	// boss, changes ownership upon death?
	Creature* m_boss;

	// guards, need to be respawned when changes ownership
	vector<Creature*> m_guards;

	// peon locations, used in mines (todo)
	vector<Creature*> m_peonLocations;

	// control point (capturable)
	GameObject* m_flag;

	// aura (light-shiny stuff)
	GameObject* m_aura;
	GameObject* m_glow;

	// home NPc
	Creature* m_homeNPC;

	// destroyed flag (prevent all actions)
	bool m_destroyed;

	// state
	uint32 m_state;
	uint32 m_lastState;
	uint32 m_nodeId;

	// spirit guides
	Creature* m_spiritGuide;

public:
	friend class IsleOfConquest;

	// constructor
	IOCNode(IsleOfConquest* parent, IOCNodeTemplate *tmpl, uint32 node_id);
	~IOCNode();

	// initial spawn
	void Spawn();

	// assault
	void Assault(Player* plr);

	// capture event
	void Capture();

	// spawn guards
	void SpawnGuards(uint32 x);

	// state change
	void ChangeState(uint32 new_state);

	// spawn home buff guard
	void SpawnHomeGuard();

	uint32 GetState() { return m_state; }

	bool IsGraveyard() { return m_template->m_isGraveyard; }
};

class IsleOfConquest : public CBattleground
{
protected:
	list< GameObject* > m_gates;
	uint32 m_reinforcements[2];
	bool m_nearingVictory[2];
	IOCNode *m_nodes[IOC_NUM_CONTROL_POINTS];
	bool m_LiveCaptain[2];
	int m_bonusHonor;

public:
    IsleOfConquest(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t);
    ~IsleOfConquest();
	virtual void Init();

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
	void OnPlatformTeleport(Player* plr);
	void Respawn();
	void IsleOfConquest::AddReinforcements(uint32 teamId, uint32 amt);
	void IsleOfConquest::RemoveReinforcements(uint32 teamId, uint32 amt);
	LocationVector GetStartingCoords(uint32 Team);

	static CBattleground* Create(MapMgr* m, uint32 i, uint32 l, uint32 t) { return new IsleOfConquest(m, i, l, t); }

	const char * GetName() { return "Isle of Conquest"; }

	void OnStart();

	bool SupportsPlayerLoot() { return true; }
	bool HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell);

	void HookGenerateLoot(Player* plr, Corpse* pCorpse);

	void SetIsWeekend(bool isweekend);
    void IsleOfConquest::HookOnUnitKill(Player* plr, Unit* pVictim);
	void Herald(const char *format, ...);

private:

};

enum GENERAL_IOC_DEFINES
{
	IOC_NUM_REINFORCEMENTS				= 600,		// Amount of reinforcements we start off with
	IOC_SCORE_WARNING					= 530,		// Dunno what this should be ;p
	IOC_ADD_POINTS_ON_CONTROLLED_MINE	= 1,		// Points to give the team who controls (a) mine(s)
	IOC_REINFORCEMENT_ADD_INTERVAL		= 45000,	// The interval (in milliseconds) that points from mines are awarded
	IOC_POINTS_ON_DESTROY_BUNKER			= 75,		// Points to remove for destroying a team's bunker
	IOC_POINTS_ON_KILL					= 1,		// Points to remove when killing a member of the opposite team
	IOC_POINTS_ON_KILL_CAPTAIN			= 100,		// Points  to remove for killing a team's captain
	IOC_NUM_CONTESTED_AREAS				= 9,		// Total contested areas (graveyards/mines)
	IOC_NUM_DESTROYABLE_AREAS			= 8,		// Total destroyable areas (towers/bunkers)
	IOC_NUM_BOSS_UNITS					= 14,		// Boss units (generals/captains/wing commanders etc)
	IOC_NUM_COLDTOOTH_UNITS				= 5,		// Coldtooth mine NPC types
	IOC_NUM_IRONDEEP_UNITS				= 4,		// Irondeep mine NPC types
	IOC_NUM_SNOWFALL_FLAGS				= 2,		// Count of Snowfall flags (used when changing them on a team's acquiration of the CP
	IOC_CONTESTED_AREAS_START			= 0,		// ID at which contested points start (for loops/ifs)
	IOC_CONTESTED_AREAS_END				= 8,		// ID at which contested points end (for loops/ifs)
	IOC_DESTROYABLE_AREAS_START			= 9,		// ID at which destroyable points start (for loops/ifs)
	IOC_DESTROYABLE_AREAS_END			= 16,		// ID at which contested points finish (for loops/ifs)
	IOC_PER_KILL_HONOR					= 21,
};
#endif		// _ICO_H
