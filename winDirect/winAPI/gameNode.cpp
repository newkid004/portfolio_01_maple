#include "stdafx.h"
#include "gameNode.h"

//================
// # init # �ʱ�ȭ
//================
HRESULT gameNode::init(void)
{
	this->init(true);

	// ���� ���� �ʱ�ȭ
	RECT r;
	GetClientRect(_hWnd, &r);

	D2D1_SIZE_F real_size = _renderTarget->GetSize();
	_renderRate = { real_size.width / RectWidth(r), real_size.height / RectHeight(r) };

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
#ifdef PROCESS_D3D

#else
	_hdc = GetDC(_hWnd);
#endif

	_managerInit = managerInit;

	if (managerInit)
	{
		//Ÿ�̸� �ʱ�ȭ
		// SetTimer(_hWnd, 1, 10, NULL);

		//Ű�Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();

		//������� �ʱ�ȭ
		RND->init();

		// �̹����Ŵ��� �ʱ�ȭ
		IMAGEMANAGER->init();

		// Ÿ�ӸŴ��� �ʱ�ȭ
		TIMEMANAGER->init();

		// ī�޶�Ŵ��� �ʱ�ȭ
		CAMERAMANAGER->init();

		// TXT�Ŵ��� �ʱ�ȭ
		TXTMANAGER->init();

		// ini�Ŵ��� �ʱ�ȭ
		INIDATA->init();

		// �� �Ŵ��� �ʱ�ȭ
		SCENEMANAGER->init();

		// ����Ŵ��� �ʱ�ȭ
		// SOUNDMANAGER->init();

		return S_OK;
	}
	return S_OK;
}

//=================
// # release # ����
//=================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		// KillTimer(_hWnd, 1);

		//Ű �Ŵ��� ����
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		//���� �̱��� ����
		RND->releaseSingleton();

		// �̹����Ŵ��� �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//Ÿ�ӸŴ��� ����, �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		// ī�޶�Ŵ��� ����
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		// TXT�Ŵ��� ����
		TXTMANAGER->release();
		TXTMANAGER->releaseSingleton();

		// INI�Ŵ��� ����
		INIDATA->release();
		INIDATA->releaseSingleton();

		// �� �Ŵ��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		// ���� �Ŵ��� ����
		// SOUNDMANAGER->release();
		// SOUNDMANAGER->releaseSingleton();
	}

#ifdef PROCESS_D3D

#else
	ReleaseDC(_hWnd, _hdc);
#endif
}

//====================
// # update # ������Ʈ
//====================
void gameNode::update(void)
{
	//���ΰ�ħ
	//���� ���۸� ���� ������� �ʴ´�
	// InvalidateRect(_hWnd, NULL, FALSE);
}

//================
// # render # ����
//================
void gameNode::render(void)
{
}

//=========================
// # MainProc # �������ν���
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
			// PostMessage(hWnd, WM_DESTROY, 0, 0); // ��������
			break;
		}
		break;

	case WM_KEYUP:
		KEYMANAGER->setInputKey(NULL);
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