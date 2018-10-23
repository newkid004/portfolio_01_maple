#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init(void)
{
	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();
}

image * imageManager::addImage(string strKey, int width, int height)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 이미 있다면 리턴
	if (img) return img;

	img = new image;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	// 맵에 추가
	// _mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 이미 있다면 리턴
	if (img) return img;

	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	// 맵에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 이미 있다면 리턴
	if (img) return img;

	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	// 맵에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 이미 있다면 리턴
	if (img) return img;

	img = new image;
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	// 맵에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 이미 있다면 리턴
	if (img) return img;

	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	// 맵에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// imageManager 핵심 함수
image * imageManager::findImage(string strKey)
{
	// 해당 키 검색
	mapImageIter key = _mImageList.find(strKey);

	// 찾음
	if (key != _mImageList.end()) return key->second;

	// 못찾음
	return NULL;
}

BOOL imageManager::deleteImage(string strKey)
{
	// 해당 키 검색
	mapImageIter key = _mImageList.find(strKey);

	// 찾음
	if (key != _mImageList.end())
	{
		// 이미지 삭제
		key->second->release();
		SAFE_DELETE(key->second);

		// 맵 인자 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

BOOL imageManager::deleteAll()
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		// 이미지가 있으면
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		// 이미지가 없으면
		else
		{
			++iter;
		}
	}

	// 안전장치
	_mImageList.clear();

	return TRUE;
}

void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourW, sourH);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, float ratio)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, ratio);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, float ratioX, float ratioY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, ratioX, ratioY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratio)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourW, sourH, ratio);
}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourW, sourH, alpha);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, curruntFrameX, curruntFrameY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, COLORREF changeColor, COLORREF renderColor)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, curruntFrameX, curruntFrameY, changeColor, renderColor);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int flip)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, flip);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, int flip)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, curruntFrameX, curruntFrameY, flip);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, float ratio)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, ratio);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, float ratioX, float ratioY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, ratioX, ratioY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, curruntFrameX, curruntFrameY, ratio);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratioX, float ratioY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, curruntFrameX, curruntFrameY, ratioX, ratioY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, float ratio, int flip)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, ratio, flip);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio, int flip)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, curruntFrameX, curruntFrameY, ratio, flip);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY, ratio);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}
