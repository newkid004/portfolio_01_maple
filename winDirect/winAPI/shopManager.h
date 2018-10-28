#pragma once
#include "singletonBase.h"

class shopBase;

class shopManager : public singletonBase<shopManager>
{
private :
	map<string, shopBase*> _mShop;

public :
	HRESULT init(void);
	void release(void);

	shopBase * add(string name, shopBase * addition);
	shopBase * find(string name);

public:
	shopManager() {};
	~shopManager() {};
};

