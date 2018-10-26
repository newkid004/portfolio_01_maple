#include "stdafx.h"
#include "itemBase.h"

// ----- ItemBase ----- //
void itemBase::render2Field(void)
{
	// RENDERMANAGER->add(RO_ITEM, _content->imgIcon, )
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

