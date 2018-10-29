<<<<<<< HEAD
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
	fPOINT posOffset = winShop->getPos();	// ¿©µµøÏ <-> ªÛ¡° ∞£∞›∏∏≈≠ ¥ı«œ±‚ « ø‰

	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		itemBase* viewItem = find(i + winShop->getScroll());

		if (viewItem)
			viewItem->render2Inventory(posOffset, i);
		else
			break;
	}
}
=======
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
	fPOINT posOffset = winShop->getPos();	// ¿©µµøÏ <-> ªÛ¡° ∞£∞›∏∏≈≠ ¥ı«œ±‚ « ø‰

	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		itemBase* viewItem = find(i + winShop->getScroll());

		if (viewItem)
			viewItem->render2Inventory(posOffset, i);
		else
			break;
	}
}
>>>>>>> parent of d0a58f6... Ïò§Î•ò Ïª§Î∞ã
