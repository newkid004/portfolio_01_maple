#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init(void)
{
	// 이미지 팩토리 생성
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_imgFactory));

	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();

	_imgFactory->Release();
}

image * imageManager::addImage(string strKey, wchar_t * fileName)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = find(strKey);

	// 이미 있다면 리턴
	if (img) return img;

	// 없으면 생성
	img = new image;
	img->init(fileName);

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// imageManager 핵심 함수
image * imageManager::find(string strKey)
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