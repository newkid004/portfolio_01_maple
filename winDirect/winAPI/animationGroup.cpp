#include "stdafx.h"
#include "animationGroup.h"


HRESULT animationGroup::init(void)
{
	_curAni = add("_current", new animation);
	_curAniName = "_current";

	return S_OK;
}

void animationGroup::update(void)
{
	_curAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void animationGroup::update(float ratio)
{
	_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * ratio);
}

void animationGroup::release(void)
{
	map<string, animation*>::iterator iter = _mAnimation.begin();
	for (; iter != _mAnimation.end();)
	{
		animation *& ani = iter->second;
		if (ani)
		{
			ani->release();
			SAFE_DELETE(ani);
		}
		iter = _mAnimation.erase(iter);
	}
}

animation * animationGroup::add(string key, animation * ani, bool isCurrent)
{
	map<string, animation*>::iterator iter = _mAnimation.find(key);
	if (iter != _mAnimation.end()) return iter->second;

	_mAnimation.insert(make_pair(key, ani));
	ani->setAnimationFixed();
	ani->start();

	if (isCurrent)
	{
		_curAniName = key;
		*_curAni = ani;
	}

	return ani;
}

animation * animationGroup::find(string key)
{
	map<string, animation*>::iterator iter = _mAnimation.find(key);
	if (iter == _mAnimation.end()) return NULL;

	return iter->second;
}

animation * animationGroup::set(string key, bool isInit)
{
	if (_curAniName == key && !isInit) return _curAni;

	map<string, animation*>::iterator iter = _mAnimation.find(key);
	if (iter == _mAnimation.end()) return NULL;

	_curAniName = iter->first;
	*_curAni = iter->second;

	return _curAni;
}
