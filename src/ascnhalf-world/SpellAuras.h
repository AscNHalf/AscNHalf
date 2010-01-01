/* AscNHalf */

#ifndef _SPELLAURAS_H
#define _SPELLAURAS_H

#include "SpellAuraDefines.h"

struct Modifier
{
//    uint32 m_actamt;       // actual amt, for percent and stuff
    uint32 m_type;           // What does it modify? (str,int,hp)
    int32 m_amount;          // By how much does it mod?	always should be m_baseAmount * stackSize
	int32 m_baseAmount;		// amount per one stack
    int32 m_miscValue;       // Misc Value
    uint32 i;

    ///needed for per level effect
    int32 realamount;
    
	//need this to store % values or they cannot be reverted corectly (i think :D )
    int32 fixed_amount[7];

	// float fixed amounts
	float fixed_float_amount[7];
};


struct ProcTriggerSpellOnSpell
{
    uint32 origId;
    uint32 spellId;
    uint64 caster;
    uint32 procChance;
    uint32 procFlags;
    uint32 RemainingCharges;
    uint32 LastTrigger;
    void  *owner;//mark the owner of this proc to know which one to delete
};

struct DamageProc
{
    uint32 m_spellId;
    uint32 m_damage;
  //  uint64 m_caster;//log is: some reflects x arcane/nature damage to 'attacker' no matter who casted
    uint32 m_school;
    uint32 m_flags;
    void  *owner;//mark the owner of this proc to know which one to delete
};

struct ProcTriggerSpell
{
	uint32 origId;
	uint32 spellId;
	uint64 caster;
	uint32 procChance;
	uint32 procFlags;
	uint32 procCharges;
	uint32 LastTrigger;
	uint32 ProcType; //0=triggerspell/1=triggerclassspell
	uint32 SpellClassMask[3];
	uint32 weapon_damage_type; // 0=Any, 1=Main hand, 2=off hand
	bool deleted;
};

typedef set<uint32> AreaAuraList;

class SERVER_DECL Aura : public EventableObject
{
	uint64 periodic_target;
public:
    Aura(SpellEntry *proto, int32 duration,Object* caster, Unit* target);
	~Aura();

	void ExpireRemove();
    void Remove();
    void Expire();
    void AddMod(uint32 t, int32 a,uint32 miscValue,uint32 i);

    INLINE SpellEntry* GetSpellProto() const { return m_spellProto; }
    INLINE uint32 GetSpellId() const {return m_spellProto->Id; }
    INLINE bool IsPassive(){ if(!m_spellProto) return false; return (m_spellProto->Attributes & ATTRIBUTES_PASSIVE && !m_areaAura);}

    INLINE int32 GetDuration() const { return m_duration; }
    void SetDuration(int32 duration) { m_duration = duration; }
	void SetTimeLeft(int32 time);

	INLINE uint32 GetModCount() const { return m_modcount; }
	INLINE Modifier *GetMod(uint32 x) { return &m_modList[x]; }

    INLINE uint8 GetAuraSlot() const { return m_auraSlot; }
	void SetAuraSlot(uint8 slot) { m_auraSlot = slot; }
	INLINE uint8 GetAuraFlags() const { return m_auraFlags; }
	void SetAuraFlags(uint8 flags) { m_auraFlags = flags; }
	void SetAuraFlag(uint16 flag) { if( ! (m_auraFlags & flag ) ) m_auraFlags |= flag; };
	INLINE uint8 GetAuraLevel() const { return m_auraLevel; }
	void SetAuraLevel(uint8 level) { m_auraLevel = level; }

	INLINE bool IsPositive() { return m_positive>0; }
	void SetNegative(signed char value=1) { m_positive -= value; }
	void SetPositive(signed char value=1) { m_positive += value; }

	bool m_applied;

	Unit* GetUnitCaster();
	INLINE Object* GetCaster() {return TO_OBJECT(GetUnitCaster());}
	INLINE uint64 GetCasterGUID(){return m_casterGuid;}

	INLINE Object* GetTarget() {return ((m_target != NULL && m_target->IsInWorld()) ? TO_OBJECT(m_target): NULLOBJ);}
	INLINE Unit* GetUnitTarget() {return TO_UNIT(GetTarget());}
	INLINE uint64 GetTargetGUID(){return m_target->GetGUID();}



	void RemoveIfNecessary();

	Aura*  StrongerThat(Aura* aur);
	void ApplyModifiers(bool apply);
	void UpdateModifiers();
	void AddAuraVisual();
	void BuildAuraUpdate();
	void EventUpdateCreatureAA(float r);
	void EventUpdatePlayerAA(float r);
	void EventRelocateRandomTarget();
	void RemoveAA();
	void AttemptDispel(Unit* pCaster, bool canResist = true);
	bool m_dispelled;
	uint32 m_resistPctChance;
		
