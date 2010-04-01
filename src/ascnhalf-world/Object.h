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

#ifndef _OBJECT_H
#define _OBJECT_H

#include "ObjectDefines.h"
#include "LootMgr.h"

class Unit;
class Spell;
class Aura;
class DynamicObject;
class Map;

#define DEFAULT_WORLD_OBJECT_SIZE	0.388999998569489f	// player size, also currently used (correctly?) for any non Unit world objects

typedef struct
{ 
	uint32 school_type;
	int32 full_damage;
	uint32 resisted_damage;
} dealdamage;

class WorldPacket;
class ByteBuffer;
class WorldSession;
class Player;
class MapCell;
class MapMgr;

//====================================================================
//  Object
//  Base object for every item, unit, player, corpse, container, etc
//====================================================================
class SERVER_DECL Object : public EventableObject
{
public:
	typedef UNORDERED_SET< Object* > InRangeSet;

	typedef std::map<string, void*> ExtensionSet;

	virtual ~Object ( );
	virtual void Destructor();
	virtual void Init();

	virtual void Update ( uint32 time ) { }
  //! True if object exists in world
 
	
	INLINE bool IsInWorld() { return m_mapMgr != NULL; }
	virtual void AddToWorld();
	virtual void AddToWorld(MapMgr* pMapMgr);
	void PushToWorld(MapMgr* );
	virtual void OnPushToWorld() { }
	virtual void OnPrePushToWorld() { }
	virtual void RemoveFromWorld(bool free_guid);

	INLINE void ObjLock() { m_objlock.Acquire(); }
	INLINE void ObjUnlock() { m_objlock.Release(); }

	// guid always comes first
	INLINE const uint64& GetGUID() const { return *((uint64*)m_uint32Values); }
	INLINE const WoWGuid& GetNewGUID() const { return m_wowGuid; }
	INLINE uint32 GetEntry(){return m_uint32Values[OBJECT_FIELD_ENTRY];}
	
	INLINE const uint32 GetEntryFromGUID() const	{ return uint32( (*(uint64*)m_uint32Values >> 24) & 0xFFFFFFFF ); }
	INLINE const uint32 GetTypeFromGUID() const { return (m_uint32Values[1] & HIGHGUID_TYPE_MASK); }
	INLINE const uint32 GetUIdFromGUID() const { return (m_uint32Values[0] & LOWGUID_ENTRY_MASK); }
	INLINE const uint32 GetLowGUID() const { return (m_uint32Values[0]); }
	INLINE const ByteBuffer& GetPackGUID() const { return m_PackGUID; }

	// type
	bool m_isVehicle;
	INLINE const uint8& GetTypeId() const { return m_objectTypeId; }
	INLINE bool IsUnit()	{ return ( m_objectTypeId == TYPEID_UNIT || m_objectTypeId == TYPEID_PLAYER ); }
	INLINE bool IsPlayer() { return m_objectTypeId == TYPEID_PLAYER; }
	INLINE bool IsCreature() { return m_objectTypeId == TYPEID_UNIT; }
	INLINE bool IsVehicle() { return m_isVehicle; }
	INLINE bool IsGameObject() { return m_objectTypeId == TYPEID_GAMEOBJECT; }
	bool IsPet();

	//! This includes any nested objects we have, inventory for example.
	virtual uint32 __fastcall BuildCreateUpdateBlockForPlayer( ByteBuffer *data, Player* target );
	uint32 __fastcall BuildValuesUpdateBlockForPlayer( ByteBuffer *buf, Player* target );
	uint32 __fastcall BuildValuesUpdateBlockForPlayer( ByteBuffer * buf, UpdateMask * mask );
	uint32 __fastcall BuildOutOfRangeUpdateBlock( ByteBuffer *buf );

	WorldPacket* BuildFieldUpdatePacket(uint32 index,uint32 value);
	void BuildFieldUpdatePacket(Player* Target, uint32 Index, uint32 Value);
	void BuildFieldUpdatePacket(ByteBuffer * buf, uint32 Index, uint32 Value);

