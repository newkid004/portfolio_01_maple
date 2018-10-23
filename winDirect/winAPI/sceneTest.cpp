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
	RECT r;
	GetClientRect(_hWnd, &r);
	
	D2D1_SIZE_F real_size = _renderTarget->GetSize();
	D2D1_SIZE_F rate = { real_size.width / RectWidth(r), real_size.height / RectHeight(r) };
	
	D2D1_ELLIPSE region;

	region.point.x = 100.0f * rate.width;
	region.point.y = 100.0f * rate.height;
	region.radiusX = 70.0f * rate.width;
	region.radiusY = 80.0f * rate.height;

	_renderTarget->FillEllipse(region, _brush);
}
