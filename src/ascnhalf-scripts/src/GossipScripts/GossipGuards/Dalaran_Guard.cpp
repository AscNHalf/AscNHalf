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

class DalaranGuard : public GossipScript
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
        
        Menu->AddItem(0, "Auction House"		, 1);
        Menu->AddItem(0, "Bank of Dalaran"	    , 2);
        Menu->AddItem(0, "Portals"			    , 3);
		Menu->AddItem(0, "Teleporter Crystal"	, 4);
        Menu->AddItem(0, "The Inn"				, 5);
        Menu->AddItem(0, "Gryphon Master"		, 6);    
        Menu->AddItem(0, "Guild Master"			, 7);
        Menu->AddItem(0, "Mailbox"				, 8);
        Menu->AddItem(0, "Stable Master"		, 9);
        Menu->AddItem(0, "Battlemaster"			, 10);
		Menu->AddItem(0, "Underbelly"			, 11);
		Menu->AddItem(0, "Barber"		        , 12);
        Menu->AddItem(0, "Class Trainer"		, 13);
        Menu->AddItem(0, "Profession Trainer"	, 14);
		Menu->AddItem(0, "Mount Vendor"	        , 15);
		Menu->AddItem(0, "Riding Trainer"	    , 16);
		Menu->AddItem(0, "TierSet Vendors"	    , 17);

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
            SendQuickMenu(14010);
            break;

        case 2:     // Bank of Dalaran
            SendQuickMenu(14007);
            Plr->Gossip_SendPOI(5965.58, 614.49, 7, 6, 0, "Bank of Dalaran");
            break;

		case 3:     // Faction Portals
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13977, Plr);
			Menu->AddItem( 0, "Silver Enclave (Alliance)"           , 19);
			Menu->AddItem( 0, "Sunreaver's Sancturary (Horde)"           , 20);
			Menu->SendTo(Plr);
            break;

        case 4:     // Teleporter Crystal
            Plr->Gossip_SendPOI(5808, 585, 7, 6, 0, "Teleporter Crystal");
			Plr->Gossip_Complete();
            break;

        case 5:     // The Inn
            SendQuickMenu(14002);
            Plr->Gossip_SendPOI(5850, 646, 7, 6, 0, "The Inn");
            break;

        case 6:     // Gryphon Master
            SendQuickMenu(14004);
            Plr->Gossip_SendPOI(5813, 453, 7, 6, 0, "Gryphon Master");
            break;

        case 7:     // Guild Master
            SendQuickMenu(14015);
            Plr->Gossip_SendPOI(5759, 623, 7, 6, 0, "Guild Master");
            break;

        case 8:     // Mailbox
            SendQuickMenu(14008);
            break;

        case 9:     // Stable Master
            SendQuickMenu(14103);
            Plr->Gossip_SendPOI(5849, 564, 7, 6, 0, "Stable Master");
            break;

        case 10:     // Battlemaster
		    if(Plr->GetTeam() == 1)  // Horde
			{
			Plr->Gossip_SendPOI(5958, 562, 7, 6, 0, "Battlemaster");
			Plr->Gossip_Complete();
			}
			else // Alliance
			{
            Plr->Gossip_SendPOI(5665, 789, 7, 6, 0, "Battlemaster");
			Plr->Gossip_Complete();
			}
            break;

        case 11:    // Underbelly
            SendQuickMenu(14026);
            Plr->Gossip_SendPOI(5803, 553, 7, 6, 0, "Underbelly");
            break;

        case 12:    // Barber
            {
			SendQuickMenu(14003);
            Plr->Gossip_SendPOI(5891, 620, 7, 6, 0, "Barber");
            }break;

		case 13:     // Class Trainer(mage)
            {
			 objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 14018, Plr);
             Menu->AddItem( 0, "Mage Trainer"           , 18);
			 Menu->SendTo(Plr);
			
            }break;

        case 14:    // Profession Trainers
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13980, Plr);
				
                Menu->AddItem( 0, "Alchemy"           , 25);
                Menu->AddItem( 0, "Blacksmithing"     , 26);
                Menu->AddItem( 0, "Cooking"           , 27);
                Menu->AddItem( 0, "Enchanting"        , 28);
                Menu->AddItem( 0, "Engineering"       , 29);
                Menu->AddItem( 0, "First Aid"         , 30);
                Menu->AddItem( 0, "Fishing"           , 31);
                Menu->AddItem( 0, "Herbalism"         , 32);
				Menu->AddItem( 0, "Inscription"		  , 33);
                Menu->AddItem( 0, "Leatherworking"    , 34);
                Menu->AddItem( 0, "Mining"            , 35);
                Menu->AddItem( 0, "Skinning"          , 36);
                Menu->AddItem( 0, "Tailoring"         , 37);
				Menu->AddItem( 0, "Jewelcrafting"     , 38);
                Menu->SendTo(Plr);
			}break;

        case 15:    // Mount Vendor
            SendQuickMenu(14103);
            Plr->Gossip_SendPOI(5833.83, 570.1, 7, 6, 0, "Mount Vendor");
            break;
			
		case 16:    // Riding Trainer
		    SendQuickMenu(13998);
            Plr->Gossip_SendPOI(5815, 473, 7, 6, 0, "Riding Trainer");
            break;
			
		case 17:    // TierSet Vendors
		    switch(Plr->getClass()) {
	          case WARLOCK:
			  Plr->Gossip_SendPOI(5796, 690, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case PRIEST:
			  Plr->Gossip_SendPOI(5796, 690, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case MAGE:
			  Plr->Gossip_SendPOI(5796, 690, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case ROGUE:
			  Plr->Gossip_SendPOI(5667, 627, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case DRUID:
			  Plr->Gossip_SendPOI(5667, 627, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case PALADIN:
			  Plr->Gossip_SendPOI(5920, 666, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case WARRIOR:
			  Plr->Gossip_SendPOI(5920, 666, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case DEATHKNIGHT:
			  Plr->Gossip_SendPOI(5920, 666, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case SHAMAN:
			  Plr->Gossip_SendPOI(5667, 627, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			  
			  case HUNTER:
			  Plr->Gossip_SendPOI(5667, 627, 7, 6, 0, "Tierset Vendor");
			  Plr->Gossip_Complete();
			  break;
			 }
            break;	

			///////////////////////
			// Sub Menus
			///////////////////
			
		case 18:     // Class Trainer(mage)
            {
			SendQuickMenu(13999);
			Plr->Gossip_SendPOI(5808, 585, 7, 6, 0, "Mage Trainer");
            }break;
			
		case 19:     // Silver Enclave
            {
			SendQuickMenu(13973);
			Plr->Gossip_SendPOI(5726, 740, 7, 6, 0, "Silver Enclave");
            }break;
			
		case 20:     // Sunreaver's Sancturary
            {
			SendQuickMenu(13972);
			Plr->Gossip_SendPOI(5912, 539, 7, 6, 0, "Sunreaver's Sancturary");
            }break;
			
        case 25: //Alchemy
            {
                Plr->Gossip_SendPOI(5888, 702, 7, 6, 0, "Agronomical Apothecary");
                SendQuickMenu(13995);
            }break;

        case 26: //Blacksmithing
            {
                Plr->Gossip_SendPOI(5907, 679, 7, 6, 0, "Blacksmithing Trainer");
				Plr->Gossip_Complete();
            }break;

        case 27: //Cooking
            {
			if(Plr->GetTeam() == 1)  // Horde
			{
			Plr->Gossip_SendPOI(5853, 473, 7, 6, 0, "Cooking Trainer");
			Plr->Gossip_Complete();
			}
			else
			{
            Plr->Gossip_SendPOI(5727, 682, 7, 6, 0, "Cooking Trainer");
		    Plr->Gossip_Complete();
			}
            }break;

        case 28: //Enchanting
            {
                Plr->Gossip_SendPOI(5841, 727, 7, 6, 0, "Enchanting Trainer");
                SendQuickMenu(13990);
            }break;

        case 29: //Engineering
            {
                Plr->Gossip_SendPOI(5925, 727, 7, 6, 0, "Lilliam Sparkspindle");
                SendQuickMenu(13989);
            }break;

        case 30: //First Aid
            {
                Plr->Gossip_SendPOI(5861, 764, 7, 6, 0, "First Aid Trainer");
                SendQuickMenu(13988);
            }break;

        case 31: //Fishing
            {
                Plr->Gossip_SendPOI(5707, 612, 7, 6, 0, "Marcia Chase");
                SendQuickMenu(13987);
            }break;

        case 32: //Herbalism
            {
                Plr->Gossip_SendPOI(5877, 693, 7, 6, 0, "Herbalism Trainer");
                SendQuickMenu(13986);
            }break;

		case 33: //Inscription
            {
                Plr->Gossip_SendPOI(5862, 705, 7, 6, 0, "Inscription Trainer");
				Plr->Gossip_Complete();
            }break;

        case 34: //Leatherworking
            {
                Plr->Gossip_SendPOI(5903, 755, 7, 6, 0, "Leatherworking Trainer");
                SendQuickMenu(13982);
            }break;

        case 35: //Mining
            {
                Plr->Gossip_SendPOI(5923, 709, 7, 6, 0, "Glitters Prospecting Co.");
                SendQuickMenu(13983);
            }break;

        case 36: //Skinning
            {
                Plr->Gossip_SendPOI(5903, 755, 7, 6, 0, "Skinning Trainer");
                SendQuickMenu(13982);
            }break;

        case 37: //Tailoring
            {
                Plr->Gossip_SendPOI(5881, 640, 7, 6, 0, "Talismanic Textiles");
                SendQuickMenu(13981);
            }break;
			
		case 38: //Jewelcrafting
            {
                Plr->Gossip_SendPOI(5875, 718, 7, 6, 0, "Cartier & Co.");
                SendQuickMenu(13984);
            }break;
        }
    }
};

void SetupDalaran_Guard(ScriptMgr * mgr)
{
	GossipScript * dala = (GossipScript*) new DalaranGuard();
	mgr->register_gossip_script(32681, dala);  // The Magnificent Merleaux
	mgr->register_gossip_script(32685, dala);  // Kitz Proudbreeze
	mgr->register_gossip_script(32680, dala);  // Fabioso the Fabulous
	mgr->register_gossip_script(32676, dala);  // Grindle Firespark
	mgr->register_gossip_script(32687, dala);  // Linda Ann Kastinglow
	mgr->register_gossip_script(32692, dala);  // Arcanist Alec
	mgr->register_gossip_script(32688, dala);  // Archmage Tenaj
	mgr->register_gossip_script(32679, dala);  // Darthalia Ebonscorch
	mgr->register_gossip_script(32683, dala);  // Grezla the Hag
	mgr->register_gossip_script(32686, dala);  // Crafticus Mindbender
	mgr->register_gossip_script(32691, dala);  // Magus Fansy Goodbringer
	mgr->register_gossip_script(32689, dala);  // Adorean Lew
	mgr->register_gossip_script(32690, dala);  // Bitty Frostflinger
	mgr->register_gossip_script(32684, dala);  // Mona Everspring
	mgr->register_gossip_script(32677, dala);  // Whirt the All-Knowing
}