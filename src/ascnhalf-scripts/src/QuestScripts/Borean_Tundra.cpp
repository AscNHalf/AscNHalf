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

/*
	Borean Tundra Quest Scripts
	Copyright (C) 2010 Twl
	All rights reserved.
*/

#include "StdAfx.h"
#include "Setup.h"
#include "../Common/EasyFunctions.h"

enum SinkHoles
{
	SOUTH_SINKHOLE = 25402,
	EAST_SINKHOLE = 25403,
	WEST_SINKHOLE,
	NORTH_SINKHOLE
	
};

static const int BURY_THOSE_COCKROACHES = 11608;

inline bool NullCheck(Creature* cr)
{
	return (cr && cr != NULL);
}

bool BuryThoseCockroaches(uint32 i, Spell* pSpell)
{
	if( !pSpell->u_caster->IsPlayer() )
		return true;

	Player* plr = pSpell->p_caster;

	if(!plr || plr == NULL)
		return true;

	QuestLogEntry* qle = plr->GetQuestLogForEntry(BURY_THOSE_COCKROACHES);

	if(!qle || qle == NULL)
		return true;

	Creature* south = plr->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), SOUTH_SINKHOLE, 5.0f);

	if(!NullCheck(south))
	{
		Creature* east  = plr->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), EAST_SINKHOLE, 5.0f);
		
		if(!NullCheck(east))
		{
			Creature* west = plr->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), WEST_SINKHOLE, 5.0f);

			if(!NullCheck(west))
			{
				Creature* north = plr->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), NORTH_SINKHOLE, 5.0f);
				
				if(!NullCheck(north))
					return true;

				sEAS.SpawnCreature(plr, 25401, north->GetPositionX(), north->GetPositionY(), north->GetPositionZ(), north->GetOrientation(), 15000);


				if(qle->GetMobCount(3) < qle->GetQuest()->required_mobcount[3])
				{
					qle->SetMobCount(3, qle->GetMobCount(3) + 1);
					qle->SendUpdateAddKill(3);
				}

				north->Despawn(15000, 20000);
			}
			else
			{
				sEAS.SpawnCreature(plr, 25401, west->GetPositionX(), west->GetPositionY(), west->GetPositionZ(), west->GetOrientation(), 15000);


				if(qle->GetMobCount(2) < qle->GetQuest()->required_mobcount[2])
				{
					qle->SetMobCount(2, qle->GetMobCount(2) + 1);
					qle->SendUpdateAddKill(2);
				}

				west->Despawn(15000, 20000);
			}
		}
		else
		{
			sEAS.SpawnCreature(plr, 25401, east->GetPositionX(), east->GetPositionY(), east->GetPositionZ(), east->GetOrientation(), 15000);


			if(qle->GetMobCount(1) < qle->GetQuest()->required_mobcount[1])
			{
				qle->SetMobCount(1, qle->GetMobCount(1) + 1);
				qle->SendUpdateAddKill(4);
			}

			east->Despawn(15000, 20000);
		}
	}
	else
	{
		sEAS.SpawnCreature(plr, 25401, south->GetPositionX(), south->GetPositionY(), south->GetPositionZ(), south->GetOrientation(), 15000);


		if(qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[0])
		{
			qle->SetMobCount(0, qle->GetMobCount(0) + 1);
			qle->SendUpdateAddKill(0);
		}

		south->Despawn(15000, 20000);
	}

	plr->UpdateNearbyGameObjects();
	qle->UpdatePlayerFields();
	return true;
}