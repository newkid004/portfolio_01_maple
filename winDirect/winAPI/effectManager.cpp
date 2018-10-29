#include "stdafx.h"
#include "effectManager.h"

#include "effectBase.h"

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
	for (_miEffect = _mEffect.begin(); _miEffect != _mEffect.end(); ++_miEffect)
	{
		(*_miEffect).second->release();
		SAFE_DELETE((*_miEffect).second);
	}
	_mEffect.clear();
}

void effectManager::addEffect(string name, effectBase * effect)
{
	for (_miEffect = _mEffect.begin(); _miEffect != _mEffect.end(); ++_miEffect)
	{
		if ((*_miEffect).first == name)
		{
			break;
		}
	}
	if (_mEffect.end() == _miEffect)
	{
		_mEffect.insert(make_pair(name, effect));
	}
}

effectBase * effectManager::findEffect(string name)
{
	for (_miEffect = _mEffect.begin(); _miEffect != _mEffect.end(); ++_miEffect)
	{
		if ((*_miEffect).first == name)
		{
			return (*_miEffect).second;
		}
	}
	return NULL;
}

void effectManager::delEffect(string name)
{
	for (_miEffect = _mEffect.begin(); _miEffect != _mEffect.end(); ++_miEffect)
	{
		if ((*_miEffect).first == name)
		{
			((*_miEffect).second)->release();
			SAFE_DELETE((*_miEffect).second);
			_mEffect.erase(_miEffect);
		}
	}
}
