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

class GoldshireGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4259, Plr);
		Menu->AddItem( 0, "Bank"                 , 1);
		Menu->AddItem( 0, "Gryphon Master"       , 2);
		Menu->AddItem( 0, "Guild Master"         , 3);
		Menu->AddItem( 0, "Inn"                  , 4);
		Menu->AddItem( 0, "Stable Master"        , 5);
		Menu->AddItem( 0, "Class Trainer"        , 6);
		Menu->AddItem( 0, "Profession Trainer"   , 7);
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
			SendQuickMenu(4260);
			break;

		case 2:     //Gryphon Master
	        SendQuickMenu(4261);
		    break;

		case 3:     //Guild Master
			SendQuickMenu(4262);
		    break;
	
	   case 4:     //Inn
	       SendQuickMenu(4263);
	       Plr->Gossip_SendPOI(-9459.34, 42.08, 99, 6, 0, "Lion's Pride Inn");
	      break;

	   case 5:     //Stable Master
	       SendQuickMenu(5983);
	       Plr->Gossip_SendPOI(-9466.62, 45.87, 99, 6, 0, "Erma");
	        break;

	   case 6:     //Class Trainer
		   {
		   objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4264, Plr);

	       Menu->AddItem( 0, "Druid",                8);
	       Menu->AddItem( 0, "Hunter",               9);
	       Menu->AddItem( 0, "Mage",                 10);
	       Menu->AddItem( 0, "Paladin",              11);
	       Menu->AddItem( 0, "Priest",               12);
	       Menu->AddItem( 0, "Rogue",                13);
		   Menu->AddItem( 0, "Shaman",               14);
	       Menu->AddItem( 0, "Warlock",              15);
		   Menu->AddItem( 0, "Warrior",              16);

			Menu->SendTo(Plr);
		   }break;

		case 7:		//Profession Trainer
			{
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);

			Menu->AddItem( 0, "Alchemy"              ,17);
			Menu->AddItem( 0, "Blacksmithing"        ,18);
			Menu->AddItem( 0, "Cooking"              ,19);
			Menu->AddItem( 0, "Enchanting"           ,20);
			Menu->AddItem( 0, "Engineering"          ,21);
			Menu->AddItem( 0, "First Aid"            ,22);
			Menu->AddItem( 0, "Fishing"              ,23);
			Menu->AddItem( 0, "Herbalism"            ,24);
			Menu->AddItem( 0, "Inscription"       , 25);
			Menu->AddItem( 0, "Leatherworking"       ,26);
			Menu->AddItem( 0, "Mining"               ,27);
			Menu->AddItem( 0, "Skinning"             ,28);
			Menu->AddItem( 0, "Tailoring"            ,29);
			Menu->SendTo(Plr);
			}break;

		case 8: //Druid
            {
                SendQuickMenu(4265);
            }break;

		case 9: //Hunter
            {
                SendQuickMenu(4266);
            }break;

		case 10: //Mage
            {
                Plr->Gossip_SendPOI(-9471.12, 33.44, 7, 6, 0, "Zaldimar Wefhellt");
                SendQuickMenu(4268);
            }break;

		case 11: //Paladin
            {
                Plr->Gossip_SendPOI(-9469, 108.05, 7, 6, 0, "Brother Wilhelm");
                SendQuickMenu(4269);
            }break;

		case 12: //Priest
            {
                Plr->Gossip_SendPOI(-9461.07, 32.6, 7, 6, 0, "Priestess Josetta");
                SendQuickMenu(4267);
            }break;

		case 13: //Rogue
            {
                Plr->Gossip_SendPOI(-9465.13, 13.29, 7, 6, 0, "Keryn Sylvius");
                SendQuickMenu(4270);
            }break;

		case 14: //Shaman
            {
                SendQuickMenu(10101);
            }break;

		case 15: //Warlock
            {
                Plr->Gossip_SendPOI(-9473.21, -4.08, 7, 6, 0, "Maximillian Crowe");
                SendQuickMenu(4272);
            }break;

		case 16: //Warrior
            {
                Plr->Gossip_SendPOI(-9461.82, 109.50, 7, 6, 0, "Lyria Du Lac");
                SendQuickMenu(4271);
            }break;

		case 17: //Alchemy
            {
                Plr->Gossip_SendPOI(-9057.04, 153.63, 7, 6, 0, "Alchemist Mallory");
                SendQuickMenu(4274);
            }break;

		case 18: //Blacksmithing
            {
                Plr->Gossip_SendPOI(-9456.58, 87.90, 7, 6, 0, "Smith Argus");
                SendQuickMenu(4275);
            }break;

		case 19: //Cooking
            {
                Plr->Gossip_SendPOI(-9467.54, -3.16, 7, 6, 0, "Tomas");
                SendQuickMenu(4276);
            }break;

		case 20: //Enchanting
            {
                SendQuickMenu(4277);
            }break;

		case 21: //Engineering
            {
                SendQuickMenu(4278);
            }break;

		case 22: //First Aid
            {
                Plr->Gossip_SendPOI(-9456.82, 30.49, 7, 6, 0, "Michelle Belle");
                SendQuickMenu(4279);
            }break;

		case 23: //Fishing
            {
                Plr->Gossip_SendPOI(-9386.54, -118.73, 7, 6, 0, "Lee Brown");
                SendQuickMenu(4280);
            }break;

		case 24: //Herbalism
            {
                Plr->Gossip_SendPOI(-9060.70, 149.23, 7, 6, 0, "Herbalist Pomeroy");
                SendQuickMenu(4281);        
            }break;

		case 25: //Inscription
            {
                Plr->Gossip_SendPOI(-8853.33, 857.66, 7, 6, 0, "Stormwind Inscription");
                SendQuickMenu(13881);
            }break;

		case 26: //Leatherworking
            {
                Plr->Gossip_SendPOI(-9376.12, -75.23, 7, 6, 0, "Adele Fielder");
                SendQuickMenu(4282);
            }break;

		case 27: //Mining
            {
                SendQuickMenu(4283);
            }break;

		case 28: //Skinning
            {
                Plr->Gossip_SendPOI(-9536.91, -1212.76, 7, 6, 0, "Helene Peltskinner");
                SendQuickMenu(4284);
            }break;

		case 29: //Tailoring
            {
                Plr->Gossip_SendPOI(-9376.12, -75.23, 7, 6, 0, "Eldrin");
                SendQuickMenu(4285);
            }break;
		}
    }   
};

void SetupGoldshire_Guard(ScriptMgr * mgr)
{
	GossipScript * gold = (GossipScript*) new GoldshireGuard();
	mgr->register_gossip_script(1423, gold);			// Goldshire Guard 
}