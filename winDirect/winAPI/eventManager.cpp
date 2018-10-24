#include "stdafx.h"
#include "eventManager.h"

void eventManager::release()
{
	deleteAll();
}

void eventManager::update()
{
	for (auto iter = _lEvent.begin(); iter != _lEvent.end();)
	{
		(*iter)->update();

		if ((*iter)->getTimeAlive() <= 0)
		{
			(*iter)->release();
			SAFE_DELETE(*iter);
			iter = _lEvent.erase(iter);
		}
		else ++iter;
	}
}

void eventManager::render()
{
	for (auto iter = _lEvent.begin(); iter != _lEvent.end(); ++iter)
	{
		(*iter)->render();
	}
}

void eventManager::add(eventBase * ev)
{
	_lEvent.push_back(ev);
}

void eventManager::deleteAll()
{
	for (auto iter = _lEvent.begin(); iter != _lEvent.end(); ++iter)
	{
		(*iter)->release();
		SAFE_DELETE(*iter);
	}
}
