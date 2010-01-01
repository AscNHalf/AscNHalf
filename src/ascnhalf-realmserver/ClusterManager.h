/* AscNHalf */

#define MAX_WORKER_SERVERS 100
#define MAX_SINGLE_MAPID 600

struct Instance
{
	uint32 InstanceId;
	uint32 MapId;
	uint32 MapCount; //used for load balancing for things like battleground servers
	WServer * Server;
};

#define IS_INSTANCE(a) (((a)>1)&&((a)!=530))
#define IS_MAIN_MAP(a) (((a)<2)||((a)==530))

class ClusterMgr : public Singleton<ClusterMgr>
{
	typedef map<uint32, Instance*> InstanceMap;

	RWLock m_lock;
	WServer * WorkerServers[MAX_WORKER_SERVERS];
	Instance * SingleInstanceMaps[MAX_SINGLE_MAPID];
	
	InstanceMap Instances;
	uint32 m_maxInstanceId;
	uint32 m_maxWorkerServer;

public:
	ClusterMgr();

	//this is the prototype for instanced maps that haven't been created yet
	//yes, its a multimap, you can have multiple servers per map (battleground servers)
	std::multimap<uint32, Instance*> InstancedMaps;

	WServer * GetServerByInstanceId(uint32 InstanceId);
	WServer * GetServerByMapId(uint32 MapId);

	Instance * GetInstanceByInstanceId(uint32 InstanceId);
	Instance * GetInstanceByMapId(uint32 MapId);
	Instance * GetAnyInstance();
	Instance * GetPrototypeInstanceByMapId(uint32 MapId);

	void OnServerDisconnect(WServer* s);

	WServer * CreateWorkerServer(WSSocket * s);
	INLINE WServer * GetWorkerServer(uint32 Id) { return (Id < MAX_WORKER_SERVERS) ? WorkerServers[Id] : 0; }
	void AllocateInitialInstances(WServer * server, vector<uint32>& preferred);

	// find the worker server with the least load for the new instance
	WServer * GetWorkerServerForNewInstance();

	/* create new instance, or a main map */
	Instance * CreateInstance(uint32 MapId, WServer * server);

	/* create new instance based on template, or a saved instance */
	Instance * CreateInstance(uint32 InstanceId, uint32 MapId);

	/* gets the instance struct by instance id */
	Instance * GetInstance(uint32 InstanceId)
	{
		InstanceMap::iterator itr = Instances.find(InstanceId);
		return (itr == Instances.end()) ? 0 : itr->second;
	}

	/* distribute packet to all worker servers */
	INLINE void DistributePacketToAll(WorldPacket * data) { DistributePacketToAll(data, 0); }

	/* distribute packet to all worker server excluding one */
	void DistributePacketToAll(WorldPacket * data, WServer * exclude);

	/* loop */
	void Update();

};


#define sClusterMgr ClusterMgr::getSingleton()


