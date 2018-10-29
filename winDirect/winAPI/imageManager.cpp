#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init(void)
{
	// 이미지 팩토리 생성
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_imgFactory));

	// 이미지 클리핑으로 사용될 레이어 생성
	_renderTarget->CreateLayer(NULL, &_layer);

	// state 초기화
	_imgPos = { 0, 0 };
	_imgFlip = 0;
	_imgRotate = 0.0f;

	_renderState = 0;

	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();

	_imgFactory->Release();
	_layer->Release();
}

image * imageManager::add(string strKey, wchar_t * fileName, int maxFrameX, int maxFrameY)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = find(strKey);

	// 이미 있다면 리턴
	if (img) return img;

	// 없으면 생성
	img = new image;
	img->init(fileName, maxFrameX, maxFrameY);

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

void imageManager::pushLayer(fRECT * clippedArea)
{
	_renderTarget->PushLayer(
		LayerParameters(RectF(
			clippedArea->LT.x,
			clippedArea->LT.y,
			clippedArea->RB.x,
			clippedArea->RB.y)),
		_layer);
}

void imageManager::popLayer(void)
{
	_renderTarget->PopLayer();
}

void imageManager::resetTransform(void)
{
	_imgPos = { 0 ,0 };
	_imgFlip = 0; 
	_imgRotate = 0.0f;
}

void imageManager::resetTransform(e_RESET_TRANSFORM resetValue)
{
	if (resetValue & RTF_POSITION)	_imgPos = { 0 ,0 };
	if (resetValue & RTF_ROTATION)	_imgRotate = 0.0f;
	if (resetValue & RTF_FLIP)		_imgFlip = 0;
}

void imageManager::setTransform(D2D1_POINT_2F * pos)
{
	D2D1_SIZE_F flipPos; _flip2fpos(_imgFlip, flipPos);

	_renderTarget->SetTransform(
		Matrix3x2F::Scale(flipPos, *pos) *				// 반전
		Matrix3x2F::Rotation(_imgRotate, *pos) *		// 회전
		Matrix3x2F::Translation(_imgPos.x, _imgPos.y)	// 위치
		);
}

void imageManager::setRenderState(e_IMG_RENDER_STATE state, int value)
{
	switch (state)
	{
	case IRS_ALWAYS_RESET_TRANSFORM: {		// 항상 초기화 하는지
		if (value)	_renderState = bit_put(_renderState, state);
		else		_renderState = bit_pick(_renderState, state);
	} break;
	}
}

void imageManager::_flip2fpos(int flip, D2D1_SIZE_F & output)
{
	output.width = 0 < (flip & e_IMAGE_FLIP::IMAGE_FLIP_VERTICAL) ? -1.0f : 1.0f;
	output.height = 0 < (flip & e_IMAGE_FLIP::IMAGE_FLIP_HORIZON) ? -1.0f : 1.0f;
}
