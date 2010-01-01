/* AscNHalf */

class WServer;
class Session;
class WSSocket : public Socket
{
	bool _authenticated;
	uint32 _remaining;
	uint16 _cmd;
	WServer * _ws;
public:
	uint32 m_id;

	WSSocket(SOCKET fd);
	~WSSocket();

	void SendPacket(WorldPacket * pck);
	void SendWoWPacket(Session * from, WorldPacket * pck);
	void OnRead();

	void HandleAuthRequest(WorldPacket & pck);
	void HandleRegisterWorker(WorldPacket & pck);
	void OnConnect();
	void OnDisconnect();

};