	INLINE uint32 GetTimeLeft()//in sec
	{
		if(m_duration==-1)return (uint32)-1;
		int32 n=int32((UNIXTIME-time_t(timeleft))*1000);
		if(n>=m_duration) return 0;
		else 
		return (m_duration-n);
	}

	INLINE uint32 GetMSExpiryTime()
	{ 		
		if (GetDuration() == -1)
			return -1;
		int32 n = getMSTime() - timeleft;

		if (n > GetDuration())
			return 0;

		return (GetDuration() - n);
	}

	uint32 procCharges;
	uint32 GetMaxProcCharges(Unit* caster);
	void ModProcCharges(int32 mod);
	uint32 stackSize;
	void ModStackSize(int32 mod);
	void UpdateModAmounts();

		// Aura Handlers
	void SpellAuraNULL(bool apply);
	void SpellAuraBindSight(bool apply);
	void SpellAuraModPossess(bool apply);
	void SpellAuraPeriodicDamage(bool apply);
	void SpellAuraDummy(bool apply);
	void SpellAuraModConfuse(bool apply);
	void SpellAuraModCharm(bool apply);
	void SpellAuraModFear(bool apply);
	void SpellAuraPeriodicHeal(bool apply);
	void SpellAuraModAttackSpeed(bool apply);
	void SpellAuraModThreatGenerated(bool apply);
	void SpellAuraModTaunt(bool apply);
	void SpellAuraModStun(bool apply);
	void SpellAuraModDamageDone(bool apply);
	void SpellAuraModDamageTaken(bool apply);
	void SpellAuraDamageShield(bool apply);
	void SpellAuraModStealth(bool apply);
	void SpellAuraModDetect(bool apply);
	void SpellAuraModInvisibility(bool apply);
	void SpellAuraModInvisibilityDetection(bool apply);
	void SpellAuraModTotalHealthRegenPct(bool apply);
	void SpellAuraModTotalManaRegenPct(bool apply);
	void SpellAuraModResistance(bool apply);
	void SpellAuraPeriodicTriggerSpell(bool apply);
	void SpellAuraPeriodicEnergize(bool apply);
	void SpellAuraModPacify(bool apply);
	void SpellAuraModRoot(bool apply);
	void SpellAuraModSilence(bool apply);
	void SpellAuraReflectSpells(bool apply);
	void SpellAuraModStat(bool apply);
	void SpellAuraModSkill(bool apply);
	void SpellAuraModIncreaseSpeed(bool apply);
	void SpellAuraModDecreaseSpeed(bool apply);
	void SpellAuraModIncreaseHealth(bool apply);
	void SpellAuraModIncreaseEnergy(bool apply);
	void SpellAuraModShapeshift(bool apply);
	void SpellAuraModEffectImmunity(bool apply);
	void SpellAuraModStateImmunity(bool apply);
	void SpellAuraModSchoolImmunity(bool apply);
	void SpellAuraModDmgImmunity(bool apply);
	void SpellAuraModDispelImmunity(bool apply);
	void SpellAuraProcTriggerSpell(bool apply);
	void SpellAuraProcTriggerDamage(bool apply);
	void SpellAuraTrackCreatures(bool apply);
	void SpellAuraTrackResources(bool apply);	
	void SpellAuraModParryPerc(bool apply);	
	void SpellAuraModDodgePerc(bool apply);	
	void SpellAuraModBlockPerc(bool apply);
	void SpellAuraModCritPerc(bool apply);
	void SpellAuraPeriodicLeech(bool apply);
	void SpellAuraModHitChance(bool apply);
	void SpellAuraModSpellHitChance(bool apply);
	void SpellAuraTransform(bool apply);
	void SpellAuraModSpellCritChance(bool apply);
	void SpellAuraIncreaseSwimSpeed(bool apply);	
	void SpellAuraModCratureDmgDone(bool apply);
	void SpellAuraPacifySilence(bool apply);
	void SpellAuraModScale(bool apply);
	void SpellAuraPeriodicHealthFunnel(bool apply);	
	void SpellAuraPeriodicManaLeech(bool apply);
	void SpellAuraModCastingSpeed(bool apply);
	void SpellAuraFeignDeath(bool apply);
	void SpellAuraModDisarm(bool apply);
	void SpellAuraModStalked(bool apply);
	void SpellAuraSchoolAbsorb(bool apply);	
	void SpellAuraModSpellCritChanceSchool(bool apply);
	void SpellAuraModPowerCost(bool apply);
	void SpellAuraModPowerCostSchool(bool apply);
	void SpellAuraReflectSpellsSchool(bool apply);
	void SpellAuraModLanguage(bool apply);
	void SpellAuraAddFarSight(bool apply);
	void SpellAuraMechanicImmunity(bool apply);
	void SpellAuraMounted(bool apply);
	void SpellAuraModDamagePercDone(bool apply);
	void SpellAuraModPercStat(bool apply);
	void SpellAuraSplitDamage(bool apply);
	void SpellAuraWaterBreathing(bool apply);
	void SpellAuraModBaseResistance(bool apply);
	void SpellAuraModRegen(bool apply);
	void SpellAuraModPowerRegen(bool apply);
	void SpellAuraModHealingPct(bool apply);
	void SpellAuraChannelDeathItem(bool apply);
	void SpellAuraModDamagePercTaken(bool apply);
	void SpellAuraModRegenPercent(bool apply);
	void SpellAuraPeriodicDamagePercent(bool apply);
	void SpellAuraModResistChance(bool apply);
	void SpellAuraModDetectRange(bool apply);
	void SpellAuraPreventsFleeing(bool apply);
	void SpellAuraModUnattackable(bool apply);
	void SpellAuraInterruptRegen(bool apply);
	void SpellAuraGhost(bool apply);
	void SpellAuraMagnet(bool apply);
	void SpellAuraManaShield(bool apply);
	void SpellAuraSkillTalent(bool apply);
	void SpellAuraModAttackPower(bool apply);
	void SpellAuraVisible(bool apply);
	void SpellAuraModResistancePCT(bool apply);
	void SpellAuraModCreatureAttackPower(bool apply);
	void SpellAuraModTotalThreat(bool apply);
	void SpellAuraWaterWalk(bool apply);
	void SpellAuraFeatherFall(bool apply);
	void SpellAuraHover(bool apply);
	void SpellAuraAddFlatModifier(bool apply);
	void SpellAuraAddPctMod(bool apply);
	void SpellAuraAddTargetTrigger(bool apply);
	void SpellAuraModPowerRegPerc(bool apply);	
	void SpellAuraOverrideClassScripts(bool apply);
	void SpellAuraModRangedDamageTaken(bool apply);	
	void SpellAuraModHealing(bool apply);
	void SpellAuraIgnoreRegenInterrupt(bool apply);
	void SpellAuraModMechanicResistance(bool apply);
	void SpellAuraModHealingPCT(bool apply);   
	void SpellAuraEmphaty(bool apply);
	void SpellAuraUntrackable(bool apply);
	void SpellAuraModOffhandDamagePCT(bool apply);
	void SpellAuraModPenetration(bool apply);
	void SpellAuraModRangedAttackPower(bool apply);
	void SpellAuraModMeleeDamageTaken(bool apply);
	void SpellAuraModMeleeDamageTakenPct(bool apply);
	void SpellAuraRAPAttackerBonus(bool apply);
	void SpellAuraModPossessPet(bool apply);
	void SpellAuraModIncreaseSpeedAlways(bool apply);
	void SpellAuraModIncreaseMountedSpeed(bool apply);
	void SpellAuraModCreatureRangedAttackPower(bool apply);
	void SpellAuraModIncreaseEnergyPerc(bool apply);
	void SpellAuraModIncreaseHealthPerc(bool apply);
	void SpellAuraModManaRegInterrupt(bool apply);
	void SpellAuraModHealingDone(bool apply);
	void SpellAuraModHealingDonePct(bool apply);
	void SpellAuraModTotalStatPerc(bool apply);
	void SpellAuraModHaste(bool apply);
	void SpellAuraForceReaction(bool apply);
	void SpellAuraModRangedHaste(bool apply);
	void SpellAuraModRangedAmmoHaste(bool apply);
	void SpellAuraModBaseResistancePerc(bool apply);
	void SpellAuraModResistanceExclusive(bool apply);
	void SpellAuraSafeFall(bool apply);
	void SpellAuraRetainComboPoints(bool apply);
	void SpellAuraResistPushback(bool apply);
	void SpellAuraModShieldBlockPCT(bool apply);
	void SpellAuraTrackStealthed(bool apply);
	void SpellAuraModDetectedRange(bool apply);
	void SpellAuraSplitDamageFlat(bool apply);
	void SpellAuraModStealthLevel(bool apply);
	void SpellAuraModUnderwaterBreathing(bool apply);
	void SpellAuraModReputationAdjust(bool apply);
	void SpellAuraModIgnoreArmorPct(bool apply);
	void SpellAuraNoPVPCredit(bool apply);
	void SpellAuraModHealthRegInCombat(bool apply);
	void SpellAuraPowerBurn(bool apply);
	void SpellAuraModCritDmgPhysical(bool apply);
	void SpellAuraModPAttackPower(bool apply);
	void SpellAuraModRangedAttackPowerPct(bool apply);
	void SpellAuraAPAttackerBonus(bool apply);
	void SpellAuraIncreaseDamageTypePCT(bool apply);
	void SpellAuraIncreaseCricticalTypePCT(bool apply);
	void SpellAuraIncreasePartySpeed(bool apply);
	void SpellAuraIncreaseSpellDamageByAttribute(bool apply);
	void SpellAuraIncreaseHealingByAttribute(bool apply);
	void SpellAuraIncreaseArmorByPctInt(bool apply);
	void SpellAuraReduceAttackerMHitChance(bool apply);
	void SpellAuraReduceAttackerRHitChance(bool apply);
	void SpellAuraReduceAttackerSHitChance(bool apply);
	void SpellAuraReduceEnemyMCritChance(bool apply);
	void SpellAuraReduceEnemyRCritChance(bool apply);
	void SpellAuraUseNormalMovementSpeed(bool apply);
	void SpellAuraIncreaseTimeBetweenAttacksPCT(bool apply);
//	void SpellAuraIncreaseSpellDamageByInt(bool apply);
//	void SpellAuraIncreaseHealingByInt(bool apply);
	void SpellAuraIncreaseAllWeaponSkill(bool apply);
	void SpellAuraModAttackerCritChance(bool apply);
	void SpellAuraIncreaseHitRate(bool apply);
	void SpellAuraReduceCritMeleeAttackDmg(bool apply);
	void SpellAuraReduceCritRangedAttackDmg(bool apply);
	void SpellAuraEnableFlight(bool apply);
	void SpellAuraEnableFlightWithUnmountedSpeed(bool apply);
	void SpellAuraIncreaseRageFromDamageDealtPCT(bool apply);
	void SpellAuraIncreaseFlightSpeed(bool apply);
	void SpellAuraIncreaseMovementAndMountedSpeed(bool apply);
	void SpellAuraIncreaseRating(bool apply);
	void SpellAuraIncreaseCastTimePCT(bool apply);
	void SpellAuraRegenManaStatPCT(bool apply);
	void SpellAuraSpellHealingStatPCT(bool apply);
	void SpellAuraAuraModInvisibilityDetection(bool apply);
	void SpellAuraIncreaseMaxHealth(bool apply);
	void SpellAuraSpiritOfRedemption(bool apply);
	void SpellAuraIncreaseAttackerSpellCrit(bool apply);
	void SpellAuraIncreaseRepGainPct(bool apply);
	void SpellAuraIncreaseRangedAPStatPCT(bool apply);
	//void SpellAuraModRangedDamageTakenPCT(bool apply);
	void SpellAuraModBlockValue(bool apply);
	void SpellAuraFinishingMovesCannotBeDodged(bool apply);
	void SpellAuraExpertise(bool apply);
	void SpellAuraDrinkNew(bool apply);
	void SpellAuraModSpellDamageFromAP(bool apply);
	void SpellAuraModSpellHealingFromAP(bool apply);
	void SpellAuraSkipCanCastCheck(bool apply);
	void EventPeriodicDrink(uint32 amount);
	void SpellAuraModDamageTakenPctPerCaster(bool apply);
	void SpellAuraSetPhase(bool apply);
	void SpellAuraIncreaseAPByAttribute(bool apply);
	void SpellAuraVehiclePassenger(bool apply);
	void SpellAuraReduceEffectDuration(bool apply);
	void SpellAuraNoReagent(bool apply);
	void SpellAuraCastFilter(bool apply);
	void SpellAuraModBaseHealth(bool apply);
	void SpellAuraModDamageTakenByMechPCT(bool apply);
	void SpellAuraAddCreatureImmunity(bool apply);
	void SpellAuraRedirectThreat(bool apply);
	void SpellAuraReduceAOEDamageTaken(bool apply);
	void SpellAuraHasteRanged(bool apply);
	void SpellAuraReflectInfront(bool apply);
	void SpellAuraModPetTalentPoints(bool apply);
	
