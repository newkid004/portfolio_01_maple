#include "stdafx.h"
#include "patternBase.h"

HRESULT patternBase::init()
{
	return S_OK;
}

void patternBase::update()
{
	//등장
	if (_kind == PATTERN_ORDER_CREATE)
	{
		appear();
	}
	//살아있음 유지
	if (_kind == PATTERN_ORDER_RETAIN)
	{
		retain();
	}
	//죽음
	if (_kind == PATTERN_ORDER_DEAD)
	{
		disappear();
	}
}

void patternBase::appear()
{

}

void patternBase::retain()
{
	if (_order == PATTERN_ORDER_WAIT)
	{

	}
	else if (_order == PATTERN_ORDER_MOVE)
	{

	}
}

void patternBase::disappear()
{
}

void patternBase::release()
{
}