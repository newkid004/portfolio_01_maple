#pragma once
#include "gameNode.h"

#include "animation.h"

class sceneTest : public gameNode
{
private :
	ID2D1SolidColorBrush * _brush;
	animation* _ani;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void updateControl(void);

	void renderEllipse(void);
public:
	sceneTest() {};
	~sceneTest() {};
};

