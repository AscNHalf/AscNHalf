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

#ifndef _OBJECT_DEFINES_H
#define _OBJECT_DEFINES_H

enum HIGHGUID_TYPE
{
	HIGHGUID_TYPE_VEHICLE			= 0xF1500000,
	HIGHGUID_TYPE_UNIT				= 0xF1300000,
	HIGHGUID_TYPE_PET				= 0xF1400000,
	HIGHGUID_TYPE_GAMEOBJECT		= 0xF1100000,
	HIGHGUID_TYPE_ITEM				= 0x40000000,
	HIGHGUID_TYPE_CONTAINER			= 0x50000000,			// confirm this pl0x
	HIGHGUID_TYPE_PLAYER			= 0x00000000,
	HIGHGUID_TYPE_DYNAMICOBJECT		= 0x60000000,
	HIGHGUID_TYPE_TRANSPORTER		= 0x1FC00000,
	HIGHGUID_TYPE_WAYPOINT			= 0x10000000,
	HIGHGUID_TYPE_CORPSE			= 0x30000000,
//===============================================
	HIGHGUID_TYPE_MASK				= 0xFFF00000,
	LOWGUID_ENTRY_MASK				= 0x00FFFFFF,
};

#define GET_TYPE_FROM_GUID(x) (GUID_HIPART((x)) & HIGHGUID_TYPE_MASK)
#define GET_LOWGUID_PART(x) (GUID_LOPART((x)) & LOWGUID_ENTRY_MASK)

// TODO: fix that type mess

enum TYPE
{
	TYPE_OBJECT			= 1,
	TYPE_ITEM			= 2,
	TYPE_CONTAINER		= 4,
	TYPE_UNIT			= 8,
	TYPE_PLAYER			= 16,
	TYPE_GAMEOBJECT		= 32,
	TYPE_DYNAMICOBJECT	= 64,
	TYPE_CORPSE			= 128,
	TYPE_AIGROUP		= 256,
	TYPE_AREATRIGGER	= 512,
};

enum TYPEID
{
	TYPEID_OBJECT			= 0,
	TYPEID_ITEM				= 1,
	TYPEID_CONTAINER		= 2,
	TYPEID_UNIT				= 3,
	TYPEID_PLAYER			= 4,
	TYPEID_GAMEOBJECT		= 5,
	TYPEID_DYNAMICOBJECT	= 6,
	TYPEID_CORPSE			= 7,
	TYPEID_AIGROUP			= 8,
	TYPEID_AREATRIGGER		= 9,
	TYPEID_UNUSED			= 10,//used to signal invalid reference (object dealocated but someone is still using it)
};

enum OBJECT_UPDATE_TYPE
{
	UPDATETYPE_VALUES					= 0,
	//  8 bytes - GUID
	//  Goto Update Block
	UPDATETYPE_MOVEMENT					= 1,
	//  8 bytes - GUID
	//  Goto Position Update
	UPDATETYPE_CREATE_OBJECT			= 2,
	//  8 bytes - GUID
	//  1 byte - Object Type (*)
	//  Goto Position Update
	//  Goto Update Block
	UPDATETYPE_CREATE_YOURSELF			= 3, // looks like 3 & 4 do the same thing
	//  4 bytes - Count
	//  Loop Count Times:
	//  8 bytes - GUID
	UPDATETYPE_OUT_OF_RANGE_OBJECTS		= 4, // <- this is correct, not sure about 3
	//  4 bytes - Count
	//  Loop Count Times:
	//  8 bytes - GUID

	UPDATETYPE_NEAR_OBJECTS				= 5,
	//  4 bytes - Count
	//  Loop Count Times:
	//  8 bytes - GUID
};

enum PHASEMODE
{
	ALL_PHASES = -1,
	PHASE_1,
	PHASE_2,
	PHASE_3, // should be enough for the emulator to know about, but we can have more :P
};

enum GAMEOBJECT_BYTES
{
	GAMEOBJECT_BYTES_STATE			= 0,
	GAMEOBJECT_BYTES_TYPE_ID		= 1,
	GAMEOBJECT_BYTES_UNK			= 2, // todo: unknown atm
	GAMEOBJECT_BYTES_ANIMPROGRESS	= 3,
};

