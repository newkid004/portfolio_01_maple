#include "stdafx.h"
#include "itemBase.h"

// ----- ItemBase ----- //
void itemBase::render2Field(float alphaRatio)
{
	RENDERMANAGER->add(RO_ITEM, _content->imgIcon,
		_position - _content->imgIcon->getCenterFramePos(),
		_content->imgFramePos,
		_content->imgIcon->getFrameSize(),
		alphaRatio);
}

void itemBase::render2Inventory(fPOINT posOffset, fPOINT placement)
{
	fPOINT renderPos = posOffset +
		INTERVAL_INVENTORY_TASK_BAR + 
		fPOINT(
			INTERVAL_ITEM_IN_INVENTORY * placement.x,
			INTERVAL_ITEM_IN_INVENTORY * placement.y);

	IMAGEMANAGER->statePos(renderPos);
	_content->imgShadow->frameRender(_content->imgFramePos);
}

// ----- Weapon ----- //
HRESULT itemWeapon::init(void)
{
	_content = new itemContentWeapon();
	return S_OK;
}

void itemWeapon::update(void)
{
}

void itemWeapon::render(void)
{
}

// ----- Armor ----- //
HRESULT itemArmor::init(void)
{
	_content = new itemContentArmor();
	return S_OK;
}

void itemArmor::update(void)
{
}

void itemArmor::render(void)
{
}