	void DealDamage(Unit* pVictim, uint32 damage, uint32 targetEvent, uint32 unitEvent, uint32 spellId, bool no_remove_auras = false);

	virtual void DestroyForPlayer( Player* target ) const;

	void BuildHeartBeatMsg( WorldPacket *data ) const;
	WorldPacket * BuildTeleportAckMsg( const LocationVector & v);
	bool IsBeingTeleported() { return mSemaphoreTeleport; }
	void SetSemaphoreTeleport(bool semphsetting) { mSemaphoreTeleport = semphsetting; }

	bool SetPosition( float newX, float newY, float newZ, float newOrientation, bool allowPorting = false );
	bool SetPosition( const LocationVector & v, bool allowPorting = false);
	void SetRotation( uint64 guid );

	void CastSpell(Object* Target, SpellEntry* Sp, bool triggered);
	void CastSpell(Object* Target, uint32 SpellID, bool triggered);
	void CastSpell(uint64 targetGuid, SpellEntry* Sp, bool triggered);
	void CastSpell(uint64 targetGuid, uint32 SpellID, bool triggered);

	INLINE const float& GetPositionX( ) const { return m_position.x; }
	INLINE const float& GetPositionY( ) const { return m_position.y; }
	INLINE const float& GetPositionZ( ) const { return m_position.z; }
	INLINE const float& GetOrientation( ) const { return m_position.o; }
	INLINE void SetOrientation( float &o ) { m_position.o = o; }

	INLINE const float& GetSpawnX( ) const { return m_spawnLocation.x; }
	INLINE const float& GetSpawnY( ) const { return m_spawnLocation.y; }
	INLINE const float& GetSpawnZ( ) const { return m_spawnLocation.z; }
	INLINE const float& GetSpawnO( ) const { return m_spawnLocation.o; }
	INLINE void SetSpawnX(float x) { m_spawnLocation.x = x; }
	INLINE void SetSpawnY(float y) { m_spawnLocation.y = y; }
	INLINE void SetSpawnZ(float z) { m_spawnLocation.z = z; }
	INLINE void SetSpawnO(float o) { m_spawnLocation.o = o; }

	INLINE const LocationVector & GetPosition() { return m_position; }
	INLINE LocationVector & GetPositionNC() { return m_position; }
	INLINE LocationVector * GetPositionV() { return &m_position; }

	//Distance Calculation
	float CalcDistance(Object* Ob);
	float CalcDistance(float ObX, float ObY, float ObZ);
	float CalcDistance(Object* Oa, Object* Ob);
	float CalcDistance(Object* Oa, float ObX, float ObY, float ObZ);
	float CalcDistance(float OaX, float OaY, float OaZ, float ObX, float ObY, float ObZ);

	//! Only for MapMgr use
	INLINE MapCell* GetMapCell() const { return m_mapCell; }
	//! Only for MapMgr use
	INLINE void SetMapCell(MapCell* cell) { m_mapCell = cell; }
	//! Only for MapMgr use
	INLINE MapMgr* GetMapMgr() const { return m_mapMgr; }

	INLINE void SetMapId(uint32 newMap) { m_mapId = newMap; }
	void SetZoneId(uint32 newZone);

	INLINE const uint32 GetMapId( ) const { return m_mapId; }
	INLINE const uint32& GetZoneId( ) const { return m_zoneId; }

	//! Get uint32 property
	INLINE const uint32& GetUInt32Value( uint32 index ) const { return m_uint32Values[ index ]; }

	//! Get uint64 property
	INLINE const uint64& GetUInt64Value( uint32 index ) const { return *((uint64*)&(m_uint32Values[ index ])); }

	//! Get float property
	INLINE const float& GetFloatValue( uint32 index ) const { return m_floatValues[ index ]; }

	void __fastcall ModFloatValue(const uint32 index, const float value );
	void ModSignedInt32Value(uint32 index, int32 value);
	void ModUnsigned32Value(uint32 index, int32 mod);
	uint32 GetModPUInt32Value(const uint32 index, const int32 value);

