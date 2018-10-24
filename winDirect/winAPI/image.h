#pragma once

// 클래스 전방선언
class animation;

enum e_IMAGE_FLIP
{
	IMAGE_FLIP_NONE		= 0b00,
	IMAGE_FLIP_VERTICAL	= 0b10,
	IMAGE_FLIP_HORIZON	= 0b01
};

class image
{
public:
	typedef struct tagImage
	{
		ID2D1Bitmap*	bitmap;			// 비트맵
		
		fPOINT			size;			// 크기
										
		int				maxFrameX;		// 최대 프레임 x갯수
		int				maxFrameY;		// 최대 프레임 y갯수
		POINT			frameSize;		// 프레임 크기

		tagImage()
		{
			bitmap		= NULL;
			
			size		= { 0.0f, 0.0f };

			maxFrameX	= 0;
			maxFrameY	= 0;
			frameSize	= { 0, 0 };
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO*		_imageInfo;		//이미지 정보
	wstring			_fileName;		//이미지 이름

private :
	HRESULT _putImage(void);
	void	_putImageInfo(void);
	void	_flip2fpos(int flip, D2D1_SIZE_F & output);

public:
	// 프레임 초기화
	HRESULT init(const wchar_t * fileName);
	HRESULT init(const wchar_t * fileName, int maxFrameX, int maxFrameY);

	//해제
	void release(void);

	//렌더 (내가 지정한 좌표에 이미지 출력한다)
	void render(int flip = IMAGE_FLIP_NONE, float rotate = 0.0f, float alpha = 1.0f);

	//// 이미지 클리핑
	//void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH);
	//void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, int flip);

	//// 이미지 stretch
	//void render(HDC hdc, int destX, int destY, float ratio);
	//void render(HDC hdc, int destX, int destY, float ratioX, float ratioY);

	//// 이미지 클리핑 stretch (늘리기 -> 렌더)
	//void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratio);
	//void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratioX, float ratioY);

	//// 알파 렌더
	//void alphaRender(HDC hdc, BYTE alpha);
	//void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	//void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha);

	//// 알파 렌더 : 뒤집기
	//void alphaRender(HDC hdc, BYTE alpha, int flip);
	//void alphaRender(HDC hdc, int destX, int destY, BYTE alpha, int flip);
	//void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, int flip);

	//// 알파 렌더 : stretch
	//void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, float ratioX, float ratioY);

	//// 프레임 렌더
	//void frameRender(HDC hdc, int destX, int destY);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, COLORREF changeColor, COLORREF renderColor);

	//// 프레임 렌더 : 뒤집기 x / y
	//void frameRender(HDC hdc, int destX, int destY, int flip);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, int flip);

	//// 프레임 렌더 : stretch
	//void frameRender(HDC hdc, int destX, int destY, float ratio);
	//void frameRender(HDC hdc, int destX, int destY, float ratioX, float ratioY);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratioX, float ratioY);

	//// 프레임 렌더 : 뒤집기 + stretch
	//void frameRender(HDC hdc, int destX, int destY, float ratio, int flip);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio, int flip);

	//// 루프 렌더
	//void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	//void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio);
	//void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//// 애니 렌더
	//void aniRender(HDC hdc, int destX, int destY, animation * ani);

	// =========================== inline ============================== //

	// ** 이미지 가로, 세로크기 **
	inline const fPOINT & getSize(void) { return _imageInfo->size; };

	// 이미지 1프레임 가로, 세로 크기
	inline const POINT & getFrameSize(void) { return _imageInfo->frameSize; }

	// 비트맵 픽셀
	D3DCOLORVALUE getBitmapPixel(POINT pos);

	image();
	~image() {}
};