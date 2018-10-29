#pragma once


enum QUEST_TYPE
{
	ANNIHILATION				=0x0001,	//撰資
	GATHERING					=0x0010,//熱餵
	AN_GA						=0x0011//熱餵,撰資
};



class questBase
{
protected:
	string	_name;
	string	_explain;
	QUEST_TYPE	_type;

	string* _monsterKind;
	string* _monsterName;
	int* _monsterNum;


	string* _toGatItemKind;
	string* _toGatItemName;
	int* _toGatItemNum;

	int _gatItemKindNum;
	int _monsterKindNum;
	NUM_REAL	_exp;
public:
	virtual HRESULT init(string name, string explain, NUM_REAL exp,QUEST_TYPE type);
	virtual void release();
	virtual void setMonsterNum(string monsterNum);
	virtual void setMonsterName(string monsterName);

	virtual void setGatItemNum(string itemNum);
	virtual void setGatItemName(string itemName);
	questBase();
	~questBase();
};

typedef class  compensation_MoneyQuest :public questBase
{
protected:
	int _money;


public:
	virtual HRESULT init(
		string name,string explain, NUM_REAL exp, QUEST_TYPE type,
		int money,string monsterName,string monsterNum,int monsterKindNum,
		string gatItemName,string gatItemNum,int itemKindNum
	);
	virtual void release();
}MoneyQuest;

typedef class compensation_ItemQuest :public questBase
{
protected:
	int*				_itemNum;
	string*				_itemName;
public:
	virtual HRESULT init(
		string name, string explain, NUM_REAL exp, QUEST_TYPE type,
		string itemNum, string itemName,
		string monsterName, string monsterNum, int monsterKindNum,
		string gatItemName, string gatItemNum, int itemKindNum
	);
	virtual void release();

	void setItemName(string itemNameArray);
	void setItemNum(string itemNum);
}ItemQuest;