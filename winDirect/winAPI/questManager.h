#pragma once
#include "questBase.h"

class questManager:public singletonBase<questManager>
{
private:
	typedef map<string, questBase*> mQuest;
	typedef map<string, questBase*>::iterator miQuest;
	
	typedef map<string, MoneyQuest*> mMoneyQuest;
	typedef map<string, MoneyQuest*>::iterator miMoneyQuest;

	typedef map<string, ItemQuest*> mItemQuest;
	typedef map<string, ItemQuest*>::iterator miItemQuest;
private:
	mQuest			_mQuest;					miQuest			_miQuest;
	mMoneyQuest		_mMoneyQuest;				miMoneyQuest	_miMoneyQuest;
	mItemQuest		_mItemQuest;				miItemQuest		_miItemQuest;



public:
	HRESULT init();
	void release();
	
	void setQuest();

	mQuest&				getmQuest()			{ return _mQuest; }
	mMoneyQuest&		getmMoneyQuest()	{ return _mMoneyQuest; }
	mItemQuest&			getmItemQuest()		{ return _mItemQuest; }
	
	questBase*			findQuest_base(string name);
	MoneyQuest*			findQuest_Money(string name);
	ItemQuest*			findQuest_Item(string name);

	questManager() {};
	~questManager() {};
};