	//! Set uint32 property
	void SetByte(uint32 index, uint32 index1,uint8 value);

	INLINE uint8 GetByte(uint32 i,uint32 i1) { return ((uint8*)m_uint32Values)[i*4+i1]; }
	
	INLINE void SetNewGuid(uint32 Guid)
	{
		uint64 new_full_guid = Guid;
		if( m_objectTypeId == TYPEID_GAMEOBJECT )
			new_full_guid |= ((uint64)GetEntry() << 24) | ((uint64)HIGHGUID_TYPE_GAMEOBJECT << 32);

		if( m_objectTypeId == TYPEID_UNIT )
			new_full_guid |= ((uint64)GetEntry() << 24) | ((uint64)HIGHGUID_TYPE_UNIT << 32);

		SetUInt64Value(OBJECT_FIELD_GUID, new_full_guid);
		m_wowGuid.Init(GetGUID());
	}

	void EventSetUInt32Value(uint32 index, uint32 value);
	void __fastcall SetUInt32Value( const uint32 index, const uint32 value );

	//! Set uint64 property
	void __fastcall SetUInt64Value( const uint32 index, const uint64 value );

	//! Set float property
	void __fastcall SetFloatValue( const uint32 index, const float value );

	void __fastcall SetFlag( const uint32 index, uint32 newFlag );

	void __fastcall RemoveFlag( const uint32 index, uint32 oldFlag );

	void __fastcall SetByteFlag( const uint32 index, const uint32 flag, uint8 newFlag);
	bool __fastcall HasByteFlag( const uint32 index, const uint32 flag, uint8 checkFlag);
	void __fastcall RemoveByteFlag(const uint32 index, const uint32 flag, uint8 checkFlag);

	INLINE bool HasFlag( const uint32 index, uint32 flag ) const { return (m_uint32Values[ index ] & flag) != 0;	}
	
	////////////////////////////////////////
	void ClearUpdateMask( )
	{
		m_updateMask.Clear();
		m_objectUpdated = false;
	}

	bool HasUpdateField(uint32 index) { return m_updateMask.GetBit(index); }

	//use it to check if a object is in range of another
	bool isInRange(Object* target, float range);

	// Use it to Check if a object is in front of another one
	bool isInFront(Object* target);
	bool isInBack(Object* target);
	
	// Check to see if an object is in front of a target in a specified arc (in degrees)
	bool isInArc(Object* target , float degrees); 

	/* Calculates the angle between two Positions */
	float calcAngle( float Position1X, float Position1Y, float Position2X, float Position2Y );
	float calcRadAngle( float Position1X, float Position1Y, float Position2X, float Position2Y );

	/* converts to 360 > x > 0 */
	float getEasyAngle( float angle );

	INLINE const float GetDistanceSq(Object* obj)
	{
		if(obj->GetMapId() != m_mapId) return 40000.0f; //enough for out of range
		return m_position.DistanceSq(obj->GetPosition());
	}

	INLINE float GetDistanceSq(LocationVector & comp)
	{
		return comp.DistanceSq(m_position);
	}

	INLINE float CalcDistance(LocationVector & comp)
	{
		return comp.Distance(m_position);
	}

	INLINE const float GetDistanceSq(float x, float y, float z)
	{
		return m_position.DistanceSq(x, y, z);
	}

	INLINE const float GetDistance2dSq( Object* obj )
	{
		if( obj->GetMapId() != m_mapId )
			return 40000.0f; //enough for out of range
		return m_position.Distance2DSq( obj->m_position );
	}

	INLINE float GetDistance2dSq(float x, float y)
	{
		return m_position.Distance2DSq( x, y );
	}


	// In-range object management, not sure if we need it
	INLINE bool IsInRangeSet( Object* pObj )
	{
		return !( m_objectsInRange.find( pObj ) == m_objectsInRange.end() );
	}
	
