/* AscNHalf */

#include "MemoryLeaks.h"

//#include <vld.h>
//#include <vldapi.h>

#if COMPILER == MICROSOFT

createFileSingleton( MemoryManager ) ;

/// Catch memory leaks
MemoryManager::MemoryManager( )
{
  //VLDEnable();
}

#endif

