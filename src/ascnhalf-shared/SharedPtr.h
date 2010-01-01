#ifndef _SHARED_PTR_H
#define _SHARED_PTR_H

//#define LAZY_SHARED_TO_RAW_PTR_METHOD

// Meh
class CBattleground;
class CBattlegroundManager;
class AlteracValley;
class ArathiBasin;
class Arena;
class Aura;
class Container;
class Corpse;
class Creature;
class DynamicObject;
class EventableObject;
class EyeOfTheStorm;
class GameObject;
class Item;
class LootRoll;
class MapMgr;
class Object;
class Pet;
class Player;
class QuestMgr;
class Spell;
class Transporter;
class Unit;
class Vehicle;
class WarsongGulch;
class WeatherInfo;
class World;
class StrandOfTheAncients;
class IsleOfConquest;

#define CAST(x,y) static_cast<x*>(y)

#define TO_PLAYER(ptr) ((Player*)ptr)
#define TO_UNIT(ptr) ((Unit*)ptr)
#define TO_CREATURE(ptr) ((Creature*)ptr)
#define TO_PET(ptr) ((Pet*)ptr)
#define TO_CONTAINER(ptr) ((Container*)ptr)
#define TO_ITEM(ptr) ((Item*)ptr)
#define TO_OBJECT(ptr) ((Object*)ptr)
#define TO_GAMEOBJECT(ptr) ((GameObject*)ptr)
#define TO_DYNAMICOBJECT(ptr) ((DynamicObject*)ptr)
#define TO_CORPSE(ptr) ((Corpse*)ptr)
#define TO_EVENTABLEOBJECT(ptr) ((EventableObject*)ptr)
#define TO_CBATTLEGROUND(ptr) ((CBattleground*)ptr)
#define TO_CBATTLEGROUNDMGR(ptr) ((CBattlegroundManager*)ptr)
#define TO_ALTERACVALLEY(ptr) ((AlteracValley*)ptr)
#define TO_EYEOFTHESTORM(ptr) ((EyeOfTheStorm*)ptr)
#define TO_WARSONGGULCH(ptr) ((WarsongGulch*)ptr)
#define TO_SOTA(ptr) ((StrandOfTheAncients*)ptr)
#define TO_ICO(ptr) ((IsleOfConquest*)ptr)
#define TO_ARENA(ptr) ((Arena*)ptr)
#define TO_ARATHIBASIN(ptr) ((ArathiBasin*)ptr)
#define TO_TRANSPORT(ptr) ((Transporter*)ptr)
#define TO_AURA(ptr) ((Aura*)ptr)
#define TO_SPELL(ptr) ((Spell*)ptr)
#define TO_LOOTROLL(ptr) ((LootRoll*)ptr)
#define TO_VEHICLE(ptr) ((Vehicle*)ptr)
#define TO_WEATHER(ptr) ((WeatherInfo*)ptr)

#define NULLPTR 0
#define NULLGOB 0
#define NULLPLR 0
#define NULLOBJ 0
#define NULLUNIT 0
#define NULLPET 0
#define NULLITEM 0
#define NULLDYN 0
#define NULLCREATURE 0
#define NULLVEHICLE 0
#define NULLCORPSE 0
#define NULLTRANSPORT 0
#define NULLEVENTABLEOBJECT 0
#define NULLCONTAINER 0
#define NULLMAPMGR 0
#define NULLBGMGR 0
#define NULLBATTLEGROUND 0
#define NULLWEATHER 0
#define NULLWORLD 0
#define NULLINSTANCEMGR 0
#define NULLAURA 0
#define NULLROLL 0
#define NULLMAPMGR 0
#define NULLSPELL 0

#ifdef LAZY_SHARED_TO_RAW_PTR_METHOD

typedef CBattleground* BattlegroundPointer;
typedef CBattlegroundManager* BattlegroundMgrPointer;
typedef AlteracValley* AlteracValleyPointer;
typedef ArathiBasin* ArathiBasinPointer;
typedef Arena* ArenaPointer;
typedef Aura* AuraPointer;
typedef CBattleground* CBattlegroundPointer;
typedef CBattlegroundManager* CBattlegroundManagerPointer;
typedef Container* ContainerPointer;
typedef Corpse* CorpsePointer;
typedef Creature* CreaturePointer;
typedef DynamicObject* DynamicObjectPointer;
typedef EventableObject* EventableObjectPointer;
typedef EyeOfTheStorm* EyeOfTheStormPointer;
typedef GameObject* GameObjectPointer;
typedef Item* ItemPointer;
typedef LootRoll* LootRollPointer;
typedef MapMgr* MapMgrPointer;
typedef Object* ObjectPointer;
typedef Pet* PetPointer;
typedef Player* PlayerPointer;
typedef QuestMgr* QuestMgrPointer;
typedef Spell* SpellPointer;
typedef Transporter* TransporterPointer;
typedef Unit* UnitPointer;
typedef Vehicle* VehiclePointer;
typedef WarsongGulch* WarsongGulchPointer;
typedef WeatherInfo* WeatherInfoPointer;
typedef World* WorldPointer;
typedef StrandOfTheAncients* SotaPointer;
typedef IsleOfConquest* IcoPointer;

#define object_shared_from_this() TO_OBJECT(this)
#define obj_shared_from_this() TO_OBJECT(this)
#define gob_shared_from_this() TO_GAMEOBJECT(this)
#define unit_shared_from_this() TO_UNIT(this)
#define plr_shared_from_this() TO_PLAYER(this)
#define player_shared_from_this() TO_PLAYER(this)
#define dyn_shared_from_this() TO_DYNAMICOBJECT(this)
#define item_shared_from_this() TO_ITEM(this)
#define creature_shared_from_this() TO_CREATURE(this)
#define pet_shared_from_this() TO_PET(this)
#define spell_shared_from_this() TO_SPELL(this)
#define aura_shared_from_this() TO_AURA(this)
#define lootroll_shared_from_this() TO_LOOTROLL(this)
#define vehicle_shared_from_this() TO_VEHICLE(this)
#define shared_from_this() this

#endif

#endif
