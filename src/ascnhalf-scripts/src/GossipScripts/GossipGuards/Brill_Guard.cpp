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

class BrillGuard : public GossipScript
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
        Menu->AddItem(0, "The bat handler", 2);
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
            SendQuickMenu(4074);
            break;

        case 2:     // The bat handler
            SendQuickMenu(4075);
            break;

        case 3:     // The inn
            SendQuickMenu(4076);
            Plr->Gossip_SendPOI(2246.68, 241.89, 7, 6, 0, "Gallows` End Tavern"); 
			break;

        case 4:     // The stable master
            SendQuickMenu(5978);
            Plr->Gossip_SendPOI(2267.66, 319.32, 7, 6, 0, "Morganus");
            break;

        case 5:     // A class trainer
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4292, Plr);
                Menu->AddItem( 0, "Mage"         , 7);
				Menu->AddItem( 0, "Paladin"      , 8);
				Menu->AddItem( 0, "Priest"       , 9);
				Menu->AddItem( 0, "Rogue"       , 10);
				Menu->AddItem( 0, "Warlock"     , 11);
                Menu->AddItem( 0, "Warrior"     , 12);
                Menu->SendTo(Plr);
			}break;

        case 6:     // A profession trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4300, Plr);
                Menu->AddItem( 0, "Alchemy"           , 13);
                Menu->AddItem( 0, "Blacksmithing"     , 14);
                Menu->AddItem( 0, "Cooking"           , 15);
                Menu->AddItem( 0, "Enchanting"        , 16);
                Menu->AddItem( 0, "Engineering"       , 17);
                Menu->AddItem( 0, "First Aid"         , 18);
                Menu->AddItem( 0, "Fishing"           , 19);
                Menu->AddItem( 0, "Herbalism"         , 20);
                Menu->AddItem( 0, "Leatherworking"    , 21);
                Menu->AddItem( 0, "Mining"            , 22);
                Menu->AddItem( 0, "Skinning"          , 23);
                Menu->AddItem( 0, "Tailoring"         , 24);
                Menu->SendTo(Plr);
            }break;


            ////////////////
            // Class trainer submenu
            ////////

        case 7: //Mage
            {
                Plr->Gossip_SendPOI(2259.18, 240.93, 7, 6, 0, "Cain Firesong");
                SendQuickMenu(4077);
            }break;        

        case 8: //Paladin
            {
                SendQuickMenu(0); // Need to add correct text
            }break;

        case 9: //Priest
            {
                Plr->Gossip_SendPOI(2259.18, 240.93, 7, 6, 0, "Dark Cleric Beryl");
                SendQuickMenu(4078);
            }break;

        case 10: //Rogue
			{
                Plr->Gossip_SendPOI(2259.18, 240.93, 7, 6, 0, "Marion Call");
                SendQuickMenu(4079);
            }break;

        case 11: //Warlock
            {
                Plr->Gossip_SendPOI(2259.18, 240.93, 7, 6, 0, "Rupert Boch");
                SendQuickMenu(4080);
            }break;

        case 12: //Warrior
            {
                Plr->Gossip_SendPOI(2256.48, 240.32, 7, 6, 0, "Austil de Mon");
                SendQuickMenu(4081);
            }break;

        case 13: //Alchemy
            {
				Plr->Gossip_SendPOI(2263.25, 344.23, 7, 6, 0, "Carolai Anise");
                SendQuickMenu(4082);
            }break;

        case 14: //Blacksmithing
            {
                SendQuickMenu(4083);
            }break;

        case 15: //Cooking
            {
                SendQuickMenu(4084);
            }break;

        case 16: //Enchanting
            {
				Plr->Gossip_SendPOI(2250.35, 249.12, 7, 6, 0, "Vance Undergloom");
				SendQuickMenu(4085);
            }break;
			
        case 17: //Engineering
            {
                SendQuickMenu(4086);
            }break;

        case 18: //First Aid
            {
                Plr->Gossip_SendPOI(2246.68, 241.89, 7, 6, 0, "Nurse Neela");
                SendQuickMenu(4087);
            }break;

        case 19: //Fishing
            {
                Plr->Gossip_SendPOI(2292.37, -10.72, 7, 6, 0, "Clyde Kellen");
                SendQuickMenu(4088);
            }break;

        case 20: //Herbalism
            {
				Plr->Gossip_SendPOI(2268.21, 331.69, 7, 6, 0, "Faruza");
                SendQuickMenu(4089);
            }break;

        case 21: //Leatherworking
            {
				Plr->Gossip_SendPOI(2027, 78.72, 7, 6, 0, "Shelene Rhobart");
                SendQuickMenu(4090);
            }break;

        case 22: //Mining
            {
                SendQuickMenu(4091);
            }break;

        case 23: //Skinning
            {
                Plr->Gossip_SendPOI(2027, 78.72, 7, 6, 0, "Rand Rhobart");
                SendQuickMenu(4092); 
            }break;

		case 24: //Tailoring
            {
				Plr->Gossip_SendPOI(2160.45, 659.93, 7, 6, 0, "Bowen Brisboise");
                SendQuickMenu(4093);
            }break;
        }
    }
};

void SetupBrill_Guard(ScriptMgr * mgr)
{
	GossipScript * brill = (GossipScript*) new BrillGuard();
	mgr->register_gossip_script(5725, brill);			// Deathguard Lundmark
	mgr->register_gossip_script(1738, brill);			// Deathguard Terrence
	mgr->register_gossip_script(1652, brill);			// Deathguard Burgess
	mgr->register_gossip_script(1746, brill);			// Deathguard Cyrus
	mgr->register_gossip_script(1745, brill);			// Deathguard Morris
	mgr->register_gossip_script(1743, brill);			// Deathguard Lawrence
	mgr->register_gossip_script(1744, brill);			// Deathguard Mort
	mgr->register_gossip_script(1496, brill);			// Deathguard Dillinger
	mgr->register_gossip_script(1742, brill);			// Deathguard Bartholomew
}