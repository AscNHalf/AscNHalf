/* AscNHalf */

#include "vmap/IVMapManager.h"
#include "vmap/VMapManager.h"
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include "LocationVector.h"

VMAP::VMapManager* vmgr;

void * collision_init()
{
	vmgr = new VMAP::VMapManager();
	return vmgr;
}

void collision_shutdown()
{
	vmgr->unloadMap(0);
	vmgr->unloadMap(1);
	vmgr->unloadMap(530);
	vmgr->unloadMap(571);
}

