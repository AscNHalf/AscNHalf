/**
  * External Battleground scripts.
  * Author: Twl
  * Team: AscNHalf
*/

#include "StdAfx.h"
#include "Setup.h"

#define TITAN_RELIC_ID 192829

class TitanRelic : public GameObjectAIScript
{
public:
	TitanRelic(GameObject* goinstance) : GameObjectAIScript(goinstance) { }
	static GameObjectAIScript * Create(GameObject* GO) { return new TitanRelic(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->m_bg && pPlayer->m_bg->GetType() == BATTLEGROUND_STRAND_OF_THE_ANCIENTS)
		{
			StrandOfTheAncients* sota = (StrandOfTheAncients*)pPlayer->m_bg;

			if(sota && sota != NULL)
			{
				sLog.outColor(TGREEN, "\nSOTA: OnActivate() called, relic clicked. SOTA is not NULL. Executing SOTARebuild().");
				sLog.outColor(TBLUE, "\nPlayer GUID:%u\n", pPlayer->GetGUID());

				sota->SOTARebuild(true);
			}
			else
			{
				sLog.outColor(TRED, "\nSOTA OnActivate() called, relic clicked. SOTA is NULL! Report!");
			}
		}
	}
};

void SetupBGScripts(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(TITAN_RELIC_ID, &TitanRelic::Create);
}