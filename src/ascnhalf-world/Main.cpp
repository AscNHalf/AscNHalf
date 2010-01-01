/* AscNHalf */

#include "StdAfx.h"
//#include <vld.h>

#ifdef WIN32
#include "CrashHandler.h"
#endif

#ifndef WIN32
#include <sys/resource.h>
#endif

uint8 loglevel = DEFAULT_LOG_LEVEL;

#ifndef WIN32
int unix_main(int argc, char ** argv)
{
	rlimit rl;
	if (getrlimit(RLIMIT_CORE, &rl) == -1)
		printf("getrlimit failed. This could be problem.\n");
	else
	{
		rl.rlim_cur = rl.rlim_max;
		if (setrlimit(RLIMIT_CORE, &rl) == -1)
			printf("setrlimit failed. Server may not save core.dump files.\n");
	}

	if(!sMaster.Run(argc, argv))
		exit(-1);
	else
		exit(0);

	return 0;// shouldn't be reached
}

#else

int win32_main( int argc, char ** argv )
{
	SetThreadName( "Main Thread" );
	StartCrashHandler();

	THREAD_TRY_EXECUTION
	{
		sMaster.Run( argc, argv );
	}
	THREAD_HANDLE_CRASH;
	exit( 0 );
	return 0;
}

#endif

int main( int argc, char ** argv )
{
#ifdef WIN32
	win32_main( argc, argv );
#else
	unix_main( argc, argv );
#endif
}

