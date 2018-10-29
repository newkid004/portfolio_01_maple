#include "stdafx.h"
#include "gameNode.h"

//================
// # init # 초기화
//================
HRESULT gameNode::init(void)
{
	this->init(true);

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
#ifdef PROCESS_D3D
	// 렌더 비율 초기화
	// RECT r;
	// GetClientRect(_hWnd, &r);
	// 
	// D2D1_SIZE_F real_size = _renderTarget->GetSize();
	// _renderRate = { real_size.width / RectWidth(r), real_size.height / RectHeight(r) };

	// COM 라이브러리 초기화
	CoInitialize(NULL);
#else
	_hdc = GetDC(_hWnd);
#endif

	_managerInit = managerInit;

	if (managerInit)
	{
		//타이머 초기화
		// SetTimer(_hWnd, 1, 10, NULL);

		//키매니져 초기화
		KEYMANAGER->init();

		//랜덤펑션 초기화
		RND->init();

		// 이미지매니저 초기화
		IMAGEMANAGER->init();

		// 타임매니저 초기화
		TIMEMANAGER->init();

		// 카메라매니저 초기화
		CAMERAMANAGER->init();

		// TXT매니저 초기화
		TXTMANAGER->init();

		// ini매니저 초기화
		INIDATA->init();

		// 씬 매니저 초기화
		SCENEMANAGER->init();

		// 사운드매니저 초기화
		SOUNDMANAGER->init();

		// 렌더 매니저 초기화
		RENDERMANAGER->init();

		// 윈도우 매니저 초기화
		WINMANAGER->init();

		// 필드 매니저 초기화
		FIELDMANAGER->init();

		PATTERNMANAGER->init();
		SKILLMANAGER->init();
		ANIGROUPMANAGER->init();
		BUFFMANAGER->init();
		NPCMANAGER->init();
		QUESTMANAGER->init();

		// 상점 매니저 초기화
		SHOPMANAGER->init();

		// 게임 시스템 싱글톤 초기화
		GAMESYSTEM->init();

		return S_OK;
	}
	return S_OK;
}

//=================
// # release # 해제
//=================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//타이머 해제
		// KillTimer(_hWnd, 1);

		//키 매니저 해제
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		//랜덤 싱글톤 해제
		RND->releaseSingleton();

		// 이미지매니저 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//타임매니져 해제, 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		// 카메라매니저 해제
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		// TXT매니저 해제
		TXTMANAGER->release();
		TXTMANAGER->releaseSingleton();

		// INI매니저 해제
		INIDATA->release();
		INIDATA->releaseSingleton();

		// 씬 매니저 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		// 사운드 매니저 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		// 렌더 매니저 해제
		RENDERMANAGER->release();
		RENDERMANAGER->releaseSingleton();

		// 윈도우 매니저 해제
		WINMANAGER->release();
		WINMANAGER->releaseSingleton();

		// 필드 매니저 해제
		FIELDMANAGER->release();
		FIELDMANAGER->releaseSingleton();

		// 상점 매니저 해제
		SHOPMANAGER->release();
		SHOPMANAGER->releaseSingleton();

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

		// 게임 시스템 해제
		GAMESYSTEM->release();
		GAMESYSTEM->releaseSingleton();
	}

#ifdef PROCESS_D3D

#else
	ReleaseDC(_hWnd, _hdc);
#endif
}

//====================
// # update # 업데이트
//====================
void gameNode::update(void)
{
	//새로고침
	//더블 버퍼링 이후 사용하지 않는다
	// InvalidateRect(_hWnd, NULL, FALSE);
}

//================
// # render # 렌더
//================
void gameNode::render(void)
{
}

//=========================
// # MainProc # 메인프로시져
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
			// PostMessage(hWnd, WM_DESTROY, 0, 0); // 강제종료
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