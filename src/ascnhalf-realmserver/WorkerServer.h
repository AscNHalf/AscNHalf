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

#ifndef _R_WORKERSERVER_H
#define _R_WORKERSERVER_H

#define MAX_SESSIONS_PER_SERVER 1000

struct Instance;
typedef void(WServer::*WServerHandler)(WorldPacket &);

class WServer
{
	static WServerHandler PHandlers[IMSG_NUM_TYPES];
	uint32 m_id;
	WSSocket * m_socket;
	FastQueue<WorldPacket*, Mutex> m_recvQueue;
	list<Instance*> m_instances;

public:
	static void InitHandlers();
	WServer(uint32 id, WSSocket * s);
	~WServer() { sSocketGarbageCollector.QueueSocket(m_socket); };

	INLINE size_t GetInstanceCount() { return m_instances.size(); }
	INLINE void SendPacket(WorldPacket * data) { if(m_socket) m_socket->SendPacket(data); }
	INLINE void SendWoWPacket(Session * from, WorldPacket * data) { if(m_socket) m_socket->SendWoWPacket(from, data); }
	INLINE void AddInstance(Instance * pInstance) { m_instances.push_back(pInstance); }
	INLINE void QueuePacket(WorldPacket * data) { m_recvQueue.Push(data); }
	INLINE uint32 GetID() { return m_id; }

	void Update();

protected:
	/* packet handlers */
	void HandleRegisterWorker(WorldPacket & pck);
	void HandleWoWPacket(WorldPacket & pck);
	void HandlePlayerLoginResult(WorldPacket & pck);
	void HandlePlayerLogout(WorldPacket & pck);
	void HandleTeleportRequest(WorldPacket & pck);
	void HandleError(WorldPacket & pck);
	void HandleSwitchServer(WorldPacket & pck);
	void HandleCreatePlayerResult(WorldPacket & pck);
	void HandleTransporterMapChange(WorldPacket & pck);
	void HandleSaveAllPlayers(WorldPacket & pck);
	void HandlePlayerTeleport(WorldPacket & pck);
	void HandlePlayerInfo(WorldPacket & pck);
	void HandleChannelAction(WorldPacket & pck);
	void HandleChannelUpdate(WorldPacket & pck);
	void HandleChannelLFGDungeonStatusReply(WorldPacket& pck);
};

#endif