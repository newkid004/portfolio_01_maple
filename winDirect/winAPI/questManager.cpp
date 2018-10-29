#include "stdafx.h"
#include "questManager.h"

HRESULT questManager::init()
{
	setQuest();
	return S_OK;
}

void questManager::release()
{
	if (!_mQuest.empty())
	{
		_miQuest = _mQuest.begin();
		for (; _miQuest != _mQuest.end();)
		{
			_miQuest->second->release();
			SAFE_DELETE(_miQuest->second);
			_miQuest = _mQuest.erase(_miQuest);
		}
		_mQuest.clear();
		_mMoneyQuest.clear();
		_mItemQuest.clear();
	}
}

void questManager::setQuest()
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("questList.json");
	for (auto it = root["quest"].begin(); it != root["quest"].end(); it++)
	{
		if ((*it).isObject())
		{
			Json::Value subRoot;
			QUEST_TYPE questType;

			string monsterName;
			string monsterNum;
			string gatItemName;
			string gatItemNum;

			if ((*it)["type"].asString() == "gathering")
			{
				questType = QUEST_TYPE::GATHERING;

				subRoot = (*it)["gatItemName"];
				for (auto It = subRoot.begin(); It != subRoot.end(); It++)
				{
					gatItemName += (*It).asString();
					gatItemName += ",";
				}
				gatItemName[gatItemName.size() - 1] = '\0';

				subRoot = (*it)["gatItemNum"];
				for (auto It = subRoot.begin(); It != subRoot.end(); It++)
				{
					gatItemNum += (*It).asString();
					gatItemNum += ",";
				}
				gatItemNum[gatItemNum.size() - 1] = '\0';
			}
			else if ((*it)["type"].asString() == "annihilation")
			{
				questType = QUEST_TYPE::ANNIHILATION;

				subRoot = (*it)["monsterName"];
				for (auto It = subRoot.begin(); It != subRoot.end(); It++)
				{
					monsterName += (*It).asString();
					monsterName += ",";
				}
				monsterName[monsterName.size() - 1] = NULL;

				subRoot = (*it)["monsterNum"];
				for (auto It = subRoot.begin(); It != subRoot.end(); It++)
				{
					monsterNum += (*It).asString();
					monsterNum += ",";
				}
				monsterNum[monsterNum.size() - 1] = '\0';
			}
			else
			{
				questType = (QUEST_TYPE)(QUEST_TYPE::GATHERING | QUEST_TYPE::ANNIHILATION);
			}

			if ((*it)["compensation"].asString() == "money")
			{
				MoneyQuest* quest = new MoneyQuest;
				quest->init(
					(*it)["name"].asString(),
					(*it)["explain"].asString(),
					(*it)["exp"].asInt(),
					questType,
					(*it)["money"].asInt(),
					monsterName,monsterNum,(*it)["monsterKindNum"].asInt(),
					gatItemName,gatItemNum,(*it)["gatItemKindNum"].asInt()
				);
				_mQuest.insert(make_pair((*it)["subName"].asString(), static_cast<questBase*>(quest)));
				_mMoneyQuest.insert(make_pair((*it)["subName"].asString(), quest));
			}
			else if ((*it)["compensation"].asString() == "item")
			{
				ItemQuest* quest = new ItemQuest;
				string itemName;
				subRoot = (*it)["itemName"];
				for (auto It = subRoot.begin(); It != subRoot.end(); It++)
				{
					itemName += (*It).asString();
					itemName += ",";
				}
				itemName[itemName.size() - 1] = NULL;

				quest->init(
					(*it)["name"].asString(),
					(*it)["explain"].asString(),
					(*it)["exp"].asInt(),
					questType,
					(*it)["itemNum"].asString(),
					itemName, monsterName, monsterNum, (*it)["monsterKindNum"].asInt(),
					gatItemName, gatItemNum, (*it)["gatItemKindNum"].asInt()
				);

				_mQuest.insert(make_pair((*it)["subName"].asString(), static_cast<questBase*>(quest)));
				_mItemQuest.insert(make_pair((*it)["subName"].asString(), quest));
			}			
		}
	}
}

questBase * questManager::findQuest_base(string name)
{
	_miQuest = find_if(_mQuest.begin(), _mQuest.end(), [name](pair<string, questBase*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});

	if (_miQuest != _mQuest.end())
	{
		return _miQuest->second;
	}
	return NULL;
}

MoneyQuest * questManager::findQuest_Money(string name)
{
	_miMoneyQuest = find_if(_mMoneyQuest.begin(), _mMoneyQuest.end(), [name](pair<string, questBase*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});

	if (_miMoneyQuest != _mMoneyQuest.end())
	{
		return _miMoneyQuest->second;
	}
	return NULL;
}

ItemQuest * questManager::findQuest_Item(string name)
{
	_miItemQuest = find_if(_mItemQuest.begin(), _mItemQuest.end(), [name](pair<string, questBase*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});

	if (_miItemQuest != _mItemQuest.end())
	{
		return _miItemQuest->second;
	}
	return NULL;
}