	void UpdateAuraModDecreaseSpeed();

	void SendModifierLog(int32 ** m,int32 v,uint32 *mask,uint8 type,bool pct = false);
	void SendDummyModifierLog(std::map<SpellEntry*,uint32> * m,SpellEntry * spellInfo,uint32 i,bool apply,bool pct = false);

	// Events
	void EventPeriodicDamage(uint32);
	void EventPeriodicDamagePercent(uint32);
	void EventPeriodicHeal(uint32);
	void EventPeriodicTriggerSpell(SpellEntry* spellInfo);
	void EventPeriodicEnergize(uint32,uint32);
	void EventPeriodicHeal1(uint32);
	void EventPeriodicLeech(uint32);
	void EventPeriodicBurn(uint32,uint32);
	void EventPeriodicHealthFunnel(uint32);
	void EventPeriodicManaLeech(uint32);
	void EventPeriodicHealPct(float);
	void EventPeriodicManaPct(float);
	void EventPeriodicRegenManaStatPct(uint32 perc,uint32 stat);
	void EventPeriodicSpeedModify(int32 mod);
	void RelocateEvents();
	int32 event_GetInstanceID();

	// log message's
	void SendPeriodicAuraLog(uint32 amt, uint32 Flags);
	static void SendPeriodicAuraLog(Unit* Caster, Unit* Target, SpellEntry *sp, uint32 Amount, uint32 abs_dmg, uint32 resisted_damage, uint32 Flags, uint32 pSpellId = 0);
	static void SendPeriodicAuraLog(const uint64& CasterGuid, Unit* Target, SpellEntry *sp, uint32 Amount, uint32 abs_dmg, uint32 resisted_damage, uint32 Flags, uint32 pSpellId = 0);

