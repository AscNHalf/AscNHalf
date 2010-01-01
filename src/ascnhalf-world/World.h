/* AscNHalf */

#ifndef __WORLD_H
#define __WORLD_H

#define IS_INSTANCE(a) (a>1 && a!=530 && a != 571)

class Object;
class WorldPacket;
class WorldSession;
class Unit;
class Creature;
class GameObject;
class DynamicObject;
class Player;
class EventableObjectHolder;
class MapMgr;
class Battleground;

enum Rates
{
	RATE_HEALTH=0,
	RATE_POWER1,	
	RATE_POWER2,	
	RATE_POWER3,	
	RATE_DROP0, // separate rates for each quality level
	RATE_DROP1,
	RATE_DROP2,
	RATE_DROP3,
	RATE_DROP4,
	RATE_DROP5,
	RATE_DROP6,
	RATE_MONEY,
	RATE_QUEST_MONEY,
	RATE_XP,
	RATE_RESTXP,
	RATE_QUESTXP,
	RATE_HONOR,
	RATE_QUESTREPUTATION,
	RATE_KILLREPUTATION,
	RATE_SKILLCHANCE,
	RATE_SKILLRATE,
	RATE_ARENAPOINTMULTIPLIER2X,
	RATE_ARENAPOINTMULTIPLIER3X,
	RATE_ARENAPOINTMULTIPLIER5X,
	RATE_EOTS_CAPTURERATE,
	MAX_RATES
};		

enum IntRates
{
	INTRATE_SAVE=0,
	INTRATE_COMPRESSION,
	INTRATE_PVPTIMER,
	MAX_INTRATES
};

enum EventIdFlags
{
	EVENTID_FLAG_NONE = 0,
	EVENTID_FLAG_PHASE = 1,
	EVENTID_FLAG_MODELID = 2,
	EVENTID_FLAG_EQUIP = 4, //this obviously cannot be used for gameobjects
	EVENTID_FLAG_SPAWN = 8
};

enum EnviromentalDamage
{
	DAMAGE_EXHAUSTED = 0,
	DAMAGE_DROWNING = 1,
	DAMAGE_FALL = 2,
	DAMAGE_LAVA = 3,
	DAMAGE_SLIME = 4,
	DAMAGE_FIRE = 5
};

enum CharCreateErrors
{
	SUCCESS,
	FAILURE,
	CANCELLED,
	DISCONNECT_FROM_SERVER,
	FAILED_TO_CONNECT,
	CONNECTED,
	WRONG_CLIENT_VERSION,
	CONNECTING_TO_SERVER,
	NEGOTIATING_SECURITY,
	NEGOTIATING_SECURITY_COMPLETE,
	NEGOTIATING_SECURITY_FAILED,
	AUTHENTICATING,
	AUTHENTICATION_SUCCESSFUL,
	AUTHENTICATION_FAILED,
	LOGIN_UNAVAIBLE,
	SERVER_IS_NOT_VALID,
	SYSTEM_UNAVAIBLE,
	SYSTEM_ERROR,
	BILLING_SYSTEM_ERROR,
	ACCOUNT_BILLING_EXPIRED,
	WRONG_CLIENT_VERSION_2,
	UNKNOWN_ACCOUNT,
	INCORRECT_PASSWORD,
	SESSION_EXPIRED,
	SERVER_SHUTTING_DOWN,
	ALREADY_LOGGED_IN,
	INVALID_LOGIN_SERVER,
	POSITION_IN_QUEUE_0,
	THIS_ACCOUNT_HAS_BEEN_BANNED,
	THIS_CHARACTER_STILL_LOGGED_ON,
	YOUR_WOW_SUBSCRIPTION_IS_EXPIRED,
	THIS_SESSION_HAS_TIMED_OUT,
	THIS_ACCOUNT_TEMP_SUSPENDED,
	ACCOUNT_BLOCKED_BY_PARENTAL_CONTROL,
	RETRIEVING_REALMLIST,
	REALMLIST_RETRIEVED,
	UNABLE_TO_CONNECT_REALMLIST_SERVER,
	INVALID_REALMLIST,
	GAME_SERVER_DOWN,
	CREATING_ACCOUNT,
	ACCOUNT_CREATED,
	ACCOUNT_CREATION_FAIL,
	RETRIEVE_CHAR_LIST,
	CHARLIST_RETRIEVED,
	CHARLIST_ERROR,
	CREATING_CHARACTER,
	CHARACTER_CREATED,
	ERROR_CREATING_CHARACTER,
	CHARACTER_CREATION_FAIL,
	NAME_IS_IN_USE,
	CREATION_OF_RACE_DISABLED,
	ALL_CHARS_ON_PVP_REALM_MUST_AT_SAME_SIDE,
	ALREADY_HAVE_MAXIMUM_CHARACTERS,
	ALREADY_HAVE_MAXIMUM_CHARACTERS_2,
	SERVER_IS_CURRENTLY_QUEUED,
	ONLY_PLAYERS_WHO_HAVE_CHARACTERS_ON_THIS_REALM,
	NEED_EXPANSION_ACCOUNT,
	DELETING_CHARACTER,
	CHARACTER_DELETED,
	CHARACTER_DELETION_FAILED,
	ENTERING_WOW,
	LOGIN_SUCCESFUL,
	WORLD_SERVER_DOWN,
	A_CHARACTER_WITH_THAT_NAME_EXISTS,
	NO_INSTANCE_SERVER_AVAIBLE,
	LOGIN_FAILED,
	LOGIN_FOR_THAT_RACE_DISABLED,
	LOGIN_FOR_THAT_RACE_CLASS_DISABLED,//check
	ENTER_NAME_FOR_CHARACTER,
	NAME_AT_LEAST_TWO_CHARACTER,
	NAME_AT_MOST_12_CHARACTER,
	NAME_CAN_CONTAIN_ONLY_CHAR,
	NAME_CONTAIN_ONLY_ONE_LANG,
	NAME_CONTAIN_PROFANTY,
	NAME_IS_RESERVED,
	YOU_CANNOT_USE_APHOS,
	YOU_CAN_ONLY_HAVE_ONE_APHOS,
	YOU_CANNOT_USE_SAME_LETTER_3_TIMES,
	NO_SPACE_BEFORE_NAME,
	BLANK,
	INVALID_CHARACTER_NAME,
	BLANK_1
	//All further codes give the number in dec.
};

