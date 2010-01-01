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

class ExodarGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9551, Plr);
        Menu->AddItem(0, "Auction House"		, 1);
        Menu->AddItem(0, "The Bank"				, 2);
        Menu->AddItem(0, "Hippogryph Master"	, 3);
		Menu->AddItem(0, "Guild Master"			, 4);
        Menu->AddItem(0, "The Inn"				, 5);    
        Menu->AddItem(0, "Mailbox"				, 6);
        Menu->AddItem(0, "Stable Master"		, 7);
        Menu->AddItem(0, "Weapon Master"		, 8);
        Menu->AddItem(0, "Battlemasters"		, 9);
        Menu->AddItem(0, "Class Trainer"		, 10);
        Menu->AddItem(0, "Profession Trainer"	, 11);
		Menu->AddItem(0, "Lexicon of Power"		, 34);
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

        case 1:     // Auction House
            SendQuickMenu(9528);
            Plr->Gossip_SendPOI(-4013.82, -11729.64, 7, 6, 0, "Exodar, Auctioneer");
            break;

        case 2:     // The Bank
            SendQuickMenu(9529);
            Plr->Gossip_SendPOI(-3923.89, -11544.5, 7, 6, 0, "Exodar, bank");
            break;

        case 3:     // Hippogryph Master
            SendQuickMenu(9530);
            Plr->Gossip_SendPOI(-4058.45, -11789.7, 7, 6, 0, "Exodar, Hippogryph Master");
            break;

        case 4:     // Guild Master
            SendQuickMenu(9539);
            Plr->Gossip_SendPOI(-4093.38, -11630.39, 7, 6, 0, "Exodar, Guild Master");
            break;

        case 5:     // The Inn
            SendQuickMenu(9545);
            Plr->Gossip_SendPOI(-3765.34, -11695.8, 7, 6, 0, "Exodar, Inn");
            break;

        case 6:     // Mailbox
            SendQuickMenu(10254);
            Plr->Gossip_SendPOI(-3913.75, -11606.83, 7, 6, 0, "Exodar, Mailbox");
            break;

        case 7:     // Stable Master
            SendQuickMenu(9558);
            Plr->Gossip_SendPOI(-3787.01, -11702.7, 7, 6, 0, "Exodar, Stable Master");
            break;

        case 8:     // Weapon Master
            SendQuickMenu(9565);
            Plr->Gossip_SendPOI(-4215.68, -11628.9, 7, 6, 0, "Exodar, Weapon Master");
            break;

	    case 9:     // Battlemasters
            Plr->Gossip_SendPOI(-3999.82, -11368.33, 7, 6, 0, "Exodar, Battlemasters");
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9531, Plr);
            Menu->AddItem(0, "Arena Battlemaster"  , 12);
            Menu->SendTo(Plr);
            break;

        case 10:    // Class Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9533, Plr);
                Menu->AddItem( 0, "Druid"       , 13);
                Menu->AddItem( 0, "Hunter"      , 14);
                Menu->AddItem( 0, "Mage"        , 15);
                Menu->AddItem( 0, "Paladin"     , 16);
                Menu->AddItem( 0, "Priest"      , 17);
                Menu->AddItem( 0, "Shaman"      , 18);
                Menu->AddItem( 0, "Warrior"     , 19);
                Menu->SendTo(Plr);
            }break;

        case 11:    // Profession Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9555, Plr);
                Menu->AddItem( 0, "Alchemy"           , 20);
                Menu->AddItem( 0, "Blacksmithing"     , 21);
                Menu->AddItem( 0, "Enchanting"        , 22);
                Menu->AddItem( 0, "Engineering"       , 23);
                Menu->AddItem( 0, "First Aid"         , 24);
                Menu->AddItem( 0, "Fishing"           , 25);
                Menu->AddItem( 0, "Herbalism"         , 26);
				Menu->AddItem( 0, "Inscription"       , 27);
				Menu->AddItem( 0, "Jewelcrafting"     , 28);
                Menu->AddItem( 0, "Leatherworking"    , 29);
                Menu->AddItem( 0, "Mining"            , 30);
                Menu->AddItem( 0, "Skinning"          , 31);
                Menu->AddItem( 0, "Tailoring"         , 32);
                Menu->AddItem( 0, "Cooking"           , 33);
                Menu->SendTo(Plr);
            }break;

            //////////////////
            // Battlemaster submenu
            ////////

		case 12://Arena Battlemaster Exodar
            {
                Plr->Gossip_SendPOI(-3725.25, -11688.3, 7, 6, 0, "Arena Battlemaster Exodar");
                SendQuickMenu(10223);
            }break;

        case 13: //Druid
            {
                Plr->Gossip_SendPOI(-4274.81, -11495.3, 7, 6, 0, "Exodar, Druid Trainer"); 
                SendQuickMenu(9534);
            }break;

        case 14: //Hunter
            {
                Plr->Gossip_SendPOI(-4229.36, -11563.36, 7, 6, 0, "Exodar, Hunter Trainers");
                SendQuickMenu(9544);
            }break;

        case 15: //Mage
            {
                Plr->Gossip_SendPOI(-4048.8, -11559.02, 7, 6, 0, "Exodar, Mage Trainers");
                SendQuickMenu(9550);
            }break;

        case 16: //Paladin
            {
                Plr->Gossip_SendPOI(-4176.57, -11476.46, 7, 6, 0, "Exodar, Paladin Trainers");
                SendQuickMenu(9553);
            }break;

        case 17: //Priest
            {
                Plr->Gossip_SendPOI(-3972.38, -11483.2, 7, 6, 0, "Exodar, Priest Trainers");
                SendQuickMenu(9554);
            }break;

        case 18: //Shaman
            {
                Plr->Gossip_SendPOI(-3843.8, -11390.75, 7, 6, 0, "Exodar, Shaman Trainer");
                SendQuickMenu(9556);
            }break;

        case 19: //Warrior
            {
                Plr->Gossip_SendPOI(-4191.11, -11650.45, 7, 6, 0, "Exodar, Warrior Trainers");
                SendQuickMenu(9562);
            }break;

        case 20: //Alchemy
            {
                Plr->Gossip_SendPOI(-4042.37, -11366.3, 7, 6, 0, "Exodar, Alchemist Trainers");
                SendQuickMenu(9527);
            }break;

        case 21: //Blacksmithing
            {
                Plr->Gossip_SendPOI(-4232.4, -11705.23, 7, 6, 0, "Exodar, Blacksmithing Trainers");
                SendQuickMenu(9532);
            }break;

        case 22: //Enchanting
            {
                Plr->Gossip_SendPOI(-3889.3, -11495, 7, 6, 0, "Exodar, Enchanters");
                SendQuickMenu(9535);
            }break;

        case 23: //Engineering
            {
                Plr->Gossip_SendPOI(-4257.93, -11636.53, 7, 6, 0, "Exodar, Engineering");
                SendQuickMenu(9536);
            }break;

        case 24: //First Aid
            {
                Plr->Gossip_SendPOI(-3766.05, -11481.8, 7, 6, 0, "Exodar, First Aid Trainer");
                SendQuickMenu(9537);
            }break;

        case 25: //Fishing
            {
                Plr->Gossip_SendPOI(-3726.64, -11384.43, 7, 6, 0, "Exodar, Fishing Trainer");
                SendQuickMenu(9538);
            }break;

        case 26: //Herbalism
            {
                Plr->Gossip_SendPOI(-4052.5, -11356.6, 7, 6, 0, "Exodar, Herbalism Trainer");
                SendQuickMenu(9543);
            }break;

		case 27: //Inscription
            {
                Plr->Gossip_SendPOI(-3889.3, -11495, 7, 6, 0, "Exodar, Inscription");
                SendQuickMenu(13887);
            }break;

        case 28: //Jewelcrafting
            {
                Plr->Gossip_SendPOI(-3786.27, -11541.33, 7, 6, 0, "Exodar, Jewelcrafters");
                SendQuickMenu(9547);
            }break;

        case 29: //Leatherworking
            {
                Plr->Gossip_SendPOI(-4134.42, -11772.93, 7, 6, 0, "Exodar, Leatherworking");
                SendQuickMenu(9549);
            }break;

        case 30: //Mining
            {
                Plr->Gossip_SendPOI(-4220.31, -11694.29, 7, 6, 0, "Exodar, Mining Trainers");
                SendQuickMenu(9552);
            }break;

        case 31: //Skinning
            {
                Plr->Gossip_SendPOI(-4134.97, -11760.5, 7, 6, 0, "Exodar, Skinning Trainer");
                SendQuickMenu(9557);
            }break;

		case 32: //Tailoring
            {
                Plr->Gossip_SendPOI(-4095.78, -11746.9, 7, 6, 0, "Exodar, Tailors");
                SendQuickMenu(9350);
            }break;

        case 33: //Cooking
            {
                Plr->Gossip_SendPOI(-3799.69, -11650.51, 7, 6, 0, "Exodar, Cook");
                SendQuickMenu(9559);
            }break;

		case 34: //Lexicon of Power
            {
                Plr->Gossip_SendPOI(-3889.3, -11495, 7, 6, 0, "Exodar, Inscription");
                SendQuickMenu(14174);
            }break;
        }
    }
};

void SetupExodar_Guard(ScriptMgr * mgr)
{
	GossipScript * exodar = (ExodarGuard*) new ExodarGuard();
	mgr->register_gossip_script(16733, exodar);	        // Exodar Peacekeeper
	mgr->register_gossip_script(20674, exodar);	        // Shield of Velen
}