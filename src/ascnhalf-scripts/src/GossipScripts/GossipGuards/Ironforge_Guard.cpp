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

class IronforgeGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2760, Plr);
        Menu->AddItem(0, "Auction House"			, 1);
        Menu->AddItem(0, "Bank of Ironforge"		, 2);
        Menu->AddItem(0, "Deeprun Tram"				, 3);
        Menu->AddItem(0, "Gryphon Master"			, 4);
        Menu->AddItem(0, "Guild Master"				, 5);
        Menu->AddItem(0, "The Inn"					, 6);    
        Menu->AddItem(0, "Mailbox"					, 7);
        Menu->AddItem(0, "Stable Master"			, 8);
        Menu->AddItem(0, "Weapons Trainer"			, 9);
        Menu->AddItem(0, "Battlemaster"				, 10);
		Menu->AddItem(0, "Barber"					, 11);
        Menu->AddItem(0, "Class Trainer"			, 12);
        Menu->AddItem(0, "Profession Trainer"		, 13);
		Menu->AddItem(0, "Lexicon of Power"			, 35);
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
            SendQuickMenu(3014);
            Plr->Gossip_SendPOI(-4957.39, -911.6, 7, 6, 0, "Ironforge Auction House");
            break;

        case 2:     // Bank of Ironforge
            SendQuickMenu(2761);
            Plr->Gossip_SendPOI(-4891.91, -991.47, 7, 6, 0, "The Vault");
            break;

        case 3:     // Deeprun Tram
            SendQuickMenu(3814);
            Plr->Gossip_SendPOI(-4835.27, -1294.69, 7, 6, 0, "Deeprun Tram");
            break;

        case 4:     // Gryphon Master
            SendQuickMenu(2762);
            Plr->Gossip_SendPOI(-4821.52, -1152.3, 7, 6, 0, "Ironforge Gryphon Master");
            break;

        case 5:     // Guild Master
            SendQuickMenu(2764);
            Plr->Gossip_SendPOI(-5021, -996.45, 7, 6, 0, "Ironforge Visitor's Center");
            break;

        case 6:     // The Inn
            SendQuickMenu(2768);
            Plr->Gossip_SendPOI(-4850.47, -872.57, 7, 6, 0, "Stonefire Tavern");
			break;

        case 7:     // Mailbox
            SendQuickMenu(2769);
            Plr->Gossip_SendPOI(-4845.7, -880.55, 7, 6, 0, "Ironforge Mailbox");
            break;

	    case 8:     // Stable Master
			SendQuickMenu(5986);
            Plr->Gossip_SendPOI(-5010.2, -1262, 7, 6, 0, "Ulbrek Firehand");
            break;

        case 9:    // Weapon Trainer
			SendQuickMenu(4518);
			Plr->Gossip_SendPOI(-5040, -1201.88, 7, 6, 0, "Bixi and Buliwyf");
            break;

        case 10:    // Battlemaster
			SendQuickMenu(10216);
			Plr->Gossip_SendPOI(-5038.54, -1266.44, 7, 6, 0, "Battlemasters Ironforge");
            break;

		case 11:    // Barber
			SendQuickMenu(13885);
			Plr->Gossip_SendPOI(-4838.49, -919.18, 7, 6, 0, "Ironforge Barber");
            break;

        case 12:    // A class trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2766, Plr);
                Menu->AddItem( 0, "Hunter"      , 14);
                Menu->AddItem( 0, "Mage"        , 15);
                Menu->AddItem( 0, "Paladin"     , 16);
                Menu->AddItem( 0, "Priest"      , 17);
                Menu->AddItem( 0, "Rogue"       , 18);
                Menu->AddItem( 0, "Warlock"     , 19);
                Menu->AddItem( 0, "Warrior"     , 20);
                Menu->AddItem( 0, "Shaman"      , 21);
                Menu->SendTo(Plr);
            }break;

        case 13:    // A profession trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2793, Plr);
                Menu->AddItem( 0, "Alchemy"           , 22);
                Menu->AddItem( 0, "Blacksmithing"     , 23);
                Menu->AddItem( 0, "Cooking"           , 24);
                Menu->AddItem( 0, "Enchanting"        , 25);
				Menu->AddItem( 0, "Engineering"       , 26);
                Menu->AddItem( 0, "First Aid"         , 27);
                Menu->AddItem( 0, "Fishing"           , 28);
                Menu->AddItem( 0, "Herbalism"         , 29);
				Menu->AddItem(0, "Inscription"		  , 30);
                Menu->AddItem( 0, "Leatherworking"    , 31);
                Menu->AddItem( 0, "Mining"            , 32);
                Menu->AddItem( 0, "Skinning"          , 33);
                Menu->AddItem( 0, "Tailoring"         , 34);
                Menu->SendTo(Plr);
            }break;

            ////////////////
            // Class trainer submenu
            ////////

        case 14: //Hunter
            {
                Plr->Gossip_SendPOI(-5023, -1253.68, 7, 6, 0, "Hall of Arms");
                SendQuickMenu(2770);
            }break;

        case 15: //Mage
            {
                Plr->Gossip_SendPOI(-4627, -926.45, 7, 6, 0, "Hall of Mysteries");
                SendQuickMenu(2771);
            }break;

        case 16: //Paladin
            {
                Plr->Gossip_SendPOI(-4627.02, -926.45, 7, 6, 0, "Hall of Mysteries");
                SendQuickMenu(2773);
            }break;

        case 17: //Priest
            {
                Plr->Gossip_SendPOI(-4627, -926.45, 7, 6, 0, "Hall of Mysteries");
                SendQuickMenu(2772);
            }break;

        case 18: //Rogue
            {
                Plr->Gossip_SendPOI(-4647.83, -1124, 7, 6, 0, "Ironforge Rogue Trainer");
                SendQuickMenu(2774);
            }break;

        case 19: //Warlock
			{
                Plr->Gossip_SendPOI(-4605, -1110.45, 7, 6, 0, "Ironforge Warlock Trainer");
                SendQuickMenu(2775);
            }break;

        case 20: //Warrior
			{
                Plr->Gossip_SendPOI(-5023.08, -1253.68, 7, 6, 0, "Hall of Arms");
                SendQuickMenu(2776);
            }break;

        case 21: //Shaman
			{
                Plr->Gossip_SendPOI(-4722.02, -1150.66, 7, 6, 0, "Ironforge Shaman Trainer");
                SendQuickMenu(10842);
            }break;

        case 22: //Alchemy
            {
                Plr->Gossip_SendPOI(-4858.5, -1241.83, 7, 6, 0, "Berryfizz's Potions and Mixed Drinks");
                SendQuickMenu(2794);
            }break;

        case 23: //Blacksmithing
            {
                Plr->Gossip_SendPOI(-4796.97, -1110.17, 7, 6, 0, "The Great Forge");
                SendQuickMenu(2795);
            }break;

        case 24: //Cooking
            {
                Plr->Gossip_SendPOI(-4767.83, -1184.59, 7, 6, 0, "The Bronze Kettle");
                SendQuickMenu(2796);
            }break;

        case 25: //Enchanting
            {
                Plr->Gossip_SendPOI(-4803.72, -1196.53, 7, 6, 0, "Thistlefuzz Arcanery");
                SendQuickMenu(2797);
            }break;

		case 26: //Engineering
            {
                Plr->Gossip_SendPOI(-4799.56, -1250.23, 7, 6, 0, "Springspindle's Gadgets");
                SendQuickMenu(2798);
            }break;

        case 27: //First Aid
            {
                Plr->Gossip_SendPOI(-4881.6, -1153.13, 7, 6, 0, "Ironforge Physician");
                SendQuickMenu(2799);
            }break;

        case 28: //Fishing
            {
                Plr->Gossip_SendPOI(-4597.91, -1091.93, 7, 6, 0, "Traveling Fisherman");
                SendQuickMenu(2800);
            }break;

        case 29: //Herbalism
            {
                Plr->Gossip_SendPOI(-4876.9, -1151.92, 7, 6, 0, "Ironforge Physician");
                SendQuickMenu(2801);
            }break;

		case 30: //Inscription
            {
                Plr->Gossip_SendPOI(-4801.72, -1189.41, 7, 6, 0, "Ironforge Inscription");
                SendQuickMenu(13884);
            }break;

        case 31: //Leatherworking
            {
                Plr->Gossip_SendPOI(-4745, -1027.57, 7, 6, 0, "Finespindle's Leather Goods");
                SendQuickMenu(2802);
            }break;

        case 32: //Mining
            {
                Plr->Gossip_SendPOI(-4705.06, -1116.43, 7, 6, 0, "Deepmountain Mining Guild");
                SendQuickMenu(2804);
            }break;

        case 33: //Skinning
            {
                Plr->Gossip_SendPOI(-4745, -1027.57, 7, 6, 0, "Finespindle's Leather Goods");
                SendQuickMenu(2805); 
            }break;

		case 34: //Tailoring
            {
                Plr->Gossip_SendPOI(-4719.60, -1056.96, 7, 6, 0, "Stonebrow's Clothier");
                SendQuickMenu(2807);
            }break;

		case 35: //Lexicon of Power
            {
                Plr->Gossip_SendPOI(-4801.72, -1189.41, 7, 6, 0, "Ironforge Inscription");
                SendQuickMenu(14174);
            }break;
        }
    }
};

void SetupIronforge_Guard(ScriptMgr * mgr)
{
	GossipScript * irf = (GossipScript*) new IronforgeGuard();
	mgr->register_gossip_script(5595, irf);				// Ironforge Guard
}