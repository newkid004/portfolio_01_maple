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
	unsigned int		_hp;
	unsigned int		_maxHp;

	unsigned int		_mp;
	unsigned int		_maxMp;

	NUM_REAL			_atkMelee;
	NUM_REAL			_atkSpell;

	NUM_REAL			_defMelee;
	NUM_REAL			_defSpell;

	NUM_REAL			_moveSpeed;
	NUM_REAL			_jumpSpeed;
};

struct stateLimit
{
	classesDef::CLASSES	_classes;
	int					_Lv;

};

struct statePoint
{
	unsigned int		_str;
	unsigned int		_dex;
	unsigned int		_int;
	unsigned int		_luk;
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

};
