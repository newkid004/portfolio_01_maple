#pragma once
#include "baseObject.h"
#include "animationGroup.h"
class npcBase :public baseObject
{
protected:
	animationGroup *					_animationGroup;


public:
	void release();
	npcBase() {};
	~npcBase() {};
};