	virtual void AddInRangeObject(Object* pObj)
	{
		if( pObj == NULL )
			return;

		m_objectsInRange.insert( pObj );

		if( pObj->GetTypeId() == TYPEID_PLAYER )
			m_inRangePlayers.insert( TO_PLAYER(pObj) );
	}

	INLINE void RemoveInRangeObject( Object* pObj )
	{
		if( pObj == NULL )
			return;

		OnRemoveInRangeObject( pObj );
		m_objectsInRange.erase( pObj );
	}

	INLINE bool HasInRangeObjects()
	{
		return ( m_objectsInRange.size() > 0 );
	}

	virtual void OnRemoveInRangeObject( Object* pObj )
	{
		if( pObj->GetTypeId() == TYPEID_PLAYER )
			m_inRangePlayers.erase( TO_PLAYER(pObj) );
	}

	virtual void ClearInRangeSet()
	{
		m_objectsInRange.clear();
		m_inRangePlayers.clear();
		m_oppFactsInRange.clear();
	}

	INLINE size_t GetInRangeCount() { return m_objectsInRange.size(); }
	INLINE size_t GetInRangePlayersCount() { return m_inRangePlayers.size();}
	INLINE InRangeSet::iterator GetInRangeSetBegin() { return m_objectsInRange.begin(); }
	INLINE InRangeSet::iterator GetInRangeSetEnd() { return m_objectsInRange.end(); }
	INLINE InRangeSet::iterator FindInRangeSet(Object* obj) { return m_objectsInRange.find(obj); }

	void RemoveInRangeObject(InRangeSet::iterator itr)
	{ 
		OnRemoveInRangeObject(*itr);
		m_objectsInRange.erase(itr);
	}

	INLINE bool RemoveIfInRange( Object* obj )
	{
		InRangeSet::iterator itr = m_objectsInRange.find(obj);
		if( obj->GetTypeId() == TYPEID_PLAYER )
			m_inRangePlayers.erase( TO_PLAYER(obj) );

		if( itr == m_objectsInRange.end() )
			return false;
		
		m_objectsInRange.erase( itr );
		return true;
	}

	INLINE void AddInRangePlayer( Object* obj )
	{
		m_inRangePlayers.insert( TO_PLAYER(obj) );
	}

	INLINE void RemoveInRangePlayer( Object* obj )
	{
		m_inRangePlayers.erase( TO_PLAYER(obj) );
	}

	bool IsInRangeOppFactSet(Object* pObj) { return (m_oppFactsInRange.count(pObj) > 0); }
	void UpdateOppFactionSet();
	INLINE UNORDERED_SET<Object* >::iterator GetInRangeOppFactsSetBegin() { return m_oppFactsInRange.begin(); }
	INLINE UNORDERED_SET<Object* >::iterator GetInRangeOppFactsSetEnd() { return m_oppFactsInRange.end(); }
	INLINE UNORDERED_SET<Player*  >::iterator GetInRangePlayerSetBegin() { return m_inRangePlayers.begin(); }
	INLINE UNORDERED_SET<Player*  >::iterator GetInRangePlayerSetEnd() { return m_inRangePlayers.end(); }
	INLINE UNORDERED_SET<Player*  > * GetInRangePlayerSet() { return &m_inRangePlayers; };

	void __fastcall SendMessageToSet(WorldPacket *data, bool self,bool myteam_only=false);
	INLINE void SendMessageToSet(StackPacket * data, bool self) { OutPacketToSet(data->GetOpcode(), (uint16)data->GetSize(), data->GetBufferPointer(), self); }
	void OutPacketToSet(uint16 Opcode, uint16 Len, const void * Data, bool self);

	//! Fill values with data from a space seperated string of uint32s.
	void LoadValues(const char* data);

	INLINE uint16 GetValuesCount() const { return m_valuesCount; }

	//! Blizzard seem to send those for all object types. weird.
	float m_walkSpeed;
	float m_runSpeed;
	float m_backWalkSpeed;
	float m_swimSpeed;
	float m_backSwimSpeed;
	float m_turnRate;
	float m_flySpeed;
	float m_backFlySpeed;

