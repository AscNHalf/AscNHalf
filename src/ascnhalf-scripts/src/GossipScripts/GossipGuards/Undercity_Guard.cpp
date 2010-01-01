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

class UndercityGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3543, Plr);
		
		Menu->AddItem(0, "The bank", 1);
		Menu->AddItem(0, "The bat handler", 2);
		Menu->AddItem(0, "The guild master", 3);
		Menu->AddItem(0, "The inn", 4);
		Menu->AddItem(0, "The mailbox", 5);
		Menu->AddItem(0, "The auction house", 6);
		Menu->AddItem(0, "The zeppelin master", 7);
		Menu->AddItem(0, "The weapon master", 8);
		Menu->AddItem(0, "The stable master", 9);
		Menu->AddItem(0, "The battlemaster", 10);
		Menu->AddItem(0, "A class trainer", 11);
		Menu->AddItem(0, "A profession trainer", 12);
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
			
		case 1:     // The bank
            SendQuickMenu(3514);
            Plr->Gossip_SendPOI(1595.64, 232.45, 7, 6, 0, "Undercity Bank");
            break;

        case 2:     // The bat handler
            SendQuickMenu(3515);
            Plr->Gossip_SendPOI(1565.9, 271.43, 7, 6, 0, "Undercity Bat Handler");
            break;

        case 3:     // The guild master
            SendQuickMenu(3516);
            Plr->Gossip_SendPOI(1594.17, 205.57, 7, 6, 0, "Undercity Guild Master");
            break;

        case 4:     // The inn
            SendQuickMenu(3517);
            Plr->Gossip_SendPOI(1639.43, 220.99, 7, 6, 0, "Undercity Inn");
            break;

        case 5:     // The mailbox
            SendQuickMenu(3518);
            Plr->Gossip_SendPOI(1632.68, 219.4, 7, 6, 0, "Undercity Mailbox");
            break;

        case 6:     // The auction house
            SendQuickMenu(3520);
            Plr->Gossip_SendPOI(1647.9, 258.49, 7, 6, 0, "Undercity Auction House");
            break;

        case 7:     // The zeppelin master
            SendQuickMenu(3519);
            Plr->Gossip_SendPOI(2059, 274.86, 7, 6, 0, "Undercity Zeppelin");
            break;

        case 8:     // The weapon master
            SendQuickMenu(4521);
            Plr->Gossip_SendPOI(1670.31, 324.66, 7, 6, 0, "Archibald");
            break;

        case 9:     // The stable master
            SendQuickMenu(5979);
            Plr->Gossip_SendPOI(1634.18, 226.76, 7, 6, 0, "Anya Maulray");
            break;

        case 10:    // The battlemaster
            {
				SendQuickMenu(7527);
				Plr->Gossip_SendPOI(1300.33, 350.92, 7, 6, 0, "Battlemasters Undercity");
            }break;

        case 11:    // A class trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3542, Plr);
                Menu->AddItem( 0, "Mage"		 , 13);
                Menu->AddItem( 0, "Paladin"      , 14);
                Menu->AddItem( 0, "Priest"       , 15);
                Menu->AddItem( 0, "Rogue"        , 16);
                Menu->AddItem( 0, "Warlock"      , 17);
                Menu->AddItem( 0, "Warrior"      , 18);
                Menu->SendTo(Plr);
            }break;

        case 12:    // A profession trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3541, Plr);
                Menu->AddItem( 0, "Alchemy"           , 19);
                Menu->AddItem( 0, "Blacksmithing"     , 20);
                Menu->AddItem( 0, "Cooking"           , 21);
                Menu->AddItem( 0, "Enchanting"        , 22);
                Menu->AddItem( 0, "Engineering"       , 23);
                Menu->AddItem( 0, "First Aid"         , 24);
                Menu->AddItem( 0, "Fishing"           , 25);
                Menu->AddItem( 0, "Herbalism"         , 26);
                Menu->AddItem( 0, "Leatherworking"    , 27);
                Menu->AddItem( 0, "Mining"            , 28);
                Menu->AddItem( 0, "Skinning"          , 29);
                Menu->AddItem( 0, "Tailoring"         , 30);
                Menu->SendTo(Plr);
            }break;

            ////////////////
            // Class trainer submenu
            ////////

        case 13: //Mage
            {
                Plr->Gossip_SendPOI(1781, 53, 7, 6, 0, "Undercity Mage Trainers");
                SendQuickMenu(3513);
            }break;

        case 14: //Paladin
            {
                Plr->Gossip_SendPOI(1298.98, 316.51, 7, 6, 0, "Champion Cyssa Downrose");
                SendQuickMenu(3521);
            }break;

        case 15: //Priest
            {
                Plr->Gossip_SendPOI(1758.33, 401.5, 7, 6, 0, "Undercity Priest Trainers");
                SendQuickMenu(3521);
            }break;

        case 16: //Rogue
            {
                Plr->Gossip_SendPOI(1418.56, 65, 7, 6, 0, "Undercity Rogue Trainers");
                SendQuickMenu(3526);
            }break;

        case 17: //Warlock
            {
                Plr->Gossip_SendPOI(1780.92, 53.16, 7, 6, 0, "Undercity Warlock Trainers");
                SendQuickMenu(3526);
            }break;

        case 18: //Warrior
            {
                Plr->Gossip_SendPOI(1775.59, 418.19, 7, 6, 0, "Undercity Warrior Trainers");
                SendQuickMenu(3527);
            }break;

        case 19: //Alchemy
            {
                Plr->Gossip_SendPOI(1419.82, 417.19, 7, 6, 0, "The Apothecarium");
                SendQuickMenu(3528);
            }break;

        case 20: //Blacksmithing
            {
                Plr->Gossip_SendPOI(1696, 285, 7, 6, 0, "Undercity Blacksmithing Trainer");
                SendQuickMenu(3529);
            }break;

        case 21: //Cooking
            {
                Plr->Gossip_SendPOI(1596.34, 274.68, 7, 6, 0, "Undercity Cooking Trainer");
                SendQuickMenu(3530);
            }break;

        case 22: //Enchanting
            {
                Plr->Gossip_SendPOI(1488.54, 280.19, 7, 6, 0, "Undercity Enchanting Trainer");
                SendQuickMenu(3531);
            }break;

        case 23: //Engineering
            {
                Plr->Gossip_SendPOI(1408.58, 143.43, 7, 6, 0, "Undercity Engineering Trainer");
                SendQuickMenu(3532);
            }break;

        case 24: //First Aid
            {
                Plr->Gossip_SendPOI(1519.65, 167.19, 7, 6, 0, "Undercity First Aid Trainer");
                SendQuickMenu(3533);
            }break;

        case 25: //Fishing
            {
                Plr->Gossip_SendPOI(1679.9, 89, 7, 6, 0, "Undercity Fishing Trainer");
                SendQuickMenu(3534);
            }break;

        case 26: //Herbalism
            {
                Plr->Gossip_SendPOI(1558, 349.36, 7, 6, 0, "Undercity Herbalism Trainer");
                SendQuickMenu(3535);
            }break;

        case 27: //Leatherworking
            {
                Plr->Gossip_SendPOI(1498.76, 196.43, 7, 6, 0, "Undercity Leatherworking Trainer");
                SendQuickMenu(3536);
            }break;

        case 28: //Mining
            {
                Plr->Gossip_SendPOI(1642.88, 335.58, 7, 6, 0, "Undercity Mining Trainer");
                SendQuickMenu(3537);
            }break;

        case 29: //Skinning
            {
                Plr->Gossip_SendPOI(1498.6, 196.46, 7, 6, 0, "Undercity Skinning Trainer");
                SendQuickMenu(3538);
            }break;

        case 30: //Tailoring
            {
                Plr->Gossip_SendPOI(1689.55, 193, 7, 6, 0, "Undercity Tailoring Trainer");
                SendQuickMenu(3539);
            }break;
        }
    }
};

void SetupUndercity_Guard(ScriptMgr * mgr)
{
	GossipScript * under = (GossipScript*) new UndercityGuard();
	mgr->register_gossip_script(5624, under);			// Undercity Guardian
}