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
	static windowShop *& winShop = SHOPMANAGER->getWindow();
	fPOINT posOffset = winShop->getPos();	// 윈도우 <-> 상점 간격만큼 더하기 필요

	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		itemBase* viewItem = find(i + winShop->getScroll());

		if (viewItem)
			viewItem->render2Inventory(posOffset, i);
		else
			break;
	}
}
