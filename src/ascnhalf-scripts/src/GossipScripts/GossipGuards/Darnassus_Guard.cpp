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

class DarnassusGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3016, Plr);

        Menu->AddItem( 0, "Auction House"      , 1);
        Menu->AddItem( 0, "The Bank"           , 2);
        Menu->AddItem( 0, "Hippogryph Master"  , 3);
        Menu->AddItem( 0, "Guild Master"       , 4);
        Menu->AddItem( 0, "The Inn"            , 5);
        Menu->AddItem( 0, "Mailbox"            , 6);
        Menu->AddItem( 0, "Stable Master"      , 7);
        Menu->AddItem( 0, "Weapons Trainer"    , 8);
        Menu->AddItem( 0, "Battlemaster"       , 9);
        Menu->AddItem( 0, "Class Trainer"      , 10);
	 	Menu->AddItem( 0, "Profession Trainer" , 11);
		Menu->AddItem( 0, "Lexicon of Power"   , 27);

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
            // Main menu handlers (Most/All 'borrowed' from scriptdev)
            /////

        case 1:     // Auction House
			SendQuickMenu(3833);
			Plr->Gossip_SendPOI(9861.23, 2334.55, 7, 6, 0, "Darnassus Auction House");
			break;
			
		case 2:		// The Bank
			SendQuickMenu(3017);
			Plr->Gossip_SendPOI(9938.45, 2512.35, 7, 6, 0, "Darnassus Bank");
			break;
		
		case 3:		// Hippogryph Master
			SendQuickMenu(3018);
			Plr->Gossip_SendPOI(9945.65, 2618.94, 7, 6, 0, "Rut'theran Village");
			break;
			
		case 4:		// Guild Master
			SendQuickMenu(3019);
			Plr->Gossip_SendPOI(10076.40, 2199.59, 7, 6, 0, "Darnassus Guild Master");
			break;
			
		case 5:		// The Inn
			SendQuickMenu(3020);
			Plr->Gossip_SendPOI(10133.29, 2222.52, 7, 6, 0, "Darnassus Inn");
			break;
			
		case 6:		// Mailbox
			SendQuickMenu(3021);
			Plr->Gossip_SendPOI(9942.17, 2495.48, 7, 6, 0, "Darnassus Mailbox");
			break;
		
		case 7:		// Stable Master
			SendQuickMenu(5980);
			Plr->Gossip_SendPOI(10167.20, 2522.66, 7, 6, 0, "Alassin");
			break;
			
		case 8:		// Weapons Trainer
			SendQuickMenu(4517);
			Plr->Gossip_SendPOI(9907.11, 2329.70, 7, 6, 0, "Ilyenia Moonfire");
			break;
			
		case 9:    // Battlemaster
            {
				SendQuickMenu(7519);
				Plr->Gossip_SendPOI(9981.9, 2325.9, 7, 6, 0, "Battlemasters Darnassus");
            }break;
			
		case 10:    // Class Trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4264, Plr);
                Menu->AddItem( 0, "Druid"       , 12);
                Menu->AddItem( 0, "Hunter"      , 13);
                Menu->AddItem( 0, "Priest"      , 14);
                Menu->AddItem( 0, "Rogue"       , 15);
                Menu->AddItem( 0, "Warrior"     , 16);
                Menu->SendTo(Plr);
            }break;

        case 11:    // Profession Trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
                Menu->AddItem( 0, "Alchemy"           , 17);
                Menu->AddItem( 0, "Cooking"           , 18);
                Menu->AddItem( 0, "Enchanting"        , 19);
                Menu->AddItem( 0, "First Aid"         , 20);
                Menu->AddItem( 0, "Fishing"           , 21);
                Menu->AddItem( 0, "Herbalism"         , 22);
				Menu->AddItem( 0, "Inscription"       , 23);
                Menu->AddItem( 0, "Leatherworking"    , 24);
                Menu->AddItem( 0, "Skinning"          , 25);
                Menu->AddItem( 0, "Tailoring"         , 26);
                Menu->SendTo(Plr);
            }break;
		
		case 12:	// Druid
            {
                Plr->Gossip_SendPOI(10186, 2570.46, 7, 6, 0, "Darnassus Druid Trainer");
                SendQuickMenu(3024);
            }break;

		case 13:	// Hunter
            {
                Plr->Gossip_SendPOI(10177.29, 2511.10, 7, 6, 0, "Darnassus Hunter Trainer");
                SendQuickMenu(3023);
            }break;

        case 14:	// Priest
            {
                Plr->Gossip_SendPOI(9659.12, 2524.88, 7, 6, 0, "Temple of the Moon");
                SendQuickMenu(3025);
            }break;
	
        case 15:	// Rogue
            {
                Plr->Gossip_SendPOI(10122, 2599.12, 7, 6, 0, "Darnassus Rogue Trainer");
                SendQuickMenu(3026);
            }break;

        case 16:	// Warrior
            {
                Plr->Gossip_SendPOI(9951.91, 2280.38, 7, 6, 0, "Warrior's Terrace");
                SendQuickMenu(3033);
            }break;
			
		case 17: //Alchemy
            {
                Plr->Gossip_SendPOI(10075.90, 2356.76, 7, 6, 0, "Darnassus Alchemy Trainer");
                SendQuickMenu(3035);
            }break;

        case 18: //Cooking
            {
                Plr->Gossip_SendPOI(10088.59, 2419.21, 7, 6, 0, "Darnassus Cooking Trainer");
                SendQuickMenu(3036);
            }break;
			
        case 19: //Enchanting
            {
                Plr->Gossip_SendPOI(10146.09, 2313.42, 7, 6, 0, "Darnassus Enchanting Trainer");
                SendQuickMenu(3337);
            }break;

        case 20: //First Aid
            {
                Plr->Gossip_SendPOI(10150.09, 2390.43, 7, 6, 0, "Darnassus First Aid Trainer");
                SendQuickMenu(3037);
            }break;

        case 21: //Fishing
            {
                Plr->Gossip_SendPOI(9836.20, 2432.17, 7, 6, 0, "Darnassus Fishing Trainer");
                SendQuickMenu(3038);
            }break;

        case 22: //Herbalism
            {
                Plr->Gossip_SendPOI(9757.17, 2430.16, 7, 6, 0, "Darnassus Herbalism Trainer");
                SendQuickMenu(3039);
            }break;
		case 23: //Inscription
            {
                Plr->Gossip_SendPOI(10146.09, 2313.42, 7, 6, 0, "Darnassus Inscription Trainer");
                SendQuickMenu(13886);
            }break;

        case 24: //Leatherworking
            {
                Plr->Gossip_SendPOI(10086.59, 2255.77, 7, 6, 0, "Darnassus Leatherworking Trainer");
                SendQuickMenu(3040);
            }break;

        case 25: //Skinning
            {
                Plr->Gossip_SendPOI(10081.40, 2257.18, 7, 6, 0, "Darnassus Skinning Trainer");
                SendQuickMenu(3042);
            }break;

        case 26: //Tailoring
            {
                Plr->Gossip_SendPOI(10079.70, 2268.19, 7, 6, 0, "Darnassus Tailor");
                SendQuickMenu(3044);
            }break;

		case 27: //Lexicon of Power
            {
                Plr->Gossip_SendPOI(10146.09, 2313.42, 7, 6, 0, "Darnassus Inscription Trainer");
                SendQuickMenu(14174);
            }break;
		}
	}
};

void SetupDarnassus_Guard(ScriptMgr * mgr)
{
	GossipScript * darn = (GossipScript*) new DarnassusGuard();
	mgr->register_gossip_script(4262, darn);			// Darnassus Sentinel
}