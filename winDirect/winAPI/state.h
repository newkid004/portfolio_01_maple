#pragma once
#include "stdafx.h"
#include "classesDef.h"


enum MOVEMENT
{
	M_NONE				= 0x0000,
	M_WAKE				= 0x0001,
	M_DOWN				= 0x0002,
	M_JUMP				= 0x0004,
	M_DEAD				= 0x0008,
	M_ATTACK			= 0x0010,
	M_INV				= 0x0011,
	M_FLY				= 0x0012,

};

struct stateBasic
{
	unsigned int		_hp;								//현재	hp
	unsigned int		_maxHp;								//현재 최대 hp

	unsigned int		_mp;								//현재	mp
	unsigned int		_maxMp;								//현재 최대 mp

	NUM_REAL			_atkMelee;							//현재 물리공격력
	NUM_REAL			_atkSpell;							//현재 마법공격력

	NUM_REAL			_defMelee;							//현재 물리방어력
	NUM_REAL			_defSpell;							//현재 마법방어력

	NUM_REAL			_moveSpeed;							//현재 이동속도
	NUM_REAL			_jumpSpeed;							//현재 점프속도

	stateBasic()
	{
		ZeroMemory(this, sizeof(stateBasic));
	}
};

struct stateLimit
{
	classesDef::CLASSES	_classes;							//분류(직업)
	int					_Lv;								//레벨
	NUM_REAL			_stateAtk;							//스텟공격력

	stateLimit()
	{
		ZeroMemory(this, sizeof(stateLimit));
	}
};

struct statePoint
{
	unsigned int		_str;								//주스텟 힘(전사)
	unsigned int		_dex;								//주스텟	민첩(궁수)
	unsigned int		_int;								//주스텟 지력(마법사)
	unsigned int		_luk;								//주스텟 운(도적)

	statePoint()
	{
		ZeroMemory(this, sizeof(statePoint));
	}
};

struct statePersent
{
	NUM_REAL		_perDamage;								//데미지 퍼센트
	NUM_REAL		_perMeleeAtk;							//공격력 퍼센트
	NUM_REAL		_perSpellAtk;							//마력	퍼센트
	NUM_REAL		_perBossDamage;							//보스 공격력 퍼센트

	NUM_REAL		_perMeleeDef;							//물리 방어력 퍼센트
	NUM_REAL		_perSpellDef;							//마법 방어력 퍼센트

	NUM_REAL		_perAllStatePoint;						//주스텟(모든) 퍼센트
	
	NUM_REAL		_perStr;								//주스텟(힘) 퍼센트
	NUM_REAL		_perDex;								//주스텟(민첩) 퍼센트
	NUM_REAL		_perInt;								//주스텟(지력) 퍼센트
	NUM_REAL		_perLuk;								//주스텟(운)  퍼센트

	NUM_REAL		_perCritical;							//크리티컬확률 퍼센트
	NUM_REAL		_perCriticalDamage;						//크리티컬데미지 퍼센트

	NUM_REAL		_perMaxHp;								//최대 Hp 퍼센트
	NUM_REAL		_perMaxMp;								//최대 mp 퍼센트

	statePersent()
	{
		ZeroMemory(this, sizeof(statePersent));
	}
};

struct state
{
	MOVEMENT			_movement;

	stateLimit			_stateLimit;

	stateBasic			_permanentBasic;
	stateBasic			_adjStateBasic;
	stateBasic			_totalStateBasic;

	statePoint			_permanentPoint;
	statePoint			_itemStatePoint;
	statePoint			_totalStatePoint;

	statePersent		_permanentPersent;
	statePersent		_itemStatePersent;
	statePersent		_totalStatePersent;
};
