#include "stdafx.h"
#include "timer.h"
#include <MMSystem.h>

//TimeGetTime 함수를 사용하기 위한 라이브러리
#pragma comment (lib, "winmm.lib")

HRESULT timer::init(void)
{
	//_periodFrequency 값에 초당 파악 할 수 있는 시간이 들어간다
	//밀리쎄컨까지 계산 가능하다면 1000의 값이 들어감
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		//초당 시간을 계산 할 수 있는 시간주기
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;
		//timeGetTime은 밀리쎄컨 단위 시간으로 초당 1000
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;
	_timeElapsed = 0;

	return S_OK;
}

//현재 시간을 계산한다
void timer::tick(float lockFPS)
{
	//지원되냐?
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//지원하지 않으면 Time함수를 사용
		_curTime = timeGetTime();
	}

	//마지막 시간과 현재시간의 경과량 측정한다
	_timeElapsed = (_curTime - _lastTime) * _timeScale;


	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			//마지막 시간과 현재시간의 경과량를 측정한다
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//마지막 시간을 기록한다
	_lastTime = _curTime;

	//초당 프레임 카운트 증가시킨다
	_FPSFrameCount++;

	//초당 프레임 시간 경과량 측정한다
	_FPSTimeElapsed += _timeElapsed;

	//전체 시간 경과량 측정한다
	_worldTime += _timeElapsed;

	//프레임 1초마다 초기화 한다
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

//현재 FPS
unsigned long timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		wsprintf(str, "fps : %d", _frameRate);
	}
	return _frameRate;
}