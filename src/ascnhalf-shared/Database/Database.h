/* AscNHalf */

#ifndef _DATABASE_H
#define _DATABASE_H

#include <string>
#include "../Threading/Queue.h"
#include "../CallBack.h"
#include <mysql/mysql.h>

using namespace std;
class QueryResult;
class QueryThread;
class Database;

struct DatabaseConnection
{
	FastMutex Busy;
	MYSQL *conn;
};

struct SERVER_DECL AsyncQueryResult
{
	QueryResult * result;
	char * query;
};

class SERVER_DECL AsyncQuery
{
	friend class Database;
	SQLCallbackBase * func;
	vector<AsyncQueryResult> queries;
	Database * db;
public:
	AsyncQuery(SQLCallbackBase * f) : func(f) {}
	~AsyncQuery();
	void AddQuery(const char * format, ...);
	void Perform();
	INLINE void SetDB(Database * dbb) { db = dbb; }
};

class SERVER_DECL QueryBuffer
{
	vector<char*> queries;
public:
	friend class Database;
	void AddQuery( const char * format, ... );
	void AddQueryNA( const char * str );
	void AddQueryStr(const string& str);
};

class SERVER_DECL Database : public ThreadContext
{
	friend class QueryThread;
	friend class AsyncQuery;

public:
	Database();
	virtual ~Database();

	/************************************************************************/
	/* Thread Stuff                                                         */
	/************************************************************************/
	bool run();
	bool ThreadRunning;

	/************************************************************************/
	/* Virtual Functions                                                    */
	/************************************************************************/
	bool Initialize(const char* Hostname, unsigned int port,
		const char* Username, const char* Password, const char* DatabaseName,
		uint32 ConnectionCount, uint32 BufferSize);
	
	void Shutdown();

	QueryResult* Query(const char* QueryString, ...);
	QueryResult* QueryNA(const char* QueryString);
	QueryResult * FQuery(const char * QueryString, DatabaseConnection *con);
	void FWaitExecute(const char * QueryString, DatabaseConnection *con);
	bool WaitExecute(const char* QueryString, ...);//Wait For Request Completion
	bool WaitExecuteNA(const char* QueryString);//Wait For Request Completion
	bool Execute(const char* QueryString, ...);
	bool ExecuteNA(const char* QueryString);

	INLINE const string& GetHostName() { return mHostname; }
	INLINE const string& GetDatabaseName() { return mDatabaseName; }
	INLINE const uint32 GetQueueSize() { return queries_queue.get_size(); }

	string EscapeString(string Escape);
	void EscapeLongString(const char * str, uint32 len, stringstream& out);
	string EscapeString(const char * esc, DatabaseConnection *con);
	
	void QueueAsyncQuery(AsyncQuery * query);
	void EndThreads();
	
	void thread_proc_query();
	void FreeQueryResult(QueryResult * p);

	DatabaseConnection *GetFreeConnection();

	void PerformQueryBuffer(QueryBuffer * b, DatabaseConnection *ccon);
	void AddQueryBuffer(QueryBuffer * b);

	static void CleanupLibs();
	static Database *Create();

	/* database is killed off manually. */
	void OnShutdown() {}

protected:

	// actual query function
	bool _SendQuery(DatabaseConnection *con, const char* Sql, bool Self);
	QueryResult * _StoreQueryResult(DatabaseConnection * con);
	bool _HandleError(DatabaseConnection *conn, uint32 ErrorNumber);
	bool _Reconnect(DatabaseConnection *conn);

	////////////////////////////////
	FQueue<QueryBuffer*> query_buffer;

	////////////////////////////////
	FQueue<char*> queries_queue;
	DatabaseConnection *m_connections;
	
	uint32 _counter;
	///////////////////////////////

	int32 mConnectionCount;

	// For reconnecting a broken connection
	string mHostname;
	string mUsername;
	string mPassword;
	string mDatabaseName;
	uint32 mPort;

	QueryThread * qt;
};

class SERVER_DECL QueryResult
{
public:
	QueryResult(MYSQL_RES *res, uint32 fields, uint32 rows);
	~QueryResult();

	bool NextRow();
	void Delete() { delete this; }

	INLINE Field* Fetch() { return mCurrentRow; }
	INLINE uint32 GetFieldCount() const { return mFieldCount; }
	INLINE uint32 GetRowCount() const { return mRowCount; }

protected:
	uint32 mFieldCount;
	uint32 mRowCount;
    Field *mCurrentRow;
	MYSQL_RES *mResult;
};

class SERVER_DECL QueryThread : public ThreadContext
{
	friend class Database;
	Database * db;
public:
	QueryThread(Database * d) : ThreadContext(), db(d) {}
	~QueryThread();
	bool run();
};

#endif
