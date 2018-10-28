#pragma once

class itemBase;

class shopBase
{
private :
	vector<itemBase*> _vItem;

public :
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);



public:
	shopBase()  {};
	~shopBase() {};
};

