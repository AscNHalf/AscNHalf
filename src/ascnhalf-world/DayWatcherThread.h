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

#ifndef _DAYWATCHERTHREAD_
#define _DAYWATCHERTHREAD_

enum DAYWATCHERSETTINGS
{
	WEEKLY		= 1,
	DAILY		= 2,
	MONTHLY		= 3,
	HOURLY		= 4,
	MINUTELY	= 5,
};

struct Events
{
	uint8 eventId;
	uint8 daynumber;
	uint8 monthnumber;
	uint8 activedays;
	time_t lastactivated;
	bool isactive;
	bool eventbyhour;
	uint8 starthour;
	uint8 endhour;
};

typedef std::vector<Events*>								EventsList;

// Multimap typedef's
typedef std::multimap<uint8, uint16>						CreatureEventSpawnMaps;
typedef std::multimap<uint8, uint16>						GameobjectEventSpawnMaps;

class SERVER_DECL DayWatcherThread : public Singleton<DayWatcherThread>, public ThreadContext
{
	bool m_threadRunning;
	bool m_busy;
	bool m_dirty;
	bool _loaded;
	bool runEvents;
	bool _firstrun[2];
	bool m_heroic_reset;

	static const time_t timeout = 120;		/* check every 2 minutes */
	time_t currenttime;
	tm local_currenttime;
	time_t last_arena_time;
	tm local_last_arena_time;
	time_t last_daily_reset_time;
	tm local_last_daily_reset_time;
	time_t last_eventid_time;
	tm local_last_eventid_time;

	uint32 arena_period;

public:
	DayWatcherThread();
	~DayWatcherThread();

	bool run();
	void terminate();
	void maintenence();
	void dupe_tm_pointer(tm * returnvalue, tm * mypointer);
	void load_settings();
	void update_settings();
	void set_tm_pointers();
	uint32 get_timeout_from_string(const char * string, uint32 def);
	bool has_timeout_expired(tm * now_time, tm * last_time, uint32 timeoutval);
	void update_arena();
	void update_daily();
	void Reset_Heroic_Instances();
	//ING Events
	CreatureEventSpawnMaps m_creatureEventSpawnMaps;
	GameobjectEventSpawnMaps m_gameobjectEventSpawnMaps;
	EventsList m_eventIdList;

	void update_event_settings(uint8 eventid, time_t activated);
	void LoadEventIdSettings();
	bool CheckHourlyEvent(tm * now_time, uint8 starthour, uint8 endhour);
	bool has_eventid_timeout_expired(tm * nowtime, int updatetime, uint8 timeoutval);
	bool has_eventid_expired(int activedays, time_t lastactivated);
	bool SpawnEventId(uint8 eventId, bool activate = true);
	uint8 eventToDespawn;
};
#define sDayWatcher DayWatcherThread::getSingleton()

#endif
