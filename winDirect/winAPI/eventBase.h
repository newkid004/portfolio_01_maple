#pragma once

class baseObject;

class eventBase
{
private:
	baseObject*		_dest;
	baseObject*		_sour;
	
	unsigned long	_param;

	float _timeAlive;
private:
	eventBase()	: _dest(0), _sour(0), _param(0), _timeAlive(0){}

public:
	virtual HRESULT init() { return S_OK; }
	virtual void release(){}
	virtual void update(){}
	virtual void render(){}

public:
	static eventBase * makeEvent(baseObject* sour, baseObject* dest, unsigned long param = 0ul, float timeAlive = 0.0f);

public: // getter, setter
	float getTimeAlive() { return _timeAlive; }
	~eventBase(){}
};