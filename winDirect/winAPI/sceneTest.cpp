#include "stdafx.h"
#include "sceneTest.h"

HRESULT sceneTest::init(void)
{
	_renderTarget->CreateSolidColorBrush(C_COLOR_GREEN, &_brush);

	IMAGEMANAGER->addImage("test", L"image/texture.png");

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
	IMAGEMANAGER->find("test")->render();
}

void sceneTest::renderEllipse(void)
{
	D2D1_ELLIPSE region;

	region.point.x = 500.0f;
	region.point.y = 500.0f;
	region.radiusX = 70.0f;
	region.radiusY = 80.0f;

	_renderTarget->SetTransform(Matrix3x2F::Rotation(50.0f, Point2F(500.0f, 500.0f)));

	_renderTarget->FillEllipse(region, _brush);
}
