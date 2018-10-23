#include "stdafx.h"
#include "sceneTest.h"

HRESULT sceneTest::init(void)
{
	_renderTarget->CreateSolidColorBrush(C_COLOR_GREEN, &_brush);

	return S_OK;
}

void sceneTest::release(void)
{
}

void sceneTest::update(void)
{
}

void sceneTest::render(void)
{
	D2D1_ELLIPSE region;

	region.point.x = 100.0f;
	region.point.y = 100.0f;
	region.radiusX = 70.0f;
	region.radiusY = 80.0f;

	_renderTarget->FillEllipse(region, _brush);
}
