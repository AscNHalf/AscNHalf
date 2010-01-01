/* AscNHalf */

enum LFGTypes 
{
	LFG_TYPE_NONE                 = 0,
	LFG_TYPE_DUNGEON              = 1,
	LFG_TYPE_RAID                 = 2,
	LFG_TYPE_QUEST                = 3,
	LFG_TYPE_ZONE                 = 4,
	LFG_TYPE_HEROIC_DUNGEON       = 5,
	LFG_TYPE_ANY_DUNGEON          = 6,
	LFG_TYPE_ANY_HEROIC_DUNGEON   = 7,
	LFG_TYPE_DAILY_DUNGEON        = 8,
	LFG_TYPE_DAILY_HEROIC_DUNGEON = 9
};

#define MAX_DUNGEONS 257+1 // check max entrys +1 on lfgdungeons.dbc
#define MAX_LFG_QUEUE_ID 3
#define LFG_MATCH_TIMEOUT 30		// in seconds

class LfgMatch;
class LfgMgr : public Singleton < LfgMgr >, EventableObject
{
public:	
	
	typedef list<Player*  > LfgPlayerList;

	LfgMgr();
	~LfgMgr();
	
	bool AttemptLfgJoin(Player* pl, uint32 LfgDungeonId);
	void SetPlayerInLFGqueue(Player* pl,uint32 LfgDungeonId);
	void SetPlayerInLfmList(Player* pl, uint32 LfgDungeonId);
	void RemovePlayerFromLfgQueue(Player* pl,uint32 LfgDungeonId);
	void RemovePlayerFromLfgQueues(Player* pl);
	void RemovePlayerFromLfmList(Player* pl, uint32 LfmDungeonId);
	void UpdateLfgQueue(uint32 LfgDungeonId);
	void SendLfgList(Player* plr, uint32 Dungeon);
	void EventMatchTimeout(LfgMatch * pMatch);

	int32 event_GetInstanceId() { return -1; }
	
protected:
	
	LfgPlayerList m_lookingForGroup[MAX_DUNGEONS];
	LfgPlayerList m_lookingForMore[MAX_DUNGEONS];
	Mutex m_lock;
	
	
};

class LfgMatch
{
public:
	set<Player*  > PendingPlayers;
	set<Player*  > AcceptedPlayers;
	Mutex lock;
	uint32 DungeonId;
    Group * pGroup;

	LfgMatch(uint32 did) : DungeonId(did),pGroup(NULL) { }
};

extern uint32 LfgDungeonTypes[MAX_DUNGEONS];

#define sLfgMgr LfgMgr::getSingleton()
