#pragma once
#include "npcBase.h"
#include "singletonBase.h"

class npcManager:public singletonBase<npcManager>
{
private:
	typedef map<string, npcBase*> mNpc;
	typedef map<string, npcBase*>::iterator miNpc;
private:

	mNpc	_mNpc;
	miNpc	_miNpc;

public:
	HRESULT init();
	void release();
	void add(string npcName, npcBase* npc);
	void Del(string npcName);
	
	npcBase* getNPC(string npcName);

	npcManager() {};
	~npcManager() {};
};
