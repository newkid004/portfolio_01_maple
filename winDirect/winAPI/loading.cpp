#include "stdafx.h"
#include "loading.h"

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = (bool)isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = (int)x;
	_imageResource.y = (int)y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = (bool)isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForGDI(string keyName, TCHAR * fileName, BOOL isTrans, COLORREF transColor)
{
	// 로딩종류 초기화
	_kind = LOAD_KIND_GDIP_IMAGE;

	// 이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForGDIFrame(string keyName, TCHAR * fileName, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	// 로딩종류 초기화
	_kind = LOAD_KIND_GDIP_FRAMEIMAGE;

	// 이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForSound(string keyName, string soundName, bool bgm, bool loop)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_SOUND;

	//사운드 구조체 초기화
	_soundResource.keyName = keyName;
	_soundResource.soundName = soundName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}

HRESULT loadItem::initForTileMap(string keyName)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_TILEMAP;

	// 구조체 초기화
	_tileMapResource.keyName = keyName;

	return S_OK;
}

HRESULT loadItem::initForEffect(string keyName, string imgName, POINT & start, POINT & end, POINT & offset, int & FPS, bool & isLoop, fPOINT & speed, float & timeLive, float & timeAniStart, BYTE & alpha, float & alphaAdd, float & timeAfterAlpha)
{
	// 로딩종류 초기화
	_kind = LOAD_KIND_EFFECT;

	// 구조체 초기화
	_effectResource.keyName			= keyName;
	_effectResource.imgName			= imgName;
	_effectResource.start			= start;
	_effectResource.end				= end;

	_effectResource.offset			= offset;
	_effectResource.speed			= speed;
	_effectResource.timeLive		= timeLive;
	_effectResource.timeAniStart	= timeAniStart;

	_effectResource.FPS				= FPS;
	_effectResource.isLoop			= isLoop;
	
	_effectResource.alpha			= alpha;
	_effectResource.alphaAdd		= alphaAdd;
	_effectResource.timeAfterAlpha	= timeAfterAlpha;

	return S_OK;
}

HRESULT loading::init(void)
{
	// //로딩화면 백그라운드 이미지 초기화
	// _background = IMAGEMANAGER->addImage("bgLoadingScene", "image/scene/loading/loadingBg.bmp", WINSIZEX, WINSIZEY);
	// 
	// //로딩바 초기화
	// _loadingBar = new progressBar;
	// _loadingBar->init("image/scene/loading/loadingBarFront", "image/scene/loading/loadingBarBack", 25, WINSIZEY / 2 + 70, 200, 10);
	// _loadingBar->setGauge(0, 0);
	// _loadingBarRun = IMAGEMANAGER->addFrameImage("loadingBarRun", "image/scene/loading/loadingBarRun.bmp", 119, 23, 7, 1, true, RGB(255, 0, 255));
	
	_currentGauge = 0;
	_frameCount = 0;
	_soundCount = 0;

	return S_OK;
}

void loading::release(void)
{
	for (int i = 0; i < _vLoadItem.size(); i++)
		SAFE_DELETE(_vLoadItem[i]);

	_vLoadItem.clear();
}

void loading::update(void)
{
}

void loading::render(void)
{/*
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		_loadingBarRun->setFrameX(_loadingBarRun->getFrameX() + 1);
		if (_loadingBarRun->getFrameX() >= _loadingBarRun->getMaxFrameX()) _loadingBarRun->setFrameX(0);
	}*/

	if (_frameCount == 100) _frameCount = 0;
}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImageGDI(string keyName, TCHAR * fileName, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForGDI(keyName, fileName, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImageFrameGDI(string keyName, TCHAR * fileName, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForGDIFrame(keyName, fileName, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, string soundName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, soundName, bgm, loop);
	_vLoadItem.push_back(item);

	_soundCount++;
}

void loading::loadTileMap(string keyName)
{
	loadItem* item = new loadItem;
	item->initForTileMap(keyName);
	_vLoadItem.push_back(item);
}

void loading::loadEffect(string keyName, string imgName, POINT & start, POINT & end, POINT offset, int FPS, bool isLoop, fPOINT speed, float timeLive, float timeAniStart, BYTE alpha, float alphaAdd, float timeAfterAlpha)
{
	loadItem* item = new loadItem;
	item->initForEffect(keyName, imgName, start, end, offset, FPS, isLoop, speed, timeLive, timeAniStart, alpha, alphaAdd, timeAfterAlpha);
	_vLoadItem.push_back(item);
}

//로딩완료 됐냐? (로딩완료후 화면 전환)
BOOL loading::loadingDone(void)
{
	//로딩이 완료 됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];
/*
	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0: {
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	} break;

	case LOAD_KIND_IMAGE_1: {
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
	} break;

	case LOAD_KIND_IMAGE_2: {
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
	} break;

	case LOAD_KIND_FRAMEIMAGE_0: {
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	} break;

	case LOAD_KIND_FRAMEIMAGE_1: {
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	} break;

	// case LOAD_KIND_SOUND: {
	// 	tagSoundResource snd = item->getSoundResource();
	// 	SOUNDMANAGER->addSound(snd.keyName.c_str(), snd.soundName.c_str(), snd.bgm, snd.loop);
	// 	
	// }  break;

	}
	*/

	_currentGauge++;

	//로딩바 이미지 변경
	// _loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	return FALSE;
}

loadItem * loading::getNextItem(void)
{
	if (_vLoadItem.size() <= _currentGauge + 1)
		return NULL;

	return _vLoadItem[_currentGauge + 1];
}