	bool WasCastInDuel() { return m_castInDuel; }

	SpellEntry * m_spellProto;
	Modifier * mod;
	AreaAuraList targets;//this is only used for AA

	uint32 m_auraSlot;

	uint32 m_castedItemId;
	bool m_areaAura;		// Area aura stuff -> never passive.
	uint8 m_auraFlags;
	uint8 m_auraLevel;
	uint32 pSpellId; //this represents the triggering spell id

	// this stuff can be cached in spellproto.
	INLINE bool IsCombatStateAffecting()
	{
		for(uint32 x = 0; x < 3; ++x) {
			if(m_spellProto->EffectApplyAuraName[x] == SPELL_AURA_PERIODIC_DAMAGE || 
				m_spellProto->EffectApplyAuraName[x] == SPELL_AURA_PERIODIC_DAMAGE_PERCENT ||
				m_spellProto->EffectApplyAuraName[x] == SPELL_AURA_PERIODIC_TRIGGER_SPELL ||
				m_spellProto->EffectApplyAuraName[x] == SPELL_AURA_PERIODIC_LEECH ||
				m_spellProto->EffectApplyAuraName[x] == SPELL_AURA_PERIODIC_MANA_LEECH)
			{
				return true;
			}
		}

		return false;
	}

	INLINE bool HasMechanic(uint32 MechanicsType)
	{
		return Spell::HasMechanic(m_spellProto, MechanicsType);
	}
	INLINE uint32 GetMechanic()
	{
		return Spell::GetMechanic(m_spellProto);
	}