// ServerMessages.dbc
enum ServerMessageType
{
	SERVER_MSG_SHUTDOWN_TIME	  = 1,
	SERVER_MSG_RESTART_TIME	   = 2,
	SERVER_MSG_STRING			 = 3,
	SERVER_MSG_SHUTDOWN_CANCELLED = 4,
	SERVER_MSG_RESTART_CANCELLED  = 5
};

enum ServerShutdownType
{
	SERVER_SHUTDOWN_TYPE_SHUTDOWN	= 1,
	SERVER_SHUTDOWN_TYPE_RESTART	= 2,
};

enum WorldMapInfoFlag
{
	WMI_INSTANCE_ENABLED   = 0x1,
	WMI_INSTANCE_WELCOME   = 0x2,
	WMI_INSTANCE_MULTIMODE = 0x4,
	WMI_INSTANCE_XPACK_01  = 0x8, //The Burning Crusade expansion
	WMI_INSTANCE_XPACK_02  = 0x10, //Wrath of the Lich King expansion
};

enum AccountFlags
{
	ACCOUNT_FLAG_VIP		 = 0x1,
	ACCOUNT_FLAG_NO_AUTOJOIN = 0x2,
	//ACCOUNT_FLAG_XTEND_INFO  = 0x4,
	ACCOUNT_FLAG_XPACK_01	= 0x8,
	ACCOUNT_FLAG_XPACK_02	= 0x10,
};

#pragma pack(push,1)
struct MapInfo
{
	uint32 mapid;
	uint32 screenid;
	uint32 type;
	uint32 playerlimit;
	uint32 minlevel;
	float repopx;
	float repopy;
	float repopz;
	uint32 repopmapid;
	char * name;
	uint32 flags;
	uint32 cooldown;
 	uint32 required_quest;
	uint32 required_item;
	uint32 heroic_key[2];
	float update_distance;
	uint32 checkpoint_id;
	bool collision;
	bool cluster_loads_map;

	bool HasFlag(uint32 flag)
	{
		return (flags & flag) != 0;
	}
};

#pragma pack(pop)

enum REALM_TYPE
{
    REALM_PVE = 0,
    REALM_PVP = 1,
};
struct AreaTable;

class BasicTaskExecutor : public ThreadContext
{
	CallbackBase * cb;
	uint32 priority;
public:
	BasicTaskExecutor(CallbackBase * Callback, uint32 Priority) : cb(Callback), priority(Priority) {}
	~BasicTaskExecutor() { delete cb; }
	bool run();
};

