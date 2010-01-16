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

#include "StdAfx.h"

ChainAggroEntity::ChainAggroEntity(Creature* pOwner)
{
	AddAggroEntity(pOwner);
}

ChainAggroEntity::~ChainAggroEntity()
{

}

void ChainAggroEntity::AddAggroEntity(Creature* pCreature)
{
	pCreature->GetAIInterface()->m_ChainAgroSet = this;
	m_agroEntitySet.insert(pCreature);
}

void ChainAggroEntity::RemoveAggroEntity(Creature* pCreature)
{
	pCreature->GetAIInterface()->m_ChainAgroSet = NULL;
	m_agroEntitySet.erase(pCreature);

	// Oh noes, I am with the worms!
	if(m_agroEntitySet.size() == 0)
	{
		delete this;
	}
}

void ChainAggroEntity::Delete()
{
	set<Creature*>::iterator itr = m_agroEntitySet.begin();
	for(; itr != m_agroEntitySet.end(); ++itr)
	{
		(*itr)->GetAIInterface()->m_ChainAgroSet = NULL;
	}
	delete this;
}

void ChainAggroEntity::EventEnterCombat(Unit* pTarget)
{
	set<Creature*>::iterator itr = m_agroEntitySet.begin();
	for(; itr != m_agroEntitySet.end(); ++itr)
	{
		if( (*itr)->isDead() )
			continue;

		(*itr)->GetAIInterface()->AttackReaction( pTarget, 1 );
	}
}
