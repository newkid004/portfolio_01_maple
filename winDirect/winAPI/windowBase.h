#pragma once

class windowBase;

class buttonBase
{
protected :
	fPOINT _pos;	// relative
	fPOINT _size;

	function<void(void)> _active;

public :
	virtual list<windowBase*>::iterator* update(void) { return NULL; };
	virtual void render(fPOINT & offset) {};

public :
	fPOINT & getPos(void) { return _pos; };
	fPOINT & getSize(void) { return _size; };
	function<void(void)> & getActivate(void) { return _active; };

public :
	buttonBase() {};
	~buttonBase() {};
};

class windowBase
{
protected :
	typedef list<windowBase*>::iterator UI_LIST_ITER;

protected:
	UI_LIST_ITER* _managedIter;
	string _winName;
	fPOINT _pos;

	list<buttonBase*> _lButton;

public :
	virtual HRESULT init(void);
	virtual void release(void);
	virtual UI_LIST_ITER* update(void);
	virtual void render(void);

public :
	list<windowBase*>::iterator*& getIter(void) { return _managedIter; };
	string & getName(void) { return _winName; };
	fPOINT & getPos(void) { return _pos; };

public :	// ----- window ----- //
	virtual void show(void) { WINMANAGER->show(this); };
	virtual list<windowBase*>::iterator* close(void) {return WINMANAGER->close(this); };
	virtual bool isShow(void) { return _managedIter ? true : false; };

public :	// ----- button ----- //
	buttonBase* addButton(buttonBase* addition) { _lButton.push_back(addition); };

public :
	windowBase() {};
	~windowBase() {};
};

// ----- window : shop ----- //
#define CNT_SHOP_ITEM_LIST 9
class shopBase;
class windowShop : public windowBase
{
private :
	int _scroll;
	shopBase* _shop;

public :
	HRESULT init(void);
	void render(void);

public :
	int & getScroll(void) { return _scroll; };
	shopBase*& getShop(void) { return _shop; };

	list<windowBase*>::iterator* close(void) override { _scroll = 0; return windowBase::close(); };

public:
	windowShop() {};
	~windowShop() {};
};