class Task
{
	CallbackBase * _cb;
public:
	Task(CallbackBase * cb) : _cb(cb), completed(false), in_progress(false) {}
	~Task() { delete _cb; }
	bool completed;
	bool in_progress;
	void execute();
};

struct CharacterLoaderThread : public ThreadContext
{
#ifdef WIN32
	HANDLE hEvent;
#else
	pthread_cond_t cond;
	pthread_mutex_t mutex;
#endif
public:
	CharacterLoaderThread();
	~CharacterLoaderThread();
	void OnShutdown();
	bool run();
};
class TaskList
{
	set<Task*> tasks;
	Mutex queueLock;
public:
	Task * GetTask();
	void AddTask(Task* task);
	void RemoveTask(Task * task)
	{
		queueLock.Acquire();
		tasks.erase(task);
		queueLock.Release();
	}

	void spawn();
	void kill();

	void wait();
	void waitForThreadsToExit();
	uint32 thread_count;
	bool running;

	Mutex tcMutex;
	void incrementThreadCount()
	{
		tcMutex.Acquire();
		++thread_count;
		tcMutex.Release();
	}

	void decrementThreadCount()
	{
		tcMutex.Acquire();
		--thread_count;
		tcMutex.Release();
	}
};

enum BasicTaskExecutorPriorities
{
	BTE_PRIORITY_LOW		= 0,
	BTE_PRIORITY_MED		= 1,
	BTW_PRIORITY_HIGH	   = 2,
};

class TaskExecutor : public ThreadContext
{
	TaskList * starter;
public:
	TaskExecutor(TaskList * l) : starter(l) { l->incrementThreadCount(); }
	~TaskExecutor() { starter->decrementThreadCount(); }

	bool run();
};

class NewsAnnouncer : public ThreadContext
{
	struct NewsAnnouncement
	{
		uint32 m_id;
		uint32 m_lastTime;
		uint32 m_timePeriod;
		int32 m_factionMask;
		string m_message;
	};

	map<uint32, NewsAnnouncement> m_announcements;

	void _UpdateMessages();
	void _ReloadMessages();
	void _SendMessage(NewsAnnouncement *ann);
	void _Init();
public:
	bool run();
};

class WorldSocket;

// Slow for remove in middle, oh well, wont get done much.
typedef std::list<WorldSocket*> QueueSet;
typedef set<WorldSession*> SessionSet;

// The maximum level attainable, period, regardless of flags on your account.
#define MAXIMUM_ATTAINABLE_LEVEL 80

class SERVER_DECL World : public Singleton<World>, public EventableObject
{
public:
	World();
	~World();
	void Destructor();

	uint32 GetMaxLevel(Player* plr);

	/** Reloads the config and sets all of the setting variables 
	 */
	void Rehash(bool load);

	void CleanupCheaters();
	WorldSession* FindSession(uint32 id);
	WorldSession* FindSessionByName(const char *);
	void AddSession(WorldSession *s);
	void RemoveSession(uint32 id);

	void AddGlobalSession(WorldSession *GlobalSession);
	void RemoveGlobalSession(WorldSession *GlobalSession);
	void DeleteGlobalSession(WorldSession *GlobalSession);

	INLINE size_t GetSessionCount() const { return m_sessions.size(); }

	INLINE size_t GetQueueCount() { return mQueuedSessions.size(); }
	void GetStats(uint32 * GMCount, float * AverageLatency);

	INLINE uint32 GetPlayerLimit() const { return m_playerLimit; }
	void SetPlayerLimit(uint32 limit) { m_playerLimit = limit; }

	INLINE bool getAllowMovement() const { return m_allowMovement; }
	void SetAllowMovement(bool allow) { m_allowMovement = allow; }
	INLINE bool getGMTicketStatus() { return m_gmTicketSystem; };
	bool toggleGMTicketStatus()
	{
		m_gmTicketSystem = !m_gmTicketSystem;
		return m_gmTicketSystem;
	};

	INLINE std::string getGmClientChannel() { return GmClientChannel; }

	void SetMotd(const char *motd) { m_motd = motd; }
	INLINE const char* GetMotd() const { return m_motd.c_str(); }

	INLINE time_t GetGameTime() const { return m_gameTime; }

	bool SetInitialWorldSettings();