	float m_base_runSpeed;
	float m_base_walkSpeed;

	void SpellNonMeleeDamageLog(Unit* pVictim, uint32 spellID, uint32 damage, bool allowProc, bool static_damage = false, bool no_remove_auras = false, uint32 AdditionalCritChance = 0);
	
	//*****************************************************************************************
	//* SpellLog packets just to keep the code cleaner and better to read
	//*****************************************************************************************
	void SendSpellLog(Object* Caster, Object* Target,uint32 Ability, uint8 SpellLogType);
	void SendSpellNonMeleeDamageLog( Object* Caster, Unit* Target, uint32 SpellID, uint32 Damage, uint8 School, uint32 AbsorbedDamage, uint32 ResistedDamage, bool PhysicalDamage, uint32 BlockedDamage, bool CriticalHit, bool bToSet );
	void SendAttackerStateUpdate( Unit* Target, dealdamage *dmg, uint32 realdamage, uint32 abs, uint32 blocked_damage, uint32 hit_status, uint32 vstate );

	//Dynamic objects
	DynamicObject* dynObj;

	//object faction
	void _setFaction();
	uint32 _getFaction(){return m_faction->Faction;}
	
	FactionTemplateDBC *m_faction;
	FactionDBC *m_factionDBC;

	INLINE void SetInstanceID(int32 instance) { m_instanceId = instance; }
	INLINE int32 GetInstanceID() { return m_instanceId; }

	int32 event_GetInstanceID();

	bool Active;
	bool CanActivate();
	void Activate(MapMgr* mgr);
	void Deactivate(MapMgr* mgr);
	bool m_inQueue;
	INLINE void SetMapMgr(MapMgr* mgr) { m_mapMgr = mgr; }

	void Delete()
	{
		if(IsInWorld())
			RemoveFromWorld(true);
		Destructor();
	}

	INLINE size_t GetInRangeOppFactCount() { return m_oppFactsInRange.size(); }
	void PlaySoundToSet(uint32 sound_entry);
	void EventSpellHit(Spell* pSpell);

	bool PhasedCanInteract(Object* pObj);
	bool HasPhase() { return m_phaseMode != 0; }
	void EnablePhase(int32 phaseMode);
	void DisablePhase(int32 phaseMode);
	void SetPhase(int32 phase); // Don't fucking use this.

	Aura* m_phaseAura;

protected:
	Object (  );
	
	ByteBuffer m_PackGUID;

	//void _Create (uint32 guidlow, uint32 guidhigh);
	void _Create( uint32 mapid, float x, float y, float z, float ang);

	//! Mark values that need updating for specified player.
	virtual void _SetUpdateBits(UpdateMask *updateMask, Player* target) const;
	//! Mark values that player should get when he/she/it sees object for first time.
	virtual void _SetCreateBits(UpdateMask *updateMask, Player* target) const;

	void _BuildMovementUpdate( ByteBuffer *data, uint32 flags, uint32 flags2, Player* target );
	void _BuildValuesUpdate( ByteBuffer *data, UpdateMask *updateMask, Player* target );

	/* Main Function called by isInFront(); */
	bool inArc(float Position1X, float Position1Y, float FOV, float Orientation, float Position2X, float Position2Y );

	int32 m_phaseMode;
	int32 m_phaseMapId; // -1 = Disregard?
	LocationVector m_phaseLocation;
	uint32 m_phaseDistanceLimit;

	Mutex m_objlock;

	//! WoWGuid class
	WoWGuid m_wowGuid;

	 //! Type id.
	uint8 m_objectTypeId;

	//! Zone id.
	uint32 m_zoneId;
	//! Continent/map id.
	uint32 m_mapId;
	//! Map manager
	MapMgr* m_mapMgr;
	//! Current map cell
	MapCell *m_mapCell;

	LocationVector m_position;
	LocationVector m_lastMapUpdatePosition;
	LocationVector m_spawnLocation;

