#pragma once
#include "baseObject.h"
#include "animationGroup.h"

class fieldBase;

class interactBase :public baseObject
{
private:



public:
	interactBase() {};
	~interactBase() {};
};




class portal :public interactBase
{
protected:
	animation*	_animation;
	fieldBase*	_destField;
	fPOINT		_destPos;
public:
	HRESULT init();
	void update();
	void render();
	void release();

	animation* getAnimation() { return _animation; }
	
	fieldBase*	getDestField() { return _destField; }
	fPOINT		getDestPos() { return _destPos; }
	portal() {};
	~portal() {};
};




class hiddenPortal : public portal
{
private:
	NUM_REAL			_distance;
public:
	NUM_REAL			getDistance() { return _distance; }

	hiddenPortal() {};
	~hiddenPortal() {};

};

