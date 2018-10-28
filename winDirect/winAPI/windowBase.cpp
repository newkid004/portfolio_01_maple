#include "stdafx.h"
#include "windowBase.h"
#include "winManager.h"

HRESULT windowBase::init(void)
{
	_managedIter = NULL;

	return S_OK;
}

void windowBase::release(void)
{
}

windowBase::UI_LIST_ITER * windowBase::update(void)
{
	return NULL;
}

void windowBase::render(void)
{
}


// ----- windowShop ----- //
HRESULT windowShop::init(void)
{
	return S_OK;
}

void windowShop::release(void)
{
}

windowBase::UI_LIST_ITER * windowShop::update(void)
{
	return NULL;
}

void windowShop::render(void)
{
}
