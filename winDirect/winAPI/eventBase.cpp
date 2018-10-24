#include "stdafx.h"
#include "eventBase.h"
#include "baseObject.h"


eventBase * eventBase::makeEvent(baseObject * sour, baseObject * dest, unsigned long param, float timeAlive)
{
	eventBase* ev = new eventBase;
	ev->_sour = sour;
	ev->_dest = dest;
	ev->_param = param;
	ev->_timeAlive = timeAlive;

	return ev;
}
