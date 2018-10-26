#include "stdafx.h"
#include "fieldBase.h"

#include "baseObject.h"
#include "enemyBase.h"
#include "npcBase.h"

HRESULT fieldBase::init(void)
{
	return S_OK;
}

void fieldBase::release(void)
{
	releaseTotal();
}

void fieldBase::update(void)
{
}

void fieldBase::render(void)
{
}

void fieldBase::releaseTotal(void)
{
	// releaseItem();
	releaseEnemy();
	// releaseInteract();
	releaseNPC();
}

template<typename OBJ>
inline void fieldBase::addObject(OBJ input, list<pair<list<baseObject*>::iterator*, OBJ>> & o_list)
{
	_fieldList.totalObject.push_front(input);
	o_list.push_front(make_pair(&_fieldList.totalObject.begin(), input));
}

template<typename OBJ>
inline void fieldBase::releaseList(list<pair<list<baseObject*>::iterator*, OBJ>>& o_list, bool isDelete)
{
	for (auto & iter = o_list.begin(); iter != o_list.end();)
	{
		auto totalIter = iter->first;
		OBJ  viewObject = iter->second;

		if (isDelete)
		{
			viewObject->release();
			SAFE_DELETE(viewObject);
		}

		_fieldList.totalObject.erase(*totalIter);
		iter = o_list.erase(iter);
	}
}
