/* AscNHalf */

#ifndef _VOICECHATCLIENTSOCKET_H
#define _VOICECHATCLIENTSOCKET_H

#ifdef VOICE_CHAT

class VoiceChatClientSocket : public Socket
{
	uint16 op;
	uint16 remaining;
public:
	VoiceChatClientSocket(uint32 fd);
	void OnDisconnect();
	void OnRead();
	void SendPacket(WorldPacket* data);
	time_t next_ping;
	time_t last_pong;
};

#endif		// VOICE_CHAT
#endif		// _VOICECHATCLIENTSOCKET_H

