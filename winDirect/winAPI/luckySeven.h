#pragma once
#include "activeSkill.h"
class luckySeven : public attackSkill
{
public:
	HRESULT init();
	void release();
	void render();
	void getLv_info(int Lv);
	luckySeven(){}
	~luckySeven(){}
};

