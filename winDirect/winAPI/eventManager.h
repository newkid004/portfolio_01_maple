#pragma once
#include "singletonBase.h"
#include "eventBase.h"

class eventManager:public singletonBase<eventManager>
{
private:
	list<eventBase*> _lEvent;
	
public:
	HRESULT init() {}
	void release();
	void update();
	void render();

	void add(eventBase* ev);
	void deleteAll();

public:
	eventManager(){}
	~eventManager(){}
};