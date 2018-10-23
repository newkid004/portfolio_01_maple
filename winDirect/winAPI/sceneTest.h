#pragma once
#include "gameNode.h"


class sceneTest : public gameNode
{
private :
	ID2D1SolidColorBrush * _brush;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renderEllipse(void);
public:
	sceneTest() {};
	~sceneTest() {};
};

