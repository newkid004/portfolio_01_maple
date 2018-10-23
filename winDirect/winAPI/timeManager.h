#pragma once
#include "singletonbase.h"
#include "timer.h"

class timeManager : public singletonBase <timeManager>
{
private:
	timer * _timer;

public:
	HRESULT init(void);
	void release(void);
	//프레임 적용
	void update(float lock = 0.0f);
	//해당 HDC에 정보 찍는다
	void render(HDC hdc);
	//전체 시간 가져온다
	inline float getWorldTime(void) const { return _timer->getWorldTime(); }
	//프레임 경과 시간
	inline float getElapsedTime(void) const { return _timer->getElapsedTime(); }
	// FPS
	inline unsigned long getFPS(void) const { return _timer->getFrameRate(); }

	timeManager() {}
	~timeManager() {}
};