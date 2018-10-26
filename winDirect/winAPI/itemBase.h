#pragma once
#include "baseObject.h"
#include "itemDef.h"
#include "state.h"

struct itemContentBase
{
	int type;

	image* imgIcon = NULL;
	image* imgShadow = NULL;

	string name;
	string memo;

	int cost;

	itemContentBase() :
		type(0),
		imgIcon(NULL),
		cost(0)
	{}
	virtual ~itemContentBase() {};
};

struct tagItemEquipmentInfo
{
	image* img;
	fPOINT offset;
	POINT frame;
};

struct itemContentEquip : public itemContentBase
{


	stateLimit limit;
	stateBasic basic;
	statePoint point;
	itemContentEquip() : itemContentBase() { type |= itemDef::ITEM_TYPE_EQUIP | itemDef::ITEM_TYPE_USEABLE; }
};

struct itemContentWeapon : public itemContentEquip {
	itemContentWeapon() : itemContentEquip() { type |= itemDef::ITEM_TYPE_WEAPON; }
};
struct itemContentArmor : public itemContentEquip {
	itemContentArmor() : itemContentEquip() { type |= itemDef::ITEM_TYPE_AMMOR; }
};

class itemBase : public baseObject
{
protected :
	itemContentBase * _content = NULL;

public :
	virtual HRESULT init(void) {};
	virtual void release(void) { SAFE_DELETE(_content); };
	virtual void update(void) {};
	virtual void render(void) {};

public :
	virtual void render2Field(void);

public :
	itemContentBase* getContent(void) { return _content; };
	static int getContentType(itemBase* i)			{ return i->getContent()->type & itemDef::ITEM_TYPE_CHECK; };
	static int getContentType(itemContentBase* i)	{ return i->type & itemDef::ITEM_TYPE_CHECK; };

public:
	itemBase() {};
	~itemBase() {};
};
class itemEquip : public itemBase{};

class itemWeapon : public itemEquip
{
public :
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(void);

public:
	itemWeapon() {};
	~itemWeapon() {};
};

class itemArmor : public itemEquip
{
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(void);

public:
	itemArmor() {};
	~itemArmor() {};
};

