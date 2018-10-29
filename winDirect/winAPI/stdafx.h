
//stdafx.h: ÀÚÁÖ »ç¿ëÇÏÁö¸¸ ÀÚÁÖ º¯°æµÇÁö´Â ¾Ê´Â
//Ç¥ÁØ ½Ã½ºÅÛ Æ÷ÇÔ ÆÄÀÏ ¶Ç´Â ÇÁ·ÎÁ§Æ® °ü·Ã Æ÷ÇÔ ÆÄÀÏÀÌ
//µé¾î ÀÖ´Â Æ÷ÇÔ ÆÄÀÏ
#pragma once
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "windowscodecs.lib")

#include <SDKDDKver.h>

//°ÅÀÇ »ç¿ëµÇÁö ¾Ê´Â ³»¿ëÀº Windows Çì´õ¿¡¼­ Á¦¿Ü
#define WIN32_LEAN_AND_MEAN

// #pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//Windows Çì´õ ÆÄÀÏ
#include <Windows.h>
#include <wincodec.h>

//C ·±Å¸ÀÓ Çì´õ ÆÄÀÏ
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h>
#include <ole2.h>
#include <assert.h>

//C++ ·±Å¸ÀÓ Çì´õ ÆÄÀÏ
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

// Direct Çì´õ ÆÄÀÏ
#include <d2d1.h>

using namespace std;
using namespace D2D1;

//===================================
// # ³»°¡ ¸¸µç Çì´õÆÄÀÏÀ» ÀÌ°÷¿¡ Ãß°¡ #
//===================================
// #include "triFunction.h"
#include "utils.h"




using namespace MY_UTIL;

// ¸Å´ÏÀú
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtDataManager.h"
#include "iniData.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "cameraManager.h"

#include "jsoncpp\include\json\json.h"
#include "JsonSaveLoader.h"

// ¸Å´ÏÀú : ÀÓÀÇ Ãß°¡
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> parent of 8f5701d... ì˜¤ë¥˜ì»¤ë°‹
=======
>>>>>>> parent of d0a58f6... ì˜¤ë¥˜ ì»¤ë°‹
#include "renderManager.h"
#include "winManager.h"
#include "fieldManager.h"
#include "patternManager.h"
#include "skillManager.h"
#include "animationGroupManager.h"
#include "buffManager.h"
#include "npcManager.h"
#include "questManager.h"
#include "shopManager.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "effectManager.h"

#include "gameSystem.h"
=======
>>>>>>> parent of bf82ed1... ì˜¤ë¥˜ì»¤ë°‹
=======

#include "gameSystem.h"
>>>>>>> parent of 8f5701d... ì˜¤ë¥˜ì»¤ë°‹
=======
#include "effectManager.h"

#include "gameSystem.h"
>>>>>>> parent of d0a58f6... ì˜¤ë¥˜ ì»¤ë°‹

//========================
// # ½Ì±ÛÅæÀ» ÀÌ°÷¿¡ Ãß°¡ #
//========================
#define RND				randomFunction::getSingleton()
#define KEYMANAGER		keyManager::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define TXTMANAGER		txtDataManager::getSingleton()
#define INIDATA			iniData::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define CAMERAMANAGER	cameraManager::getSingleton()
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> parent of 8f5701d... ì˜¤ë¥˜ì»¤ë°‹
=======
>>>>>>> parent of d0a58f6... ì˜¤ë¥˜ ì»¤ë°‹
#define JSONDATAMANAGER	JsonSaveLoader::getSingleton()
#define RENDERMANAGER	renderManager::getSingleton()
#define WINMANAGER		winManager::getSingleton()
#define FIELDMANAGER	fieldManager::getSingleton()
#define PATTERNMANAGER	patternManager::getSingleton()
#define SKILLMANAGER	skillManager::getSingleton()
#define ANIGROUPMANAGER animationGroupManager::getSingleton()
#define BUFFMANAGER		buffManager::getSingleton()
#define NPCMANAGER		npcManager::getSingleton()
#define QUESTMANAGER	questManager::getSingleton()
#define SHOPMANAGER		shopManager::getSingleton()
<<<<<<< HEAD
<<<<<<< HEAD
#define EFFECTMANAGER	effectManager::getSingleton()

