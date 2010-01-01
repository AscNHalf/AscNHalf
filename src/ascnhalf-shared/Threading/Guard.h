/* AscNHalf */

#ifndef _THREADING_GUARD_H
#define _THREADING_GUARD_H

#include "Mutex.h"

/************************************************************************/
/* Guard class, unlocks mutex on destroy								*/
/************************************************************************/
// crossplatform :)

class SERVER_DECL Guard
{
public:
	Guard(Mutex& mutex) : target(mutex)
	{
		target.Acquire();
	}

	~Guard()
	{
		target.Release();
	}

	Guard& operator=(Guard& src)
	{
		this->target = src.target;
		return *this;
	}

protected:
	Mutex& target;
};

#endif

