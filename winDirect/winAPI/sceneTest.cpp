#include "stdafx.h"
#include "sceneTest.h"

HRESULT sceneTest::init(void)
{
	// _renderTarget->CreateSolidColorBrush(C_COLOR_GREEN, &_brush);

	getBackColor() = C_COLOR_GRAY;

	IMAGEMANAGER->add("test", L"image/testImg.png");
	IMAGEMANAGER->add("frame", L"image/frame.png", 12, 1);
	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	return S_OK;
}

void sceneTest::release(void)
{
}

void sceneTest::update(void)
{
	updateControl();
	static int i = 1;
	auto color = IMAGEMANAGER->find("test")->getBitmapPixel(POINT{i,i});
	cout << (int)color.a<<"  " <<(int)color.r <<"  " <<(int)color.g << "  " <<(int)color.b << "  "<< endl;
	i++;
	if (i > 99)i = 0;
}

void sceneTest::render(void)
{
	static POINT frame = { 0 ,0 };
	static float interval = 0.1f;
	static float curFrame = 0.0f;

	curFrame += TIMEMANAGER->getElapsedTime();
	if (interval < curFrame)
	{
		frame.x = IMAGEMANAGER->find("frame")->getMaxFrame().x < ++frame.x ? 0 : frame.x;
		curFrame -= interval;
	}

	IMAGEMANAGER->find("frame")->frameRender(frame.x, 0);
}

void sceneTest::updateControl(void)
{
	static fPOINT pos;
	static float rot;
	static int flip;

	static fPOINT clipPos = fPOINT(100.0f, 20.0f);
	static fPOINT clipSize = fPOINT(100.0f, 100.0f);

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
