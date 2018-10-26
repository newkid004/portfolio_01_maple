#pragma once
#include "characterBase.h"
class enemyBase:public characterBase
{
protected:
	NUM_REAL			_hp;


public:
	HRESULT init();
	void update();
	void release();
	void render();

	enemyBase() {};
	~enemyBase() {};
};

