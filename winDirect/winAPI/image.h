#pragma once

// 클래스 전방선언
class animation;

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//리소스로 로딩
		LOAD_FILE,				//파일로 로딩
		LOAD_EMPTY,				//빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;			//리소스 ID
		HDC			hMemDC;			//메모리 DC
		HBITMAP		hBit;			//비트맵
		HBITMAP		hOBit;			//올드비트맵
		
		float		x;				// 이미지 x좌표
		float		y;				// 이미지 y좌표
		int			width;			//이미지 가로크기
		int			height;			//이미지 세로크기
									
		int			curruntFrameX;	// 현재 프레임 x좌표
		int			curruntFrameY;	// 현재 프레임 y좌표
		int			maxFrameX;		// 최대 프레임 x갯수
		int			maxFrameY;		// 최대 프레임 y갯수
		int			frameWidth;		// 1프레임 가로
		int			frameHeight;	// 1프레임 세로
									
		BYTE		loadType;		//이미지 로드타입

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			
			x = y = 0;
			width = 0;
			height = 0;

			curruntFrameX = 0;
			curruntFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;

			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 이름
	BOOL			_isTrans;		//배경색 없앨건지
	COLORREF		_transColor;	//배경색 없앨 RGB값 (마젠타 = RGB(255, 0, 255))

	LPIMAGE_INFO	_strchImage;	// stretch 이미지

	BLENDFUNCTION	_blendFunc;		// 알파블렌드 기능
	LPIMAGE_INFO	_blendImage;	// 알파블렌드 이미지

public:
	//빈 비트맵으로 초기화
	HRESULT init(int width, int height);
	//이미지 리소스로 초기화
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화(주 사용)
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// 프레임 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// stretch 초기화
	HRESULT initForStretch(void);
	// 알파블렌드 초기화
	HRESULT initForAlphaBlend(void);

	//투명 컬러키 셋팅 (배경색 날릴꺼냐?, 어떤색깔)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//해제
	void release(void);

	//렌더 (내가 지정한 좌표에 이미지 출력한다)
	void render(HDC hdc);
	void render(HDC hdc, float ratio);
	void render(HDC hdc, int destX, int destY);

	// 이미지 클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, int flip);

	// 이미지 stretch
	void render(HDC hdc, int destX, int destY, float ratio);
	void render(HDC hdc, int destX, int destY, float ratioX, float ratioY);

	// 이미지 클리핑 stretch (늘리기 -> 렌더)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratio);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratioX, float ratioY);

	// 알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha);

	// 알파 렌더 : 뒤집기
	void alphaRender(HDC hdc, BYTE alpha, int flip);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha, int flip);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, int flip);

	// 알파 렌더 : stretch
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, float ratioX, float ratioY);

	// 프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, COLORREF changeColor, COLORREF renderColor);

	// 프레임 렌더 : 뒤집기 x / y
	void frameRender(HDC hdc, int destX, int destY, int flip);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, int flip);

	// 프레임 렌더 : stretch
	void frameRender(HDC hdc, int destX, int destY, float ratio);
	void frameRender(HDC hdc, int destX, int destY, float ratioX, float ratioY);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratioX, float ratioY);

	// 프레임 렌더 : 뒤집기 + stretch
	void frameRender(HDC hdc, int destX, int destY, float ratio, int flip);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio, int flip);

	// 루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// 애니 렌더
	void aniRender(HDC hdc, int destX, int destY, animation * ani);

	//DC 얻기
	inline HDC &getMemDC(void) { return _imageInfo->hMemDC; }
	inline HDC &getBlendDC(void) { return _blendImage->hMemDC; };

	// =========================== inline ============================== //

	// 이미지 좌표
	inline float getX(void) { return _imageInfo->x; };
	inline void setX(float x) { _imageInfo->x = x; };
	inline float getY(void) { return _imageInfo->y; };
	inline void setY(float y) { _imageInfo->y = y; };

	// 이미지 센터
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// ** 이미지 가로, 세로크기 **
	inline int getWidth(void) { return _imageInfo->width; };
	inline int getHeight(void) { return _imageInfo->height; };
	inline POINT getSize(void) { return POINT{ _imageInfo->width, _imageInfo->height }; }

	// 바운딩 박스(충돌용 렉트)
	inline RECT boundingBox(void) { return RectMake((int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height); };
	inline RECT boundingBoxFrame(void) { return RectMake((int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->frameWidth, _imageInfo->frameHeight); };

	// 프레임 X
	inline int getFrameX(void) { return _imageInfo->curruntFrameX; };
	inline void setFrameX(int FrameX) { _imageInfo->curruntFrameX = _imageInfo->maxFrameX < FrameX ? _imageInfo->maxFrameX : FrameX; }

	// 프레임 Y
	inline int getFrameY(void) { return _imageInfo->curruntFrameY; };
	inline void setFrameY(int FrameY) { _imageInfo->curruntFrameY = _imageInfo->maxFrameY < FrameY ? _imageInfo->maxFrameY : FrameY; }

	// 이미지 1프레임 가로, 세로 크기
	inline int & getFrameWidth(void) { return _imageInfo->frameWidth; };
	inline int & getFrameHeight(void) { return _imageInfo->frameHeight; };
	inline POINT getFrameSize(void) { return POINT{ _imageInfo->frameWidth, _imageInfo->frameHeight }; }

	// 최대 프레임 x, y 갯수
	inline int & getMaxFrameX(void) { return _imageInfo->maxFrameX; };
	inline int & getMaxFrameY(void) { return _imageInfo->maxFrameY; };

	// 비트맵 픽셀
	inline COLORREF getBitmapPixel(POINT pos) { return GetPixel(_imageInfo->hMemDC, pos.x, pos.y); }
	inline COLORREF getTransColor() { return _transColor; };

	image();
	~image() {}
};