#pragma once
#include "skillBase.h"
class activeSkill:public skillBase
{
protected:
	NUM_REAL					_cooltime;						//쿨타임

	bool						_isBuff;						//버프인지 아닌지의 여부
public:
	virtual HRESULT	init();
	virtual void release();
	virtual void render();

	activeSkill() {}
	~activeSkill() {}
};


class buffSkill :public activeSkill
{
protected:
	NUM_REAL		_aliveTime;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void render();

	buffSkill() {}
	~buffSkill() {}
};

class attackSkill :public activeSkill
{
protected:
	NUM_REAL					_hitbyhitTime;					//데미지 뜨는 속도

	int							_hitNum;						//한 몬스터에 때리는 타수
	int							_hitMonsterNum;					//때릴수 있는 몬스터 수
public:
	virtual HRESULT init();
	virtual void release();
	virtual void render();

	attackSkill() {}
	~attackSkill() {}
};

class moveSkill : public activeSkill
{
protected:
	NUM_REAL			_velocity;
	NUM_REAL			_angle;
	NUM_REAL			_airTime;
public:	
	virtual HRESULT init();
	virtual void release();
	virtual void render();
};