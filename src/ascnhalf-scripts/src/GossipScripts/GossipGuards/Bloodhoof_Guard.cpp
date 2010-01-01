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

class BloodhoofGuard : public GossipScript
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
        Menu->AddItem(0, "The inn", 3);
        Menu->AddItem(0, "The stable master", 4);
        Menu->AddItem(0, "A class trainer", 5);
        Menu->AddItem(0, "A profession trainer", 6);    
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
            SendQuickMenu(4051);
            break;

        case 2:     // The wind rider master
            SendQuickMenu(4052);
            break;

        case 3:     // The inn
            SendQuickMenu(4053);
            Plr->Gossip_SendPOI(-2361.38, -349.19, 7, 6, 0, "Bloodhoof Village Inn");      
			break;

        case 4:     // The stable master
            SendQuickMenu(5976);
            Plr->Gossip_SendPOI(-2338.86, -357.56, 7, 6, 0, "Seikwa");
            break;

        case 5:     // A class trainer
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4069, Plr);
                Menu->AddItem( 0, "Druid"       , 7);
                Menu->AddItem( 0, "Hunter"      , 8);
                Menu->AddItem( 0, "Shaman"      , 9);
                Menu->AddItem( 0, "Warrior"    , 10);
                Menu->SendTo(Plr);
			}break;

        case 6:     // A profession trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3541, Plr);
                Menu->AddItem( 0, "Alchemy"           , 11);
                Menu->AddItem( 0, "Blacksmithing"     , 12);
                Menu->AddItem( 0, "Cooking"           , 13);
                Menu->AddItem( 0, "Enchanting"        , 14);
                Menu->AddItem( 0, "First Aid"         , 15);
                Menu->AddItem( 0, "Fishing"           , 16);
                Menu->AddItem( 0, "Herbalism"         , 17);
                Menu->AddItem( 0, "Leatherworking"    , 18);
                Menu->AddItem( 0, "Mining"            , 19);
                Menu->AddItem( 0, "Skinning"          , 20);
                Menu->AddItem( 0, "Tailoring"         , 21);
                Menu->SendTo(Plr);
            }break;


            ////////////////
            // Class trainer submenu
            ////////

        case 7: //Druid
            {
                Plr->Gossip_SendPOI(-2312.15, -443.69, 7, 6, 0, "Gennia Runetotem");
                SendQuickMenu(4054);
            }break;

        case 8: //Hunter
            {
                Plr->Gossip_SendPOI(-2178.14, -406.14, 7, 6, 0, "Yaw Sharpmane");
                SendQuickMenu(4055);
            }break;

        case 9: //Shaman
            {
                Plr->Gossip_SendPOI(-2301.5, -439.87, 7, 6, 0, "Narm Skychaser");
                SendQuickMenu(4056);
            }break;

        case 10: //Warrior
			{
                Plr->Gossip_SendPOI(-2345.43, -494.11, 7, 6, 0, "Krang Stonehoof");
                SendQuickMenu(4057);
            }break;

        case 11: //Alchemy
            {
                SendQuickMenu(4058);
            }break;

        case 12: //Blacksmithing
            {
                SendQuickMenu(4059);
            }break;

        case 13: //Cooking
            {
                Plr->Gossip_SendPOI(-2263.34, -287.91, 7, 6, 0, "Pyall Silentstride");
                SendQuickMenu(4060);
            }break;

        case 14: //Enchanting
            {
				SendQuickMenu(4061);
            }break;

        case 15: //First Aid
            {
                Plr->Gossip_SendPOI(-2353.52, -355.82, 7, 6, 0, "Vira Younghoof");
                SendQuickMenu(4062);
            }break;

        case 16: //Fishing
            {
                Plr->Gossip_SendPOI(-2349.21, -241.37, 7, 6, 0, "Uthan Stillwater");
                SendQuickMenu(4063);
            }break;

        case 17: //Herbalism
            {
                SendQuickMenu(4064);
            }break;

        case 18: //Leatherworking
            {
                Plr->Gossip_SendPOI(-2257.12, -288.63, 7, 6, 0, "Chaw Stronghide");
                SendQuickMenu(4065);
            }break;

        case 19: //Mining
            {
                SendQuickMenu(4066);
            }break;

        case 20: //Skinning
            {
                Plr->Gossip_SendPOI(-2252.94, -291.32, 7, 6, 0, "Yonn Deepcut");
                SendQuickMenu(4067); 
            }break;

		case 21: //Tailoring
            {
                SendQuickMenu(4068);
            }break;
        }
    }
};

void SetupBloodhoof_Guard(ScriptMgr * mgr)
{
	GossipScript * blood = (GossipScript*) new BloodhoofGuard();
	mgr->register_gossip_script(3222, blood);			// Brave Wildrunner
	mgr->register_gossip_script(3224, blood);			// Brave Cloudmane
	mgr->register_gossip_script(3220, blood);			// Brave Darksky
	mgr->register_gossip_script(3219, blood);			// Brave Leaping Deer
	mgr->register_gossip_script(3217, blood);			// Brave Dawneagle
	mgr->register_gossip_script(3215, blood);			// Brave Strongbash
	mgr->register_gossip_script(3218, blood);			// Brave Swiftwind
	mgr->register_gossip_script(3221, blood);			// Brave Rockhorn
	mgr->register_gossip_script(3223, blood);			// Brave Rainchaser
	mgr->register_gossip_script(3212, blood);			// Brave Ironhorn
}