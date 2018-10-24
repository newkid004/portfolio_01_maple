#pragma once
#include "singletonBase.h"
class patternManager:public singletonBase<patternManager>
{

public:
	patternManager();
	~patternManager();
};

