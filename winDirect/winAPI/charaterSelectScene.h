#pragma once
#include "gameNode.h"

class playableBase;

struct selectionSlot
{
	playableBase* pB;
	fPOINT pos;
	int currentFrameY;
	float elapsedTime;
	float updateTime;
};

class charaterSelectScene:public gameNode
{
private:
	selectionSlot _charater[8];

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	charaterSelectScene(){}
	~charaterSelectScene(){}
};

