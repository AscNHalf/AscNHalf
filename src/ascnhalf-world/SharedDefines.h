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

#ifndef _SHARED_DEFINES_H
#define _SHARED_DEFINES_H

enum UNIT_TYPE
{
	NOUNITTYPE					= 0,
	BEAST						= 1,
	DRAGONSKIN					= 2,
	DEMON						= 3,
	ELEMENTAL					= 4,
	GIANT						= 5,
	UNDEAD						= 6,
	HUMANOID					= 7,
	CRITTER						= 8,
	MECHANICAL					= 9,
	UNIT_TYPE_MISC				= 10,
	UNIT_TYPE_TOTEM 			= 11,
	UNIT_TYPE_NONCOMBAT_PET		= 12,
	UNIT_TYPE_GAS_CLOUD 		= 13,
	NUM_UNIT_TYPE				= 14,
};

#define NUM_DISPEL_TYPES 11

#define NUM_SUMMON_SLOTS 7

enum SpellState
{
	SPELL_STATE_NULL	  = 0,
	SPELL_STATE_PREPARING = 1,
	SPELL_STATE_CASTING   = 2,
	SPELL_STATE_FINISHED  = 3,
	SPELL_STATE_IDLE	  = 4
};

enum ShapeshiftForm
{
	FORM_NORMAL				= 0,  //1
	FORM_CAT				= 1,  //2
	FORM_TREE				= 2,  //4
	FORM_TRAVEL				= 3,  //8
	FORM_AQUA				= 4,  //16
	FORM_BEAR				= 5,  //32
	FORM_AMBIENT			= 6,  //64
	FORM_GHOUL				= 7,  //128
	FORM_DIREBEAR			= 8,  //256
	FORM_9					= 9,  //512
	FORM_10					= 10, //1024
	FORM_11					= 11, //2048
	FORM_12					= 12, //4096
	FORM_13					= 13, //8192
	FORM_CREATUREBEAR		= 14, //16384
	FORM_GHOSTWOLF			= 16, //65536
	FORM_BATTLESTANCE		= 17, //131072
	FORM_DEFENSIVESTANCE	= 18, //262144
	FORM_BERSERKERSTANCE	= 19, //524288
	FORM_20					= 20, //1048576
	FORM_ZOMBIE				= 21, //2097152
	FORM_DEMON				= 22, //4194304
	FORM_23					= 23, //8388608
	FORM_24					= 24, //16777216
	FORM_25					= 25, //33554432
	FORM_26					= 26, //67108864
	FORM_SWIFT				= 27, //134217728
	FORM_SHADOW				= 28, //268435456
	FORM_FLIGHT				= 29, //536870912
	FORM_STEALTH			= 30, //1073741824
	FORM_MOONKIN			= 31, //2147483648
	FORM_SPIRITOFREDEMPTION = 32, //4294967296
};

enum DISPEL_TYPE
{
	DISPEL_ZGTRINKETS = -1,
	DISPEL_NULL,
	DISPEL_MAGIC,
	DISPEL_CURSE,
	DISPEL_DISEASE,
	DISPEL_POISON,
	DISPEL_STEALTH,
	DISPEL_INVISIBILTY,
	DISPEL_ALL,
	DISPEL_SPECIAL_NPCONLY,
	DISPEL_FRENZY,
};

enum DISPEL_MECHANIC_TYPE
{
	DISPEL_MECHANIC_CHARM		= 1,
	DISPEL_MECHANIC_FEAR		= 5,
	DISPEL_MECHANIC_ROOT		= 7,
	DISPEL_MECHANIC_SLEEP		= 10,
	DISPEL_MECHANIC_SNARE		= 11,
	DISPEL_MECHANIC_STUN		= 12,
	DISPEL_MECHANIC_KNOCKOUT	= 14,
	DISPEL_MECHANIC_BLEED		= 15,
	DISPEL_MECHANIC_POLYMORPH	= 17,
	DISPEL_MECHANIC_BANISH		= 18,
	DISPEL_MECHANIC_MOUNTED		= 21,
};

enum MECHANICS
{
	MECHANIC_CHARMED = 1,
	MECHANIC_DISORIENTED, // 2
	MECHANIC_DISARMED, // 3
	MECHANIC_DISTRACED, // 4
	MECHANIC_FLEEING, // 5
	MECHANIC_CLUMSY, // 6
	MECHANIC_ROOTED, // 7
	MECHANIC_PACIFIED, // 8
	MECHANIC_SILENCED, // 9
	MECHANIC_ASLEEP, // 10
	MECHANIC_ENSNARED, // 11
	MECHANIC_STUNNED, // 12
	MECHANIC_FROZEN, // 13
	MECHANIC_INCAPACIPATED, // 14
	MECHANIC_BLEEDING, // 15
	MECHANIC_HEALING, // 16
	MECHANIC_POLYMORPHED, // 17
	MECHANIC_BANISHED, // 18
	MECHANIC_SHIELDED, // 19
	MECHANIC_SHACKLED, // 20
	MECHANIC_MOUNTED, // 21
	MECHANIC_SEDUCED, // 22
	MECHANIC_TURNED, // 23
	MECHANIC_HORRIFIED, // 24
	MECHANIC_INVULNARABLE, // 25
	MECHANIC_INTERRUPTED, // 26
	MECHANIC_DAZED, // 27
	MECHANIC_DISCOVERY, // 28
	MECHANIC_PROTECTED, // 29
	MECHANIC_SAPPED, // 30
	MECHANIC_ENRAGED, // 31
	MECHANIC_COUNT
};

#endif