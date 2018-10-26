#pragma once

// 클래스 전방선언
class animation;

class image
{
public:
	typedef struct tagImage
	{
		IWICBitmap*		wBitmap;
		ID2D1Bitmap*	bitmap;			// 비트맵
		fPOINT			size;			// 크기
		POINT			maxFrame;		// 최대 프레임 수
		POINT			frameSize;		// 프레임 크기

		tagImage()
		{
			bitmap		= NULL;
			size		= { 0.0f, 0.0f };
			maxFrame	= { 0, 0 };
			frameSize	= { 0, 0 };
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO*		_imageInfo;		//이미지 정보
	wstring			_fileName;		//이미지 이름

private :
	HRESULT _putImage(void);
	void	_putImageInfo(void);

public:
	// 프레임 초기화
	HRESULT init(const wchar_t * fileName);
	HRESULT init(const wchar_t * fileName, int maxFrameX, int maxFrameY);

	//해제
	void release(void);

	//렌더 (내가 지정한 좌표에 이미지 출력한다)
	void render(float alpha = 1.0f);

	// 이미지 클리핑
	void render(float clipX, float clipY, float clipW, float clipH, float alpha = 1.0f);

	// 프레임 렌더
	void frameRender(int frameX, int frameY, float alpha = 1.0f);

	// 애니 렌더
	void aniRender(animation * ani, float alpha = 1.0f);

public :
	// 비트맵 픽셀
	ColorF getBitmapPixel(POINT pos);

	// 행렬 지정
	// static void initRenderState(void);

public :
	// =========================== inline ============================== //
	// 이미지 가로, 세로크기
	inline const fPOINT & getSize(void) { return _imageInfo->size; };

	// 이미지 1프레임 가로, 세로 크기
	inline const POINT & getFrameSize(void) { return _imageInfo->frameSize; }

	// 이미지 프레임 개수
	inline const POINT & getMaxFrame(void) { return _imageInfo->maxFrame; };

	image();
	~image() {}
};