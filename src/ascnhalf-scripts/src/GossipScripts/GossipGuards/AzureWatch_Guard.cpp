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

class AzureWatchGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}

    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10066, Plr);
        Menu->AddItem(0, "Bank"					, 1);
        Menu->AddItem(0, "Hippogryph Master"	, 2);
        Menu->AddItem(0, "Guild Master"			, 3);
        Menu->AddItem(0, "Inn"					, 4);
        Menu->AddItem(0, "Stable"				, 5);
        Menu->AddItem(0, "Class Trainer"		, 6);
		Menu->AddItem(0, "Profession Trainer"	, 7);
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

        case 1:     //Bank
            SendQuickMenu(10067);
            break;

        case 2:     //Hippogryph Master
            SendQuickMenu(10071);
			break;
			
        case 3:     //Guild Master
            SendQuickMenu(10073);
			break;

        case 4:     //Inn
            SendQuickMenu(10074);
            Plr->Gossip_SendPOI(-4127.81, -12467.7, 7, 6, 0, "Azure Watch, Innkeeper");
            break;

        case 5:     //Stable Master
            SendQuickMenu(10075);
            Plr->Gossip_SendPOI(-4146.42, -12492.7, 7, 6, 0, "Azure Watch, Stable Master");
            break;

        case 6:     //Class Trainer
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10076, Plr);
                Menu->AddItem( 0, "Druid"       , 8);
				Menu->AddItem( 0, "Hunter"      , 9);
				Menu->AddItem( 0, "Mage"		, 10);
				Menu->AddItem( 0, "Paladin"     , 11);
                Menu->AddItem( 0, "Priest"      , 12);
				Menu->AddItem( 0, "Shaman"      , 13);
                Menu->AddItem( 0, "Warrior"     , 14);
                Menu->SendTo(Plr);
			}break;

        case 7:     //Profession Trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10087, Plr);
                Menu->AddItem( 0, "Alchemy"           , 15);
                Menu->AddItem( 0, "Blacksmithing"     , 16);
                Menu->AddItem( 0, "Cooking"           , 17);
                Menu->AddItem( 0, "Enchanting"        , 18);
                Menu->AddItem( 0, "Engineering"       , 19);
                Menu->AddItem( 0, "First Aid"         , 20);
                Menu->AddItem( 0, "Fishing"           , 21);
                Menu->AddItem( 0, "Herbalism"         , 22);
				Menu->AddItem( 0, "Inscription"       , 23);
				Menu->AddItem( 0, "Jewelcrafting"     , 24);
                Menu->AddItem( 0, "Leatherworking"    , 25);
                Menu->AddItem( 0, "Mining"            , 26);
                Menu->AddItem( 0, "Skinning"          , 27);
                Menu->AddItem( 0, "Tailoring"         , 28);
                Menu->SendTo(Plr);
            }break;


            ////////////////
            // Class trainer submenu
            ////////

        case 8: //Druid
            {
                SendQuickMenu(10077);
            }break;

        case 9: //Hunter
            {
                Plr->Gossip_SendPOI(-4203.65, -12467.7, 7, 6, 0, "Azure Watch, Hunter Trainer");
                SendQuickMenu(10078);
            }break;

        case 10: //Mage
            {
                Plr->Gossip_SendPOI(-4149.62, -12530.1, 7, 6, 0, "Azure Watch, Mage Trainer");
                SendQuickMenu(10081);
            }break;

        case 11: //Paladin
			{
                Plr->Gossip_SendPOI(-4138.98, -12468.5, 7, 6, 0, "Azure Watch, Paladin Trainer");
                SendQuickMenu(10083);
            }break;

        case 12: //Priest
            {
                Plr->Gossip_SendPOI(-4131.66, -12478.6, 7, 6, 0, "Azure Watch, Priest Trainer");
                SendQuickMenu(10084);
            }break;

        case 13: //Shaman
            {
                Plr->Gossip_SendPOI(-4162.33, -12456.1, 7, 6, 0, "Azure Watch, Shaman Trainer");
                SendQuickMenu(10085);
            }break;

        case 14: //Warrior
            {
                Plr->Gossip_SendPOI(-4165.05, -12536.4, 7, 6, 0, "Azure Watch, Warrior Trainer");
                SendQuickMenu(10086);
            }break;

        case 15: //Alchemy
            {
                Plr->Gossip_SendPOI(-4191.15, -12470, 7, 6, 0, "Azure Watch, Alchemist");
                SendQuickMenu(10088);
            }break;

        case 16: //Blacksmithing
            {
				Plr->Gossip_SendPOI(-4726.29, -12387.0, 7, 6, 0, "Odesyus' Landing, Blacksmith");
                SendQuickMenu(10089);
            }break;

        case 17: //Cooking
            {
				Plr->Gossip_SendPOI(-4708.59, -12400.3, 7, 6, 0, "Odesyus' Landing, Cook");
                SendQuickMenu(10090);
            }break;

        case 18: //Enchanting
            {
				SendQuickMenu(10091);
            }break;
			
        case 19: //Engineering
            {
                Plr->Gossip_SendPOI(-4157.57, -12470.2, 7, 6, 0, "Azure Watch, Engineering Trainer");
                SendQuickMenu(10092);
            }break;

        case 20: //First Aid
            {
                Plr->Gossip_SendPOI(-4199.1, -12469.9, 7, 6, 0, "Azure Watch, First Aid Trainer");
                SendQuickMenu(10093);
            }break;

        case 21: //Fishing
            {
                Plr->Gossip_SendPOI(-4266.34, -12985.4, 7, 6, 0, "Ammen Ford, Fisherwoman");
                SendQuickMenu(10094);
            }break;

        case 22: //Herbalism
            {
                Plr->Gossip_SendPOI(-4189.43, -12459.4, 7, 6, 0, "Azure Watch, Herbalist");
                SendQuickMenu(10095);
            }break;

		case 23: //Inscription
            {
                Plr->Gossip_SendPOI(-3889.3, -11495, 7, 6, 0, "Exodar, Inscription");
                SendQuickMenu(13887);
            }break;

        case 24: //Jewelcrafting
            {
                SendQuickMenu(10100);
            }break;

        case 25: //Leatherworking
            {
                Plr->Gossip_SendPOI(-3442.68, -12322.2, 7, 6, 0, "Stillpine Hold, Leatherworker");
                SendQuickMenu(10096);
            }break;

        case 26: //Mining
            {
				Plr->Gossip_SendPOI(-4179.89, -12493.1, 7, 6, 0, "Azure Watch, Mining Trainer");
                SendQuickMenu(10097);
            }break;

        case 27: //Skinning
            {
				Plr->Gossip_SendPOI(-3431.17, -12316.5, 7, 6, 0, "Stillpine Hold, Skinner");
                SendQuickMenu(10098);
            }break;

		case 28: //Tailoring
            {
				Plr->Gossip_SendPOI(-4711.54, -12386.7, 7, 6, 0, "Odesyus' Landing, Tailor");
                SendQuickMenu(10099);
            }break;
        }
    }
};

void SetupAzureWatch_Guard(ScriptMgr * mgr)
{
	GossipScript * azure = (AzureWatchGuard*) new AzureWatchGuard();
	mgr->register_gossip_script(18038, azure);			// Azuremyst Peacekeeper
}