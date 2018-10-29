#pragma once
#include "stdafx.h"
#include "classesDef.h"


enum MOVEMENT
{
	M_NONE				= 0x0000,
	M_WAKE				= 0x0001,
	M_DOWN				= 0x0002,
	M_JUMP				= 0x0004,
	M_ATTACK			= 0x0008,
	M_INV				= 0x0010,
	M_FLY				= 0x0020,
	M_DEAD			    = 0x0040,
	M_SPWAN				= 0x0080,
};

struct stateBasic
{
	unsigned int		hp;								//현재	hp
	unsigned int		maxHp;							//현재 최대 hp

	unsigned int		mp;								//현재	mp
	unsigned int		maxMp;							//현재 최대 mp

	NUM_REAL			atkMelee;						//현재 물리공격력
	NUM_REAL			atkSpell;						//현재 마법공격력

	NUM_REAL			defMelee;						//현재 물리방어력
	NUM_REAL			defSpell;						//현재 마법방어력

	NUM_REAL			moveSpeed;						//현재 이동속도
	NUM_REAL			jumpSpeed;						//현재 점프속도

	stateBasic()
	{
		ZeroMemory(this, sizeof(stateBasic));
	}
};

struct stateLimit
{
	classesDef::CLASSES	classes;						//분류(직업)
	int					Lv;								//레벨

	stateLimit()
	{
		ZeroMemory(this, sizeof(stateLimit));
	}
};

struct statePoint
{
	unsigned int		STR;							//주스텟 힘(전사)
	unsigned int		DEX;							//주스텟 민첩(궁수)
	unsigned int		INT;							//주스텟 지력(마법사)
	unsigned int		LUK;							//주스텟 운(도적)

	statePoint()
	{
		ZeroMemory(this, sizeof(statePoint));
	}
};

struct statePersent
{
	NUM_REAL		damage;								//데미지 퍼센트
	NUM_REAL		meleeAtk;							//공격력 퍼센트
	NUM_REAL		spellAtk;							//마력	퍼센트
	NUM_REAL		bossDamage;							//보스 공격력 퍼센트

	NUM_REAL		meleeDef;							//물리 방어력 퍼센트
	NUM_REAL		spellDef;							//마법 방어력 퍼센트

	NUM_REAL		allStatePoint;						//주스텟(모든) 퍼센트
	
	NUM_REAL		STR;								//주스텟(힘) 퍼센트
	NUM_REAL		DEX;								//주스텟(민첩) 퍼센트
	NUM_REAL		INT;								//주스텟(지력) 퍼센트
	NUM_REAL		LUK;								//주스텟(운)  퍼센트

	NUM_REAL		critical;							//크리티컬확률 퍼센트
	NUM_REAL		criticalDamage;						//크리티컬데미지 퍼센트

	NUM_REAL		maxHp;								//최대 Hp 퍼센트
	NUM_REAL		maxMp;								//최대 mp 퍼센트

	statePersent()
	{
		ZeroMemory(this, sizeof(statePersent));
	}
};

struct state
{
	MOVEMENT			movement;

	stateLimit			stateLimit;

	stateBasic			permanentBasic;
	stateBasic			adjStateBasic;
	stateBasic			totalStateBasic;

	statePoint			permanentPoint;
	statePoint			itemStatePoint;
	statePoint			totalStatePoint;

	statePersent		permanentPersent;
	statePersent		itemStatePersent;
	statePersent		totalStatePersent;
};
