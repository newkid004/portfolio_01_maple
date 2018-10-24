#include "stdafx.h"
#include "mainGame.h"

//=============
// # 전역변수 #
//=============
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

ID2D1Factory * _factory = NULL;
ID2D1HwndRenderTarget*	_renderTarget = NULL;

mainGame* _mg;

//==================
// # 함수 전방선언 #
//==================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//==================
// # Direct #
//==================
// IDirect3D9*			_d3d9;
// int					_dHVP;
// IDirect3DDevice9*	_dDevice = 0;

//===================
// # 윈도우 메인함수 #
//===================
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	_mg = new mainGame();

	//인스턴스를 전역변수에 담는다
	_hInstance = hInstance;

	//WNDCLASS: 윈도우 창의 정보를 저장하기 위한 구조체
	//윈도우창 구조체 선언 및 초기화
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;									   //클래스 여분 메모리
	wndClass.cbWndExtra = 0;									   //윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				   //마우스 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			   //아이콘
	wndClass.hInstance = hInstance;								   //인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;					   //윈도우 프로시져
	wndClass.lpszClassName = WINNAME;							   //클래스 이름
	wndClass.lpszMenuName = NULL;								   //메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;		   //윈도우 스타일

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	//디바이스 모드 구조체 (화면 디스플레이관련 구조체)
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));
	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;			//32비트 트루컬러
	dm.dmPelsWidth = 1980;			//가로 해상도
	dm.dmPelsHeight = 1020;			//세로 해상도
	dm.dmDisplayFrequency = 60;		//재생빈도 60Hz
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//화면이 종료되면 자동으로 원래 화면의 해상도로 복구
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//화면에 보여줄 윈도우 창을 생성
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스의 이름
		WINNAME,				//윈도우 타이틀바 이름
		WINSTYLE,				//윈도우 스타일
		WINSTARTX,				//윈도우 화면 X좌표
		WINSTARTY,				//윈도우 화면 Y좌표
		WINSIZEX,				//윈도우 화면 가로크기
		WINSIZEY,				//윈도우 화면 세로크기
		NULL,					//부모 윈도우
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 지정
		NULL					//윈도우의 자식 윈도우를 생성하면 지정하고 그렇지 않으면 NULL
								//필요에 의해서 사용하지만 지금은 NULL
		);

	//클라이언트 영역의 사이즈를 정확히 잡아준다
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
#else
	//화면에 보여줄 윈도우 창을 생성
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스의 이름
		WINNAME,				//윈도우 타이틀바 이름
		WINSTYLE,				//윈도우 스타일
		WINSTARTX,				//윈도우 화면 X좌표
		WINSTARTY,				//윈도우 화면 Y좌표
		WINSIZEX,				//윈도우 화면 가로크기
		WINSIZEY,				//윈도우 화면 세로크기
		NULL,					//부모 윈도우
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 지정
		NULL					//윈도우의 자식 윈도우를 생성하면 지정하고 그렇지 않으면 NULL
								//필요에 의해서 사용하지만 지금은 NULL
		);

	//클라이언트 영역의 사이즈를 정확히 잡아준다
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#endif		// #ifdef FULLSCREEN

	// // ===== Direct ===== //
	// ----- 팩토리 개체 생성 : 싱글 스레드
	if (S_OK != D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory))
		return 0;

	RECT r;
	GetClientRect(_hWnd, &r);	// 현재 윈도우를 출력 대상 윈도우로
	if (S_OK != _factory->CreateHwndRenderTarget(								// 렌더 타겟 생성
		RenderTargetProperties(),												// 렌더 타겟 세부 설정 : default
		HwndRenderTargetProperties(_hWnd, SizeU(RectWidth(r), RectHeight(r))),	// 출력 대상 윈도우 핸들
		&_renderTarget))														// 렌더 타겟 설정
		return 0;
	
	// antialias 설정
	_renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);	// 사용

	//화면에 윈도우창 보여주기
	ShowWindow(_hWnd, nCmdShow);

	//MSG: 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	MSG message;

	// 초기화 : 실패 시, 종료
	if (FAILED(_mg->init()))		// 메인게임 클래스의 초기화
	{
		return 0;
	}

	//게임용
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}

	//일반 프로그래밍용
	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	_mg->release();

	// D2D 해제
	_factory->Release();
	_renderTarget->Release();

	//윈도우 클래스 등록 해제
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

//===================
// # 윈도우 프로시져 # 
//===================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

//=============================================================
// # 윈도우 크기 조정 # (클라이언트 영역의 사이즈를 정확히 잡아준다)
//=============================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);

	//위 렉트 정보로 윈도우 클라이언트 사이즈 셋팅
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}