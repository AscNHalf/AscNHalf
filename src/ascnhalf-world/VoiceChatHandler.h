/* AscNHalf */

#ifndef _VOICECHATHANDLER_H
#define _VOICECHATHANDLER_H

#ifdef VOICE_CHAT

#include "../ascnhalf-voicechat/ascnhalf_opcodes.h"
#include "VoiceChatClientSocket.h"

class VoiceChatClientSocket;
struct VoiceChatChannelRequest
{
	string channel_name;
	uint32 team;
	uint32 id;
	uint32 groupid;
};

struct VoiceChannel
{
	void* miscPointer;
	uint8 type;
	uint8 team;
	uint32 channelId;
};

class VoiceChatHandler : public Singleton<VoiceChatHandler>
{
	VoiceChatClientSocket * m_client;
	Mutex m_lock;
	vector<VoiceChatChannelRequest> m_requests;
	uint32 request_high;
	uint32 ip;
	uint16 port;
	time_t next_connect;
	bool enabled;
	string ip_s;
	HM_NAMESPACE::hash_map<uint32, VoiceChannel*> m_voiceChannels;
public:
	VoiceChatHandler();
	void Startup();
	void Update();
	void SocketDisconnected();
	void OnRead(WorldPacket* pck);

	INLINE uint32 GetVoiceServerIP() { return ip; }
	INLINE uint16 GetVoiceServerPort() { return port; }
	void CreateVoiceChannel(Channel * chn);
	void DestroyVoiceChannel(Channel * chn);
	bool CanCreateVoiceChannel(Channel * chn);
	bool CanUseVoiceChat();

	void CreateGroupChannel(Group * pGroup);
	void DestroyGroupChannel(Group * pGroup);
	void ActivateChannelSlot(uint16 channel_id, uint8 slot_id);
	void DeactivateChannelSlot(uint16 channel_id, uint8 slot_id);
};

#define sVoiceChatHandler VoiceChatHandler::getSingleton()

#endif		// VOICE_CHAT
#endif		// _VOICECHATHANDLER_H
