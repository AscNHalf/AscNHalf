/*
  * Moon++ Scripts for Ascent MMORPG Server
  * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
  * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
  * Copyright (C) 2009 AscNHalf Team <http://ascnhalf.scymex.info/>
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

#include "Guards.h"

#ifdef WIN32
#pragma warning(disable:4305)		// warning C4305: 'argument' : truncation from 'double' to 'float'
#endif

class UnderbellyGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13349, Plr);
		
        Menu->AddItem(0, "Arena Vendor"		    , 1);
		Menu->AddItem(0, "Arena Battlemaster"   , 2);
		Menu->AddItem(0, "Black Market"         , 3);
        Menu->AddItem(0, "Exit of Dalaran"	    , 4);
        
        if(AutoSend)
            Menu->SendTo(Plr);
    }

    void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
    {
        GossipMenu * Menu;
        switch(IntId)
        {
        case 0:     // Return to start
            GossipHello(pObject, Plr, true);
            break;

            //////////////////////
            // Main menu handlers
            /////

		case 1:    // Arena Vendor
		    Plr->Gossip_SendPOI(5757, 583, 7, 6, 0, "Arena Vendor");
			Plr->Gossip_Complete();
		    break;
		
		case 2:    // Arena Battlemaster
		    Plr->Gossip_SendPOI(5852, 609, 7, 6, 0, "Arena Battlemaster");
			Plr->Gossip_Complete();
		    break;
			
		case 3:    // Black Market
		    Plr->Gossip_SendPOI(5919, 569, 7, 6, 0, "Black Market");
			Plr->Gossip_Complete();
		    break;
		
		case 4:    // Exit of Dalaran
		    Plr->Gossip_SendPOI(5765, 753, 7, 6, 0, "Exit of dalaran");
            SendQuickMenu(14020);
		    break;	
			
		}
	}
};

void SetupUnderbelly_Guard(ScriptMgr * mgr)
{
	GossipScript * unb = (GossipScript*) new UnderbellyGuard();
	mgr->register_gossip_script(32730, unb);  // Goldlilly Gleamingfell
	mgr->register_gossip_script(32732, unb);  // Dorfus Alphamage
	mgr->register_gossip_script(32726, unb);  // The Chooch
	mgr->register_gossip_script(32727, unb);  // Natalie Tootiblare
	mgr->register_gossip_script(32729, unb);  // Lofwyr Le'Fleur
	mgr->register_gossip_script(32731, unb);  // Metopious Loreseeker
	mgr->register_gossip_script(32728, unb);  // Illusionist Karina
	mgr->register_gossip_script(32733, unb);  // Joboba Mezbreaker
}