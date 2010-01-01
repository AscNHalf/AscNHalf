/* AscNHalf */

#include "StdAfx.h"
#include "Setup.h"

#define GOSSIP_SALESMAN		"I would like to get a Demolisher."
#define BG_DEMOLISHER	28781

const float spawncoordinates[2][4] = {
	{1353.65f, 224.56f, 35.20f, 4.31f},
	{1371.41f, -317.01f, 34.99f, 1.92f},
};

// Gorgril Rigspark1s GossipScript
class SOTA_Gossip_Gorgril : public GossipScript
{
public:
    void GossipHello(Object * pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
        // Check mapID
        if(plr->GetMapId() == 607)
        {
           objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
		   Menu->AddItem( 0, GOSSIP_SALESMAN, 1);
        }
        else
        {
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);	// send an empty menu
        }
        
        if(AutoSend)
            Menu->SendTo(plr);
    }

    void GossipSelectOption(Object * pObject, Player * plr, uint32 Id, uint32 IntId, const char * Code)
    {
        if(pObject->GetTypeId()!=TYPEID_UNIT)
			return;
		
        switch(IntId)
        {
		case 0:
			GossipHello(pObject, plr, true);
			break;

        case 1:
			plr->Gossip_Complete();
			Creature* veh = plr->GetMapMgr()->GetInterface()->SpawnCreature(BG_DEMOLISHER, spawncoordinates[0][0], spawncoordinates[0][1], spawncoordinates[0][2], spawncoordinates[0][3], true, false, 0, 0);
			break;
		}
    }

    void Destroy()
    {
        delete this;
    }
};

// Rigger Sparklight's GossipScript
class SOTA_Gossip_Rigger : public GossipScript
{
public:
    void GossipHello(Object * pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
        // Check mapID
        if(plr->GetMapId() == 607)
        {
           objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
		   Menu->AddItem( 0, GOSSIP_SALESMAN, 1);
        }
        else
        {
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);	// send an empty menu
        }
        
        if(AutoSend)
            Menu->SendTo(plr);
    }

    void GossipSelectOption(Object * pObject, Player * plr, uint32 Id, uint32 IntId, const char * Code)
    {
        if(pObject->GetTypeId()!=TYPEID_UNIT)
			return;
		
        switch(IntId)
        {
		case 0:
			GossipHello(pObject, plr, true);
			break;

        case 1:
			plr->Gossip_Complete();
			Creature* veh = plr->GetMapMgr()->GetInterface()->SpawnCreature(BG_DEMOLISHER, spawncoordinates[1][0], spawncoordinates[1][1], spawncoordinates[1][2], spawncoordinates[1][3], true, false, 0, 0);
			break;
		}
    }

    void Destroy()
    {
        delete this;
    }
};

void SetupSOTAGossip(ScriptMgr * mgr)
{
	GossipScript * Gorgril = (GossipScript*) new SOTA_Gossip_Gorgril;
	mgr->register_gossip_script(29262, Gorgril);	// Gorgril Rigspark
	GossipScript * Rigger = (GossipScript*) new SOTA_Gossip_Rigger;
	mgr->register_gossip_script(29260, Rigger);		// Rigger Sparklight
}
