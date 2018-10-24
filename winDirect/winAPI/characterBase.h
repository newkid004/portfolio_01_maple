#pragma once
#include "baseObject.h"
#include "patternBase.h"
#include "buffBase.h"
#include "state.h"




class characterBase:public baseObject
{
protected:
	patternBase * _currentPattern;			//현재 패턴

	list<buffBase*> _LbuffList;				//버프 리스트
	list<buffBase*>::iterator _Libuff;		

protected:
	fPOINT	_velocity;						//속도
	state	_state;							//스텟
public:

	void setPattern(patternBase* pattern) { _currentPattern = pattern; }
	
	list<buffBase*>&getBuffList() { return _LbuffList; }
	patternBase* getPattern() { return _currentPattern; }


	void characterMove() { _position.x += _velocity.x; _position.y += _velocity.y; };


	characterBase() {};
	~characterBase() {};
};

