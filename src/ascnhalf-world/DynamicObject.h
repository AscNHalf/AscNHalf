/* AscNHalf */

#ifndef WOWSERVER_DYNAMICOBJECT_H
#define WOWSERVER_DYNAMICOBJECT_H

struct SpellEntry;

typedef UNORDERED_SET<Unit* >  DynamicObjectList;
typedef UNORDERED_SET<Unit* >  FactionRangeList;

class SERVER_DECL DynamicObject : public Object
{
public:
	DynamicObject( uint32 high, uint32 low );
	~DynamicObject( );
	virtual void Destructor();
	virtual void Init();

	void Create(Object* caster, Spell* pSpell, float x, float y, float z, uint32 duration, float radius);
	void UpdateTargets();

	void AddInRangeObject(Object* pObj);
	void OnRemoveInRangeObject(Object* pObj);
	void Remove();

	//Accessors
	void SetAliveDuration(uint32 dur){m_aliveDuration = dur;};

protected:
	
	SpellEntry * m_spellProto;
	Unit* u_caster;
	Player* p_caster;
	Object* m_caster;
	GameObject* g_caster;
	Spell* m_parentSpell;
	DynamicObjectList targets;
	
	uint32 m_aliveDuration;
	uint32 _fields[DYNAMICOBJECT_END];
	FactionRangeList  m_inRangeOppFactions;
};

#endif

