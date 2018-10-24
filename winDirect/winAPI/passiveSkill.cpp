#include "stdafx.h"
#include "passiveSkill.h"

HRESULT passiveSkill::init()
{
	_skillType = skillBase::SKILLTYPE::PASSIVE;
	return S_OK;
}

void passiveSkill::release()
{
}

void passiveSkill::render()
{
}
