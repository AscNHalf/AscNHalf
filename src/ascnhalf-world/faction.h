/* AscNHalf */

#ifndef __FACTION_H
#define __FACTION_H

#include "Unit.h"
#define NUM_SANCTUARIES 2
static const uint32 SANCTUARY_ZONES[NUM_SANCTUARIES] = { 3703, 4395 }; //Shatrath city, Dalaran

SERVER_DECL bool isHostile(Object* objA, Object* objB); // B is hostile for A?
SERVER_DECL bool isAttackable(Object* objA, Object* objB, bool CheckStealth = true); // A can attack B?
SERVER_DECL bool isCombatSupport(Object* objA, Object* objB); // B combat supports A?;
SERVER_DECL bool isAlliance(Object* objA); // A is alliance?

INLINE bool isFriendly(Object* objA, Object* objB)// B is friendly to A if its not hostile
{
	return !isHostile(objA, objB);
}

INLINE bool isSameFaction(Object* objA, Object* objB)
{
	// shouldn't be necessary but still
	if( objA->m_faction == NULL || objB->m_faction == NULL )
		return false;

	return (objB->m_faction->Faction == objA->m_faction->Faction);
}
INLINE  Player* GetPlayerFromObject(Object* obj); 
#endif
