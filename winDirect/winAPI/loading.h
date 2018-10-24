#pragma once
#include "gameNode.h"

//로드 아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			//빈비트맵 이미지
	LOAD_KIND_IMAGE_1,			//일반 이미지
	LOAD_KIND_IMAGE_2,			//일반 이미지(위치좌표)
	LOAD_KIND_FRAMEIMAGE_0,		//프레임 이미지
	LOAD_KIND_FRAMEIMAGE_1,		//프레임 이미지(위치좌표)
	LOAD_KIND_GDIP_IMAGE,		// GDI+ 이미지
	LOAD_KIND_GDIP_FRAMEIMAGE,	// GDI+ 프레임 이미지
	LOAD_KIND_SOUND,			//사운드
	
	LOAD_KIND_TILEMAP,			// 타일맵
	LOAD_KIND_EFFECT,			// 이펙트

	LOAD_KIND_END
};

//이미지 리소스 구조체
struct tagImageResource
{
	string keyName;				//이미지 키값
	TCHAR* fileName;		//파일 이름
	int x, y;					//위치 좌표
	int width, height;			//가로, 세로크기
	int frameX, frameY;			//프레임 x, y
	bool trans;					//배경 없앨건지?
	COLORREF transColor;		//지워버릴 배경색
};

//사운드 리소스 구조체
struct tagSoundResource
{
	string keyName;
	string soundName;
	bool bgm;
	bool loop;
};

// 타일맵 리소스 구조체
struct tagTileMapResource
{
	string keyName;
};

// 이펙트 리소스 구조체
struct tagEffectResource
{
	string	keyName;
	string	imgName;
	POINT	start;
	POINT	end;

	BYTE	alpha;
	float	alphaAdd;

	float	timeLive;
	float	timeAniStart;
	float	timeAfterAlpha;

	int		FPS;
	bool	isLoop;

	POINT	offset;
	fPOINT	speed;
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;
	tagTileMapResource _tileMapResource;
	tagEffectResource _effectResource;

public:
	// ---------------- init ---------------- //
	//빈 비트맵 초기화
	HRESULT initForImage(string keyName, int width, int height);

	//이미지 파일로 초기화
	HRESULT initForImage(string keyName, char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForImage(string keyName, char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//프레임 이미지 파일로 초기화
	HRESULT initForFrameImage(string keyName, char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForFrameImage(string keyName, char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// GDI+ 이미지로 초기화
	HRESULT initForGDI(string keyName, TCHAR* fileName, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForGDIFrame(string keyName, TCHAR* fileName, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//사운드 파일로 초기화
	HRESULT initForSound(string keyName, string soundName, bool bgm, bool loop);

	// 타일맵 파일로 초기화
	HRESULT initForTileMap(string keyName);

	// 이펙트로 초기화
	HRESULT initForEffect(string keyName, string imgName, POINT & start, POINT & end, POINT & offset, int & FPS, bool & isLoop, fPOINT & speed, float & timeLive, float & timeAniStart, BYTE & alpha, float & alphaAdd, float & timeAfterAlpha);

	// ---------------- 접근자 ---------------- //
	//로딩아이템 종류 가져오기
	LOAD_KIND getLoadingKind(void) { return _kind; }

	//이미지 리소스 가져오기
	tagImageResource getImageResource(void) { return _imageResource; }

	//사운드 리소스 가져오기
	tagSoundResource getSoundResource(void) { return _soundResource; }

	// 타일맵 리소스 가져오기
	tagTileMapResource getTileMapResource(void) { return _tileMapResource; };

	// 이펙트 리소스 가져오기
	tagEffectResource getEffectResource(void) { return _effectResource; };

	loadItem() {}
	~loadItem() {}
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	//로딩화면에 사용할 이미지 및 로딩바
	image* _background;
	image* _loadingBarRun;

	int _currentGauge;
	int _frameCount;
	int _soundCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//빈 비트맵 초기화
	void loadImage(string keyName, int width, int height);

	//이미지 파일로 초기화
	void loadImage(string keyName, char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string keyName, char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//프레임 이미지 파일로 초기화
	void loadFrameImage(string keyName, char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadFrameImage(string keyName, char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// GDI+ 이미지 파일 초기화
	void loadImageGDI(string keyName, TCHAR* fileName, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImageFrameGDI(string keyName, TCHAR* fileName, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//사운드 파일로 초기화
	void loadSound(string keyName, string soundName, bool bgm, bool loop);

	// 타일맵 파일로 초기화
	void loadTileMap(string keyName);

	// 이펙트 초기화
	void loadEffect(string keyName, string imgName, POINT & start, POINT & end, POINT offset = { 0 }, int FPS = 12, bool isLoop = false, fPOINT speed = { 0, 0 }, float timeLive = 0, float timeAniStart = 0, BYTE alpha = 255, float alphaAdd = 0, float timeAfterAlpha = 0);

public :
	//로딩 완료? (로딩완료후 화면전환)
	BOOL loadingDone(void);

	//로드아이템 벡터 가져오기
	arrLoadItem& getLoadItem(void) { return _vLoadItem; }

	// 현재 로드중인 아이템 종류
	loadItem* getItem(void) { if (_vLoadItem.size() <= _currentGauge) return NULL; return _vLoadItem[_currentGauge]; }
	loadItem* getNextItem(void);

public:
	float getProgress(void) { return (float)_currentGauge / (float)_vLoadItem.size(); };
	int& getGaugeValue(void) { return _currentGauge; };
	int& getSoundCount(void) { return _soundCount; };

	loading() {}
	~loading() {}
};