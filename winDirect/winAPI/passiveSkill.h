#pragma once
#include "skillBase.h"
class passiveSkill:public skillBase
{
public:
	virtual HRESULT	init();
	virtual void release();
	virtual void render();

	passiveSkill() {};
	~passiveSkill() {};
};