#define GAMESYSTEM		gameSystem::getSingleton()
=======
>>>>>>> parent of bf82ed1... ì˜¤ë¥˜ì»¤ë°‹
=======

#define GAMESYSTEM		gameSystem::getSingleton()
>>>>>>> parent of 8f5701d... ì˜¤ë¥˜ì»¤ë°‹
=======
#define EFFECTMANAGER	effectManager::getSingleton()

#define GAMESYSTEM		gameSystem::getSingleton()
>>>>>>> parent of d0a58f6... ì˜¤ë¥˜ ì»¤ë°‹


//============================
// # ¸ÅÅ©·Î # (À©µµ¿ìÃ¢ ÃÊ±âÈ­)
//============================
#define WINNAME		(LPTSTR)(TEXT("MapleStory"))

//#define FULLSCREEN
#define PROCESS_D3D

#ifdef FULLSCREEN
#define WINSTARTX	0
#define WINSTARTY	0
#define WINSIZEX	GetSystemMetrics(SM_CXSCREEN)
#define WINSIZEY	GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE
#else
#define WINSTARTX	10
#define WINSTARTY	10
#define WINSIZEX	1280
#define WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU
#endif

#define WINRATIO	1.0f
#define WINSIZEX_R	(WINSIZEX * WINRATIO)
#define WINSIZEY_R	(WINSIZEY * WINRATIO)
#define CENTERX		(WINSIZEX / 2)
#define CENTERY		(WINSIZEY / 2)

//===============================================
// # ¸ÅÅ©·Î ÇÔ¼ö # (Å¬·¡½º¿¡¼­ µ¿ÀûÇÒ´çµÈ ºÎºÐ ÇØÁ¦)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = NULL;}}
#define D3D_RELEASE(p)			{if(p) {(p)->Release(); (p) = NULL;}}

//===============================================
// # ¸ÅÅ©·Î »ö»ó #
//===============================================
#ifdef PROCESS_D3D
	#define C_COLOR_RED			D2D1::ColorF(1.0f, 0.0f, 0.0f)
	#define C_COLOR_GREEN		D2D1::ColorF(0.0f, 1.0f, 0.0f)
	#define C_COLOR_BLUE		D2D1::ColorF(0.0f, 0.0f, 1.0f)
	#define C_COLOR_MAGENTA		D2D1::ColorF(1.0f, 0.0f, 1.0f)
	#define C_COLOR_YELLOW		D2D1::ColorF(1.0f, 1.0f, 0.0f)
	#define C_COLOR_CYAN		D2D1::ColorF(0.0f, 1.0f, 1.0f)
	#define C_COLOR_WHITE		D2D1::ColorF(1.0f, 1.0f, 1.0f)
	#define C_COLOR_BLACK		D2D1::ColorF(0.0f, 0.0f, 0.0f)
	#define C_COLOR_GRAY		D2D1::ColorF(0.5f, 0.5f, 0.5f)
#else
	#define C_COLOR_RED			RGB(255,	0,		0)
	#define C_COLOR_GREEN		RGB(0,		255,	0)
	#define C_COLOR_BLUE		RGB(0,		0,		255)
	#define C_COLOR_MAGENTA		RGB(255,	0,		255)
	#define C_COLOR_YELLOW		RGB(255,	255,	0)
	#define C_COLOR_CYAN		RGB(0,		255,	255)
	#define C_COLOR_WHITE		RGB(255,	255,	255)
	#define C_COLOR_BLACK		RGB(0,		0,		0)
	#define C_COLOR_GRAY		RGB(128,	128,	128)
#endif

//=============
// # Àü¿ªº¯¼ö #
//=============
// ===== winAPI ===== //
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

// ===== Direct ===== //
extern ID2D1Factory*			_factory;
extern ID2D1HwndRenderTarget*	_renderTarget;

//============================
// # ¸ÅÅ©·Î # (Àü¿ªº¯¼ö »ç¿ë)
//============================
#define PTMOUSE		POINT{ _ptMouse.x / (long)WINRATIO, _ptMouse.y / (long)WINRATIO }