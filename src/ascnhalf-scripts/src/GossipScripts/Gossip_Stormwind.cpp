/*
 * Moon++ Scripts for Ascent MMORPG Server
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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

#include "StdAfx.h"
#include "Setup.h"

// Archmage Malin
#define GOSSIP_ARCHMAGE_MALIN    "Can you send me to Theramore? I have an urgent message for Lady Jaina from Highlord Bolvar."

class ArchmageMalin_Gossip : public GossipScript
{
public:
    void GossipHello(Object * pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11469, plr);

		if(plr->GetQuestLogForEntry(11223))
        Menu->AddItem( 0, GOSSIP_ARCHMAGE_MALIN, 1);
        
        if(AutoSend)
            Menu->SendTo(plr);
    }

    void GossipSelectOption(Object * pObject, Player * plr, uint32 Id, uint32 IntId, const char * Code)
    {
		Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?(TO_CREATURE(pObject)):NULLCREATURE;
		if(pObject->GetTypeId()!=TYPEID_UNIT)
			return;
		
		switch(IntId)
        {
        case 1:
			{
				plr->Gossip_Complete();
				pCreature->CastSpell(plr, dbcSpell.LookupEntry(42711), true);
            }break;
		}
    }

    void Destroy()
    {
        delete this;
    }
};

#define GOSSIP_IRONWING         "I'd like to take a flight around Stormwind Harbor."

class Ironwing_Gossip : public GossipScript
{
public:
    void GossipHello(Object * pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13454, plr);

        Menu->AddItem( 0, GOSSIP_IRONWING, 1);
        
        if(AutoSend)
            Menu->SendTo(plr);
    }

    void GossipSelectOption(Object * pObject, Player * plr, uint32 Id, uint32 IntId, const char * Code)
    {
		Creature * pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?(TO_CREATURE(pObject)):NULLCREATURE;
		if(pObject->GetTypeId()!=TYPEID_UNIT)
			return;
		
		switch(IntId)
        {
        case 1:
			{
				TaxiPath * path = sTaxiMgr.GetTaxiPath( 1041 ); // Flight Path
				plr->TaxiStart( path, 1149, 0 ); // Gryph
            }break;
		}
    }

    void Destroy()
    {
        delete this;
    }
};


void SetupStormwindGossip(ScriptMgr * mgr)
{
	GossipScript * ArchmageMalinGossip = (GossipScript*) new ArchmageMalin_Gossip;
	GossipScript * IronwingGossip = (GossipScript*) new Ironwing_Gossip;

	mgr->register_gossip_script(2708, ArchmageMalinGossip); // Archmage Malin
	mgr->register_gossip_script(29154, IronwingGossip); // Thargold Ironwing

}
