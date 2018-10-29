#include "stdafx.h"
#include "shopManager.h"

#include "windowBase.h"
#include "shopBase.h"

HRESULT shopManager::init(void)
{
	_bindWindow = NULL;

	return S_OK;
}

void shopManager::release(void)
{
}

shopBase * shopManager::add(string name, shopBase * addition)
{
	return nullptr;
}

shopBase * shopManager::find(string name)
{
	return nullptr;
}
