/* AscNHalf */

#include "StdAfx.h"

#ifdef VOICE_CHAT

VoiceChatClientSocket::VoiceChatClientSocket(uint32 fd) : Socket(fd, 250000, 250000)
{
	remaining = 0;
	op = 0;
	next_ping = UNIXTIME + 15;
	last_pong = UNIXTIME;
}

void VoiceChatClientSocket::OnDisconnect()
{
	sVoiceChatHandler.SocketDisconnected();
}

void VoiceChatClientSocket::OnRead()
{
	WorldPacket *data;

	// uint16 op
	// uint16 size
	// <data>

	for(;;)
	{
		// no more data
		if( readBuffer.GetSize() < 4 )
			break;

		readBuffer.Read(&op, 2);
		readBuffer.Read(&remaining, 2);

		if( readBuffer.GetSize() < remaining )
			break;

		data = new WorldPacket(op, remaining);
		data->resize(remaining);
		readBuffer.Read((uint8*)data->contents(), remaining);

		// handle the packet
		sVoiceChatHandler.OnRead(data);

		delete data;
		remaining = op = 0;
	}
}

void VoiceChatClientSocket::SendPacket(WorldPacket* data)
{
	if( 4 + data->size() > writeBuffer.GetSpace() )
	{
		printf("!!! VOICE CHAT CLIENT SOCKET OVERLOAD !!!\n");
		return;
	}
	uint16 opcode = data->GetOpcode();
	uint32 sz = data->size();
	bool rv;

	BurstBegin();
	rv = BurstSend((const uint8*)&opcode, 2);
	if(rv) BurstSend((const uint8*)&sz, 2);

	if( sz > 0 && rv )
	{
		rv = BurstSend((const uint8*)data->contents(), data->size());
	}

	printf("sent packet of %u bytes with op %u, buffer len is now %u\n", data->size(), data->GetOpcode(), writeBuffer.GetSize());
	if( rv )
		BurstPush();


	BurstEnd();
}

#endif		// VOICE_CHAT
