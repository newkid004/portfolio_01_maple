#include "stdafx.h"
#include "activeSkill.h"

HRESULT activeSkill::init()
{
	_skillType = skillBase::SKILLTYPE::ACTIVE;
	return S_OK;
}

void activeSkill::release()
{
}

void activeSkill::render()
{
}


//*************************** 버프스킬 ********************************//
HRESULT buffSkill::init()
{
	return S_OK;
}

void buffSkill::release()
{
}

void buffSkill::render()
{
}


//*************************** 공격스킬 ********************************//
HRESULT attackSkill::init()
{
	return S_OK;
}

void attackSkill::release()
{
}

void attackSkill::render()
{
}


//*************************** 무빙스킬 *******************************//
HRESULT moveSkill::init()
{
	return S_OK;
}

void moveSkill::release()
{
}

void moveSkill::render()
{
}
