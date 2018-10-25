#pragma once
#include "singletonBase.h"
#include "skillBase.h"
#include "activeSkill.h"
#include "passiveSkill.h"


class skillManager:public singletonBase<skillManager>
{
private:
	typedef map<string, skillBase*> mTotSkill;
	typedef map<string, activeSkill*> mActSkill;
	typedef map<string, passiveSkill*> mPasSkill;

	typedef map<string, skillBase*>::iterator miTotSkill;
	typedef map<string, activeSkill*>::iterator miActSkill;
	typedef map<string, passiveSkill*>::iterator miPasSkill;

private:
	mTotSkill _mTotSkill;		miTotSkill _miTotSkill;
	mActSkill _mActSkill;		miActSkill _miActSkill;
	mPasSkill _mPasSkill;		miPasSkill _miPasSkill;

public:
	HRESULT		init();
	void		release();
	void		render();

	void		addActiceSkill(string skillName,activeSkill* active);
	void		addPassiveSkill(string skillName,passiveSkill* passive);
	void		delSkill(string skillName);


	template <class T>
	T		findSkill(string skillName,T);

	mTotSkill& getmTotSkill() { return _mTotSkill; }
	mActSkill& getmActSkill() { return _mActSkill; }
	mPasSkill& getmPasSkill() { return _mPasSkill; }

	skillManager() {};
	~skillManager() {};
};

template<class T>
inline T skillManager::findSkill(string skillName, T)
{
	if (T == skillBase*)
	{
		_miTotSkill = find_if(_mTotSkill.begin(), _mTotSkill.end(), [skillName](pair<string, skillBase*> M)->bool {
			if (M.first == skillName) return true;
			else return false;
		});
		if(_miTotSkill != _mTotSkill.end())
		{
			return _miTotSkill->second;
		}
		else return NULL;
	}
	else if(T == activeSkill*)
	{
		_miActSkill = find_if(_mActSkill.begin(), _mActSkill.end(), [skillName](pair<string, activeSkill*> M)->bool {
			if (M.first == skillName) return true;
			else return false;
		});
			if (_miActSkill != _mActSkill.end())
			{
				return _miActSkill->second;
			}
			else return NULL;
	}
	else if (T == buffSkill * )
	{
		_miActSkill = find_if(_mActSkill.begin(), _mActSkill.end(), [skillName](pair<string, activeSkill*> M)->bool {
			if (M.first == skillName) return true;
			else return false;
		});
		if (_miActSkill != _mActSkill.end())
		{
			return static_cast<buffSkill*>(_miActSkill->second);
		}
		else return NULL;
	}
	else if (T == attackSkill * )
	{
		_miActSkill = find_if(_mActSkill.begin(), _mActSkill.end(), [skillName](pair<string, activeSkill*> M)->bool {
			if (M.first == skillName) return true;
			else return false;
		});
		if (_miActSkill != _mActSkill.end())
		{
			return static_cast<attackSkill*>(_miActSkill->second);
		}
		else return NULL;
	}
	else if (T == moveSkill * )
	{
		_miActSkill = find_if(_mActSkill.begin(), _mActSkill.end(), [skillName](pair<string, activeSkill*> M)->bool {
			if (M.first == skillName) return true;
			else return false;
		});
		if (_miActSkill != _mActSkill.end())
		{
			return static_cast<moveSkill*>(_miActSkill->second);
		}
		else return NULL;
	}
	else if (T == passiveSkill*)
	{
		_miPasSkill = find_if(_mPasSkill.begin(), _mPasSkill.end(), [skillName](pair<string, passiveSkill*> M)->bool {
			if (M.first == skillName) return true;
			else return false;
		});
			if (_miPasSkill != _mPasSkill.end())
			{
				return _miPasSkill->second;
			}
			else return NULL;
	}
	else return NULL;
}