	INLINE uint32 GetMechanicOfEffect(uint32 i)
	{
		return Spell::GetMechanicOfEffect(m_spellProto, i);
	}

	bool m_castInDuel;

private:
	uint32 GetCasterFaction() { return m_casterfaction; }
	void SetCasterFaction(uint32 faction){ m_casterfaction = faction; }
	INLINE void DurationPctMod(uint32 mechanic);

	INLINE bool IsInrange(float x1,float y1, float z1, Object* o,float square_r)
	{
		float t;
		float r;
		t=x1-o->GetPositionX();
		r=t*t;
		t=y1-o->GetPositionY();
		r+=t*t;
		t=z1-o->GetPositionZ();
		r+=t*t;
		return ( r<=square_r);
	}
	
	Unit* m_target;
	uint64 m_casterGuid;

	uint32 timeleft;
	int32 m_duration; // in msecs
//	bool m_positive;
	signed char m_positive;

	uint32 m_modcount;
	Modifier m_modList[3];

	uint32 m_dynamicValue;

protected:
	uint32 m_casterfaction;

	void SendInterrupted(uint8 result, Object* m_caster);
	void SendChannelUpdate(uint32 time, Object* m_caster);
	void SpecialCases();
public:
	bool m_deleted;
	bool m_added;
	bool m_tmpAuradeleted;
#ifdef SHAREDPTR_DEBUGMODE
	bool deleting;
#endif
	bool m_creatureAA;
	int16 m_interrupted;

	INLINE bool IsInterrupted() { return ( m_interrupted >= 0 ); }
};

typedef void(Aura::*pSpellAura)(bool apply);

#endif