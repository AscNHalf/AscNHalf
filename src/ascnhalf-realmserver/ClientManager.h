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

#ifndef _R_CLIENTMANAGER_H
#define _R_CLIENTMANAGER_H

#define MAX_SESSIONS 3000

class ClientMgr : public Singleton<ClientMgr>
{
public:
#ifdef ENABLE_BOOST
	typedef boost::unordered_map<string, RPlayerInfo*> ClientStringMap;
#else
	typedef tr1::unordered_map<string, RPlayerInfo*> ClientStringMap;
#endif
	typedef HM_NAMESPACE::hash_map<uint32, RPlayerInfo*> ClientMap;
	typedef HM_NAMESPACE::hash_map<uint32, Session*> SessionMap;
	ClientMap m_clients;
	RWLock m_lock;

protected:
	ClientStringMap m_stringclients;
	uint32 m_maxSessionId;
public:
	SessionMap m_sessions;
	HM_NAMESPACE::hash_map<RPlayerInfo*, Session*> m_sessionsbyinfo;
	std::vector<uint32> m_reusablesessions;
	std::vector<uint32> m_pendingdeletesessionids;

	ClientMgr();
	~ClientMgr();

	/* create rplayerinfo struct */
	RPlayerInfo * CreateRPlayer(uint32 guid);

	/* destroy rplayerinfo struct */
	void DestroyRPlayerInfo(uint32 guid);

	INLINE Session* GetSessionByRPInfo(RPlayerInfo* p)
	{
		m_lock.AcquireReadLock();
		HM_NAMESPACE::hash_map<RPlayerInfo*, Session*>::iterator itr = m_sessionsbyinfo.find(p);
		if (itr == m_sessionsbyinfo.end())
		{
			m_lock.ReleaseReadLock();
			return NULL;
		}
		Session* s = itr->second;
		m_lock.ReleaseReadLock();
		return s;
	}

	INLINE void AddSessionRPInfo(Session* s, RPlayerInfo* p)
	{
		m_lock.AcquireWriteLock();
		m_sessionsbyinfo.insert(std::make_pair<RPlayerInfo*, Session*>(p, s));
		m_lock.ReleaseWriteLock();
	}

	INLINE void AddStringPlayerInfo(RPlayerInfo* p)
	{
		m_lock.AcquireWriteLock();
		m_stringclients.insert(std::make_pair<std::string, RPlayerInfo*>(p->Name, p));
		m_lock.ReleaseWriteLock();
	}

	/* get rplayer */
	INLINE RPlayerInfo * GetRPlayer(uint32 guid)
	{
		m_lock.AcquireReadLock();
		ClientMap::iterator itr = m_clients.find(guid);
		if (itr == m_clients.end())
		{
			m_lock.ReleaseReadLock();
			return NULL;
		}
		RPlayerInfo* r = itr->second;
		m_lock.ReleaseReadLock();
		return r;
	}

	/* get rplayer */
	INLINE RPlayerInfo * GetRPlayer(std::string name)
	{
		m_lock.AcquireReadLock();
		ClientStringMap::iterator itr = m_stringclients.find(name);
		if (itr == m_stringclients.end())
		{
			m_lock.ReleaseReadLock();
			return NULL;
		}
		RPlayerInfo* r = itr->second;
		m_lock.ReleaseReadLock();
		return r;
	}

	/* send "mini" client data to all servers */
	void SendPackedClientInfo(WServer * server);

	/* get session by id */
	INLINE Session * GetSession(uint32 Id)
	{
		SessionMap::iterator itr=m_sessions.find(Id);
		if (itr == m_sessions.end() || itr->second->deleted)
			return NULL;
		return itr->second;
	}

	INLINE Session* GetSessionByAccountId(uint32 Id)
	{
		m_lock.AcquireReadLock();
		for (SessionMap::iterator itr=m_sessions.begin(); itr!=m_sessions.end(); ++itr)
		{
			if (!itr->second->deleted && itr->second->GetAccountId() == Id)
			{
				Session* s=itr->second;
				m_lock.ReleaseReadLock();
				return s;
			}
		}
		m_lock.ReleaseReadLock();
		return NULL;
	}

	/* create a new session, returns null if the player is already logged in */
	Session * CreateSession(uint32 AccountId);

	void DestroySession(uint32 sessionid);

	/* updates sessions */
	void Update();
};

#define sClientMgr ClientMgr::getSingleton()


#endif