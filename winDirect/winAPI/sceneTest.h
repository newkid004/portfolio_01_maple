#pragma once
#include "gameNode.h"

#include "animation.h"

class sceneTest : public gameNode
{
private :
	animation* _ani;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void updateControl(void);

public:
	sceneTest() {};
	~sceneTest() {};
};

