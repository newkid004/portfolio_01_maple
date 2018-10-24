#include "stdafx.h"
#include "sceneTest.h"

HRESULT sceneTest::init(void)
{
	// _renderTarget->CreateSolidColorBrush(C_COLOR_GREEN, &_brush);

	getBackColor() = C_COLOR_GRAY;

	IMAGEMANAGER->add("test", L"image/12.png");
	IMAGEMANAGER->add("frame", L"image/frame.png", 12, 1);

	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	_ani = new animation;
	_ani->init(IMAGEMANAGER->find("frame"));
	_ani->setFPS(15);
	_ani->setDefPlayFrame(false, true);
	_ani->isPlay() = true;

	return S_OK;
}

void sceneTest::release(void)
{
}

void sceneTest::update(void)
{
	updateControl();
}

void sceneTest::render(void)
{
	IMAGEMANAGER->find("frame")->aniRender(_ani->update());
}

void sceneTest::updateControl(void)
{
	static fPOINT pos;
	static float rot;
	static int flip;

	if (KEYMANAGER->down('W'))	rot -= TIMEMANAGER->getElapsedTime() * 180;
	if (KEYMANAGER->down('S'))	rot += TIMEMANAGER->getElapsedTime() * 180;

	if (KEYMANAGER->down(VK_LEFT))	pos.x -= TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_RIGHT))	pos.x += TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_UP))	pos.y -= TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_DOWN))	pos.y += TIMEMANAGER->getElapsedTime() * 1000;

	if (KEYMANAGER->press('A')) flip ^= IMAGE_FLIP_HORIZON;
	if (KEYMANAGER->press('D')) flip ^= IMAGE_FLIP_VERTICAL;

	IMAGEMANAGER->statePos(pos);
	IMAGEMANAGER->stateRotate(rot);
	IMAGEMANAGER->stateFlip(flip);
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
