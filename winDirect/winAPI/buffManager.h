#pragma once
#include "singletonBase.h"
#include "buffBase.h"
#include "baseObject.h"

class buffManager:public singletonBase<buffManager>
{
private:
	typedef map<string, buffBase*>			 mBuff;
	typedef map<string, buffBase*>::iterator miBuff;
private:
	mBuff		_mBuff;
	miBuff		_miBuff;

public:
	HRESULT init();
	void release();
	void render();

	void addBuff(string buffName,buffBase* buff);
	void delBuff(const string buffName);
	buffBase* findBuff(string buffName);


	mBuff&	getmBuff() { return _mBuff; }

	buffManager() {};
	~buffManager() {};
};

