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

class ThunderbluffGuard : public GossipScript
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
        Menu->AddItem(0, "The wind rider master", 2);
        Menu->AddItem(0, "The guild master", 3);
        Menu->AddItem(0, "The inn", 4);
        Menu->AddItem(0, "The mailbox", 5);
        Menu->AddItem(0, "The auction house", 6);    
        Menu->AddItem(0, "The weapon master", 7);
        Menu->AddItem(0, "The stable master", 8);
        Menu->AddItem(0, "The battlemaster", 9);
        Menu->AddItem(0, "A class trainer", 10);
        Menu->AddItem(0, "A profession trainer", 11);
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
            SendQuickMenu(1292);
            Plr->Gossip_SendPOI(-1257.8, 24.14, 7, 6, 0, "Thunder Bluff Bank");
            break;

        case 2:     // The wind rider master
            SendQuickMenu(1293);
            Plr->Gossip_SendPOI(-1196.43, 28.26, 7, 6, 0, "Wind Rider Roost");
            break;

        case 3:     // The guild master
            SendQuickMenu(1291);
            Plr->Gossip_SendPOI(-1296.5, 127.57, 7, 6, 0, "Thunder Bluff Civic Information");
            break;

        case 4:     // The inn
            SendQuickMenu(3153);
            Plr->Gossip_SendPOI(-1296, 39.7, 7, 6, 0, "Thunder Bluff Inn");
            break;

        case 5:     // The mailbox
            SendQuickMenu(3154);
            Plr->Gossip_SendPOI(-1263.59, 44.36, 7, 6, 0, "Thunder Bluff Mailbox");
            break;

        case 6:     // The auction house
            SendQuickMenu(3155);
            Plr->Gossip_SendPOI(-1205.51, 105.74, 7, 6, 0, "Thunder Bluff Auction house");
			break;

        case 7:     // The weapon master
            SendQuickMenu(4520);
            Plr->Gossip_SendPOI(-1282.31, 89.56, 7, 6, 0, "Ansekhwa");
            break;

	    case 8:     // The stable master
			SendQuickMenu(5977);
            Plr->Gossip_SendPOI(-1270.19, 48.84, 7, 6, 0, "Bulrug");
            break;

        case 9:    // The battlemaster
			SendQuickMenu(7527);
			Plr->Gossip_SendPOI(-1391.22, -81.33, 7, 6, 0, "Battlemasters Thunder Bluff");
            break;

        case 10:    // A class trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3542, Plr);
                Menu->AddItem( 0, "Druid"       , 12);
                Menu->AddItem( 0, "Hunter"      , 13);
                Menu->AddItem( 0, "Mage"        , 14);
                Menu->AddItem( 0, "Priest"      , 15);
                Menu->AddItem( 0, "Shaman"      , 16);
                Menu->AddItem( 0, "Warrior"     , 17);
                Menu->SendTo(Plr);
            }break;

        case 11:    // A profession trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3541, Plr);
                Menu->AddItem( 0, "Alchemy"           , 18);
                Menu->AddItem( 0, "Blacksmithing"     , 19);
                Menu->AddItem( 0, "Cooking"           , 20);
                Menu->AddItem( 0, "Enchanting"        , 21);
                Menu->AddItem( 0, "First Aid"         , 22);
                Menu->AddItem( 0, "Fishing"           , 23);
                Menu->AddItem( 0, "Herbalism"         , 24);
                Menu->AddItem( 0, "Leatherworking"    , 25);
                Menu->AddItem( 0, "Mining"            , 26);
                Menu->AddItem( 0, "Skinning"          , 27);
                Menu->AddItem( 0, "Tailoring"         , 28);
                Menu->SendTo(Plr);
            }break;

            ////////////////
            // Class trainer submenu
            ////////

        case 12: //Druid
            {
                Plr->Gossip_SendPOI(-1054.47, -285, 7, 6, 0, "Hall of Elders");
                SendQuickMenu(1294);
            }break;

        case 13: //Hunter
            {
                Plr->Gossip_SendPOI(-1416.32, -114.28, 7, 6, 0, "Hunter's Hall");
                SendQuickMenu(1295);
            }break;

        case 14: //Mage
            {
                Plr->Gossip_SendPOI(-1061.2, 195.5, 7, 6, 0, "Pools of Vision");
                SendQuickMenu(1296);
            }break;

        case 15: //Priest
            {
                Plr->Gossip_SendPOI(-1061.2, 195.5, 7, 6, 0, "Pools of Vision");
                SendQuickMenu(1297);
            }break;

        case 16: //Shaman
            {
                Plr->Gossip_SendPOI(-989.54, 278.25, 7, 6, 0, "Hall of Spirits");
                SendQuickMenu(1298);
            }break;

        case 17: //Warrior
			{
                Plr->Gossip_SendPOI(-1416.32, -114.28, 7, 6, 0, "Hunter's Hall");
                SendQuickMenu(1299);
            }break;

        case 18: //Alchemy
            {
                Plr->Gossip_SendPOI(-1085.56, 27.29, 7, 6, 0, "Bena's Alchemy");
                SendQuickMenu(1332);
            }break;

        case 19: //Blacksmithing
            {
                Plr->Gossip_SendPOI(-1239.75, 104.88, 7, 6, 0, "Karn's Smithy");
                SendQuickMenu(1333);
            }break;

        case 20: //Cooking
            {
                Plr->Gossip_SendPOI(-1214.5, -21.23, 7, 6, 0, "Aska's Kitchen");
                SendQuickMenu(1334);
            }break;

        case 21: //Enchanting
            {
                Plr->Gossip_SendPOI(-1112.65, 48.26, 7, 6, 0, "Dawnstrider Enchanters");
                SendQuickMenu(1335);
            }break;

        case 22: //First Aid
            {
                Plr->Gossip_SendPOI(-996.58, 200.5, 7, 6, 0, "Spiritual Healing");
                SendQuickMenu(1336);
            }break;

        case 23: //Fishing
            {
                Plr->Gossip_SendPOI(-1169.35, -68.87, 7, 6, 0, "Mountaintop Bait & Tackle");
                SendQuickMenu(1337);
            }break;

        case 24: //Herbalism
            {
                Plr->Gossip_SendPOI(-1137.7, -1.51, 7, 6, 0, "Holistic Herbalism");
                SendQuickMenu(1338);
            }break;

        case 25: //Leatherworking
            {
                Plr->Gossip_SendPOI(-1156.22, 66.86, 7, 6, 0, "Thunder Bluff Armorers");
                SendQuickMenu(1339);
            }break;

        case 26: //Mining
            {
                Plr->Gossip_SendPOI(-1249.17, 155, 7, 6, 0, "Stonehoof Geology");
                SendQuickMenu(1340);
            }break;

        case 27: //Skinning
            {
                Plr->Gossip_SendPOI(-1148.56, 51.18, 7, 6, 0, "Mooranta");
                SendQuickMenu(1343); 
            }break;

		case 28: //Tailoring
            {
                Plr->Gossip_SendPOI(-1156.22, 66.86, 7, 6, 0, "Thunder Bluff Armorers");
                SendQuickMenu(1341);
            }break;
        }
    }
};

void SetupThunderbluff_Guard(ScriptMgr * mgr)
{
	GossipScript * thun = (ThunderbluffGuard*) new ThunderbluffGuard();
	mgr->register_gossip_script(3084, thun);			// Bluffwatcher
}