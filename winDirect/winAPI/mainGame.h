#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private :
	image* _backImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	mainGame() {}
	~mainGame() {}
};