#pragma once
#include "singletonBase.h"

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	int _inputKey;
	BOOL _keyUp[KEYMAX];
	BOOL _keyDown[KEYMAX];

	function<void(void)> * _callWheelUp;
	function<void(void)> * _callWheelDown;
	function<void(void)> * _callDBClick;
public:
	//키매니져 초기화
	HRESULT init(void);
	void release(void);

	//키가 한번만 눌렸는지
	bool press(int key);
	//한번 누르고 띄었는지
	bool up(int key);
	//키가 계속 눌려 있는지
	bool down(int key);
	//토글키
	bool toggle(int key);

	// 마우스 휠
	void setWheelUp(function<void(void)> * upFunction);
	void setWheelDown(function<void(void)> * downFunction);
	void wheelUp(void) { if (_callWheelUp) (*_callWheelUp)(); };
	void wheelDown(void) { if (_callWheelDown) (*_callWheelDown)(); };

	// 누른 키
	void setInputKey(int key) { _inputKey = key; };
	int getInputKey(void) { return _inputKey; };

	// 마우스 더블클릭
	void setDBClick(function<void(void)>* dbClickFunction);
	void dbClick(void) {if (_callDBClick)(*_callDBClick)();}
	keyManager() {}
	~keyManager() {}
};