/*
 * Moon++ Scripts for Ascent MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "StdAfx.h"
#include "Setup.h"
#include "../Common/EasyFunctions.h"
#include "../Common/Base.h"

// -----------------------------------------------------------------------------
// Quest 12532 - Flown the Coop!
// Quest 12702 - Chicken Party! (by bartus

bool ChickenNet( uint32 i, Spell * pSpell )
{
	if( !pSpell->u_caster->IsPlayer() )
        return true;

	Player * pPlayer = TO_PLAYER( pSpell->u_caster );

	QuestLogEntry *qle = pPlayer->GetQuestLogForEntry( 12532 );
	if( qle == NULL )
	{
		QuestLogEntry *qle = pPlayer->GetQuestLogForEntry( 12702 );
		if( qle == NULL )
			return true;
	}

	
	if( !pSpell->GetUnitTarget()->IsCreature() )
		return true;

	Creature * Chicken = TO_CREATURE( pSpell->GetUnitTarget() );

	if( Chicken != NULL && Chicken->GetEntry() == 28161 )
	{
		Chicken->Despawn( 5000, 360000 );
		pPlayer->CastSpell( pSpell->u_caster, dbcSpell.LookupEntry( 51037 ), true );
	}

   return true;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void SetupSholazarBasin( ScriptMgr * mgr )
{
   mgr->register_dummy_spell(51959, &ChickenNet);
}