#include "stdafx.h"
#include "timeManager.h"

HRESULT timeManager::init(void)
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

//프레임 적용
void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

//해당 HDC에 정보 찍는다
void timeManager::render(HDC hdc)
{
	char str[256];
	std::string strFrame;

	SetBkMode(hdc, TRANSPARENT);

	COLORREF oColor = GetTextColor(hdc);
	int oAlign = GetTextAlign(hdc);

	SetTextColor(hdc, RGB(255, 255, 255));
	SetTextAlign(hdc, TA_LEFT);

#ifdef _DEBUG
	if (_timer != NULL)
	{
		//프레임 찍는다
		sprintf_s(str, "FramePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		// //월드 타임 찍는다
		// sprintf_s(str, "WorldTime : %f", _timer->getWorldTime());
		// TextOut(hdc, 0, 20, str, strlen(str));
		// 
		// //갱신 시간 찍는다
		// sprintf_s(str, "ElapsedTime : %f", _timer->getElapsedTime());
		// TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	if (_timer != NULL)
	{
		//프레임 찍는다
		sprintf_s(str, "FramePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif

	SetTextColor(hdc, oColor);
	SetTextAlign(hdc, oAlign);
}