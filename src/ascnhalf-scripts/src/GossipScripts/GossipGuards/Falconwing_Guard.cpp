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

class FalconwingGuard : public GossipScript
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
        Menu->AddItem(0, "Bat Handler", 1);
        Menu->AddItem(0, "Guild Master", 2);
        Menu->AddItem(0, "The Inn", 3);
        Menu->AddItem(0, "Stable Master", 4);
        Menu->AddItem(0, "Class Trainer", 5);
        Menu->AddItem(0, "Profession Trainer", 6);
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

        case 1:     //Bat Handler
            SendQuickMenu(2593);
			Plr->Gossip_SendPOI(9376.4, -7164.92, 7, 6, 0, "Silvermoon City, Flight Master");
            break;

        case 2:     //Guild Master
            SendQuickMenu(2593);
			break;
			
        case 3:     //The Inn
            SendQuickMenu(2593);
            Plr->Gossip_SendPOI(9476.916, -6859.2, 7, 6, 0, "Falconwing Square, Innkeeper");
			break;

        case 4:     //Stable Master
            SendQuickMenu(2593);
            Plr->Gossip_SendPOI(9487.6, -6830.59, 7, 6, 0, "Falconwing Square, Stable Master");
            break;

        case 5:     //Class Trainer
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4292, Plr);
                Menu->AddItem( 0, "Druid"        , 7);
				Menu->AddItem( 0, "Hunter"       , 8);
				Menu->AddItem( 0, "Mage"         , 9);
				Menu->AddItem( 0, "Paladin"     , 10);
                Menu->AddItem( 0, "Priest"      , 11);
				Menu->AddItem( 0, "Rogue"       , 12);
                Menu->AddItem( 0, "Warlock"     , 13);
                Menu->SendTo(Plr);
			}break;

        case 6:     // Profession Trainer
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);
                Menu->AddItem( 0, "Alchemy"           , 14);
                Menu->AddItem( 0, "Blacksmithing"     , 15);
                Menu->AddItem( 0, "Cooking"           , 16);
                Menu->AddItem( 0, "Enchanting"        , 17);
                Menu->AddItem( 0, "Engineering"       , 18);
                Menu->AddItem( 0, "First Aid"         , 19);
                Menu->AddItem( 0, "Fishing"           , 20);
                Menu->AddItem( 0, "Herbalism"         , 21);
				Menu->AddItem( 0, "Jewelcrafting"     , 22);
                Menu->AddItem( 0, "Leatherworking"    , 23);
                Menu->AddItem( 0, "Mining"            , 24);
                Menu->AddItem( 0, "Skinning"          , 25);
                Menu->AddItem( 0, "Tailoring"         , 26);
                Menu->SendTo(Plr);
            }break;


            ////////////////
            // Class trainer submenu
            ////////

        case 7: //Druid
            {
                SendQuickMenu(2593);
            }break;

        case 8: //Hunter
            {
                Plr->Gossip_SendPOI(9529.2, -6864.58, 7, 6, 0, "Falconwing Square, Hunter Trainer");
                SendQuickMenu(2593);
            }break;

        case 9: //Mage
            {
                Plr->Gossip_SendPOI(9462.24, -6853.45, 7, 6, 0, "Falconwing Square, Mage Trainer");
                SendQuickMenu(2593);
            }break;

        case 10: //Paladin <-- Needs to change flag to other sign (don't know how to describe it)
			{
                Plr->Gossip_SendPOI(9516.05, -6870.96, 7, 6, 0, "Falconwing Square, Paladin Trainer");
                SendQuickMenu(2593);
            }break;

        case 11: //Priest
            {
                Plr->Gossip_SendPOI(9466.62, -6844.23, 7, 6, 0, "Falconwing Square, Priest Trainer");
                SendQuickMenu(2593);
            }break;

        case 12: //Rogue
            {
                Plr->Gossip_SendPOI(9534.15, -6876.0, 7, 6, 0, "Falconwing Square, Rogue Trainer");
                SendQuickMenu(2593);
            }break;

        case 13: //Warlock
            {
                Plr->Gossip_SendPOI(9467.63, -6862.82, 7, 6, 0, "Falconwing Square, Warlock Trainer");
                SendQuickMenu(2593);
            }break;

        case 14: //Alchemy
            {
				Plr->Gossip_SendPOI(8661.36, -6367.0, 7, 6, 0, "Saltheril's Haven, Alchemist");
                SendQuickMenu(2593);
            }break;

        case 15: //Blacksmithing
            {
				Plr->Gossip_SendPOI(8986.43, -7419.07, 7, 6, 0, "Farstrider Retreat, Blacksmith");
                SendQuickMenu(2593);
            }break;

        case 16: //Cooking
            {
				Plr->Gossip_SendPOI(9494.86, -6879.45, 7, 6, 0, "Falconwing Square, Cook");
                SendQuickMenu(2593);
            }break;

        case 17: //Enchanting
            {
				Plr->Gossip_SendPOI(8657.6, -6366.7, 7, 6, 0, "Saltheril's Haven, Enchanter");
				SendQuickMenu(2593);
            }break;
			
        case 18: //Engineering
            {
                SendQuickMenu(2593);
            }break;

        case 19: //First Aid
            {
                Plr->Gossip_SendPOI(9479.53, -6880.07, 7, 6, 0, "Falconwing Square, First Aid");
                SendQuickMenu(2593);
            }break;

        case 20: //Fishing
            {
                SendQuickMenu(2593);
            }break;

        case 21: //Herbalism
            {
				Plr->Gossip_SendPOI(8678.92, -6329.09, 7, 6, 0, "Saltheril's Haven, Herbalist");
                SendQuickMenu(2593);
            }break;

        case 22: //Jewelcrafting
            {
				Plr->Gossip_SendPOI(9484.79, -6876.58, 7, 6, 0, "Falconwing Square, Jewelcrafter");
                SendQuickMenu(2593);
            }break;

        case 23: //Leatherworking
            {
				Plr->Gossip_SendPOI(9363.75, -7130.75, 7, 6, 0, "Eversong Woods, Leatherworker");
                SendQuickMenu(2593);
            }break;

        case 24: //Mining
            {
                SendQuickMenu(2593);
            }break;

        case 25: //Skinning
            {
				Plr->Gossip_SendPOI(9362.89, -7134.58, 7, 6, 0, "Eversong Woods, Skinner");
                SendQuickMenu(2593);
            }break;

		case 26: //Tailoring
            {
				Plr->Gossip_SendPOI(8680.36, -6327.51, 7, 6, 0, "Saltheril's Haven, Tailor");
                SendQuickMenu(2593);
            }break;
        }
    }
};

void SetupFalconwing_Guard(ScriptMgr * mgr)
{
	GossipScript * falcon = (GossipScript*) new FalconwingGuard();
	mgr->register_gossip_script(16221, falcon);			// Silvermoon Guardian
}