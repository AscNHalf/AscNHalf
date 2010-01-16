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

// asynchronous mysql query mgr
#ifndef _A_QUERY_MGR
#define _A_QUERY_MGR

typedef unordered_multimap<WorldSession*,AsyncQuery*> QueryMap;

class AQueryMgr : public ThreadContext, public Singleton<AQueryMgr>
{
protected:
	QueryMap map;
#ifdef WIN32
	HANDLE hEvent;
#else
	pthread_cond_t cond;
	pthread_mutex_t mutex;
#endif
	Mutex m_lock;

public:
	AQueryMgr();
	~AQueryMgr();

	void AddQuery(WorldSession* p, AsyncQuery* query);

	void RemoveQueriesByAccount(WorldSession * p);

	bool run();
};

#define sAQueryMgr AQueryMgr::getSingleton()
#endif