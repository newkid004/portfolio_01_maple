#pragma once
#include "baseObject.h"
#include "patternBase.h"
#include "buffBase.h"
#include "state.h"




class characterBase:public baseObject
{
protected:
	patternBase * _currentPattern;

	list<buffBase*> _LbuffList;
	list<buffBase*>::iterator _Libuff;

protected:
	fPOINT	_velocity;
	state	_state;
public:

	void setPattern(patternBase* pattern) { _currentPattern = pattern; }
	
	list<buffBase*>&getBuffList() { return _LbuffList; }
	patternBase* getPattern() { return _currentPattern; }


	void characterMove() { _position.x += _velocity.x; _position.y += _velocity.y; };


	characterBase() {};
	~characterBase() {};
};

