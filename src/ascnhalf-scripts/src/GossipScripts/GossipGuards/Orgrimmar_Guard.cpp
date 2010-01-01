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

class OrgrimmarGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);
        Menu->AddItem(0, "The bank", 1);
        Menu->AddItem(0, "The wind rider master", 2);
        Menu->AddItem(0, "The guild master", 3);
        Menu->AddItem(0, "The inn", 4);
        Menu->AddItem(0, "The mailbox", 5);
        Menu->AddItem(0, "The auction house", 6);    
        Menu->AddItem(0, "The zeppelin master", 7);
        Menu->AddItem(0, "The weapon master", 8);
        Menu->AddItem(0, "The stable master", 9);
        Menu->AddItem(0, "The officers' lounge", 10);
        Menu->AddItem(0, "The battlemaster", 11);
        Menu->AddItem(0, "A class trainer", 12);
        Menu->AddItem(0, "A profession trainer", 13);
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
            SendQuickMenu(2554);
            Plr->Gossip_SendPOI(1631.51, -4375.33, 7, 6, 0, "Bank of Orgrimmar");
            break;

        case 2:     // The wind rider master
            SendQuickMenu(2555);
            Plr->Gossip_SendPOI(1676.6, -4332.72, 7, 6, 0, "The Sky Tower");
            break;

        case 3:     // The guild master
            SendQuickMenu(2556);
            Plr->Gossip_SendPOI(1576.93, -4294.75, 7, 6, 0, "Horde Embassy");
            break;

        case 4:     // The inn
            SendQuickMenu(2557);
            Plr->Gossip_SendPOI(1644.51, -4447.27, 7, 6, 0, "Orgrimmar Inn");
            break;

        case 5:     // The mailbox
            SendQuickMenu(2558);
            Plr->Gossip_SendPOI(1622.53, -4388.79, 7, 6, 0, "Orgrimmar Mailbox");
            break;

        case 6:     // The auction house
            SendQuickMenu(3075);
            Plr->Gossip_SendPOI(1679.21, -4450.1, 7, 6, 0, "Orgrimmar Auction House");
			break;

        case 7:     // The zeppelin master
            SendQuickMenu(3173);
            Plr->Gossip_SendPOI(1337.36, -4632.7, 7, 6, 0, "Orgrimmar Zeppelin Tower");
            break;

        case 8:     // The weapon master
            SendQuickMenu(4519);
            Plr->Gossip_SendPOI(2092.56, -4823.95, 7, 6, 0, "Sayoc & Hanashi");
            break;

	    case 9:     // The stable master
			SendQuickMenu(5974);
            Plr->Gossip_SendPOI(2133.12, -4663.93, 7, 6, 0, "Xon'cha");
            break;

        case 10:    // The officers' lounge
			SendQuickMenu(7046);
			Plr->Gossip_SendPOI(1633.56, -4249.37, 7, 6, 0, "Hall of Legends");
            break;

        case 11:    // The battlemaster
			SendQuickMenu(7521);
			Plr->Gossip_SendPOI(1990.41, -4794.15, 7, 6, 0, "Battlemasters Orgrimmar");
            break;

        case 12:    // A class trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2599, Plr);
                Menu->AddItem( 0, "Hunter"       , 14);
                Menu->AddItem( 0, "Mage"         , 15);
                Menu->AddItem( 0, "Priest"       , 16);
                Menu->AddItem( 0, "Shaman"       , 17);
                Menu->AddItem( 0, "Rogue"        , 18);
                Menu->AddItem( 0, "Warlock"      , 19);
                Menu->AddItem( 0, "Warrior"      , 20);
                Menu->AddItem( 0, "Paladin"      , 21);
                Menu->SendTo(Plr);
            }break;

        case 13:    // A profession trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2594, Plr);
                Menu->AddItem( 0, "Alchemy"           , 22);
                Menu->AddItem( 0, "Blacksmithing"     , 23);
                Menu->AddItem( 0, "Cooking"           , 24);
                Menu->AddItem( 0, "Enchanting"        , 25);
                Menu->AddItem( 0, "Engineering"       , 26);
                Menu->AddItem( 0, "First Aid"         , 27);
                Menu->AddItem( 0, "Fishing"           , 28);
                Menu->AddItem( 0, "Herbalism"         , 29);
                Menu->AddItem( 0, "Leatherworking"    , 30);
                Menu->AddItem( 0, "Mining"            , 31);
                Menu->AddItem( 0, "Skinning"          , 32);
                Menu->AddItem( 0, "Tailoring"         , 33);
                Menu->SendTo(Plr);
            }break;

            ////////////////
            // Class trainer submenu
            ////////

        case 14: //Hunter
            {
                Plr->Gossip_SendPOI(2114.84, -4625.31, 7, 6, 0, "Orgrimmar Hunter's Hall");
                SendQuickMenu(2559);
            }break;

        case 15: //Mage
            {
                Plr->Gossip_SendPOI(1451.26, -4223.33, 7, 6, 0, "Darkbriar Lodge");
                SendQuickMenu(2560);
            }break;

        case 16: //Priest
            {
                Plr->Gossip_SendPOI(1442.21, -4183.24, 7, 6, 0, "Spirit Lodge");
                SendQuickMenu(2561);
            }break;

        case 17: //Shaman
            {
                Plr->Gossip_SendPOI(1925.34, -4181.89, 7, 6, 0, "Thrall's Fortress");
                SendQuickMenu(2562);
            }break;

        case 18: //Rogue
            {
                Plr->Gossip_SendPOI(1773.39, -4278.97, 7, 6, 0, "Shadowswift Brotherhood");
                SendQuickMenu(2563);
            }break;

        case 19: //Warlock
            {
                Plr->Gossip_SendPOI(1849.57, -4359.68, 7, 6, 0, "Darkfire Enclave");
                SendQuickMenu(2564);
            }break;

        case 20: //Warrior
            {
                Plr->Gossip_SendPOI(1983.92, -4794.2, 7, 6, 0, "Hall of the Brave");
                SendQuickMenu(2565);
            }break;

		case 21: //Paladin
            {
                Plr->Gossip_SendPOI(1937.53, -4141.0, 7, 6, 0, "Thrall's Fortress");
                SendQuickMenu(2566);
            }break;

        case 22: //Alchemy
            {
                Plr->Gossip_SendPOI(1955.17, -4475.79, 7, 6, 0, "Yelmak's Alchemy and Potions");
                SendQuickMenu(2497);
            }break;

        case 23: //Blacksmithing
            {
                Plr->Gossip_SendPOI(2054.34, -4831.85, 7, 6, 0, "The Burning Anvil");
                SendQuickMenu(2499);
            }break;

        case 24: //Cooking
            {
                Plr->Gossip_SendPOI(1780.96, -4481.31, 7, 6, 0, "Borstan's Firepit");
                SendQuickMenu(2500);
            }break;

        case 25: //Enchanting
            {
                Plr->Gossip_SendPOI(1917.5, -4434.95, 7, 6, 0, "Godan's Runeworks");
                SendQuickMenu(2501);
            }break;

        case 26: //Engineering
            {
                Plr->Gossip_SendPOI(2038.45, -4744.75, 7, 6, 0, "Nogg's Machine Shop");
                SendQuickMenu(2653);
            }break;

        case 27: //First Aid
            {
                Plr->Gossip_SendPOI(1485.21, -4160.91, 7, 6, 0, "Survival of the Fittest");
                SendQuickMenu(2502);
            }break;

        case 28: //Fishing
            {
                Plr->Gossip_SendPOI(1994.15, -4655.7, 7, 6, 0, "Lumak's Fishing");
                SendQuickMenu(2503);
            }break;

        case 29: //Herbalism
            {
                Plr->Gossip_SendPOI(1898.61, -4454.93, 7, 6, 0, "Jandi's Arboretum");
                SendQuickMenu(2504);
            }break;

        case 30: //Leatherworking
            {
                Plr->Gossip_SendPOI(1852.82, -4562.31, 7, 6, 0, "Kodohide Leatherworkers");
                SendQuickMenu(2513);
            }break;

        case 31: //Mining
            {
                Plr->Gossip_SendPOI(2029.79, -4704, 7, 6, 0, "Red Canyon Mining");
                SendQuickMenu(2515);
            }break;

        case 32: //Skinning
            {
                Plr->Gossip_SendPOI(1852.82, -4562.31, 7, 6, 0, "Kodohide Leatherworkers");
                SendQuickMenu(2516);        
            }break;

		case 33: //Tailoring
            {
                Plr->Gossip_SendPOI(1802.66, -4560.66, 7, 6, 0, "Magar's Cloth Goods");
                SendQuickMenu(2518);
            }break;
        }
    }
};

void SetupOrgrimmar_Guard(ScriptMgr * mgr)
{
	GossipScript * ogri = (OrgrimmarGuard*) new OrgrimmarGuard();
	mgr->register_gossip_script(3296, ogri);	        // Orgrimmar Grunt
}