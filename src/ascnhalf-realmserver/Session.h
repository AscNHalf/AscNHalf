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

#ifndef _R_SESSION_H
#define _R_SESSION_H

typedef void(Session::*SessionPacketHandler)(WorldPacket&);

enum PlayerFlags
{
    PLAYER_FLAG_PARTY_LEADER		= 0x01,
    PLAYER_FLAG_AFK					= 0x02,
    PLAYER_FLAG_DND					= 0x04,
    PLAYER_FLAG_GM					= 0x08,
    PLAYER_FLAG_DEATH_WORLD_ENABLE  = 0x10,
    PLAYER_FLAG_RESTING				= 0x20,
    PLAYER_FLAG_UNKNOWN1            = 0x40,
    PLAYER_FLAG_FREE_FOR_ALL_PVP	= 0x80,
    PLAYER_FLAG_UNKNOWN2            = 0x100,
    PLAYER_FLAG_PVP_TOGGLE			= 0x200,
    PLAYER_FLAG_NOHELM				= 0x400,
    PLAYER_FLAG_NOCLOAK				= 0x800,
    PLAYER_FLAG_NEED_REST_3_HOURS	= 0x1000,
    PLAYER_FLAG_NEED_REST_5_HOURS	= 0x2000,
	PLAYER_FLAG_PVP_TIMER			= 0x40000,
};

class Session
{
public:
	friend class WorldSocket;
	friend class CharacterStorage;
	Session(uint32 id);
	~Session();

protected:
	FastQueue<WorldPacket*, Mutex> m_readQueue;
	WorldSocket * m_socket;
	WServer * m_server;
	WServer * m_nextServer;
	uint32 m_sessionId;
	uint32 m_accountId;
	uint32 m_ClientBuild;
	RPlayerInfo * m_currentPlayer;
	uint32 m_latency;
	uint32 m_accountFlags;
	string m_GMPermissions;
	string m_accountName;
	uint32 m_build;
	uint32 language;
	static SessionPacketHandler Handlers[NUM_MSG_TYPES];
	bool m_loadedPlayerData;
	bool m_hasDeathKnight;
	uint8 m_highestLevel;

private:
	int8 _side;

public:
	bool deleted;
	static void InitHandlers();
	void Update();
	INLINE RPlayerInfo * GetPlayer() { return m_currentPlayer; }

	INLINE void ClearCurrentPlayer() { m_currentPlayer = 0; }
	INLINE void ClearServers() { m_nextServer = m_server = 0; }
	INLINE void SetNextServer() { m_server = m_nextServer; }
	INLINE void SetNextServer(WServer* s) { m_nextServer = s; };
	INLINE void SetServer(WServer * s) { m_server = s; }
	INLINE WServer * GetServer() { return m_server; }
	INLINE WorldSocket * GetSocket() { return m_socket; }
	INLINE uint32 GetAccountId() { return m_accountId; }
	INLINE uint32 GetSessionId() { return m_sessionId; }
	INLINE std::string GetAccountPermissions() { return m_GMPermissions; }
	INLINE std::string GetAccountName() { return m_accountName; }
	INLINE uint32 GetAccountFlags() { return m_accountFlags; }
	INLINE uint32 GetClientBuild() { return m_ClientBuild; }

	bool CanUseCommand(std::string cmdstr)
	{
		if(m_GMPermissions.find("a") != string::npos)
			return true;
		
		if(cmdstr.length() <= 1)
			return (m_GMPermissions.find(cmdstr) != string::npos);
		else
		{
			for(size_t i = 0; i < cmdstr.length(); i++)
			{
				if(m_GMPermissions.find(cmdstr[i]) == string::npos)
					return false;
			}
		}
		return true;
	}

	bool HasFlag(uint32 flag) { return (m_accountFlags & flag) != 0; }

	void SendPacket(WorldPacket * data)
	{
		if(m_socket && m_socket->IsConnected())
			m_socket->SendPacket(data);
	}

	INLINE void SendPacket(StackPacket * packet)
	{
		if(m_socket && m_socket->IsConnected())
			m_socket->SendPacket(packet);
	}

	void OutPacket(uint16 opcode, uint16 len, const void* data)
	{
		if(m_socket && m_socket->IsConnected())
			m_socket->OutPacket(opcode, len, data);
	}

	void Disconnect()
	{
		if(m_socket && m_socket->IsConnected())
			m_socket->Disconnect();
	}

	void HandlePlayerLogin(WorldPacket & pck);

	void HandleCharacterEnum(WorldPacket & pck);
	void HandleCharacterEnumProc();

	void HandleCharacterCreate(WorldPacket & pck);
	void HandleCharacterDelete(WorldPacket & pck);
	void HandleCharacterRename(WorldPacket & pck);
	
	void HandleItemQuerySingleOpcode(WorldPacket & pck);
	void HandleCreatureQueryOpcode(WorldPacket & pck);
	void HandleGameObjectQueryOpcode(WorldPacket & pck);
	void HandleItemPageQueryOpcode(WorldPacket & pck);
	void HandleNpcTextQueryOpcode(WorldPacket & pck);

	void HandleRealmSplitQuery(WorldPacket & pck);
	void HandleNameQueryOpcode( WorldPacket & recv_data );
	void HandleQueryTimeOpcode( WorldPacket & recv_data );
	void HandlePageTextQueryOpcode( WorldPacket & recv_data );
	void HandleItemNameQueryOpcode( WorldPacket & recv_data );

	/// Channel Opcodes (ChannelHandler.cpp)
	void HandleChannelJoin(WorldPacket& recvPacket);
	void HandleChannelLeave(WorldPacket& recvPacket);
	void HandleChannelList(WorldPacket& recvPacket);
	void HandleChannelPassword(WorldPacket& recvPacket);
	void HandleChannelSetOwner(WorldPacket& recvPacket);
	void HandleChannelOwner(WorldPacket& recvPacket);
	void HandleChannelModerator(WorldPacket& recvPacket);
	void HandleChannelUnmoderator(WorldPacket& recvPacket);
	void HandleChannelMute(WorldPacket& recvPacket);
	void HandleChannelUnmute(WorldPacket& recvPacket);
	void HandleChannelInvite(WorldPacket& recvPacket);
	void HandleChannelKick(WorldPacket& recvPacket);
	void HandleChannelBan(WorldPacket& recvPacket);
	void HandleChannelUnban(WorldPacket& recvPacket);
	void HandleChannelAnnounce(WorldPacket& recvPacket);
	void HandleChannelModerate(WorldPacket& recvPacket);
	void HandleChannelNumMembersQuery(WorldPacket & recvPacket);
	void HandleChannelRosterQuery(WorldPacket & recvPacket);
	void HandleMessagechatOpcode( WorldPacket & recv_data );
};

#endif


