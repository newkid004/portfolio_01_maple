#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;				// 맵 이미지 목록
	typedef map<string, image*>::iterator mapImageIter;		// 맵 이미지 목록 반복자

private:
	mapImageList _mImageList;

public:
	HRESULT init(void);
	void release(void);

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// 키값으로 이미지 탐색
	image* findImage(string strKey);

	// 키값으로 이미지 삭제
	BOOL deleteImage(string strKey);

	// 전체 이미지 삭제
	BOOL deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH);

	void render(string strKey, HDC hdc, int destX, int destY, float ratio);
	void render(string strKey, HDC hdc, int destX, int destY, float ratioX, float ratioY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratio);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, COLORREF changeColor, COLORREF renderColor);

	void frameRender(string strKey, HDC hdc, int destX, int destY, int flip);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, int flip);

	void frameRender(string strKey, HDC hdc, int destX, int destY, float ratio);
	void frameRender(string strKey, HDC hdc, int destX, int destY, float ratioX, float ratioY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratioX, float ratioY);

	void frameRender(string strKey, HDC hdc, int destX, int destY, float ratio, int flip);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio, int flip);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	imageManager() {};
	~imageManager() {};
};

