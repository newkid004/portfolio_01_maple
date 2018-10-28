#pragma once
#include "singletonBase.h"

class windowShop;
class shopBase;

class shopManager : public singletonBase<shopManager>
{
private :
	windowShop * _bindWindow;
	map<string, shopBase*> _mShop;

public :
	HRESULT init(void);
	void release(void);

public :
	shopBase * add(string name, shopBase * addition);
	shopBase * find(string name);

	windowShop *& getWindow(void) { return _bindWindow; };

public:
	shopManager() {};
	~shopManager() {};
};

