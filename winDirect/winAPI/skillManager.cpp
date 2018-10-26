#include "stdafx.h"
#include "skillManager.h"


HRESULT skillManager::init()
{
	return S_OK;
}

void skillManager::release()
{
	if (!_mTotSkill.empty())
	{
		_miTotSkill = _mTotSkill.begin();
		for (; _miTotSkill != _mTotSkill.end();)
		{
			_miTotSkill = _mTotSkill.erase(_miTotSkill);
		}
	}
	_mTotSkill.clear();
	_mActSkill.clear();
	_mPasSkill.clear();
}

void skillManager::render()
{
}

void skillManager::addActiceSkill(string skillName, activeSkill * active)
{
	
	_miTotSkill = find_if(_mTotSkill.begin(), _mTotSkill.end(), [skillName](pair<string, skillBase*> M)->bool {
		if (M.first == skillName) return true;
		else return false;
	});
	
	if (_miTotSkill == _mTotSkill.end())
	{
		_mTotSkill.insert(make_pair(skillName, active));
		_mActSkill.insert(make_pair(skillName, active));
	}
	
}

void skillManager::addPassiveSkill(string skillName, passiveSkill * passive)
{
	_miTotSkill = find_if(_mTotSkill.begin(), _mTotSkill.end(), [skillName](pair<string, skillBase*> M)->bool {
		if (M.first == skillName) return true;
		else return false;
	});

	if (_miTotSkill == _mTotSkill.end())
	{
		_mTotSkill.insert(make_pair(skillName, passive));
		_mPasSkill.insert(make_pair(skillName, passive));
	}
}

void skillManager::delSkill(string skillName)
{
	_miTotSkill = find_if(_mTotSkill.begin(), _mTotSkill.end(), [skillName](pair<string, skillBase*> M)->bool {
		if (M.first == skillName) return true;
		else return false;
	});

	if (_miTotSkill != _mTotSkill.end())
	{
		if (_miTotSkill->second->getSkillType() == skillBase::SKILLTYPE::ACTIVE)
		{
			_miActSkill = find_if(_mActSkill.begin(), _mActSkill.end(), [skillName](pair<string, activeSkill*> M)->bool {
				if (M.first == skillName) return true;
				else return false;
			});
			if (_miActSkill != _mActSkill.end())
			{
				_miActSkill->second->release();
				_miActSkill = _mActSkill.erase(_miActSkill);
			}
		}
		else if (_miTotSkill->second->getSkillType() == skillBase::SKILLTYPE::PASSIVE)
		{
			_miPasSkill = find_if(_mPasSkill.begin(), _mPasSkill.end(), [skillName](pair<string, passiveSkill*> M)->bool {
				if (M.first == skillName) return true;
				else return false;
			});
			if (_miPasSkill != _mPasSkill.end())
			{
				_miPasSkill->second->release();
				_miPasSkill = _mPasSkill.erase(_miPasSkill);
			}
		}

		_miTotSkill = _mTotSkill.erase(_miTotSkill);
	}
}
