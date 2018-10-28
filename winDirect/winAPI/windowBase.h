#pragma once

class windowBase
{
protected :
	typedef list<windowBase*>::iterator UI_LIST_ITER;

protected:
	UI_LIST_ITER* _managedIter;
	string _winName;
	fPOINT _pos;
public :
	virtual HRESULT init(void);
	virtual void release(void);
	virtual UI_LIST_ITER* update(void);
	virtual void render(void);

public :
	list<windowBase*>::iterator*& getIter(void) { return _managedIter; };
	string & getName(void) { return _winName; };
	fPOINT & getPos(void) { return _pos; };

	void show(void) { WINMANAGER->show(this); };
	list<windowBase*>::iterator* close(void) {return WINMANAGER->close(this); };

public :
	windowBase() {};
	~windowBase() {};
};

#define CNT_SHOP_ITEM_LIST 9
class shopBase;
class windowShop : public windowBase
{
private :
	shopBase* _shop;

public :
	HRESULT init(void);
	void release(void);
	UI_LIST_ITER* update(void);
	void render(void);

public :
	shopBase*& getShop(void) { return _shop; };

public:
	windowShop() {};
	~windowShop() {};
};