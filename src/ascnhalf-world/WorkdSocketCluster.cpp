/* AscNHalf */

#include "StdAfx.h"

#ifdef CLUSTERING

WorldSocket::WorldSocket(uint32 sessionid) : m_sessionId(sessionid)
{

}

WorldSocket::~WorldSocket()
{

}

void WorldSocket::Disconnect()
{

}

bool WorldSocket::IsConnected()
{
	return true;
}

void WorldSocket::OutPacket(uint16 opcode, uint16 len, const void* data)
{
	sClusterInterface.ForwardWoWPacket(opcode, len, data, m_sessionId);
}

#endif
