/* AscNHalf */

#ifndef __CConsole_LIB
#define __CConsole_LIB

#include "Common.h"

class ConsoleThread : public ThreadContext
{
protected:
	bool m_isRunning;
public:
	void terminate();
	bool run();
};

#endif
