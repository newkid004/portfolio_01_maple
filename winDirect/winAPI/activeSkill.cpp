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
