#pragma once
#include "singletonBase.h"

class windowBase;
class shopBase;

class shopManager : public singletonBase<shopManager>
{
private :
	windowBase * _bindWindow;
	map<string, shopBase*> _mShop;

public :
	HRESULT init(void);
	void release(void);

public :
	shopBase * add(string name, shopBase * addition);
	shopBase * find(string name);

	windowBase *& getWindow(void) { return _bindWindow; };

public:
	shopManager() {};
	~shopManager() {};
};

