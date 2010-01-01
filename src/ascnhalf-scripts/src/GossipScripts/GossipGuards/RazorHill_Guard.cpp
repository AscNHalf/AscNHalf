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

class RazorHillGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4037, Plr);
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
            SendQuickMenu(4032);
            break;

        case 2:     // The wind rider master
            SendQuickMenu(4033);
            break;

        case 3:     // The inn
            SendQuickMenu(4034);
            Plr->Gossip_SendPOI(338.7, -4688.87, 7, 6, 0, "Razor Hill Inn");      
			break;

        case 4:     // The stable master
            SendQuickMenu(5973);
            Plr->Gossip_SendPOI(330.31, -4710.66, 7, 6, 0, "Shoja'my");
            break;

        case 5:     // A class trainer
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4035, Plr);
                Menu->AddItem( 0, "Hunter"       , 7);
				Menu->AddItem( 0, "Mage"         , 8);
				Menu->AddItem( 0, "Priest"       , 9);
				Menu->AddItem( 0, "Rogue"       , 10);
                Menu->AddItem( 0, "Shaman"      , 11);
				Menu->AddItem( 0, "Warlock"     , 12);
                Menu->AddItem( 0, "Warrior"     , 13);
                Menu->SendTo(Plr);
			}break;

        case 6:     // A profession trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3541, Plr);
                Menu->AddItem( 0, "Alchemy"           , 14);
                Menu->AddItem( 0, "Blacksmithing"     , 15);
                Menu->AddItem( 0, "Cooking"           , 16);
                Menu->AddItem( 0, "Enchanting"        , 17);
                Menu->AddItem( 0, "Engineering"       , 18);
                Menu->AddItem( 0, "First Aid"         , 19);
                Menu->AddItem( 0, "Fishing"           , 20);
                Menu->AddItem( 0, "Herbalism"         , 21);
                Menu->AddItem( 0, "Leatherworking"    , 22);
                Menu->AddItem( 0, "Mining"            , 23);
                Menu->AddItem( 0, "Skinning"          , 24);
                Menu->AddItem( 0, "Tailoring"         , 25);
                Menu->SendTo(Plr);
            }break;


            ////////////////
            // Class trainer submenu
            ////////

        case 7: //Hunter
            {
                Plr->Gossip_SendPOI(276, -4706.72, 7, 6, 0, "Thotar");
                SendQuickMenu(4013);
            }break;        

        case 8: //Mage
            {
                Plr->Gossip_SendPOI(-839.33, -4935.6, 7, 6, 0, "Un'Thuwa");
                SendQuickMenu(4014);
            }break;

        case 9: //Priest
            {
                Plr->Gossip_SendPOI(296.22, -4828.1, 7, 6, 0, "Tai'jin");
                SendQuickMenu(4015);
            }break;

        case 10: //Rogue
			{
                Plr->Gossip_SendPOI(265.76, -4709, 7, 6, 0, "Kaplak");
                SendQuickMenu(4016);
            }break;

        case 11: //Shaman
            {
                Plr->Gossip_SendPOI(307.79, -4836.97, 7, 6, 0, "Swart");
                SendQuickMenu(4017);
            }break;

        case 12: //Warlock
            {
                Plr->Gossip_SendPOI(355.88, -4836.45, 7, 6, 0, "Dhugru Gorelust");
                SendQuickMenu(4018);
            }break;

        case 13: //Warrior
            {
                Plr->Gossip_SendPOI(312.3, -4824.66, 7, 6, 0, "Tarshaw Jaggedscar");
                SendQuickMenu(4019);
            }break;

        case 14: //Alchemy
            {
				Plr->Gossip_SendPOI(-800.25, -4894.33, 7, 6, 0, "Miao'zan");
                SendQuickMenu(4020);
            }break;

        case 15: //Blacksmithing
            {
				Plr->Gossip_SendPOI(373.24, -4716.45, 7, 6, 0, "Dwukk");
                SendQuickMenu(4021);
            }break;

        case 16: //Cooking
            {
                SendQuickMenu(4022);
            }break;

        case 17: //Enchanting
            {
				SendQuickMenu(4023);
            }break;
			
        case 18: //Engineering
            {
                Plr->Gossip_SendPOI(368.95, -4723.95, 7, 6, 0, "Mukdrak");
                SendQuickMenu(4024);
            }break;

        case 19: //First Aid
            {
                Plr->Gossip_SendPOI(327.17, -4825.62, 7, 6, 0, "Rawrk");
                SendQuickMenu(4025);
            }break;

        case 20: //Fishing
            {
                Plr->Gossip_SendPOI(-1065.48, -4777.43, 7, 6, 0, "Lau'Tiki");
                SendQuickMenu(4026);
            }break;

        case 21: //Herbalism
            {
				Plr->Gossip_SendPOI(-836.25, -4896.89, 7, 6, 0, "Mishiki");
                SendQuickMenu(4027);
            }break;

        case 22: //Leatherworking
            {
                SendQuickMenu(4028);
            }break;

        case 23: //Mining
            {
				Plr->Gossip_SendPOI(366.94, -4705, 7, 6, 0, "Krunn");
                SendQuickMenu(4029);
            }break;

        case 24: //Skinning
            {
                Plr->Gossip_SendPOI(-2252.94, -291.32, 7, 6, 0, "Yonn Deepcut");
                SendQuickMenu(4030); 
            }break;

		case 25: //Tailoring
            {
                SendQuickMenu(4031);
            }break;
        }
    }
};

void SetupRazorHill_Guard(ScriptMgr * mgr)
{
	GossipScript * razor = (GossipScript*) new RazorHillGuard();
	mgr->register_gossip_script(5953, razor);			// Razor Hill Grunt
}