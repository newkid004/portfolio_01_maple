#include "stdafx.h"
#include "luckySeven.h"

HRESULT luckySeven::init()
{
	skillBase::init();
	activeSkill::init();

	_hitbyhitTime = 0.1f;					

	_hitNum = 2;						
	_hitMonsterNum = 1;
	_name = "��Ű ����";								
	_explain = "ǥâ�ΰ�����";					

	ZeroMemory(&_spendStruct, sizeof(SPEND));

	return S_OK;
}

void luckySeven::release()
{
	
}

void luckySeven::render()
{
}

void luckySeven::getLv_info(int Lv)
{
	_adjStatePersent._perDamage = 100 + (5 * Lv);
}
