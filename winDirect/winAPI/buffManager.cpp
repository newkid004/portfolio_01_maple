#include "stdafx.h"
#include "buffManager.h"

HRESULT buffManager::init()
{
	return S_OK;
}

void buffManager::release()
{
	if (!_mBuff.empty())
	{
		_miBuff = _mBuff.begin();
		for (; _miBuff != _mBuff.end();)
		{
			_miBuff->second->release();
			_miBuff = _mBuff.erase(_miBuff);
		}
	}
	_mBuff.clear();
}

void buffManager::render()
{
}

void buffManager::addBuff(string buffName,buffBase* buff)
{
	_miBuff = find_if(_mBuff.begin(), _mBuff.end(), [buffName](pair<string, buffBase*> M)->bool {
		if (M.first == buffName)return true;
		else return false;
	});
	if (_miBuff == _mBuff.end())
	{
		_mBuff.insert(make_pair(buffName,buff));
	}
}

void buffManager::delBuff(string buffName)
{
	_miBuff = find_if(_mBuff.begin(), _mBuff.end(), [buffName](pair<string, buffBase*> M)->bool {
		if (M.first == buffName)return true;
		else return false;
	});
	if (_miBuff != _mBuff.end())
	{
		_miBuff->second->release();
		_miBuff = _mBuff.erase(_miBuff);
	}
}

buffBase * buffManager::findBuff(string buffName)
{
	buffBase* buff = NULL;
	_miBuff = find_if(_mBuff.begin(), _mBuff.end(), [buffName](pair<string, buffBase*> M)->bool {
		if (M.first == buffName)return true;
		else return false;
	});
	if (_miBuff != _mBuff.end())
	{
		buff = _miBuff->second;
	}
	return buff;
}
