#pragma once
#include "singletonBase.h"
#include "patternBase.h"



class patternManager:public singletonBase<patternManager>
{
private:
	typedef map<string, patternBase*>			mPattern;
	typedef map<string, patternBase*>::iterator	miPattern;
private:

	mPattern _mPattern;
	miPattern _miPattern;

public:
	HRESULT init();
	void release();

	void addPattern(string name, patternBase* pattern);
	void delPattern(string name);

	patternBase* findPattern(string name);
	mPattern & getmPattern() { return _mPattern; }

	patternManager() {};
	~patternManager() {};
};

