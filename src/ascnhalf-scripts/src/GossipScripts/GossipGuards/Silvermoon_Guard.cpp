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

class SilvermoonGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9316, Plr);

        Menu->AddItem(0, "Auction House"		, 1);
        Menu->AddItem(0, "The Bank"				, 2);
		Menu->AddItem(0, "Dragonhawk Master"	, 3);
        Menu->AddItem(0, "Guild Master"			, 4);
        Menu->AddItem(0, "The Inn"				, 5);
        Menu->AddItem(0, "Mailbox"				, 6);    
        Menu->AddItem(0, "Stable Master"		, 7);
        Menu->AddItem(0, "Weapon Master"		, 8);
        Menu->AddItem(0, "Battlemaster"			, 9);
        Menu->AddItem(0, "Class Trainer"		, 10);
        Menu->AddItem(0, "Profession Trainer"	, 11);
        Menu->AddItem(0, "Mana Loom"			, 12);
		Menu->AddItem(0, "Lexicon of Power"		, 40);

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
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9317, Plr);
            Menu->AddItem(0, "To the west."  , 13);
            Menu->AddItem(0, "To the east."    , 14);
            Menu->SendTo(Plr);
            break;

        case 2:     // The Bank
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9320, Plr);
            Menu->AddItem(0, "The west."  , 15);
            Menu->AddItem(0, "The east."    , 16);
            Menu->SendTo(Plr);
            break;

		case 3:     // Dragonhawk Master
            SendQuickMenu(9323);
            Plr->Gossip_SendPOI(9378.45, -7163.94, 7, 6, 0, "Silvermoon City, Flight Master");
            break;

        case 4:     // Guild Master
            SendQuickMenu(9324);
            Plr->Gossip_SendPOI(9480.75, -7345.587, 7, 6, 0, "Silvermoon City, Guild Master");
            break;

        case 5:     // The Inn
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9325, Plr);
            Menu->AddItem(0, "The Silvermoon City Inn."  , 17);
            Menu->AddItem(0, "The Wayfarer's Rest tavern."    , 18);
            Menu->SendTo(Plr);
            break;

        case 6:     // Mailbox
            SendQuickMenu(9326);
            Plr->Gossip_SendPOI(9743.078, -7466.4, 7, 6, 0, "Silvermoon City, Mailbox");
            break;

        case 7:     // Stable Master
            SendQuickMenu(9327);
            Plr->Gossip_SendPOI(9904.95, -7404.31, 7, 6, 0, "Silvermoon City, Stable Master");
            break;

        case 8:     // Weapon Master
            SendQuickMenu(9328);
            Plr->Gossip_SendPOI(9841.17, -7505.13, 7, 6, 0, "Silvermoon City, Weapon Master");
            break;

	    case 9:     // Battlemasters
			SendQuickMenu(9329);
            Plr->Gossip_SendPOI(9850.74, -7563.84, 7, 6, 0, "Silvermoon City, Battlemasters");
            break;

        case 10:    // Class Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9331, Plr);
                Menu->AddItem( 0, "Druid"       , 19);
                Menu->AddItem( 0, "Hunter"      , 20);
                Menu->AddItem( 0, "Mage"        , 21);
                Menu->AddItem( 0, "Paladin"     , 22);
                Menu->AddItem( 0, "Priest"      , 23);
                Menu->AddItem( 0, "Rogue"       , 24);
                Menu->AddItem( 0, "Warlock"     , 25);
                Menu->SendTo(Plr);
            }break;

        case 11:    // Profession Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9338, Plr);
                Menu->AddItem( 0, "Alchemy"           , 26);
                Menu->AddItem( 0, "Blacksmithing"     , 27);
                Menu->AddItem( 0, "Cooking"           , 28);
                Menu->AddItem( 0, "Enchanting"        , 29);
                Menu->AddItem( 0, "Engineering"       , 30);
                Menu->AddItem( 0, "First Aid"         , 31);
                Menu->AddItem( 0, "Fishing"           , 32);
				Menu->AddItem( 0, "Herbalism"         , 33);
				Menu->AddItem( 0, "Inscription"       , 34);
				Menu->AddItem( 0, "Jewelcrafting"     , 35);
                Menu->AddItem( 0, "Leatherworking"    , 36);
                Menu->AddItem( 0, "Mining"            , 37);
                Menu->AddItem( 0, "Skinning"          , 38);
                Menu->AddItem( 0, "Tailoring"         , 39);
                Menu->SendTo(Plr);
            }break;

		case 12: //Mana Loom
            {
                Plr->Gossip_SendPOI(9751.013, -7074.85, 7, 6, 0, "Silvermoon City, Mana Loom");
                SendQuickMenu(10502);
            }break;

        case 13: //To the west - Auction House no. 1
            {
                Plr->Gossip_SendPOI(9649.429, -7134.027, 7, 6, 0, "Silvermoon City, Auction House");
                SendQuickMenu(9318);
            }break;

        case 14: //To the east - Auction House no. 2
            {
                Plr->Gossip_SendPOI(9682.864, -7515.786, 7, 6, 0, "Silvermoon City, Auction House");
                SendQuickMenu(9319);
            }break;

        case 15:     // The bank - The west.
            SendQuickMenu(9321);
            Plr->Gossip_SendPOI(9522.104, -7208.878, 7, 6, 0, "Silvermoon City, Bank");
            break;

        case 16:     // The bank - The east.
            SendQuickMenu(9322);
            Plr->Gossip_SendPOI(9791.07, -7488.041, 7, 6, 0, "Silvermoon City, Bank");
            break;

        case 17: //The Silvermoon City Inn
            {
                Plr->Gossip_SendPOI(9677.113, -7367.575, 7, 6, 0, "Silvermoon City, Inn");
                SendQuickMenu(9325);
            }break;

        case 18: //The Wayfarer's Rest tavern
            {
                Plr->Gossip_SendPOI(9562.813, -7218.63, 7, 6, 0, "Silvermoon City, Inn");
                SendQuickMenu(9603);
            }break;

        case 19: //Druid
            {
                Plr->Gossip_SendPOI(9700.55, -7262.57, 7, 6, 0, "Silvermoon City, Druid Trainer");
                SendQuickMenu(9330);
            }break;

        case 20: //Hunter
            {
                Plr->Gossip_SendPOI(9930.568, -7412.115, 7, 6, 0, "Silvermoon City, Hunter Trainer");
                SendQuickMenu(9332);
            }break;

        case 21: //Mage
            {
                Plr->Gossip_SendPOI(9996.914, -7104.803, 7, 6, 0, "Silvermoon City, Mage Trainer");
                SendQuickMenu(9333);
            }break;

        case 22: //Paladin
            {
                Plr->Gossip_SendPOI(9850.22, -7516.93, 7, 6, 0, "Silvermoon City, Paladin Trainer");
                SendQuickMenu(9334);
            }break;

        case 23: //Priest
            {
                Plr->Gossip_SendPOI(9935.37, -7131.14, 7, 6, 0, "Silvermoon City, Priest Trainer");
                SendQuickMenu(9335);
            }break;

        case 24: //Rogue
            {
                Plr->Gossip_SendPOI(9739.88, -7374.33, 7, 6, 0, "Silvermoon City, Rogue Trainer");
                SendQuickMenu(9336);
            }break;

        case 25: //Warlock
            {
                Plr->Gossip_SendPOI(9803.052, -7316.967, 7, 6, 0, "Silvermoon City, Warlock Trainer");
                SendQuickMenu(9337);
            }break;

        case 26: //Alchemy
            {
                Plr->Gossip_SendPOI(10000.9, -7216.63, 7, 6, 0, "Silvermoon City, Alchemy");
                SendQuickMenu(9339);
            }break;

        case 27: //Blacksmithing
            {
                Plr->Gossip_SendPOI(9841.43, -7361.53, 7, 6, 0, "Silvermoon City, Blacksmithing");
                SendQuickMenu(9340);
            }break;

        case 28: //Cooking
            {
                Plr->Gossip_SendPOI(9577.26, -7243.6, 7, 6, 0, "Silvermoon City, Cooking");
                SendQuickMenu(9624);
            }break;

        case 29: //Enchanting
            {
                Plr->Gossip_SendPOI(9962.57, -7246.18, 7, 6, 0, "Silvermoon City, Enchanting");
                SendQuickMenu(9341);
            }break;

        case 30: //Engineering
            {
                Plr->Gossip_SendPOI(9808.85, -7287.31, 7, 6, 0, "Silvermoon City, Engineering");
                SendQuickMenu(9342);
            }break;

        case 31: //First Aid
            {
                Plr->Gossip_SendPOI(9588.61, -7337.526, 7, 6, 0, "Silvermoon City, First Aid");
                SendQuickMenu(9343);
            }break;

        case 32: //Fishing
            {
                Plr->Gossip_SendPOI(9601.97, -7332.34, 7, 6, 0, "Silvermoon City, Fishing");
                SendQuickMenu(9344);
            }break;

        case 33: //Herbalism
            {
                Plr->Gossip_SendPOI(9996.96, -7208.39, 7, 6, 0, "Silvermoon City, Herbalism");
                SendQuickMenu(9345);
            }break;
		case 34: //Inscription
            {
                Plr->Gossip_SendPOI(9957.12, -7242.85, 7, 6, 0, "Silvermoon City, Inscription");
                SendQuickMenu(13893);
            }break;

        case 35: //Jewelcrafting
            {
                Plr->Gossip_SendPOI(9552.8, -7502.12, 7, 6, 0, "Silvermoon City, Jewelcrafting");
                SendQuickMenu(9346);
            }break;

        case 36: //Leatherworking
            {
                Plr->Gossip_SendPOI(9502.486, -7425.51, 7, 6, 0, "Silvermoon City, Leatherworking");
                SendQuickMenu(9347);
            }break;

        case 37: //Mining
            {
                Plr->Gossip_SendPOI(9813.73, -7360.19, 7, 6, 0, "Silvermoon City, Mining");
                SendQuickMenu(9348);
            }break;

        case 38: //Skinning
            {
                Plr->Gossip_SendPOI(9513.37, -7429.4, 7, 6, 0, "Silvermoon City, Skinning");
                SendQuickMenu(9349);
            }break;

		case 39: //Tailoring
            {
                Plr->Gossip_SendPOI(9727.56, -7086.65, 7, 6, 0, "Silvermoon City, Tailoring");
                SendQuickMenu(9350);
            }break;
		case 40: //Lexicon of Power
            {
                Plr->Gossip_SendPOI(9957.12, -7242.85, 7, 6, 0, "Silvermoon City, Inscription");
                SendQuickMenu(14174);
            }break;
        }
    }
};

void SetupSilvermoon_Guard(ScriptMgr * mgr)
{
	GossipScript * silver = (SilvermoonGuard*) new SilvermoonGuard();
	mgr->register_gossip_script(16222, silver);			// Silvermoon City Guardian
}