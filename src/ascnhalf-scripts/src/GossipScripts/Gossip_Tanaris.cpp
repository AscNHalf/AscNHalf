/*
 * Moon++ Scripts for Ascent MMORPG Server
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

// Curgle Cranklehop
#define GOSSIP_CURGLE_CRANKLEHOP_1    "Please tell me more about the hippogryphs."
#define GOSSIP_CURGLE_CRANKLEHOP_2    "Please tell me more about the Gordunni ogres."

class CurgleCranklehop_Gossip : public GossipScript
{
public:
    void GossipHello(Object * pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1519, plr);
        Menu->AddItem( 0, GOSSIP_CURGLE_CRANKLEHOP_1, 1);
		Menu->AddItem( 0, GOSSIP_CURGLE_CRANKLEHOP_2, 2);
        
        if(AutoSend)
            Menu->SendTo(plr);
    }

    void GossipSelectOption(Object * pObject, Player * plr, uint32 Id, uint32 IntId, const char * Code)
    {
		if(pObject->GetTypeId()!=TYPEID_UNIT)
			return;
		
		GossipMenu * Menu;
        switch(IntId)
        {
        case 1:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1521, plr);
				Menu->SendTo(plr);
            }break;
		case 2:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1646, plr);
				Menu->SendTo(plr);
            }break;
		}
    }

    void Destroy()
    {
        delete this;
    }
};

// Trenton Lighthammer
#define GOSSIP_TRENTON_LIGHTHAMMER    "Tell me more, Trenton."

class TrentonLighthammer_Gossip : public GossipScript
{
public:
    void GossipHello(Object * pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1758, plr);
        Menu->AddItem( 0, GOSSIP_TRENTON_LIGHTHAMMER, 1);
        
        if(AutoSend)
            Menu->SendTo(plr);
    }

    void GossipSelectOption(Object * pObject, Player * plr, uint32 Id, uint32 IntId, const char * Code)
    {
		if(pObject->GetTypeId()!=TYPEID_UNIT)
			return;
		
		GossipMenu * Menu;
        switch(IntId)
        {
        case 1:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1759, plr);
				Menu->SendTo(plr);
            }break;
		}
    }

    void Destroy()
    {
        delete this;
    }
};

void SetupTanarisGossip(ScriptMgr * mgr)
{
	GossipScript * CurgleCranklehopGossip = (GossipScript*) new CurgleCranklehop_Gossip;
	GossipScript * TrentonLighthammerGossip = (GossipScript*) new TrentonLighthammer_Gossip;

	mgr->register_gossip_script(7763, CurgleCranklehopGossip);		// Curgle Cranklehop
	mgr->register_gossip_script(7804, TrentonLighthammerGossip);	// Trenton Lighthammer
}
