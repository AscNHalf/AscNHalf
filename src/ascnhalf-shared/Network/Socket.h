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

#ifndef SOCKET_H
#define SOCKET_H

#include "SocketDefines.h"

class SERVER_DECL Socket
{
public:
	// Constructor. If fd = 0, it will be assigned 
	Socket(SOCKET fd, uint32 sendbuffersize, uint32 recvbuffersize);
	
	// Destructor.
	virtual ~Socket();

	// Open a connection to another machine.
	bool Connect(const char * Address, uint32 Port);

	// Disconnect the socket.
	void Disconnect();

	// Accept from the already-set fd.
	void Accept(sockaddr_in * address);

/* Implementable methods */

	// Called when data is received.
	virtual void OnRead() {}

	// Called when a connection is first successfully established.
	virtual void OnConnect() {}

	// Called when the socket is disconnected from the client (either forcibly or by the connection dropping)
	virtual void OnDisconnect() {}

/* Sending Operations */

	// Locks sending mutex, adds bytes, unlocks mutex.
	bool Send(const uint8 * Bytes, uint32 Size);

	// Burst system - Locks the sending mutex.
	INLINE void BurstBegin() { m_writeMutex.Acquire(); }

	// Burst system - Adds bytes to output buffer.
	bool BurstSend(const uint8 * Bytes, uint32 Size);

	// Burst system - Pushes event to queue - do at the end of write events.
	void BurstPush();

	// Burst system - Unlocks the sending mutex.
	INLINE void BurstEnd() { m_writeMutex.Release(); }

/* Client Operations */

	// Get the client's ip in numerical form.
	string GetRemoteIP();
	INLINE uint32 GetRemotePort() { return ntohs(m_client.sin_port); }
	INLINE SOCKET GetFd() { return m_fd; }
	
/* Platform-specific methods */

	void SetupReadEvent();
	void ReadCallback(uint32 len);
	void WriteCallback();

	INLINE bool IsDeleted() { return m_deleted; }
	INLINE bool IsConnected() { return m_connected; }
	INLINE sockaddr_in & GetRemoteStruct() { return m_client; }
	INLINE CircularBuffer& GetReadBuffer() { return readBuffer; }
	INLINE CircularBuffer& GetWriteBuffer() { return writeBuffer; }

/* Deletion */
	void Delete();

	INLINE in_addr GetRemoteAddress() { return m_client.sin_addr; }

protected:

	// Called when connection is opened.
	void _OnConnect();
  
	SOCKET m_fd;

	CircularBuffer readBuffer;
	CircularBuffer writeBuffer;

	Mutex m_writeMutex;
	Mutex m_readMutex;

	// we are connected? stop from posting events.
        bool m_connected;

        // We are deleted? Stop us from posting events.
        bool m_deleted;

	sockaddr_in m_client;

/* Win32 - IOCP Specific Calls */
#ifdef CONFIG_USE_IOCP

public:

	// Set completion port that this socket will be assigned to.
	INLINE void SetCompletionPort(HANDLE cp) { m_completionPort = cp; }
	
	// Atomic wrapper functions for increasing read/write locks
	INLINE void IncSendLock() { InterlockedIncrement(&m_writeLock); }
	INLINE void DecSendLock() { InterlockedDecrement(&m_writeLock); }
	INLINE bool AcquireSendLock()
	{
		if(m_writeLock)
			return false;
		else
		{
			IncSendLock();
			return true;
		}
	}
	OverlappedStruct m_readEvent;
	OverlappedStruct m_writeEvent;

private:
	// Completion port socket is assigned to
	HANDLE m_completionPort;
	
	// Write lock, stops multiple write events from being posted.
	volatile long m_writeLock;
	
	// Assigns the socket to his completion port.
	void AssignToCompletionPort();

#endif

/* Linux - EPOLL Specific Calls */
#ifdef CONFIG_USE_EPOLL
public:
	// Posts a epoll event with the specifed arguments.
	void PostEvent(uint32 events);

	// Atomic wrapper functions for increasing read/write locks
	INLINE void IncSendLock() { __sync_add_and_fetch(&m_writeLock, 1); }
	INLINE void DecSendLock() { __sync_sub_and_fetch(&m_writeLock, 1); }
	INLINE bool HasSendLock() { return (m_writeLock != 0); }
	bool AcquireSendLock()
	{
		if( m_writeLock )
			return false;
		else
		{
			IncSendLock();
			return true;
		}
	}

private:
	volatile unsigned int m_writeLock;
#endif

/* FreeBSD - kqueue specific calls */
#ifdef CONFIG_USE_KQUEUE
public:
	// Posts a epoll event with the specifed arguments.
	void PostEvent(int events, bool oneshot);
	// Atomic wrapper functions for increasing read/write locks
	INLINE void IncSendLock() { __sync_add_and_fetch(&m_writeLock, 1); }
	INLINE void DecSendLock() { __sync_sub_and_fetch(&m_writeLock, 1); }
	INLINE bool HasSendLock() { return (m_writeLock != 0); }
	bool AcquireSendLock()
	{
		if( m_writeLock )
			return false;

		__sync_add_and_fetch(&m_writeLock, 1);
		return true;
	}

private:
	volatile unsigned int m_writeLock;
#endif
};

/** Connect to a server.
* @param hostname Hostname or IP address to connect to
* @param port Port to connect to
* @return templated type if successful, otherwise null
*/
template<class T>
T* ConnectTCPSocket(const char * hostname, u_short port)
{
	sockaddr_in conn;
	hostent * host;

	/* resolve the peer */
	host = gethostbyname(hostname);

	if(!host)
		return NULL;

	/* copy into our address struct */
	memcpy(&conn.sin_addr, host->h_addr_list[0], sizeof(in_addr));
	conn.sin_family = AF_INET;
	conn.sin_port = ntohs(port);

	T * s = new T(0);
	if(!s->Connect(hostname, port))
	{
		s->Delete();
		return NULL;
	}
	return s;	
}

/* Socket Garbage Collector */
#define SOCKET_GC_TIMEOUT 15

class SocketGarbageCollector : public Singleton<SocketGarbageCollector>
{
	map<Socket*, time_t> deletionQueue;
	Mutex lock;
public:
	~SocketGarbageCollector()
	{
		map<Socket*, time_t>::iterator i;
		for(i=deletionQueue.begin();i!=deletionQueue.end();++i)
			delete i->first;
	}

	void Update()
	{
		map<Socket*, time_t>::iterator i, i2;
		time_t t = UNIXTIME;
		lock.Acquire();
		for(i = deletionQueue.begin(); i != deletionQueue.end();)
		{
			i2 = i++;
			if(i2->second <= t)
			{
				delete i2->first;
				deletionQueue.erase(i2);
			}
		}
		lock.Release();
	}

	void QueueSocket(Socket * s)
	{
		lock.Acquire();
		deletionQueue.insert( map<Socket*, time_t>::value_type( s, UNIXTIME + SOCKET_GC_TIMEOUT ) );
		lock.Release();
	}
};

#define sSocketGarbageCollector SocketGarbageCollector::getSingleton()

#endif
