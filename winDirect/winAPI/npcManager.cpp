#include "stdafx.h"
#include "npcManager.h"

HRESULT npcManager::init()
{

	return S_OK;
}

void npcManager::release()
{
	_miNpc = _mNpc.begin();
	for (; _miNpc != _mNpc.end();)
	{
		_miNpc->second->release();
		_miNpc->second = NULL;
		_miNpc = _mNpc.erase(_miNpc);
	}
	_mNpc.clear();
}

void npcManager::add(string npcName, npcBase * npc)
{
	_miNpc = find_if(_mNpc.begin(), _mNpc.end(), [npcName](pair<string, npcBase*> M)->bool {
		if (npcName.compare( M.first.c_str()))return true;
		else return false;
	});

	if (_miNpc == _mNpc.end()) _mNpc.insert(make_pair(npcName, npc));
	
}

void npcManager::Del(string npcName)
{
	_miNpc = find_if(_mNpc.begin(), _mNpc.end(), [npcName](pair<string,npcBase*> M)->bool {
		if (npcName.compare(M.first.c_str()))return true;
		else return false;
	});
	if (_miNpc != _mNpc.end())_mNpc.erase(_miNpc);
}

npcBase * npcManager::getNPC(string npcName)
{
	_miNpc = find_if(_mNpc.begin(), _mNpc.end(), [npcName](pair<string, npcBase*> M)->bool {
		if (npcName.compare(M.first.c_str()))return true;
		else return false;
	});

	if (_miNpc != _mNpc.end())	return _miNpc->second;
	else return NULL;
}
