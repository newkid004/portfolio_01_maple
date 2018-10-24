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
	unsigned int		_hp;								//����	hp
	unsigned int		_maxHp;								//���� �ִ� hp

	unsigned int		_mp;								//����	mp
	unsigned int		_maxMp;								//���� �ִ� mp

	NUM_REAL			_atkMelee;							//���� �������ݷ�
	NUM_REAL			_atkSpell;							//���� �������ݷ�

	NUM_REAL			_defMelee;							//���� ��������
	NUM_REAL			_defSpell;							//���� ��������

	NUM_REAL			_moveSpeed;							//���� �̵��ӵ�
	NUM_REAL			_jumpSpeed;							//���� �����ӵ�

	stateBasic()
	{
		ZeroMemory(this, sizeof(stateBasic));
	}
};

struct stateLimit
{
	classesDef::CLASSES	_classes;							//�з�(����)
	int					_Lv;								//����
	NUM_REAL			_stateAtk;							//���ݰ��ݷ�

	stateLimit()
	{
		ZeroMemory(this, sizeof(stateLimit));
	}
};

struct statePoint
{
	unsigned int		_str;								//�ֽ��� ��(����)
	unsigned int		_dex;								//�ֽ���	��ø(�ü�)
	unsigned int		_int;								//�ֽ��� ����(������)
	unsigned int		_luk;								//�ֽ��� ��(����)

	statePoint()
	{
		ZeroMemory(this, sizeof(statePoint));
	}
};

struct statePersent
{
	NUM_REAL		_perDamage;								//������ �ۼ�Ʈ
	NUM_REAL		_perMeleeAtk;							//���ݷ� �ۼ�Ʈ
	NUM_REAL		_perSpellAtk;							//����	�ۼ�Ʈ
	NUM_REAL		_perBossDamage;							//���� ���ݷ� �ۼ�Ʈ

	NUM_REAL		_perMeleeDef;							//���� ���� �ۼ�Ʈ
	NUM_REAL		_perSpellDef;							//���� ���� �ۼ�Ʈ

	NUM_REAL		_perAllStatePoint;						//�ֽ���(���) �ۼ�Ʈ
	
	NUM_REAL		_perStr;								//�ֽ���(��) �ۼ�Ʈ
	NUM_REAL		_perDex;								//�ֽ���(��ø) �ۼ�Ʈ
	NUM_REAL		_perInt;								//�ֽ���(����) �ۼ�Ʈ
	NUM_REAL		_perLuk;								//�ֽ���(��)  �ۼ�Ʈ

	NUM_REAL		_perCritical;							//ũ��Ƽ��Ȯ�� �ۼ�Ʈ
	NUM_REAL		_perCriticalDamage;						//ũ��Ƽ�õ����� �ۼ�Ʈ

	NUM_REAL		_perMaxHp;								//�ִ� Hp �ۼ�Ʈ
	NUM_REAL		_perMaxMp;								//�ִ� mp �ۼ�Ʈ

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
