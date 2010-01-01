#include "StdAfx.h"
#include "Setup.h"
#include "../Common/EasyFunctions.h"

class WoodlandWalker : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(WoodlandWalker);
	WoodlandWalker(Creature * pCreature) : CreatureAIScript(pCreature)
	{
		pCreature->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, 35 );
	}
};

class WoodlandWalkerGossip : public GossipScript
{
public:
	void GossipHello(Object * pObject, Player * plr, bool AutoSend)
	{
		Creature *  pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?(TO_CREATURE(pObject)):NULLCREATURE;
		if( pCreature == NULL )
			return;

		uint32 chance = RandomUInt(1);
		if( chance == 0 )
		{
			pCreature->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, 14 );
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "The Woodlands Walker is angered by your request and attacks!" );
		}
		else
		{
			sEAS.AddItem( 36786, plr );
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Breaking off a piece of its bark, the Woodlands Walker hands it to you before departing." );
		}

	}

	void Destroy()
	{
		delete this;
	};
};

class WrathGateQuestCinema : public QuestScript
{	
public:
  void OnQuestComplete(Player * mTarget, QuestLogEntry *qLogEntry)
  {
	if( mTarget == NULL )
		return;

	// send packet for movie
	uint32 id = 14;	
	mTarget->GetSession()->OutPacket(SMSG_TRIGGER_MOVIE, sizeof(uint32), &id);
  }
};

void SetupDragonblight(ScriptMgr * mgr)
{
	mgr->register_creature_script(26421, &WoodlandWalker::Create);

	GossipScript * WW = (GossipScript*) new WoodlandWalkerGossip();
	mgr->register_gossip_script(26421, WW);
	
	QuestScript *WrathGateCinema = (QuestScript*) new WrathGateQuestCinema();
	mgr->register_quest_script(12499, WrathGateCinema);
	mgr->register_quest_script(12500, WrathGateCinema);
}