	// Semaphores - needed to forbid two operations on the same object at the same very time (may cause crashing\lack of data)
	bool mSemaphoreTeleport;

	//! Object properties.
	union {
		uint32* m_uint32Values;
		float* m_floatValues;
	};

	//! Number of properties
	uint32 m_valuesCount;

	//! List of object properties that need updating.
	UpdateMask m_updateMask;

	//! True if object was updated
	bool m_objectUpdated;

	//! Set of Objects in range.
	//! TODO: that functionality should be moved into WorldServer.
	UNORDERED_SET<Object* > m_objectsInRange;
	UNORDERED_SET<Player* > m_inRangePlayers;
	UNORDERED_SET<Object* > m_oppFactsInRange;
   
	int32 m_instanceId;

	ExtensionSet * m_extensions;
	void _SetExtension(const string& name, void* ptr);		// so we can set from scripts. :)

public:

	template<typename T>
		void SetExtension(const string& name, T ptr)
	{
		_SetExtension(name, ((void*)ptr));
	}

	template<typename T>
		T GetExtension(const string& name)
	{
		if( m_extensions == NULL )
			return ((T)NULL);
		else
		{
			ExtensionSet::iterator itr = m_extensions->find( name );
			if( itr == m_extensions->end() )
				return ((T)NULL);
			else
				return ((T)itr->second);
		}
	}

	bool m_loadedFromDB;

	/************************************************************************/
	/* ACCESSOR FUNCTIONS                                                   */
	/************************************************************************/
	// Stats
	INLINE uint32 GetStrength() { return m_uint32Values[UNIT_FIELD_STRENGTH]; }
	INLINE uint32 GetAgility() { return m_uint32Values[UNIT_FIELD_AGILITY]; }
	INLINE uint32 GetStamina() { return m_uint32Values[UNIT_FIELD_STAMINA]; }
	INLINE uint32 GetIntellect() { return m_uint32Values[UNIT_FIELD_INTELLECT]; }
	INLINE uint32 GetSpirit() { return m_uint32Values[UNIT_FIELD_SPIRIT]; }

	// Health
	INLINE uint32 GetHealth() { return m_uint32Values[UNIT_FIELD_HEALTH]; }
	INLINE uint32 GetMaxHealth() { return m_uint32Values[UNIT_FIELD_MAXHEALTH]; }

	bool IsInLineOfSight(Object* pObj);
	int32 GetSpellBaseCost(SpellEntry *sp);

	/************************************************************************/
	/* END ACCESSOR FUNCTIONS                                               */
	/************************************************************************/

	// declaration to fix scripting
	INLINE Loot* GetLoot() { return &m_loot; }

public:
	// loooooot
	Loot m_loot;
	bool m_looted;

	// empties loot vector
	void ClearLoot();
	
public:
	uint32 GetPhaseMask() const { return m_phaseMask; }
	bool isType(uint16 mask) const { return (mask == m_objectType); }
	void GetNearPoint2D( float &x, float &y, float distance, float absAngle) const;
	void GetNearPoint( Object const* searcher, float &x, float &y, float &z, float searcher_size, float distance2d,float absAngle) const;
	void GetClosePoint(float &x, float &y, float &z, float size, float distance2d = 0, float angle = 0) const
	{
		// angle calculated from current orientation
		GetNearPoint(NULL,x,y,z,size,distance2d,GetOrientation() + angle);
	}
	
	float GetObjectSize() const
	{
		return ( m_valuesCount > UNIT_FIELD_COMBATREACH ) ? m_floatValues[UNIT_FIELD_COMBATREACH] : DEFAULT_WORLD_OBJECT_SIZE;
	}
	
	void UpdateGroundPositionZ(float x, float y, float &z) const;
	
	Map* GetMap() const { ASSERT(m_currMap); return m_currMap; }
	Map* FindMap() const { return m_currMap; }
	Map const* GetBaseMap() const;
	
private:
	Map* m_currMap;
	uint32 m_phaseMask; // in area phase state
	uint16 m_objectType;
	
};

#endif


