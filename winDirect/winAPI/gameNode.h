#pragma once

#ifdef PROCESS_D3D

static ColorF		_backColor = C_COLOR_MAGENTA;
static D2D1_SIZE_F	_renderRate;
class gameNode
{
private:
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);

	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	static ColorF & getBackColor(void) { return _backColor; };
	static D2D1_SIZE_F & getRate(void) { return _renderRate; };

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};

#else

#include "image.h"
// 백버퍼 이미지를 정적변수로
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _strcBuffer = IMAGEMANAGER->addImage("strcBuffer", (int)WINSIZEX_R, (int)WINSIZEY_R);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);

	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	//백버퍼 이미지 얻기
	image* getBackBuffer(void) { return _backBuffer; }
	image* getStrcBuffer(void) { return _strcBuffer; }

	// 메모리DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getStrcDC() { return _strcBuffer->getMemDC(); }

	// HDC 얻기
	HDC getHDC() { return _hdc; }

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};
#endif