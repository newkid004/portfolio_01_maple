#pragma once
#include "skillBase.h"
class activeSkill:public skillBase
{
protected:
	NUM_REAL					_cooltime;						//��Ÿ��
	NUM_REAL					_hitbyhitTime;					//������ �ߴ� �ӵ�

	int							_hitNum;						//�� ���Ϳ� ������ Ÿ��
	int							_hitMonsterNum;					//������ �ִ� ���� ��

	bool						_isBuff;						//�������� �ƴ����� ����
public:
	virtual HRESULT	init();
	virtual void release();
	virtual void render();

	activeSkill() {};
	~activeSkill() {};
};

