#pragma once

class windowBase
{
private :
	typedef list<windowBase*>::iterator UI_LIST_ITER;

private :
	UI_LIST_ITER* _managedIter;
	string _winName;
	fPOINT _pos;
public :
	HRESULT init(void);
	void release(void);
	UI_LIST_ITER* update(void);
	void render(void);

public :
	winManager::UI_LIST_ITER*& getIter(void) { return _managedIter; };
	string & getName(void) { return _winName; };

	void show(void) { WINMANAGER->show(this); };
	list<windowBase*>::iterator* close(void) {return WINMANAGER->close(this); };

public :
	windowBase() {};
	~windowBase() {};
};

