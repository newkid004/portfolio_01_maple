<<<<<<< HEAD
#pragma once
#include "singletonBase.h"

class fieldBase;

class fieldManager : public singletonBase<fieldManager>
{
public :
	map<string, fieldBase*> _mField;

public :
	HRESULT init(void);
	void release(void);

public :
	fieldBase* find(string fName);
	fieldBase* add(string fName, fieldBase* fValue);

public:
	fieldManager() {};
	~fieldManager() {};
};

=======
#pragma once
#include "singletonBase.h"

class fieldBase;

class fieldManager : public singletonBase<fieldManager>
{
public :
	map<string, fieldBase*> _mField;

public :
	HRESULT init(void);
	void release(void);

public :
	fieldBase* find(string fName);
	fieldBase* add(string fName, fieldBase* fValue);

public:
	fieldManager() {};
	~fieldManager() {};
};

>>>>>>> parent of d0a58f6... 오류 커밋
