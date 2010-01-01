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

class ShattrathGuard : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10524, Plr);

        Menu->AddItem(0, "World's End Tavern", 1);
        Menu->AddItem(0, "Bank", 2);
        Menu->AddItem(0, "Inn", 3);
        Menu->AddItem(0, "Flight Master", 4);
        Menu->AddItem(0, "Mailbox", 5);    
        Menu->AddItem(0, "Stable Master", 6);
        Menu->AddItem(0, "Battlemaster", 7);
        Menu->AddItem(0, "Profession Trainer", 8);
        Menu->AddItem(0, "Mana Loom", 9);
        Menu->AddItem(0, "Alchemy Lab", 10);
        Menu->AddItem(0, "Gem Merchant", 11);

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
            // Menus
            /////

        case 1:     // World's End Tavern
            SendQuickMenu(10394);
            Plr->Gossip_SendPOI(-1760.4, 5166.9, 7, 6, 0, "World's End Tavern");
            break;

        case 2:     // Shattrath Banks
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10395, Plr);
                Menu->AddItem( 0, "Aldor Bank"          , 12);
                Menu->AddItem( 0, "Scryers Bank"         , 13);
                Menu->SendTo(Plr);
            }break;


        case 3:     // Inn's
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10398, Plr);
                Menu->AddItem( 0, "Aldor inn"          , 14);
                Menu->AddItem( 0, "Scryers inn"         , 15);
                Menu->SendTo(Plr);
            }break;

        case 4:     // Gryphon Master
            SendQuickMenu(10402);
            Plr->Gossip_SendPOI(-1831.9, 5298.2, 7, 6, 0, "Gryphon Master");
            break;

        case 5:     // Mailboxes
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10403, Plr);
                Menu->AddItem( 0, "Aldor inn"          , 16);
                Menu->AddItem( 0, "Scryers inn"         , 17);
				Menu->AddItem( 0, "Aldor Bank"          , 18);
                Menu->AddItem( 0, "Scryers Bank"         , 19);
                Menu->SendTo(Plr);
            }break;

        case 6:     // Stable Masters
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10404, Plr);
                Menu->AddItem( 0, "Aldor Stable"          , 20);
                Menu->AddItem( 0, "Scryers Stable"         , 21);
                Menu->SendTo(Plr);
            }break;

        case 7:     // Battlemasters
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10405, Plr);
                Menu->AddItem( 0, "Alliance Battlemasters"          , 22);
                Menu->AddItem( 0, "Horde & Arena Battlemasters"         , 23);
                Menu->SendTo(Plr);
            }break;

        case 8:     // Proffesion Trainers
			{
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10391, Plr);
                Menu->AddItem( 0, "Alchemy"          , 24);
                Menu->AddItem( 0, "Blacksmithing"         , 25);
				Menu->AddItem( 0, "Cooking"          , 26);
                Menu->AddItem( 0, "Enchanting"         , 27);
                Menu->AddItem( 0, "First Aid"          , 28);
                Menu->AddItem( 0, "Jewelcrafting"         , 29);
				Menu->AddItem( 0, "Leatherworking"          , 30);
                Menu->AddItem( 0, "Skinning"         , 31);
                Menu->SendTo(Plr);
            }break;

        case 9:     // Mana Loom
            SendQuickMenu(10408);
            Plr->Gossip_SendPOI(-2073.9, 5265.7, 7, 6, 0, "Mana Loom");
            break;

        case 10:    // Alchemy Lab
            SendQuickMenu(10409);
            Plr->Gossip_SendPOI(-1648.1, 5537.3, 7, 6, 0, "Alchemy Lab");
            break;

        case 11:    // Gem Merchants
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10410, Plr);
                Menu->AddItem( 0, "Aldor Gem Merchant"          , 32);
                Menu->AddItem( 0, "Scryer Gem Merchant"         , 33);
                Menu->SendTo(Plr);
            }break;

            //////////////////////
            // Banks
            /////

        case 12: //Aldor Bank
            {
                Plr->Gossip_SendPOI(-1730.8, 5496.2, 7, 6, 0, "Aldor Bank");
                SendQuickMenu(10396);
            }break;

        case 13: //Scryers Bank
            {
                Plr->Gossip_SendPOI(-1999.6, 5362.0, 7, 6, 0, "Scryers Bank");
                SendQuickMenu(10397);
            }break;

            //////////////////////
            // Inns
            /////

        case 14: //Aldor Inn
            {
                Plr->Gossip_SendPOI(-1897.5, 5767.6, 7, 6, 0, "Aldor inn");
                SendQuickMenu(10399);
            }break;

        case 15: //Scryers Inn
            {
                Plr->Gossip_SendPOI(-2180.6, 5403.9, 7, 6, 0, "Scryers inn");
                SendQuickMenu(10401);
            }break;

            //////////////////////
            // Mailboxes
            /////

        case 16: //Aldor Inn
            {
                Plr->Gossip_SendPOI(-1886.9, 5761.5, 7, 6, 0, "Aldor Inn");
                SendQuickMenu(10399);
            }break;

        case 17: //Scryers Bank
            {
                Plr->Gossip_SendPOI(-2175.0, 5411.7, 7, 6, 0, "Scryers Bank");
                SendQuickMenu(10397);
            }break;

        case 18: //Aldor Bank
            {
                Plr->Gossip_SendPOI(-1695.5, 5521.8, 7, 6, 0, "Aldor Bank");
                SendQuickMenu(10396);
            }break;

        case 19: //Scryers Inn
            {
                Plr->Gossip_SendPOI(-2033.0, 5336.1, 7, 6, 0, "Scryers Inn");
                SendQuickMenu(10401);
            }break;

            //////////////////////
            // Stable Masters
            /////

        case 20: //Aldor Stable Master
            {
                Plr->Gossip_SendPOI(-1889.6, 5761.5, 7, 6, 0, "Aldor Stable");
                SendQuickMenu(10399);
            }break;

        case 21: //Scryers Stable Master
            {
                Plr->Gossip_SendPOI(-2170.0, 5404.6, 7, 6, 0, "Scryers Stable");
                SendQuickMenu(10401);
            }break;

            //////////////////////
            // Battlemasters
            /////

        case 22: //Alliance Battlemaster
            {
                Plr->Gossip_SendPOI(-1831.9, 5298.2, 7, 6, 0, "Alliance Battlemasters");
                SendQuickMenu(10406);
            }break;

        case 23: //Horde Battle Master and Arena Battle Master
            {
                Plr->Gossip_SendPOI(-1968.7, 5262.2, 7, 6, 0, "Horde & Arena Battlemasters");
                SendQuickMenu(10407);
            }break;

            //////////////////////
            // Profession Trainers
            /////

        case 24: //Alchemy
            {
                Plr->Gossip_SendPOI(-1661.0, 5538, 7, 6, 0, "Alchemy Trainer");
                SendQuickMenu(10413);
            }break;

        case 25: //Blacksmithing
            {
                Plr->Gossip_SendPOI(-1847.7, 5230.3, 7, 6, 0, "Blacksmithing Trainer");
                SendQuickMenu(10400);
            }break;

        case 26: //Cooking
            {
                Plr->Gossip_SendPOI(-2067.4, 5316.5, 7, 6, 0, "Cooking Trainer");
                SendQuickMenu(10414);
            }break;

        case 27: //Enchanting
            {
                Plr->Gossip_SendPOI(-2278.5, 5567.7, 7, 6, 0, "Enchanting Trainer");
                SendQuickMenu(10415);
            }break;

        case 28: //First Aid
            {
                Plr->Gossip_SendPOI(-1592.0, 5263.7, 7, 6, 0, "First Aid Trainer");
                SendQuickMenu(10416);
            }break;

        case 29: //Jewelcrafting
            {
                Plr->Gossip_SendPOI(-1653.3, 5665.1, 7, 6, 0, "Jewelcrafting Trainer");
                SendQuickMenu(10417);
            }break;

        case 30: //Leatherworking
            {
                Plr->Gossip_SendPOI(-2060.9, 5256.6, 7, 6, 0, "Leatherworking Trainer");
                SendQuickMenu(10418);
            }break;

        case 31: //Skinning
            {
                Plr->Gossip_SendPOI(-2047.9, 5299.6, 7, 6, 0, "Skinning Trainer");
                SendQuickMenu(10419);
            }break;

            //////////////////////
            // Gem Merchants
            /////

        case 32: //Aldor gem merchant
            {
                Plr->Gossip_SendPOI(-1649.3, 5668.6, 7, 6, 0, "Aldor gem merchant");
                SendQuickMenu(10411);
            }break;

        case 33: //Scryers gem merchant
            {
                Plr->Gossip_SendPOI(-2193.9, 5422.1, 7, 6, 0, "Scryers gem merchant");
                SendQuickMenu(10412);
            }break;

        }
    }
};

void SetupShattrath_Guard(ScriptMgr * mgr)
{
	GossipScript * shattr = (ShattrathGuard*) new ShattrathGuard();
	mgr->register_gossip_script(19687, shattr);			// Shattrath City Guard -by AeThIs
	mgr->register_gossip_script(18568, shattr);			// Shattrath City Guard Aruspice -by AeThIs
	mgr->register_gossip_script(18549, shattr);			// Shattrath City Guard -by AeThIs
}