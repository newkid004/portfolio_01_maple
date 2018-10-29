#include "stdafx.h"
#include "gameNode.h"

//================
// # init # ÃÊ±âÈ­
//================
HRESULT gameNode::init(void)
{
	this->init(true);

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
#ifdef PROCESS_D3D
	// ·»´õ ºñÀ² ÃÊ±âÈ­
	// RECT r;
	// GetClientRect(_hWnd, &r);
	// 
	// D2D1_SIZE_F real_size = _renderTarget->GetSize();
	// _renderRate = { real_size.width / RectWidth(r), real_size.height / RectHeight(r) };

	// COM ¶óÀÌºê·¯¸® ÃÊ±âÈ­
	CoInitialize(NULL);
#else
	_hdc = GetDC(_hWnd);
#endif

	_managerInit = managerInit;

	if (managerInit)
	{
		//Å¸ÀÌ¸Ó ÃÊ±âÈ­
		// SetTimer(_hWnd, 1, 10, NULL);

		//Å°¸Å´ÏÁ® ÃÊ±âÈ­
		KEYMANAGER->init();

		//·£´ıÆã¼Ç ÃÊ±âÈ­
		RND->init();

		// ÀÌ¹ÌÁö¸Å´ÏÀú ÃÊ±âÈ­
		IMAGEMANAGER->init();

		// Å¸ÀÓ¸Å´ÏÀú ÃÊ±âÈ­
		TIMEMANAGER->init();

		// Ä«¸Ş¶ó¸Å´ÏÀú ÃÊ±âÈ­
		CAMERAMANAGER->init();

		// TXT¸Å´ÏÀú ÃÊ±âÈ­
		TXTMANAGER->init();

		// ini¸Å´ÏÀú ÃÊ±âÈ­
		INIDATA->init();

		// ¾À ¸Å´ÏÀú ÃÊ±âÈ­
		SCENEMANAGER->init();

		// »ç¿îµå¸Å´ÏÀú ÃÊ±âÈ­
<<<<<<< HEAD
		SOUNDMANAGER->init();

		// ·»´õ ¸Å´ÏÀú ÃÊ±âÈ­
		RENDERMANAGER->init();

		// À©µµ¿ì ¸Å´ÏÀú ÃÊ±âÈ­
		WINMANAGER->init();

		// ÇÊµå ¸Å´ÏÀú ÃÊ±âÈ­
		FIELDMANAGER->init();

		PATTERNMANAGER->init();
		SKILLMANAGER->init();
		ANIGROUPMANAGER->init();
		BUFFMANAGER->init();
		NPCMANAGER->init();
		QUESTMANAGER->init();

		// »óÁ¡ ¸Å´ÏÀú ÃÊ±âÈ­
		SHOPMANAGER->init();

		// ÀÌÆåÆ® ¸Å´ÏÀú ÃÊ±âÈ­
		EFFECTMANAGER->init();

		// °ÔÀÓ ½Ã½ºÅÛ ½Ì±ÛÅæ ÃÊ±âÈ­
		GAMESYSTEM->init();
=======
		// SOUNDMANAGER->init();
>>>>>>> parent of bf82ed1... ì˜¤ë¥˜ì»¤ë°‹

		return S_OK;
	}
	return S_OK;
}

//=================
// # release # ÇØÁ¦
//=================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Å¸ÀÌ¸Ó ÇØÁ¦
		// KillTimer(_hWnd, 1);

		//Å° ¸Å´ÏÀú ÇØÁ¦
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		//·£´ı ½Ì±ÛÅæ ÇØÁ¦
		RND->releaseSingleton();

		// ÀÌ¹ÌÁö¸Å´ÏÀú ½Ì±ÛÅæ ÇØÁ¦
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//Å¸ÀÓ¸Å´ÏÁ® ÇØÁ¦, ½Ì±ÛÅæ ÇØÁ¦
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		// Ä«¸Ş¶ó¸Å´ÏÀú ÇØÁ¦
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		// TXT¸Å´ÏÀú ÇØÁ¦
		TXTMANAGER->release();
		TXTMANAGER->releaseSingleton();

		// INI¸Å´ÏÀú ÇØÁ¦
		INIDATA->release();
		INIDATA->releaseSingleton();

		// ¾À ¸Å´ÏÀú ÇØÁ¦
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		// »ç¿îµå ¸Å´ÏÀú ÇØÁ¦
<<<<<<< HEAD
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		// ·»´õ ¸Å´ÏÀú ÇØÁ¦
		RENDERMANAGER->release();
		RENDERMANAGER->releaseSingleton();

		// À©µµ¿ì ¸Å´ÏÀú ÇØÁ¦
		WINMANAGER->release();
		WINMANAGER->releaseSingleton();

		// ÇÊµå ¸Å´ÏÀú ÇØÁ¦
		FIELDMANAGER->release();
		FIELDMANAGER->releaseSingleton();

		// »óÁ¡ ¸Å´ÏÀú ÇØÁ¦
		SHOPMANAGER->release();
		SHOPMANAGER->releaseSingleton();

		// ÀÌÆåÆ® ¸Å´ÏÀú ÇØÁ¦
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		PATTERNMANAGER->release();
		PATTERNMANAGER->releaseSingleton();
		SKILLMANAGER->release();
		SKILLMANAGER->releaseSingleton();
		ANIGROUPMANAGER->release();
		ANIGROUPMANAGER->releaseSingleton();
		BUFFMANAGER->release();
		BUFFMANAGER->releaseSingleton();
		NPCMANAGER->release();
		NPCMANAGER->releaseSingleton();
		QUESTMANAGER->release();
		QUESTMANAGER->releaseSingleton();

		// °ÔÀÓ ½Ã½ºÅÛ ÇØÁ¦
		GAMESYSTEM->release();
		GAMESYSTEM->releaseSingleton();
=======
		// SOUNDMANAGER->release();
		// SOUNDMANAGER->releaseSingleton();
>>>>>>> parent of bf82ed1... ì˜¤ë¥˜ì»¤ë°‹
	}

#ifdef PROCESS_D3D

#else
	ReleaseDC(_hWnd, _hdc);
#endif
}

//====================
// # update # ¾÷µ¥ÀÌÆ®
//====================
void gameNode::update(void)
{
	//»õ·Î°íÄ§
	//´õºí ¹öÆÛ¸µ ÀÌÈÄ »ç¿ëÇÏÁö ¾Ê´Â´Ù
	// InvalidateRect(_hWnd, NULL, FALSE);
}

//================
// # render # ·»´õ
//================
void gameNode::render(void)
{
}

//=========================
// # MainProc # ¸ŞÀÎÇÁ·Î½ÃÁ®
//=========================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_TIMER: {
		// this->update();

	} break;

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
			
	} break;

	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		KEYMANAGER->setInputKey(wParam);

		switch (wParam)
		{
		case VK_ESCAPE:
			// PostMessage(hWnd, WM_DESTROY, 0, 0); // °­Á¦Á¾·á
			break;
		}
		break;

	case WM_KEYUP:
		KEYMANAGER->setInputKey(NULL);
		break;
	case WM_LBUTTONDBLCLK:
		KEYMANAGER->dbClick();
		break;
	case WM_MOUSEWHEEL: {

		if ((short)HIWORD(wParam) < 0)
			KEYMANAGER->wheelDown();
		else
			KEYMANAGER->wheelUp();
	} break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}