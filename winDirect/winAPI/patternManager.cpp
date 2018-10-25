#include "stdafx.h"
#include "patternManager.h"

HRESULT patternManager::init()
{
	return S_OK;
}


void patternManager::release()
{
	if (!_mPattern.empty())
	{
		_miPattern = _mPattern.begin();
		for (; _miPattern != _mPattern.end();)
		{
			_miPattern->second->release();
			_miPattern = _mPattern.erase(_miPattern);
		}
	}
	_mPattern.clear();
}

void patternManager::addPattern(string name, patternBase * pattern)
{
	_miPattern = find_if(_mPattern.begin(), _mPattern.end(),[name](pair<string, patternBase*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});
	if (_miPattern == _mPattern.end())
	{
		_mPattern.insert(make_pair(name, pattern));
	}
}

void patternManager::delPattern(string name)
{
	_miPattern = find_if(_mPattern.begin(), _mPattern.end(), [name](pair<string, patternBase*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});
	if (_miPattern != _mPattern.end())
	{
		_miPattern->second->release();
		_miPattern = _mPattern.erase(_miPattern);
	}
}

patternBase * patternManager::findPattern(string name)
{
	_miPattern = find_if(_mPattern.begin(), _mPattern.end(), [name](pair<string, patternBase*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});
	if (_miPattern != _mPattern.end())return _miPattern->second;
	else return NULL;
}
