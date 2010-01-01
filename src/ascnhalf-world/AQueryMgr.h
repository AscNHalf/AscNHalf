/* AscNHalf */

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