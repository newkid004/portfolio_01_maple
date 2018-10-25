#include "stdafx.h"
#include "animationGroupManager.h"


HRESULT animationGroupManager::init()
{
	return S_OK;
}

void animationGroupManager::update()
{
}

void animationGroupManager::release()
{
	if (!_mAnimationGroup.empty())
	{
		_miAnimationGroup = _mAnimationGroup.begin();
		for (; _miAnimationGroup != _mAnimationGroup.end();)
		{
			_miAnimationGroup->second->release();
			_miAnimationGroup = _mAnimationGroup.erase(_miAnimationGroup);
		}
		_mAnimationGroup.clear();
	}
}

void animationGroupManager::render()
{

}

void animationGroupManager::addAniGroup(string name, animationGroup * aniGroup)
{
	_miAnimationGroup = find_if(_mAnimationGroup.begin(), _mAnimationGroup.end(), [name](pair<string, animationGroup*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});
	if (_miAnimationGroup == _mAnimationGroup.end())
	{
		_mAnimationGroup.insert(make_pair(name, aniGroup));
	}
}
void animationGroupManager::delAniGroup(string name)
{
	_miAnimationGroup = find_if(_mAnimationGroup.begin(), _mAnimationGroup.end(), [name](pair<string, animationGroup*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});
	if (_miAnimationGroup != _mAnimationGroup.end())
	{
		_miAnimationGroup->second->release();
		_miAnimationGroup = _mAnimationGroup.erase(_miAnimationGroup);
	}
}


animationGroup * animationGroupManager::findAniGroup(string name)
{
	_miAnimationGroup = find_if(_mAnimationGroup.begin(), _mAnimationGroup.end(), [name](pair<string, animationGroup*> M)->bool {
		if (M.first == name)return true;
		else return false;
	});
	if (_miAnimationGroup != _mAnimationGroup.end())
	{
		return _miAnimationGroup->second;
	}
	else return NULL;
}

