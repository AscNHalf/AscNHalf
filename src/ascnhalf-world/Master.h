/* AscNHalf */

#ifndef _MASTER_H
#define _MASTER_H

#include "Common.h"
//#include "Singleton.h"
#include "Config/ConfigEnv.h"
#include "Database/DatabaseEnv.h"
#include "MainServerDefines.h"

#ifndef _VERSION
# define _VERSION "3.2.2a"
#endif

#if PLATFORM == PLATFORM_WIN32
# define _FULLVERSION _VERSION "-SVN (Win32)"
#else
# define _FULLVERSION _VERSION "-SVN (Unix)"
#endif

#ifdef _DEBUG
#define BUILDTYPE "Debug"
#else
#define BUILDTYPE "Release"
#endif

#define DEFAULT_LOOP_TIME 0 /* 0 millisecs - instant */
#define DEFAULT_LOG_LEVEL 0
#define DEFAULT_PLAYER_LIMIT 100
#define DEFAULT_WORLDSERVER_PORT 8129
#define DEFAULT_REALMSERVER_PORT 3724
#define DEFAULT_HOST "0.0.0.0"
#define DEFAULT_REGEN_RATE 0.15
#define DEFAULT_XP_RATE 1
#define DEFAULT_DROP_RATE 1
#define DEFAULT_REST_XP_RATE 1
#define DEFAULT_QUEST_XP_RATE 1
#define DEFAULT_SAVE_RATE 300000	// 5mins

class SERVER_DECL Master : public Singleton<Master>
{
public:
	Master();
	~Master();
	bool Run(int argc, char ** argv);

	static volatile bool m_stopEvent;

private:
	bool _StartDB();
	void _StopDB();

	void _HookSignals();
	void _UnhookSignals();

	static void _OnSignal(int s);
};

#define sMaster Master::getSingleton()

#endif
