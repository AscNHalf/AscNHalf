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

class TeldrassilGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4316, Plr);

        Menu->AddItem(0, "The Bank", 1);
		Menu->AddItem(0, "Rut'Theran Ferry", 2);
		Menu->AddItem(0, "The Guild Master", 3);
		Menu->AddItem(0, "The Inn", 4);
		Menu->AddItem(0, "Stable Master", 5);
		Menu->AddItem(0, "Class Trainer", 6);
		Menu->AddItem(0, "Profession Trainer", 7);

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

        case 1:     // The Bank
            SendQuickMenu(4317);
            break;
		
		case 2:		// Rut'theran erry 
			SendQuickMenu(4318);
			break;
		
		case 3:		// The Guild Master
			SendQuickMenu(4319);
			break;
		
		case 4:		// The Inn
			Plr->Gossip_SendPOI(9821.49, 960.13, 7, 6, 0, "Dolanaar Inn");
			SendQuickMenu(4320);
			break;
			
		case 5:		// Stable Master
			Plr->Gossip_SendPOI(9808.37, 931.1, 7, 6, 0, "Seriadne");
			SendQuickMenu(5982);
			break;

        case 6:    // Class Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4264, Plr);
                Menu->AddItem( 0, "Druid"       , 8);
                Menu->AddItem( 0, "Hunter"      , 9);
                Menu->AddItem( 0, "Priest"     , 10);
                Menu->AddItem( 0, "Rogue"      , 11);
                Menu->AddItem( 0, "Warrior"    , 12);
                Menu->SendTo(Plr);
            }break;

        case 7:    // Profession Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
                Menu->AddItem( 0, "Alchemy"           , 13);
                Menu->AddItem( 0, "Cooking"           , 14);
                Menu->AddItem( 0, "Enchanting"        , 15);
                Menu->AddItem( 0, "First Aid"         , 16);
                Menu->AddItem( 0, "Fishing"           , 17);
                Menu->AddItem( 0, "Herbalism"         , 18);
				Menu->AddItem( 0, "Inscription"       , 19);
                Menu->AddItem( 0, "Leatherworking"    , 20);
                Menu->AddItem( 0, "Skinning"          , 21);
                Menu->AddItem( 0, "Tailoring"         , 22);
                Menu->SendTo(Plr);
            }break;

            ////////////////
            // Class trainer submenu
            ////////

        case 8: //Druid
            {
                Plr->Gossip_SendPOI(9741.58, 963.7, 7, 6, 0, "Kal");
                SendQuickMenu(4323);
            }break;
		
		case 9: // Hunter
			{
				Plr->Gossip_SendPOI(9815.12, 926.28, 7, 6, 0, "Dazalar");
				SendQuickMenu(4324);
			}break;
		
		case 10: // Priest
			{
				Plr->Gossip_SendPOI(9906.16, 986.63, 7, 6, 0, "Laurna Morninglight");
				SendQuickMenu(4325);
			}break;

		case 11: // Rogue
			{
				Plr->Gossip_SendPOI(9789, 942.86, 7, 6, 0, "Jannok Breezesong");
				SendQuickMenu(4326);
			}break;
			
		case 12: // Warrior
			{
				Plr->Gossip_SendPOI(9821.96, 950.61, 7, 6, 0, "Kyra Windblade");
				SendQuickMenu(4327);
			}break;

        case 13: // Alchemy
            {
                Plr->Gossip_SendPOI(9767.59, 878.81, 7, 6, 0, "Cyndra Kindwhisper");
                SendQuickMenu(4329);
            }break;
		
		case 14: // Cooking
			{
				Plr->Gossip_SendPOI(9751.19, 906.13, 7, 6, 0, "Zarrin");
				SendQuickMenu(4330);
			}break;
		
		case 15: // Enchanting
			{
				Plr->Gossip_SendPOI(10677.59, 1946.56, 7, 6, 0, "Alanna Raveneye");
				SendQuickMenu(4331);
			}break;
			
		case 16: // First Aid
			{
				Plr->Gossip_SendPOI(9903.12, 999, 7, 6, 0, "Byancie");
				SendQuickMenu(4332);
			}break;
			
		case 17: // Fishing
			{
				SendQuickMenu(4333);
			}break;
			
		case 18: // Herbalism
			{
				Plr->Gossip_SendPOI(9773.78, 875.88, 7, 6, 0, "Malorne Bladeleaf");
				SendQuickMenu(4334);
			}break;
			
		case 19: // Inscription
			{
				Plr->Gossip_SendPOI(10146.09, 2313.42, 7, 6, 0, "Darnassus Inscription Trainer");
				SendQuickMenu(13886);
			}break;
			
		case 20: // Leatherworking
			{
				Plr->Gossip_SendPOI(10152.59, 1681.46, 7, 6, 0, "Nadyia Maneweaver");
				SendQuickMenu(4335);
			}break;
			
		case 21: // Skinning
			{
				Plr->Gossip_SendPOI(10135.59, 1673.18, 7, 6, 0, "Radnaal Maneweaver");
				SendQuickMenu(4336);
			}break;
			
		case 22: // Tailoring
			{
				SendQuickMenu(4337);
			}break;
        }
    }
};

void SetupTeldrassil_Guard(ScriptMgr * mgr)
{
	GossipScript * teldra = (GossipScript*) new TeldrassilGuard();
	mgr->register_gossip_script(3571, teldra);			// Teldrassil Sentinel
}