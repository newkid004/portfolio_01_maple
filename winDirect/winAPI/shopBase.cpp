#include "stdafx.h"
#include "shopBase.h"

#include "itemBase.h"
#include "windowBase.h"

HRESULT shopBase::init(void)
{
	return S_OK;
}

void shopBase::release(void)
{
	for (auto i : _vItem)
	{
		i->release();
		SAFE_DELETE(i);
	}
}

void shopBase::update(void)
{
}

void shopBase::render(void)
{

}
