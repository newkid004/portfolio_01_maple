#pragma once



enum PATTERN_ORDER_AVATER						//패턴 시전자
{
	PATTERN_ORDER_PLAYER,
	PATTERN_ORDER_MONSTER,
	PATTERN_ORDER_BOSS
};
	
enum PATTERN_ORDER_KIND							//시전자에 따른 패턴 종류
{
	PATTERN_ORDER_CREATE,
	PATTERN_ORDER_RETAIN,
	PATTERN_ORDER_DEAD,
};

enum PATTERN_ORDER_GLOBAL						//시전 패턴
{
	PATTERN_ORDER_MOVE,
	PATTERN_ORDER_WAIT,
	PATTERN_ORDER_JUMP,
	PATTERN_ORDER_ATTACK,
	PATTERN_ORDER_SPECIAL_0,
	PATTERN_ORDER_SPECIAL_1,
	PATTERN_ORDER_SPECIAL_2,
	PATTERN_ORDER_SPECIAL_3,
};

class patternBase
{
protected:
	PATTERN_ORDER_AVATER	_avater;
	PATTERN_ORDER_KIND		_kind;
	PATTERN_ORDER_GLOBAL	_order;

	fPOINT					_patternVelocity;
	NUM_REAL				_aliveTime;
	NUM_REAL				_angle;
public:
	virtual HRESULT init();
	virtual void release();

	virtual void update();

	virtual void appear();
	virtual void retain();
	virtual void disappear();

	virtual fPOINT getPatternVelocity() { return _patternVelocity; }
	virtual NUM_REAL	getAliveTime() { return _aliveTime; }
	
	patternBase() {};
	~patternBase() {};
};
