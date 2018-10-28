#include "stdafx.h"
#include "questBase.h"


HRESULT questBase::init(string name, string explain, QUEST_TYPE type)
{
	_name = name;
	_explain = explain;
	_type = type;

	return S_OK;
}

void questBase::release()
{
	SAFE_DELETE_ARRAY(_toGatItemNum);
	SAFE_DELETE_ARRAY(_toGatItemName);

	SAFE_DELETE_ARRAY(_monsterNum);
	SAFE_DELETE_ARRAY(_monsterName);
}

void questBase::setMonsterNum(string monsterNum)
{
	string numArray = monsterNum;
	char* str = (char*)numArray.c_str();
	string num = strtok(str, ",");
	int index = 0;
	while (!num.empty())
	{
		num = strtok(NULL, ",");
		_monsterNum[index] = atoi(num.c_str());
		index++;
	}
}

void questBase::setMonsterName(string monsterName)
{
	string mName = monsterName;
	char* str = (char*)mName.c_str();
	string name = strtok(str, ",");
	int index = 0;
	while (!name.empty())
	{
		name = strtok(NULL, ",");
		_monsterName[index] = name;
		index++;
	}
}

void questBase::setGatItemNum(string itemNum)
{
	string numArray = itemNum;
	char* str = (char*)numArray.c_str();
	string num = strtok(str, ",");
	int index = 0;
	while (!num.empty())
	{
		num = strtok(NULL, ",");
		_toGatItemNum[index] = atoi(num.c_str());
		index++;
	}
}

void questBase::setGatItemName(string itemName)
{
	string mName = itemName;
	char* str = (char*)mName.c_str();
	string name = strtok(str, ",");
	int index = 0;
	while (!name.empty())
	{
		name = strtok(NULL, ",");
		_toGatItemName[index] = name;
		index++;
	}
}



questBase::questBase()
{
}


questBase::~questBase()
{
}

HRESULT compensation_MoneyQuest::init(
	string name, string explain, QUEST_TYPE type,
	int money
	, string monsterName, string monsterNum, int monsterKindNum,
	string gatItemName, string gatItemNum, int itemKindNum
)
{
	questBase::init(name, explain, type);

	_toGatItemNum = NULL;
	_toGatItemName = NULL;

	_monsterNum = NULL;
	_monsterName = NULL;

	if (type == QUEST_TYPE::GATHERING)
	{
		_gatItemKindNum = itemKindNum;
		_toGatItemNum = new int[_gatItemKindNum];
		_toGatItemName = new string[_gatItemKindNum];

		setGatItemNum(gatItemNum);
		setGatItemName(gatItemName);
	}
	else if (type == QUEST_TYPE::ANNIHILATION)
	{
		_monsterKindNum = monsterKindNum;
		_monsterNum = new int[_monsterKindNum];
		_monsterName = new string[_monsterKindNum];

		setMonsterNum(monsterNum);
		setMonsterName(monsterName);
	}
	else if (type == QUEST_TYPE::AN_GA)
	{
		_gatItemKindNum = itemKindNum;
		_toGatItemNum = new int[_gatItemKindNum];
		_toGatItemName = new string[_gatItemKindNum];

		_monsterKindNum = monsterKindNum;
		_monsterNum = new int[_monsterKindNum];
		_monsterName = new string[_monsterKindNum];

		setGatItemNum(gatItemNum);
		setGatItemName(gatItemName);

		setMonsterNum(monsterNum);
		setMonsterName(monsterName);
	}

	_money = money;

	return S_OK;
}

void compensation_MoneyQuest::release()
{
	questBase::release();
}

HRESULT compensation_ItemQuest::init(
	string name, string explain, QUEST_TYPE type,
	string itemNum, string itemName
	, string monsterName, string monsterNum, int monsterKindNum,
	string gatItemName, string gatItemNum, int itemKindNum
)
{
	questBase::init(name, explain, type);
	
	_toGatItemNum = NULL;
	_toGatItemName = NULL;

	_monsterNum = NULL;
	_monsterName = NULL;

	if (type == QUEST_TYPE::GATHERING)
	{
		_gatItemKindNum = itemKindNum;
		_toGatItemNum = new int[_gatItemKindNum];
		_toGatItemName = new string[_gatItemKindNum];

		setGatItemNum(gatItemNum);
		setGatItemName(gatItemName);
	}
	else if (type == QUEST_TYPE::ANNIHILATION)
	{
		_monsterKindNum = monsterKindNum;
		_monsterNum = new int[_monsterKindNum];
		_monsterName = new string[_monsterKindNum];

		setMonsterNum(monsterNum);
		setMonsterName(monsterName);
	}
	else if (type == QUEST_TYPE::AN_GA)
	{
		_gatItemKindNum = itemKindNum;
		_toGatItemNum = new int[_gatItemKindNum];
		_toGatItemName = new string[_gatItemKindNum];

		_monsterKindNum = monsterKindNum;
		_monsterNum = new int[_monsterKindNum];
		_monsterName = new string[_monsterKindNum];

		setGatItemNum(gatItemNum);
		setGatItemName(gatItemName);

		setMonsterNum(monsterNum);
		setMonsterName(monsterName);
	}

	setItemName(itemName);
	setItemNum(itemNum);
	return S_OK;
}

void compensation_ItemQuest::release()
{
	questBase::release();
	SAFE_DELETE_ARRAY(_itemName);
	SAFE_DELETE_ARRAY(_itemNum);
}

void compensation_ItemQuest::setItemName(string itemNameArray)
{
	string ItemName = itemNameArray;
	char* str = (char*)ItemName.c_str();
	string name = strtok(str, ",");
	int index = 0;
	while (!name.empty())
	{
		name = strtok(NULL, ",");
		_itemName[index] = ItemName;
		index++;
	}
}


void compensation_ItemQuest::setItemNum(string itemNum)
{
	string numArray = itemNum;
	char* str = (char*)numArray.c_str();
	string num = strtok(str, ",");
	int index = 0;
	while (!num.empty())
	{
		num = strtok(NULL, ",");
		_itemNum[index] = atoi(num.c_str());
		index++;
	}
}