	void SendWorldText(const char *text, WorldSession *self = 0);
	void SendWorldWideScreenText(const char *text, WorldSession *self = 0);
	void SendGlobalMessage(WorldPacket *packet, WorldSession *self = 0);
	void SendZoneMessage(WorldPacket *packet, uint32 zoneid, WorldSession *self = 0);
	void SendInstanceMessage(WorldPacket *packet, uint32 instanceid, WorldSession *self = 0);
	void SendFactionMessage(WorldPacket *packet, uint8 teamId);
	void SendMessageToGMs(WorldSession *self, const char * text, ...);

	INLINE void SetStartTime(uint32 val) { m_StartTime = val; }
	INLINE uint32 GetUptime(void) { return (uint32)UNIXTIME - m_StartTime; }
	INLINE uint32 GetStartTime(void) { return m_StartTime; }
	std::string GetUptimeString();

	// update the world server every frame
	void Update(time_t diff);
	void CheckForExpiredInstances();

   
	void UpdateSessions(uint32 diff);

	INLINE void setRate(int index,float value)
	{
		regen_values[index]=value;
	}

	INLINE float getRate(int index)
	{
		return regen_values[index];
	}
	
	INLINE uint32 getIntRate(int index)
	{
		return int_rates[index];
	}

	INLINE void setIntRate(int index, uint32 value)
	{
		int_rates[index] = value;
	}

	// talent inspection lookup tables
	std::map< uint32, uint32 > InspectTalentTabPos;
	std::map< uint32, uint32 > InspectTalentTabSize;
	std::map< uint32, uint32 > InspectTalentTabBit;
	uint32 InspectTalentTabPages[12][3];

	// map text emote to spell prices
	typedef std::map< uint32, uint32> SpellPricesMap;
	SpellPricesMap mPrices;

	INLINE uint32 GetTimeOut(){return TimeOut;}

	struct NameGenData
	{
		string name;
		uint32 type;
	};
	vector<NameGenData> _namegendata[3];
	void LoadNameGenData();
	std::string GenerateName(uint32 type = 0);

	std::map<uint32, AreaTable*> mAreaIDToTable;
	std::map<uint32, AreaTable*> mZoneIDToTable;

	std::map<uint32,uint32> TeachingSpellMap;
	uint32 GetTeachingSpell(uint32 NormalSpellId)
	{
		map<uint32,uint32>::iterator i = TeachingSpellMap.find(NormalSpellId);
		if(i!=TeachingSpellMap.end())
			return i->second;
		return 0;
	}

	uint32 AddQueuedSocket(WorldSocket* Socket);
	void RemoveQueuedSocket(WorldSocket* Socket);
	uint32 GetQueuePos(WorldSocket* Socket);
	void UpdateQueuedSessions(uint32 diff);

	Mutex queueMutex;

	uint32 mQueueUpdateInterval;

	bool cross_faction_world;
	bool free_guild_charters;
	bool m_useIrc;
	uint32 m_deathKnightReqLevel;
	bool m_deathKnightOnePerAccount;

	void SaveAllPlayers();

	string MapPath;
	string vMapPath;
	bool UnloadMapFiles;
	bool BreathingEnabled;
	bool SpeedhackProtection;
	bool Collision;
	uint32 mInWorldPlayerCount;
	uint32 mAcceptedConnections;
	uint32 SocketSendBufSize;
	uint32 SocketRecvBufSize;

	uint32 HordePlayers;
	uint32 AlliancePlayers;
	uint32 PeakSessionCount;
	bool SendStatsOnJoin;
	SessionSet gmList;
	RWLock gmList_lock;

	uint32 expansionUpdateTime;

	void DeleteObject(Object* obj);

	uint32 compression_threshold;

	uint8 StartLevel;

	void	SetKickAFKPlayerTime(uint32 idletimer){m_KickAFKPlayers=idletimer;}
	uint32	GetKickAFKPlayerTime(){return m_KickAFKPlayers;}

    uint32 GetRealmType() { return realmtype; }

	uint32 flood_lines;
	uint32 flood_seconds;
	uint32 flood_message_time;
	uint32 flood_mute_after_flood;
	uint32 flood_caps_min_len;
	float flood_caps_pct;
	bool flood_message;
	bool gm_skip_attunement;
	bool gm_force_robes;
	bool CheckProfessions;

	bool show_gm_in_who_list;
	uint32 map_unload_time;

