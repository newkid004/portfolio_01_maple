#pragma once
#include "baseObject.h"
#include "patternBase.h"
#include "buffBase.h"
#include "state.h"


class characterBase :public baseObject
{
protected:
	patternBase * _currentPattern;				//현재 패턴

	list<buffBase*> _LbuffList;					//버프 리스트
	list<buffBase*>::iterator _Libuff;

protected:
	fPOINT		_velocity;						//속도			<- 중력 + 마찰속도 + 현재 속도 (최종속도)
	rayStruct	_rayStruct;						//광선 구조체(충돌검사 광선)

	bool		_isCollision;					//충돌검사 여부 변수
protected:
	void setRayStruct();						//광선 생성 움직일때 마다 생성됨
	void rayCollision();						//광선 충돌

public:

	void setPattern(patternBase* pattern) { _currentPattern = pattern; }

	list<buffBase*>&getBuffList() { return _LbuffList; }
	patternBase* getPattern() { return _currentPattern; }
	void getVelocity() {
		_velocity = _currentPattern->getPatternVelocity();
		_velocity.y += 1.0f;

		setRayStruct();
		rayCollision();
	}

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void render() = 0;
	characterBase() {};
	~characterBase() {};
};

