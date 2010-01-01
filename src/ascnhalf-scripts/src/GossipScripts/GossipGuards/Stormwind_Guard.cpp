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

class StormwindGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 933, Plr);

        Menu->AddItem(0, "Auction House"		, 1);
        Menu->AddItem(0, "Bank of Stormwind"	, 2);
		Menu->AddItem(0, "Stormwind Harbor"		, 3);
        Menu->AddItem(0, "Deeprun Tram"			, 4);
        Menu->AddItem(0, "The Inn"				, 5);
        Menu->AddItem(0, "Gryphon Master"		, 6);    
        Menu->AddItem(0, "Guild Master"			, 7);
        Menu->AddItem(0, "Mailbox"				, 8);
        Menu->AddItem(0, "Stable Master"		, 9);
        Menu->AddItem(0, "Weapons Trainer"		, 10);
        Menu->AddItem(0, "Officers' Lounge"		, 11);
        Menu->AddItem(0, "Battlemaster"			, 12);
		Menu->AddItem(0, "Barber"				, 13);
        Menu->AddItem(0, "Class Trainer"		, 14);
        Menu->AddItem(0, "Profession Trainer"	, 15);

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
            SendQuickMenu(3834);
            Plr->Gossip_SendPOI(-8811.46, 667.46, 7, 6, 0, "Stormwind Auction House");
            break;

        case 2:     // Bank of Stormwind
            SendQuickMenu(764);
            Plr->Gossip_SendPOI(-8916.87, 622.87, 7, 6, 0, "Stormwind Bank");
            break;

		case 3:     // Stormwind Harbor
            SendQuickMenu(13439);
            Plr->Gossip_SendPOI(-8634.77, 949.64, 7, 6, 0, "Stormwind Harbor");
            break;

        case 4:     // Deeprun Tram
            SendQuickMenu(3813);
            Plr->Gossip_SendPOI(-8378.88, 554.23, 7, 6, 0, "The Deeprun Tram");
            break;

        case 5:     // The Inn
            SendQuickMenu(3860);
            Plr->Gossip_SendPOI(-8869.0, 675.4, 7, 6, 0, "The Gilded Rose");
            break;

        case 6:     // Gryphon Master
            SendQuickMenu(879);
            Plr->Gossip_SendPOI(-8837.0, 493.5, 7, 6, 0, "Stormwind Gryphon Master");
            break;

        case 7:     // Guild Master
            SendQuickMenu(882);
            Plr->Gossip_SendPOI(-8894.0, 611.2, 7, 6, 0, "Stormwind Vistor`s Center");
            break;

        case 8:     // Mailbox
            SendQuickMenu(3861);
            Plr->Gossip_SendPOI(-8876.48, 649.18, 7, 6, 0, "Stormwind Mailbox");
            break;

        case 9:     // Stable Master
            SendQuickMenu(5984);
            Plr->Gossip_SendPOI(-8433.0, 554.7, 7, 6, 0, "Jenova Stoneshield");
            break;

        case 10:     // Weapons Master
            SendQuickMenu(4516);
            Plr->Gossip_SendPOI(-8797.0, 612.8, 7, 6, 0, "Woo Ping");
            break;

        case 11:    // Officers' Lounge
            SendQuickMenu(7047);
            Plr->Gossip_SendPOI(-8759.92, 399.69, 7, 6, 0, "Champions` Hall");
            break;

        case 12:    // Battlemaster
            {
			SendQuickMenu(10218);
            Plr->Gossip_SendPOI(-8393.62, 274.21, 7, 6, 0, "Battlemasters Stormwind");
            }break;

		case 13:     // Barber
            SendQuickMenu(13882);
            Plr->Gossip_SendPOI(-8743.15, 660.36, 7, 6, 0, "Stormwind Barber");
            break;

        case 14:    // Class Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 898, Plr);
				Menu->AddItem( 0, "Druid"      , 16);
                Menu->AddItem( 0, "Hunter"     , 17);
                Menu->AddItem( 0, "Mage"       , 18);
                Menu->AddItem( 0, "Paladin"    , 19);
                Menu->AddItem( 0, "Priest"     , 20);
                Menu->AddItem( 0, "Rogue"      , 21);
                Menu->AddItem( 0, "Shaman"     , 22);
                Menu->AddItem( 0, "Warlock"    , 23);
				Menu->AddItem( 0, "Warrior"    , 24);
                Menu->SendTo(Plr);
            }break;

        case 15:    // Profession Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 918, Plr);
                Menu->AddItem( 0, "Alchemy"           , 25);
                Menu->AddItem( 0, "Blacksmithing"     , 26);
                Menu->AddItem( 0, "Cooking"           , 27);
                Menu->AddItem( 0, "Enchanting"        , 28);
                Menu->AddItem( 0, "Engineering"       , 29);
                Menu->AddItem( 0, "First Aid"         , 30);
                Menu->AddItem( 0, "Fishing"           , 31);
                Menu->AddItem( 0, "Herbalism"         , 32);
				Menu->AddItem(0, "Inscription"		, 33);
                Menu->AddItem( 0, "Leatherworking"    , 34);
                Menu->AddItem( 0, "Mining"            , 35);
                Menu->AddItem( 0, "Skinning"          , 36);
                Menu->AddItem( 0, "Tailoring"         , 37);
                Menu->SendTo(Plr);
            }break;

            ////////////////
            // Class trainer submenu
            ////////

        case 16: //Druid
            {
                Plr->Gossip_SendPOI(-8751.0, 1124.5, 7, 6, 0, "The Park");
                SendQuickMenu(902);
            }break;

        case 17: //Hunter
            {
                Plr->Gossip_SendPOI(-8413.0, 541.5, 7, 6, 0, "Hunter Lodge");
                SendQuickMenu(905);
            }break;

        case 18: //Mage
            {
                Plr->Gossip_SendPOI(-9012.0, 867.6, 7, 6, 0, "Wizard`s Sanctum");
                SendQuickMenu(899);
            }break;

        case 19: //Paladin
            {
                Plr->Gossip_SendPOI(-8577.0, 881.7, 7, 6, 0, "Cathedral Of Light");
                SendQuickMenu(904);
            }break;

        case 20: //Priest
            {
                Plr->Gossip_SendPOI(-8512.0, 862.4, 7, 6, 0, "Cathedral Of Light");
                SendQuickMenu(903);
            }break;

        case 21: //Rogue
            {
                Plr->Gossip_SendPOI(-8753.0, 367.8, 7, 6, 0, "Stormwind - Rogue House");
                SendQuickMenu(900);
            }break;

        case 22: //Shaman
            {
				Plr->Gossip_SendPOI(-9031.54, 549.87, 7, 6, 0, "Farseer Umbrua");
                SendQuickMenu(10106);
            }break;

		case 23: //Warlock
            {
                Plr->Gossip_SendPOI(-8948.91, 998.35, 7, 6, 0, "The Slaughtered Lamb");
                SendQuickMenu(906);
            }break;

        case 24: //Warrior
            {
                Plr->Gossip_SendPOI(-8714.14, 334.96, 7, 6, 0, "Stormwind Barracks");
                SendQuickMenu(901);
            }break;

        case 25: //Alchemy
            {
                Plr->Gossip_SendPOI(-8988.0, 759.60, 7, 6, 0, "Alchemy Needs");
                SendQuickMenu(919);
            }break;

        case 26: //Blacksmithing
            {
                Plr->Gossip_SendPOI(-8424.0, 616.9, 7, 6, 0, "Therum Deepforge");
                SendQuickMenu(920);
            }break;

        case 27: //Cooking
            {
                Plr->Gossip_SendPOI(-8611.0, 364.6, 7, 6, 0, "Pig and Whistle Tavern");
                SendQuickMenu(921);
            }break;

        case 28: //Enchanting
            {
                Plr->Gossip_SendPOI(-8858.0, 803.7, 7, 6, 0, "Lucan Cordell");
                SendQuickMenu(941);
            }break;

        case 29: //Engineering
            {
                Plr->Gossip_SendPOI(-8347.0, 644.1, 7, 6, 0, "Lilliam Sparkspindle");
                SendQuickMenu(922);
            }break;

        case 30: //First Aid
            {
                Plr->Gossip_SendPOI(-8513.0, 801.8, 7, 6, 0, "Shaina Fuller");
                SendQuickMenu(923);
            }break;

        case 31: //Fishing
            {
                Plr->Gossip_SendPOI(-8803.0, 767.5, 7, 6, 0, "Arnold Leland");
                SendQuickMenu(940);
            }break;

        case 32: //Herbalism
            {
                Plr->Gossip_SendPOI(-8967.0, 779.5, 7, 6, 0, "Alchemy Needs");
                SendQuickMenu(924);
            }break;

		case 33: //Inscription
            {
                Plr->Gossip_SendPOI(-8853.33, 857.66, 7, 6, 0, "Stormwind Inscription");
                SendQuickMenu(13881);
            }break;

        case 34: //Leatherworking
            {
                Plr->Gossip_SendPOI(-8726.0, 477.4, 7, 6, 0, "The Protective Hide");
                SendQuickMenu(925);
            }break;

        case 35: //Mining
            {
                Plr->Gossip_SendPOI(-8434.0, 692.8, 7, 6, 0, "Gelman Stonehand");
                SendQuickMenu(927);
            }break;

        case 36: //Skinning
            {
                Plr->Gossip_SendPOI(-8716.0, 469.4, 7, 6, 0, "The Protective Hide");
                SendQuickMenu(928);
            }break;

        case 37: //Tailoring
            {
                Plr->Gossip_SendPOI(-8938.0, 800.7, 7, 6, 0, "Duncan`s Textiles");
                SendQuickMenu(929);
            }break;
        }
    }
};

void SetupStormwind_Guard(ScriptMgr * mgr)
{
	GossipScript * sw = (GossipScript*) new StormwindGuard();
	mgr->register_gossip_script(68, sw);				// Stormwind City Guard
	mgr->register_gossip_script(1976, sw);				// Stormwind City Patroller
}