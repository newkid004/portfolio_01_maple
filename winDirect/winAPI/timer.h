#pragma once

class timer
{
private:
	bool			_isHardware;		//고성능 타이머 지원 되냐?
	float			_timeScale;			//경과시간을 조절한다
	float			_timeElapsed;		//마지막 시간과 현재시간의 경과값
	__int64			_curTime;			//현재시간
	__int64			_lastTime;			//이전시간
	__int64			_periodFrequency;	//시간주기

	unsigned long 	_frameRate;			//FPS (초당 프레임 수)
	unsigned long 	_FPSFrameCount;		//FPS 카운트
	float			_FPSTimeElapsed;
	float			_worldTime;			//게임이 시작된 후 경과된 전체 시간

public:
	HRESULT init(void);
	//현재 시간을 계산
	void tick(float lockFPS = 0.0f);
	//현재 FPS
	unsigned long getFrameRate(char* str = NULL) const;
	//마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }
	//전체 경과 시간
	inline float getWorldTime(void) const { return _worldTime; }

	timer() {}
	~timer() {}
};