<<<<<<< HEAD
#include "stdafx.h"
#include "winManager.h"
#include "windowBase.h"


HRESULT winManager::init(void)
{
	return S_OK;
}

void winManager::release(void)
{
	_lWindow.clear();
	for (auto iter = _mWindow.begin(); iter != _mWindow.end(); ++iter)
	{
		windowBase * winView = iter->second;
		
		winView->release();
		SAFE_DELETE(winView);
	}
}

void winManager::update(void)
{
	for (auto iter = _lWindow.begin(); iter != _lWindow.end();)
	{
		auto nextIter = (*iter)->update();
		
		if (nextIter)
			iter = *nextIter;
		else
			++iter;
	}
}

void winManager::render(void)
{
	for (auto winBase : _lWindow)
		winBase->render();
}

windowBase * winManager::add(string winName, windowBase * winAdd)
{
	// ¸ñ·Ï¿¡ ´ã°ÜÀÖ´ÂÁö ÆÇº°
	auto iter = _mWindow.find(winName);
	if (iter != _mWindow.end()) return iter->second;

	_mWindow.insert(make_pair(winName, winAdd));
	return winAdd;
}

windowBase * winManager::find(string winName)
{
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return NULL;

	return iter->second;
}

void winManager::show(string winName)
{
	// ¸ñ·Ï¿¡ ´ã°ÜÀÖ´ÂÁö ÆÇº°
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return;

	// ÀÌ¹Ì ¿­·È´ÂÁö ÆÇº°
	windowBase* winBase = iter->second;
	if (winBase->getIter() != NULL)
	{
		// ÀÌ¹Ì ¿­·ÁÀÖÀ½ -> ±âÁ¸ À§Ä¡ »èÁ¦
		_lWindow.erase(*winBase->getIter());
	}

	// ¸Ç ¾Õ¿¡ Ã¢ ¶ç¿ò
	_lWindow.push_front(winBase);
	winBase->getIter() = &_lWindow.begin();
}

void winManager::show(windowBase * winBase)
{
	show(winBase->getIter());
}

void winManager::show(UI_LIST_ITER *& winIter)
{
	// ** Ãæµ¹ À§Çè ** //
	// ¸Ç ¾Õ¿¡ Ã¢ »ðÀÔ ÈÄ, ±âÁ¸ À§Ä¡ »èÁ¦
	_lWindow.push_front(**winIter);
	_lWindow.erase(*winIter);
	winIter = &_lWindow.begin();
}

winManager::UI_LIST_ITER*  winManager::close(string winName)
{
	// ¸ñ·Ï¿¡ ´ã°ÜÀÖ´ÂÁö ÆÇº°
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return NULL;

	// ÀÌ¹Ì ´ÝÇû´ÂÁö ÆÇº°
	windowBase* winBase = iter->second;
	if (winBase->getIter() != NULL)
	{
		// ÀÌ¹Ì ´ÝÇôÀÖÀ½ -> ³ª°¨
		return NULL;
	}

	// ´Ý°í ÃÊ±âÈ­
	winManager::UI_LIST_ITER* nextIter = &_lWindow.erase(*winBase->getIter());
	winBase->getIter() = NULL;

	return nextIter;
}

winManager::UI_LIST_ITER* winManager::close(windowBase * winBase)
{
	return close(winBase->getIter());
}

winManager::UI_LIST_ITER* winManager::close(UI_LIST_ITER *& winIter)
{
	// ** Ãæµ¹ À§Çè ** //
	// ´Ý°í ÃÊ±âÈ­
	auto nextIter = &_lWindow.erase(*winIter);
	winIter = NULL;

	return nextIter;
}
=======
#include "stdafx.h"
#include "winManager.h"
#include "windowBase.h"


HRESULT winManager::init(void)
{
	return S_OK;
}

void winManager::release(void)
{
	_lWindow.clear();
	for (auto iter = _mWindow.begin(); iter != _mWindow.end(); ++iter)
	{
		windowBase * winView = iter->second;
		
		winView->release();
		SAFE_DELETE(winView);
	}
}

void winManager::update(void)
{
	for (auto iter = _lWindow.begin(); iter != _lWindow.end();)
	{
		auto nextIter = (*iter)->update();
		
		if (nextIter)
			iter = *nextIter;
		else
			++iter;
	}
}

void winManager::render(void)
{
	for (auto winBase : _lWindow)
		winBase->render();
}

windowBase * winManager::add(string winName, windowBase * winAdd)
{
	// ¸ñ·Ï¿¡ ´ã°ÜÀÖ´ÂÁö ÆÇº°
	auto iter = _mWindow.find(winName);
	if (iter != _mWindow.end()) return iter->second;

	_mWindow.insert(make_pair(winName, winAdd));
	return winAdd;
}

windowBase * winManager::find(string winName)
{
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return NULL;

	return iter->second;
}

void winManager::show(string winName)
{
	// ¸ñ·Ï¿¡ ´ã°ÜÀÖ´ÂÁö ÆÇº°
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return;

	// ÀÌ¹Ì ¿­·È´ÂÁö ÆÇº°
	windowBase* winBase = iter->second;
	if (winBase->getIter() != NULL)
	{
		// ÀÌ¹Ì ¿­·ÁÀÖÀ½ -> ±âÁ¸ À§Ä¡ »èÁ¦
		_lWindow.erase(*winBase->getIter());
	}

	// ¸Ç ¾Õ¿¡ Ã¢ ¶ç¿ò
	_lWindow.push_front(winBase);
	winBase->getIter() = &_lWindow.begin();
}

void winManager::show(windowBase * winBase)
{
	show(winBase->getIter());
}

void winManager::show(UI_LIST_ITER *& winIter)
{
	// ** Ãæµ¹ À§Çè ** //
	// ¸Ç ¾Õ¿¡ Ã¢ »ðÀÔ ÈÄ, ±âÁ¸ À§Ä¡ »èÁ¦
	_lWindow.push_front(**winIter);
	_lWindow.erase(*winIter);
	winIter = &_lWindow.begin();
}

winManager::UI_LIST_ITER*  winManager::close(string winName)
{
	// ¸ñ·Ï¿¡ ´ã°ÜÀÖ´ÂÁö ÆÇº°
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return NULL;

	// ÀÌ¹Ì ´ÝÇû´ÂÁö ÆÇº°
	windowBase* winBase = iter->second;
	if (winBase->getIter() != NULL)
	{
		// ÀÌ¹Ì ´ÝÇôÀÖÀ½ -> ³ª°¨
		return NULL;
	}

	// ´Ý°í ÃÊ±âÈ­
	winManager::UI_LIST_ITER* nextIter = &_lWindow.erase(*winBase->getIter());
	winBase->getIter() = NULL;

	return nextIter;
}

winManager::UI_LIST_ITER* winManager::close(windowBase * winBase)
{
	return close(winBase->getIter());
}

winManager::UI_LIST_ITER* winManager::close(UI_LIST_ITER *& winIter)
{
	// ** Ãæµ¹ À§Çè ** //
	// ´Ý°í ÃÊ±âÈ­
	auto nextIter = &_lWindow.erase(*winIter);
	winIter = NULL;

	return nextIter;
}
>>>>>>> parent of d0a58f6... ì˜¤ë¥˜ ì»¤ë°‹
