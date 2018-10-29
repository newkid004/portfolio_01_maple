#pragma once
#include "gameNode.h"

class loadingScene:public gameNode
{
private:
	int currentFrameY;

	float updateTime;
	float elapsedTime;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	loadingScene(){}
	~loadingScene(){}
};

