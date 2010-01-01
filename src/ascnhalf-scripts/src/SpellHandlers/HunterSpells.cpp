/****************************************************************************
 *
 * SpellHandler Plugin
 * Copyright (c) 2007 Team Ascent
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to Creative Commons,
 * 543 Howard Street, 5th Floor, San Francisco, California, 94105, USA.
 *
 * EXCEPT TO THE EXTENT REQUIRED BY APPLICABLE LAW, IN NO EVENT WILL LICENSOR BE LIABLE TO YOU
 * ON ANY LEGAL THEORY FOR ANY SPECIAL, INCIDENTAL, CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES
 * ARISING OUT OF THIS LICENSE OR THE USE OF THE WORK, EVEN IF LICENSOR HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */

#include "StdAfx.h"
#include "Setup.h"

bool Refocus(uint32 i, Spell * pSpell)
{
    Player * playerTarget = pSpell->GetPlayerTarget();
    if(playerTarget == 0) return true;

    SpellSet::const_iterator itr = playerTarget->mSpells.begin();
    for(; itr != playerTarget->mSpells.end(); ++itr)
    {
        if((*itr) == 24531)       // skip calling spell.. otherwise spammies! :D
            continue;

        if((*itr) == 19434 || (*itr) == 20900 || (*itr) == 20901 || (*itr) == 20902 || (*itr) == 20903 || (*itr) == 20904 || (*itr) == 27632
            || (*itr) == 2643 || (*itr) == 14288|| (*itr) == 14289|| (*itr) == 14290 || (*itr) == 25294 || (*itr) == 14443 || (*itr) == 18651 || (*itr) == 20735 || (*itr) == 21390
            || (*itr) == 1510 || (*itr) == 14294 || (*itr) == 14295 || (*itr) == 1540 || (*itr) == 22908
            || (*itr) == 3044 || (*itr) == 14281 || (*itr) == 14282 || (*itr) == 14283 || (*itr) == 14284 || (*itr) == 14285 || (*itr) == 14286 || (*itr) == 14287)
            playerTarget->ClearCooldownForSpell((*itr));
    }
    return true;
}

bool Readiness(uint32 i, Spell * pSpell)
{
    if(!pSpell->p_caster)
		return true;
    pSpell->p_caster->ClearCooldownsOnLine(50 , pSpell->m_spellInfo->Id);//Beast Mastery
    pSpell->p_caster->ClearCooldownsOnLine(163, pSpell->m_spellInfo->Id);//Marksmanship
    pSpell->p_caster->ClearCooldownsOnLine(51 , pSpell->m_spellInfo->Id);//Survival
    return true;
}

#ifdef ASCENT_CORE

class RevivePet : public SpellScript
{
public:
	ADD_SPELL_FACTORY_FUNCTION(RevivePet);
	RevivePet(Spell * pSpell) : SpellScript(pSpell) {}
	SpellCastError CanCast(bool tolerate)
	{
		if (_spell->p_caster == NULL || _spell->p_caster->GetSummon() == NULL)
			return SPELL_FAILED_NO_PET;
			
		if (!_spell->p_caster->GetSummon()->isDead())
			return SPELL_FAILED_TARGET_NOT_DEAD;

		return SPELL_CANCAST_OK;
	}
};

class SteadyShot : public SpellScript
{
public:
	ADD_SPELL_FACTORY_FUNCTION(SteadyShot);
	SteadyShot(Spell * pSpell) : SpellScript(pSpell) {}
	void CalculateEffect(uint32 EffectIndex, Unit *  target, int32* value)
	{
		if(EffectIndex == 0 && _spell->u_caster != NULL)
		{
			if( _spell->p_caster != NULL )
			{
				Item *it;
				if(_spell->p_caster->GetItemInterface())
				{
					it = _spell->p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED);
					if(it)
					{
						float weapondmg = it->GetProto()->Damage[0].Min + RandomFloat( it->GetProto()->Damage[0].Max );
						*value += float2int32(150 + weapondmg/float(it->GetProto()->Delay/1000.0f)*2.8f);
					}
				}
			}
			if(target && target->IsDazed())
				*value += 175;
			*value += (uint32)(_spell->u_caster->GetRAP()*0.2);
		}
	}
};

class MongooseBite : public SpellScript
{
public:
	ADD_SPELL_FACTORY_FUNCTION(MongooseBite);
	MongooseBite(Spell * pSpell) : SpellScript(pSpell) {}
	void CalculateEffect(uint32 EffectIndex, Unit *  target, int32* value)
	{
		if( _spell->u_caster != NULL )
			*value += _spell->u_caster->GetAP()/5;
	}
};

#endif

void SetupHunterSpells(ScriptMgr * mgr)
{
    mgr->register_dummy_spell(24531, &Refocus);
    mgr->register_dummy_spell(23989, &Readiness);
#ifdef ASCENT_CORE
	mgr->register_spell_script(982, &RevivePet::Create);
	mgr->register_spell_script(34128, &SteadyShot::Create);
	mgr->register_spell_script(1495, &MongooseBite::Create);
	mgr->register_spell_script(14269, &MongooseBite::Create);
	mgr->register_spell_script(14270, &MongooseBite::Create);
	mgr->register_spell_script(14271, &MongooseBite::Create);
	mgr->register_spell_script(36916, &MongooseBite::Create);
#endif
}
