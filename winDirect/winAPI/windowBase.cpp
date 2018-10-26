#include "stdafx.h"
#include "windowBase.h"
#include "winManager.h"

HRESULT windowBase::init(void)
{
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