enum GAMEOBJECT_TYPES
{
	GAMEOBJECT_TYPE_DOOR					= 0,
	GAMEOBJECT_TYPE_BUTTON					= 1,
	GAMEOBJECT_TYPE_QUESTGIVER				= 2,
	GAMEOBJECT_TYPE_CHEST					= 3,
	GAMEOBJECT_TYPE_BINDER					= 4,
	GAMEOBJECT_TYPE_GENERIC					= 5,
	GAMEOBJECT_TYPE_TRAP					= 6,
	GAMEOBJECT_TYPE_CHAIR					= 7,
	GAMEOBJECT_TYPE_SPELL_FOCUS				= 8,
	GAMEOBJECT_TYPE_TEXT					= 9,
	GAMEOBJECT_TYPE_GOOBER					= 10,
	GAMEOBJECT_TYPE_TRANSPORT				= 11,
	GAMEOBJECT_TYPE_AREADAMAGE				= 12,
	GAMEOBJECT_TYPE_CAMERA					= 13,
	GAMEOBJECT_TYPE_MAP_OBJECT				= 14,
	GAMEOBJECT_TYPE_MO_TRANSPORT			= 15,
	GAMEOBJECT_TYPE_DUEL_ARBITER			= 16,
	GAMEOBJECT_TYPE_FISHINGNODE				= 17,
	GAMEOBJECT_TYPE_RITUAL					= 18,
	GAMEOBJECT_TYPE_MAILBOX					= 19,
	GAMEOBJECT_TYPE_AUCTIONHOUSE			= 20,
	GAMEOBJECT_TYPE_GUARDPOST				= 21,
	GAMEOBJECT_TYPE_SPELLCASTER				= 22,
	GAMEOBJECT_TYPE_MEETINGSTONE			= 23,
	GAMEOBJECT_TYPE_FLAGSTAND				= 24,
	GAMEOBJECT_TYPE_FISHINGHOLE				= 25,
	GAMEOBJECT_TYPE_FLAGDROP				= 26,
	GAMEOBJECT_TYPE_MINI_GAME				= 27,
	GAMEOBJECT_TYPE_LOTTERY_KIOSK			= 28,
	GAMEOBJECT_TYPE_CAPTURE_POINT			= 29,
	GAMEOBJECT_TYPE_AURA_GENERATOR			= 30,
	GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY		= 31,
	GAMEOBJECT_TYPE_BARBER_CHAIR			= 32,
	GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING	= 33,
	GAMEOBJECT_TYPE_GUILD_BANK				= 34,
	GAMEOBJECT_TYPE_TRAPDOOR				= 35,
};

enum GameObjectFlags
{
    GO_FLAG_IN_USE			= 0x00000001,					//disables interaction while animated
    GO_FLAG_LOCKED			= 0x00000002,					//require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
    GO_FLAG_INTERACT_COND	= 0x00000004,					//cannot interact (condition to interact)
    GO_FLAG_TRANSPORT		= 0x00000008,					//any kind of transport? Object can transport (elevator, boat, car)
    GO_FLAG_UNK1			= 0x00000010,					//
    GO_FLAG_NODESPAWN		= 0x00000020,					//never despawn, typically for doors, they just change state
    GO_FLAG_TRIGGERED		= 0x00000040,					//typically, summoned objects. Triggered by spell or other events
    GO_FLAG_DAMAGED			= 0x00000200,
    GO_FLAG_DESTROYED		= 0x00000400,
};

enum GameObjectDynFlags
{
	GO_DYNFLAG_QUEST		= 0x09,
};

enum UPDATE_FLAGS
{
	UPDATEFLAG_NONE = 0x0000,
	UPDATEFLAG_SELF = 0x0001,
	UPDATEFLAG_TRANSPORT = 0x0002,
	UPDATEFLAG_HAS_TARGET = 0x0004,
	UPDATEFLAG_LOWGUID = 0x0008,
	UPDATEFLAG_HIGHGUID = 0x0010,
	UPDATEFLAG_LIVING = 0x0020,
	UPDATEFLAG_HAS_POSITION = 0x0040,
	UPDATEFLAG_VEHICLE = 0x0080,
	UPDATEFLAG_POSITION = 0x0100,
	UPDATEFLAG_ROTATION = 0x0200
};

#endif