	bool antihack_teleport;
	bool antihack_speed;
	bool antihack_flight;
	bool antihack_cheatengine;
	bool no_antihack_on_gm;

	bool free_arena_teams;

	bool display_free_items;

	//Enable/Disable specific battlegrounds/arenas
	bool av_disabled;
	bool wsg_disabled;
	bool eots_disabled;
	bool ab_disabled;

	// Level Caps
	uint32 LevelCap_Custom_All;

	// Duel Talent cost
	uint32 dualTalentTrainCost;

	// could add configs for every expansion..

	void CharacterEnumProc(QueryResultVector& results, uint32 AccountId);
	void LoadAccountDataProc(QueryResultVector& results, uint32 AccountId);

	void PollCharacterInsertQueue(DatabaseConnection * con);
	void PollMailboxInsertQueue(DatabaseConnection * con);
	void DisconnectUsersWithAccount(const char * account, WorldSession * session);
	void DisconnectUsersWithIP(const char * ip, WorldSession * session);
	void DisconnectUsersWithPlayerName(const char * plr, WorldSession * session);

	void LogoutPlayers();

	void BackupDB();

protected:
	// update Stuff, FIXME: use diff
	time_t _UpdateGameTime()
	{
		// Update Server time
		time_t thisTime = UNIXTIME;
		m_gameTime += thisTime - m_lastTick; //in seconds

		if(m_gameTime >= 86400)			// One day has passed
			m_gameTime -= 86400;

		m_lastTick = thisTime;

		return m_gameTime;
	}
	void FillSpellReplacementsTable();

private:
	EventableObjectHolder * eventholder;
	//! Timers
	typedef HM_NAMESPACE::hash_map<uint32, WorldSession*> SessionMap;
	SessionMap m_sessions;
	RWLock m_sessionlock;

	typedef HM_NAMESPACE::hash_map<uint32, AreaTrigger*> AreaTriggerMap;
	AreaTriggerMap m_AreaTrigger;

protected:
	Mutex SessionsMutex;//FOR GLOBAL !
	SessionSet GlobalSessions;

	float regen_values[MAX_RATES];
	uint32 int_rates[MAX_INTRATES];

	uint32 m_playerLimit;
	bool m_allowMovement;
	bool m_gmTicketSystem;
	std::string m_motd;
   
    uint32 realmtype;

	time_t m_gameTime;
	time_t m_lastTick;
	uint32 TimeOut;

	uint32 m_StartTime;
	uint32 m_queueUpdateTimer;

	QueueSet mQueuedSessions;

	uint32	m_KickAFKPlayers;//don't lag the server if you are useless anyway :P

public:
	std::string GmClientChannel;
	bool m_reqGmForCommands;
	bool m_lfgForNonLfg;
	list<SpellEntry*> dummyspells;
	bool m_limitedNames;
	bool m_useAccountData;

	char * m_banTable;

	static float m_movementCompressThreshold;
	static float m_movementCompressThresholdCreatures;
	static uint32 m_movementCompressRate;
	static uint32 m_movementCompressInterval;
	static float m_speedHackThreshold;
	static float m_speedHackLatencyMultiplier;
	static uint32 m_speedHackResetInterval;
	static uint32 m_CEThreshold;
	static float m_wallhackthreshold;

	// shutdown
	uint32 m_shutdownTime;
	uint32 m_shutdownType;
	uint32 m_shutdownLastTime;

	void QueueShutdown(uint32 delay, uint32 type);
	void CancelShutdown();
	void UpdateShutdownStatus();

	bool VerifyName(const char * name, size_t nlen)
	{
		const char * p;
		size_t i;

		static const char * bannedCharacters = "\t\v\b\f\a\n\r\\\"\'\? <>[](){}_=+-|/!@#$%^&*~`.,0123456789\0";
		static const char * allowedCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		if(m_limitedNames)
		{
			for(i = 0; i < nlen; ++i)
			{
				p = allowedCharacters;
				for(; *p != 0; ++p)
				{
					if(name[i] == *p)
						goto cont;
				}

				return false;
cont:
				continue;
			}
		}
		else
		{
			for(i = 0; i < nlen; ++i)
			{
				p = bannedCharacters;
				while(*p != 0 && name[i] != *p && name[i] != 0)
					++p;

				if(*p != 0)
					return false;
			}
		}

		return true;
	}
};

#define sWorld World::getSingleton()

#endif
