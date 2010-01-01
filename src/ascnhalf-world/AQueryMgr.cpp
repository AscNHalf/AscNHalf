/* AscNHalf */

// asynchronous mysql query mgr
#include "StdAfx.h"

initialiseSingleton( AQueryMgr );

AQueryMgr::AQueryMgr() {}
AQueryMgr::~AQueryMgr() {}

void AQueryMgr::AddQuery(WorldSession* p, AsyncQuery* query)
{
	InterlockedIncrement(&p->m_queriespending);
	m_lock.Acquire();
	map.insert( make_pair( p, query) );
	m_lock.Release();
}

void AQueryMgr::RemoveQueriesByAccount(WorldSession * p)
{
	if( !p->m_queriespending )
		return;

	uint32 id = p->GetAccountId();
	// this sucks, but is needed to avoid calling soon to be deleted memory.
	m_lock.Acquire();
	QueryMap::iterator itr = map.find( p );
	while(itr != map.end())
	{
		itr->first->m_queriespending--;
		map.erase( itr );
		itr = map.find(p);
	}
	m_lock.Release();
}

bool AQueryMgr::run()
{
#ifdef WIN32
	hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
#else
	struct timeval now;
	struct timespec tv;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
#endif

	QueryMap::iterator itr;
	QueryMap::iterator ditr;
	vector<AsyncQueryResult>::iterator itr2;
	AsyncQueryResult* aqr;
	for(;;)
	{
		// Get a single connection to maintain for the whole process.
		DatabaseConnection * con = CharacterDatabase.GetFreeConnection();
		m_lock.Acquire();
		itr = map.begin();
		for(; itr != map.end();)
		{
			ditr = itr;
			AsyncQuery* q = itr->second;
			itr2 = q->queries.begin();
			for(; itr2 != q->queries.end(); ++itr2)
			{
				aqr = &(*itr2);
				aqr->result = CharacterDatabase.FQuery( aqr->query, con );
			}
			InterlockedDecrement(&itr->first->m_queriespending);
			q->func->run(q->queries);
			++itr;
			map.erase(ditr);
			delete q;
		}
		m_lock.Release();

		if( Master::m_stopEvent )
			m_threadRunning = false;

#ifdef WIN32
		if (hEvent)
			WaitForSingleObject(hEvent,1000);
#else
		gettimeofday(&now, NULL);
		tv.tv_sec = now.tv_sec + 1;
		tv.tv_nsec = now.tv_usec * 1000;
		pthread_mutex_lock(&mutex);
		pthread_cond_timedwait(&cond, &mutex, &tv);
		pthread_mutex_unlock(&mutex);
#endif
		if(!m_threadRunning)
			break;
	}
	return true;
}