#include "stdafx.h"
#include "fieldManager.h"

#include "fieldBase.h"

HRESULT fieldManager::init(void)
{
	return S_OK;
}

void fieldManager::release(void)
{
	for (auto iter = _mField.begin(); iter != _mField.end();)
	{
		iter->second->release();
		SAFE_DELETE(iter->second);

		iter = _mField.erase(iter);
	}
}

fieldBase * fieldManager::find(string fName)
{
	auto iter = _mField.find(fName);
	if (iter == _mField.end()) return NULL;

	return iter->second;
}

fieldBase * fieldManager::add(string fName, fieldBase * fValue)
{
	auto iter = _mField.find(fName);
	if (iter != _mField.end()) return iter->second;

	_mField.insert(make_pair(fName, fValue));

	return fValue;
}
