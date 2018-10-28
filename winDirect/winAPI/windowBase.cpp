#include "stdafx.h"
#include "windowBase.h"
#include "winManager.h"

// ----- Window Base ----- //
HRESULT windowBase::init(void)
{
	_managedIter = NULL;

	return S_OK;
}

void windowBase::release(void)
{
	for (auto i = _lButton.begin(); i != _lButton.end();)
	{
		SAFE_DELETE(*i);
		i = _lButton.erase(i);
	}
}

windowBase::UI_LIST_ITER * windowBase::update(void)
{
	auto i = _lButton.begin();
	for (; i != _lButton.end();)
	{
		auto result = (*i)->update();
		if (result) return result;
	}

	return NULL;
}

void windowBase::render(void)
{
	for (auto i = _lButton.begin(); i != _lButton.end(); ++i)
		(*i)->render(_pos);
}


// ----- Window Shop ----- //
#include "shopBase.h"
HRESULT windowShop::init(void)
{
	windowBase::init();
	_scroll = 0;
	_shop = NULL;

	return S_OK;
}

void windowShop::render(void)
{
	windowBase::render();
	
	if (_shop) _shop->render();
}
