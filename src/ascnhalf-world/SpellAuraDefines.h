/*
  * AscNHalf MMORPG Server
  * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
  * Copyright (C) 2010 AscNHalf Team <http://ascnhalf.scymex.info/>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Affero General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Affero General Public License for more details.
  *
  * You should have received a copy of the GNU Affero General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

#ifndef _SPELLAURA_DEFINES_H
#define _SPELLAURA_DEFINES_H

enum AURA_FLAGS
{
	AFLAG_EMPTY		= 0x0,
	AFLAG_SET		= 0x9
};

enum AURA_STATE_FLAGS
{
	AURASTATE_FLAG_DODGE_BLOCK			= 0x00000001,
    AURASTATE_FLAG_HEALTH20             = 0x00000002,
    AURASTATE_FLAG_BERSERK              = 0x00000004,
    AURASTATE_FLAG_FROZEN               = 0x00000008,
    AURASTATE_FLAG_JUDGEMENT            = 0x00000010,
	AURASTATE_FLAG_STUNNED				= 0x00000020, // CUSTOM!
    AURASTATE_FLAG_PARRY                = 0x00000040,
	AURASTATE_FLAG_UNK2					= 0x00000080,
	AURASTATE_FLAG_UNK3					= 0x00000100,
    AURASTATE_FLAG_VICTORIOUS			= 0x00000200, // after you kill an enemy that yields experience or honor
    AURASTATE_FLAG_CRITICAL             = 0x00000400,
	AURASTATE_FLAG_UNK4					= 0x00000800,
    AURASTATE_FLAG_HEALTH35             = 0x00001000,
    AURASTATE_FLAG_IMMOLATE             = 0x00002000,
    AURASTATE_FLAG_REJUVENATE           = 0x00004000,
    AURASTATE_FLAG_POISON               = 0x00008000,
	AURASTATE_FLAG_ENRAGE               = 0x00010000,
	AURASTATE_FLAG_UNK5					= 0x00020000,
	AURASTATE_FLAG_UNK6					= 0x00040000,
	AURASTATE_FLAG_UNK7					= 0x00080000,
	AURASTATE_FLAG_UNK8					= 0x00100000,
	AURASTATE_FLAG_UNK9					= 0x00200000,
	AURASTATE_FLAG_HEALTHABOVE75		= 0x00400000,
};

enum MOD_TYPES
{
    SPELL_AURA_NONE												= 0,			// None
    SPELL_AURA_BIND_SIGHT										= 1,			// Bind Sight
    SPELL_AURA_MOD_POSSESS										= 2,			// Mod Possess
    SPELL_AURA_PERIODIC_DAMAGE									= 3,			// Periodic Damage
    SPELL_AURA_DUMMY											= 4,			// Script Aura
    SPELL_AURA_MOD_CONFUSE										= 5,			// Mod Confuse
    SPELL_AURA_MOD_CHARM										= 6,			// Mod Charm
    SPELL_AURA_MOD_FEAR											= 7,			// Mod Fear
    SPELL_AURA_PERIODIC_HEAL									= 8,			// Periodic Heal
    SPELL_AURA_MOD_ATTACKSPEED									= 9,			// Mod Attack Speed
    SPELL_AURA_MOD_THREAT										= 10,			// Mod Threat
    SPELL_AURA_MOD_TAUNT										= 11,			// Taunt
    SPELL_AURA_MOD_STUN											= 12,			// Stun
    SPELL_AURA_MOD_DAMAGE_DONE									= 13,			// Mod Damage Done
    SPELL_AURA_MOD_DAMAGE_TAKEN									= 14,			// Mod Damage Taken
    SPELL_AURA_DAMAGE_SHIELD									= 15,			// Damage Shield
    SPELL_AURA_MOD_STEALTH										= 16,			// Mod Stealth
    SPELL_AURA_MOD_DETECT										= 17,			// Mod Detect
    SPELL_AURA_MOD_INVISIBILITY									= 18,			// Mod Invisibility
    SPELL_AURA_MOD_INVISIBILITY_DETECTION						= 19,			// Mod Invisibility Detection
    SPELL_AURA_MOD_TOTAL_HEALTH_REGEN_PCT						= 20,
    SPELL_AURA_MOD_TOTAL_MANA_REGEN_PCT							= 21,
    SPELL_AURA_MOD_RESISTANCE									= 22,			// Mod Resistance
    SPELL_AURA_PERIODIC_TRIGGER_SPELL							= 23,			// Periodic Trigger
    SPELL_AURA_PERIODIC_ENERGIZE								= 24,			// Periodic Energize
    SPELL_AURA_MOD_PACIFY										= 25,			// Pacify
    SPELL_AURA_MOD_ROOT											= 26,			// Root
    SPELL_AURA_MOD_SILENCE										= 27,			// Silence
    SPELL_AURA_REFLECT_SPELLS									= 28,			// Reflect Spells %
    SPELL_AURA_MOD_STAT											= 29,			// Mod Stat
    SPELL_AURA_MOD_SKILL										= 30,			// Mod Skill
    SPELL_AURA_MOD_INCREASE_SPEED								= 31,			// Mod Speed
    SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED						= 32,			// Mod Speed Mounted
    SPELL_AURA_MOD_DECREASE_SPEED								= 33,			// Mod Speed Slow
    SPELL_AURA_MOD_INCREASE_HEALTH								= 34,			// Mod Increase Health
    SPELL_AURA_MOD_INCREASE_ENERGY								= 35,			// Mod Increase Energy
    SPELL_AURA_MOD_SHAPESHIFT									= 36,			// Shapeshift
    SPELL_AURA_EFFECT_IMMUNITY									= 37,			// Immune Effect
    SPELL_AURA_STATE_IMMUNITY									= 38,			// Immune State
    SPELL_AURA_SCHOOL_IMMUNITY									= 39,			// Immune School    
    SPELL_AURA_DAMAGE_IMMUNITY									= 40,			// Immune Damage
    SPELL_AURA_DISPEL_IMMUNITY									= 41,			// Immune Dispel Type
    SPELL_AURA_PROC_TRIGGER_SPELL								= 42,			// Proc Trigger Spell
    SPELL_AURA_PROC_TRIGGER_DAMAGE								= 43,			// Proc Trigger Damage
    SPELL_AURA_TRACK_CREATURES									= 44,			// Track Creatures
    SPELL_AURA_TRACK_RESOURCES									= 45,			// Track Resources
    SPELL_AURA_MOD_PARRY_SKILL									= 46,			// Mod Parry Skill
    SPELL_AURA_MOD_PARRY_PERCENT								= 47,			// Mod Parry Percent
    SPELL_AURA_MOD_DODGE_SKILL									= 48,			// Mod Dodge Skill
    SPELL_AURA_MOD_DODGE_PERCENT								= 49,			// Mod Dodge Percent  
    SPELL_AURA_MOD_BLOCK_SKILL									= 50,			// Mod Block Skill
    SPELL_AURA_MOD_BLOCK_PERCENT								= 51,			// Mod Block Percent
    SPELL_AURA_MOD_CRIT_PERCENT									= 52,			// Mod Crit Percent
    SPELL_AURA_PERIODIC_LEECH									= 53,			// Periodic Leech
    SPELL_AURA_MOD_HIT_CHANCE									= 54,			// Mod Hit Chance
    SPELL_AURA_MOD_SPELL_HIT_CHANCE								= 55,			// Mod Spell Hit Chance
    SPELL_AURA_TRANSFORM										= 56,			// Transform
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE							= 57,			// Mod Spell Crit Chance
    SPELL_AURA_MOD_INCREASE_SWIM_SPEED							= 58,			// Mod Speed Swim
    SPELL_AURA_MOD_DAMAGE_DONE_CREATURE							= 59,			// Mod Creature Dmg Done   
    SPELL_AURA_MOD_PACIFY_SILENCE								= 60,			// Pacify & Silence
    SPELL_AURA_MOD_SCALE										= 61,			// Mod Scale
    SPELL_AURA_PERIODIC_HEALTH_FUNNEL							= 62,			// Periodic Health Funnel
    SPELL_AURA_PERIODIC_MANA_FUNNEL								= 63,			// Periodic Mana Funnel
    SPELL_AURA_PERIODIC_MANA_LEECH								= 64,			// Periodic Mana Leech
    SPELL_AURA_MOD_CASTING_SPEED								= 65,			// Haste - Spells
    SPELL_AURA_FEIGN_DEATH										= 66,			// Feign Death
    SPELL_AURA_MOD_DISARM										= 67,			// Disarm
    SPELL_AURA_MOD_STALKED										= 68,			// Mod Stalked
    SPELL_AURA_SCHOOL_ABSORB									= 69,			// School Absorb    
    SPELL_AURA_EXTRA_ATTACKS									= 70,			// Extra Attacks
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL						= 71,			// Mod School Spell Crit Chance
    SPELL_AURA_MOD_POWER_COST									= 72,			// Mod Power Cost
    SPELL_AURA_MOD_POWER_COST_SCHOOL							= 73,			// Mod School Power Cost
    SPELL_AURA_REFLECT_SPELLS_SCHOOL							= 74,			// Reflect School Spells %
    SPELL_AURA_MOD_LANGUAGE										= 75,			// Mod Language
    SPELL_AURA_FAR_SIGHT										= 76,			// Far Sight
    SPELL_AURA_MECHANIC_IMMUNITY								= 77,			// Immune Mechanic
    SPELL_AURA_MOUNTED											= 78,			// Mounted
    SPELL_AURA_MOD_DAMAGE_PERCENT_DONE							= 79,			// Mod Dmg %   
    SPELL_AURA_MOD_PERCENT_STAT									= 80,			// Mod Stat %
    SPELL_AURA_SPLIT_DAMAGE										= 81,			// Split Damage
    SPELL_AURA_WATER_BREATHING									= 82,			// Water Breathing
    SPELL_AURA_MOD_BASE_RESISTANCE								= 83,			// Mod Base Resistance
    SPELL_AURA_MOD_REGEN										= 84,			// Mod Health Regen
    SPELL_AURA_MOD_POWER_REGEN									= 85,			// Mod Power Regen
    SPELL_AURA_CHANNEL_DEATH_ITEM								= 86,			// Create Death Item
    SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN							= 87,           // Mod Dmg % Taken
    SPELL_AURA_MOD_PERCENT_REGEN								= 88,			// Mod Health Regen Percent
    SPELL_AURA_PERIODIC_DAMAGE_PERCENT							= 89,			// Periodic Damage Percent   
    SPELL_AURA_MOD_RESIST_CHANCE								= 90,			// Mod Resist Chance
    SPELL_AURA_MOD_DETECT_RANGE									= 91,			// Mod Detect Range
    SPELL_AURA_PREVENTS_FLEEING									= 92,			// Prevent Fleeing
    SPELL_AURA_MOD_UNATTACKABLE									= 93,			// Mod Uninteractible
    SPELL_AURA_INTERRUPT_REGEN									= 94,			// Interrupt Regen
    SPELL_AURA_GHOST											= 95,			// Ghost
    SPELL_AURA_SPELL_MAGNET										= 96,			// Spell Magnet
    SPELL_AURA_MANA_SHIELD										= 97,			// Mana Shield
    SPELL_AURA_MOD_SKILL_TALENT									= 98,			// Mod Skill Talent
    SPELL_AURA_MOD_ATTACK_POWER									= 99,			// Mod Attack Power
    SPELL_AURA_AURAS_VISIBLE									= 100,			// Auras Visible
    SPELL_AURA_MOD_RESISTANCE_PCT								= 101,			// Mod Resistance %
    SPELL_AURA_MOD_CREATURE_ATTACK_POWER						= 102,			// Mod Creature Attack Power
    SPELL_AURA_MOD_TOTAL_THREAT									= 103,			// Mod Total Threat (Fade)
    SPELL_AURA_WATER_WALK										= 104,			// Water Walk
    SPELL_AURA_FEATHER_FALL										= 105,			// Feather Fall
    SPELL_AURA_HOVER											= 106,			// Hover
    SPELL_AURA_ADD_FLAT_MODIFIER								= 107,			// Add Flat Modifier
    SPELL_AURA_ADD_PCT_MODIFIER									= 108,			// Add % Modifier
    SPELL_AURA_ADD_TARGET_TRIGGER								= 109,			// Add Class Target Trigger    
    SPELL_AURA_MOD_POWER_REGEN_PERCENT							= 110,			// Mod Power Regen %
    SPELL_AURA_ADD_CASTER_HIT_TRIGGER							= 111,			// Add Class Caster Hit Trigger
    SPELL_AURA_OVERRIDE_CLASS_SCRIPTS							= 112,			// Override Class Scripts
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN							= 113,			// Mod Ranged Dmg Taken
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT						= 114,			// Mod Ranged % Dmg Taken
    SPELL_AURA_MOD_HEALING										= 115,			// Mod Healing
    SPELL_AURA_IGNORE_REGEN_INTERRUPT							= 116,			// Regen During Combat
    SPELL_AURA_MOD_MECHANIC_RESISTANCE							= 117,			// Mod Mechanic Resistance
    SPELL_AURA_MOD_HEALING_PCT									= 118,			// Mod Healing %
    SPELL_AURA_SHARE_PET_TRACKING								= 119,			// Share Pet Tracking    
    SPELL_AURA_UNTRACKABLE										= 120,			// Untrackable
    SPELL_AURA_EMPATHY											= 121,			// Empathy (Lore, whatever)
    SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT							= 122,			// Mod Offhand Dmg %
    SPELL_AURA_MOD_POWER_COST_PCT								= 123,			// Mod Power Cost % --> armor penetration & spell penetration
    SPELL_AURA_MOD_RANGED_ATTACK_POWER							= 124,			// Mod Ranged Attack Power
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN							= 125,			// Mod Melee Dmg Taken
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT						= 126,			// Mod Melee % Dmg Taken
    SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS				= 127,			// Rngd Atk Pwr Attckr Bonus
    SPELL_AURA_MOD_POSSESS_PET									= 128,			// Mod Possess Pet
    SPELL_AURA_MOD_INCREASE_SPEED_ALWAYS						= 129,			// Mod Speed Always   
    SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS							= 130,          // Mod Mounted Speed Always
    SPELL_AURA_MOD_CREATURE_RANGED_ATTACK_POWER					= 131,			// Mod Creature Ranged Attack Power
    SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT						= 132,			// Mod Increase Energy %
    SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT						= 133,			// Mod Max Health %
    SPELL_AURA_MOD_MANA_REGEN_INTERRUPT							= 134,          // Mod Interrupted Mana Regen
    SPELL_AURA_MOD_HEALING_DONE									= 135,			// Mod Healing Done
    SPELL_AURA_MOD_HEALING_DONE_PERCENT							= 136,          // Mod Healing Done %
    SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE						= 137,			// Mod Total Stat %
    SPELL_AURA_MOD_HASTE										= 138,			// Haste - Melee
    SPELL_AURA_FORCE_REACTION									= 139,			// Force Reaction    
    SPELL_AURA_MOD_RANGED_HASTE									= 140,			// Haste - Ranged
    SPELL_AURA_MOD_RANGED_AMMO_HASTE							= 141,			// Haste - Ranged (Ammo Only)
    SPELL_AURA_MOD_BASE_RESISTANCE_PCT							= 142,			// Mod Base Resistance %
    SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE							= 143,			// Mod Resistance Exclusive
    SPELL_AURA_SAFE_FALL										= 144,			// Safe Fall
    SPELL_AURA_MOD_PET_TALENT_POINTS							= 145,			// Mod Pet Talent Points
    SPELL_AURA_PERSUADED										= 146,			// Persuaded
    SPELL_AURA_ADD_CREATURE_IMMUNITY							= 147,			// Add Creature Immunity
    SPELL_AURA_RETAIN_COMBO_POINTS								= 148,			// Retain Combo Points
    SPELL_AURA_RESIST_PUSHBACK									= 149,			// Resist Pushback
    SPELL_AURA_MOD_SHIELD_BLOCK_PCT								= 150,			// Mod Shield Block %
    SPELL_AURA_TRACK_STEALTHED									= 151,			// Track Stealthed
    SPELL_AURA_MOD_DETECTED_RANGE								= 152,			// Mod Detected Range
    SPELL_AURA_SPLIT_DAMAGE_FLAT								= 153,			// Split Damage Flat
    SPELL_AURA_MOD_STEALTH_LEVEL								= 154,			// Stealth Level Modifier
    SPELL_AURA_MOD_WATER_BREATHING								= 155,			// Mod Water Breathing
    SPELL_AURA_MOD_REPUTATION_ADJUST							= 156,			// Mod Reputation Gain
    SPELL_AURA_PET_DAMAGE_MULTI									= 157,			// Mod Pet Damage
    SPELL_AURA_MOD_SHIELD_BLOCK									= 158,			// Mod Shield Block
    SPELL_AURA_NO_PVP_CREDIT									= 159,			// No PVP Credit 
    SPELL_AURA_MOD_SIDE_REAR_PDAE_DAMAGE_TAKEN					= 160,			// Mod Side/Rear PBAE Damage Taken 
    SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT						= 161,			// Mod Health Regen In Combat
    SPELL_AURA_POWER_BURN										= 162,			// Power Burn 
    SPELL_AURA_MOD_CRIT_DAMAGE_BONUS_MELEE						= 163,			// Mod Critical Damage Bonus (Physical)
    SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS				= 165,			// Melee AP Attacker Bonus
    SPELL_AURA_MOD_ATTACK_POWER_PCT								= 166,			// Mod Attack Power
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT						= 167,			// Mod Ranged Attack Power %
    SPELL_AURA_INCREASE_DAMAGE									= 168,			// Increase Damage Type
    SPELL_AURA_INCREASE_CRITICAL								= 169,			// Increase Critical Type
    SPELL_AURA_DETECT_AMORE										= 170,			// Detect Amore
    SPELL_AURA_INCREASE_MOVEMENT_AND_MOUNTED_SPEED				= 172,			// Increase Movement and Mounted Speed (Non-Stacking)
    SPELL_AURA_INCREASE_SPELL_DAMAGE_PCT						= 174,			// Increase Spell Damage by % status
    SPELL_AURA_INCREASE_SPELL_HEALING_PCT						= 175,			// Increase Spell Healing by % status
    SPELL_AURA_SPIRIT_OF_REDEMPTION								= 176,			// Spirit of Redemption Auras
    SPELL_AURA_AREA_CHARM										= 177,			// Area Charm 
    SPELL_AURA_INCREASE_ATTACKER_SPELL_CRIT						= 179,			// Increase Attacker Spell Crit Type
    SPELL_AURA_INCREASE_SPELL_DAMAGE_VS_TYPE					= 180,			// Increase Spell Damage Type
    SPELL_AURA_INCREASE_ARMOR_BASED_ON_INTELLECT_PCT			= 182,			// Increase Armor based on Intellect
    SPELL_AURA_DECREASE_CRIT_THREAT								= 183,			// Decrease Critical Threat by
    SPELL_AURA_DECREASE_ATTACKER_CHANCE_TO_HIT_MELEE			= 184,			//Reduces Attacker Chance to Hit with Melee
    SPELL_AURA_DECREASE_ATTACKER_CHANGE_TO_HIT_RANGED			= 185,			// Reduces Attacker Chance to Hit with Ranged 
    SPELL_AURA_DECREASE_ATTACKER_CHANGE_TO_HIT_SPELLS			= 186,			// Reduces Attacker Chance to Hit with Spells
    SPELL_AURA_DECREASE_ATTACKER_CHANGE_TO_CRIT_MELEE			= 187,			// Reduces Attacker Chance to Crit with Melee (Ranged?)
    SPELL_AURA_DECREASE_ATTACKER_CHANGE_TO_CRIT_RANGED			= 188,			// Reduces Attacker Chance to Crit with Ranged (Melee?)
    SPELL_AURA_INCREASE_REPUTATION								= 190,			// Increases reputation from killed creatures
    SPELL_AURA_SPEED_LIMIT										= 191,			// speed limit
    SPELL_AURA_MELEE_SLOW_PCT									= 192,
    SPELL_AURA_INCREASE_TIME_BETWEEN_ATTACKS					= 193,
    SPELL_AURA_INREASE_SPELL_DAMAGE_PCT_OF_INTELLECT			= 194,			// NOT USED ANYMORE - 174 used instead
    SPELL_AURA_INCREASE_HEALING_PCT_OF_INTELLECT				= 195,			// NOT USED ANYMORE - 175 used instead
    SPELL_AURA_MOD_ALL_WEAPON_SKILLS							= 196,
    SPELL_AURA_REDUCE_ATTACKER_CRICTICAL_HIT_CHANCE_PCT			= 197,
    SPELL_AURA_INCREASE_SPELL_HIT_PCT							= 199,
    SPELL_AURA_CANNOT_BE_DODGED									= 201,
	SPELL_AURA_FINISHING_MOVES_CANNOT_BE_DODGED					= 202,
    SPELL_AURA_REDUCE_ATTACKER_CRICTICAL_HIT_DAMAGE_MELEE_PCT	= 203,
    SPELL_AURA_REDUCE_ATTACKER_CRICTICAL_HIT_DAMAGE_RANGED_PCT	= 204,
    SPELL_AURA_INCREASE_RANGED_ATTACK_POWER_PCT_OF_INTELLECT	= 212,
    SPELL_AURA_INCREASE_RAGE_FROM_DAMAGE_DEALT_PCT				= 213,
    SPELL_AURA_INCREASE_CASTING_TIME_PCT						= 216,
	SPELL_AURA_HASTE_RANGED										= 218,
    SPELL_AURA_REGEN_MANA_STAT_PCT								= 219,
    SPELL_AURA_HEALING_STAT_PCT									= 220,
	SPELL_AURA_REDUCE_AOE_DAMAGE_TAKEN							= 229,
    SPELL_AURA_INCREASE_MAX_HEALTH								= 230,			//Used by Commanding Shout
	SPELL_AURA_VEHICLE_PASSENGER								= 236,
	SPELL_AURA_MODIFY_AXE_SKILL									= 240,
	SPELL_AURA_ADD_HEALTH										= 250,
	SPELL_AURA_MOD_DOT_DAMAGE_DONE_BY_MECHANIC					= 255,
	SPELL_AURA_NO_REAGENT										= 256,
	SPELL_AURA_SET_PHASE										= 261,
	SPELL_AURA_FROZEN_TARGET									= 262,
	SPELL_AURA_INCREASE_AP_BY_ATTRIBUTE							= 268,
	SPELL_AURA_INCREASE_SPELL_DOT_DAMAGE_PCT					= 271,
	SPELL_AURA_REDIRECT_THREAT									= 277,
	SPELL_AURA_IGNORE_ARMOR_PCT									= 280,
	SPELL_AURA_MOD_BASE_HEALTH									= 282,
	SPELL_AURA_REFLECT_INFRONT									= 287,
	SPELL_AURA_288												= 288,
	SPELL_AURA_289												= 289,
	SPELL_AURA_290												= 290,
	SPELL_AURA_291												= 291,
	SPELL_AURA_292												= 292,
	SPELL_AURA_293												= 293,
	SPELL_AURA_294												= 294,
	SPELL_AURA_295												= 295,
	SPELL_AURA_296												= 296,
	SPELL_AURA_297												= 297,
	SPELL_AURA_298												= 298,
	SPELL_AURA_299												= 299,
	SPELL_AURA_300												= 300,
	SPELL_AURA_301												= 301,
	SPELL_AURA_302												= 302,
	SPELL_AURA_303												= 303,
	SPELL_AURA_304												= 304,
	SPELL_AURA_305												= 305,
	SPELL_AURA_306												= 306,
    TOTAL_SPELL_AURAS											= 307,
};
enum AuraTickFlags
{
    FLAG_PERIODIC_DAMAGE            = 3,	// also 89
    FLAG_PERIODIC_HEAL              = 8,	// also 20
    FLAG_PERIODIC_ENERGIZE          = 21,	// also 24
	FLAG_PERIODIC_LEECH             = 64,
};
enum AuraFlags
{
    AFLAG_NONE              = 0x00,
    AFLAG_VISIBLE           = 0x01,
    AFLAG_EFF_INDEX_1       = 0x02,
    AFLAG_EFF_INDEX_2       = 0x04,
    AFLAG_NOT_GUID          = 0x08,
    AFLAG_CANCELLABLE       = 0x10,
    AFLAG_HAS_DURATION      = 0x20,
    AFLAG_UNK2              = 0x40,
    AFLAG_NEGATIVE          = 0x80,
    AFLAG_POSITIVE          = 0x1F,
    AFLAG_MASK              = 0xFF,
};

enum AURAIMMUNE_FLAG
{
	AURAIMMUNE_NONE				= 0x0,
	AURAIMMUNE_CONFUSE			= 0X1,			//SPELL_AURA_MOD_CONFUSE = 5
	AURAIMMUNE_CHARM			= 0x2,			//SPELL_AURA_MOD_CHARM = 6
	AURAIMMUNE_FEAR				= 0X4,			//SPELL_AURA_MOD_FEAR = 7
	AURAIMMUNE_STUN				= 0x8,			//SPELL_AURA_MOD_STUN = 12
	AURAIMMUNE_PACIFY			= 0x10,			//SPELL_AURA_MOD_PACIFY = 25
	AURAIMMUNE_ROOT				= 0x20,			//SPELL_AURA_MOD_ROOT = 26	
	AURAIMMUNE_SILENCE			= 0x40,			//SPELL_AURA_MOD_SILENCE = 27
	AURAIMMUNE_INCSPEED			= 0x80,         //SPELL_AURA_MOD_INCREASE_SPEED = 31
	AURAIMMUNE_DECSPEED			= 0x100,		//SPELL_AURA_MOD_DECREASE_SPEED = 33
	AURAIMMUNE_TRANSFORM		= 0x200,		//SPELL_AURA_TRANSFORM = 56
	AURAIMMUNE_TAUNT			= 0x400,		//SPELL_AURA_MOD_TAUNT = 11
	AURAIMMUNE_BLEED			= 0x800,		//MECHANIC BLEED = 15
	AURAIMMUNE_POISON			= 0x1000,		//DISPEL TYPE POISON = 4
	AURAIMMUNE_MANALEECH		= 0x2000,		//SPELL_AURA_PERIODIC_MANA_LEECH = 64,
	AURAIMMUNE_LEECH			= 0x4000,		//SPELL_AURA_PERIODIC_LEECH = 53

	AURAIMMUNE_GENERIC_BOSS     = AURAIMMUNE_CONFUSE | AURAIMMUNE_CHARM | AURAIMMUNE_FEAR |
								  AURAIMMUNE_STUN | AURAIMMUNE_PACIFY | AURAIMMUNE_ROOT |
								  AURAIMMUNE_SILENCE | AURAIMMUNE_INCSPEED | AURAIMMUNE_DECSPEED |
								  AURAIMMUNE_TRANSFORM, //1023
};

#endif