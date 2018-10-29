#include "stdafx.h"
#include "image.h"
#include "animation.h"

// 알파블렌드를 사용하기 위한 라이브러리 추가
#pragma comment(lib, "msimg32.lib")

image::image() : _imageInfo(NULL)
{
}

HRESULT image::_putImage(bool isUsePixel)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder * decoder = NULL;
	IWICBitmapFrameDecode * fDecoder = NULL;
	IWICFormatConverter * converter = NULL;
	
	// 파일 읽기
	if (S_OK != (hr =IMAGEMANAGER->getFactory()->CreateDecoderFromFilename(_fileName.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &decoder))) return hr;

	// 프레임 단위 해석 디코더
	decoder->GetFrame(0, &fDecoder);

	// 이미지 형식 변환
	if (S_OK != (hr = IMAGEMANAGER->getFactory()->CreateFormatConverter(&converter))) return hr;
	if (S_OK != (hr = converter->Initialize(fDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom))) return hr;

	// D2D용 비트맵 생성
	if (S_OK != (hr = _renderTarget->CreateBitmapFromWicBitmap(converter, NULL, &_imageInfo->bitmap))) return hr;

	// pixel용 비트맵 생성
	if (isUsePixel)
	{
		if (S_OK != (hr = IMAGEMANAGER->getFactory()->CreateBitmap(_imageInfo->bitmap->GetSize().width, _imageInfo->bitmap->GetSize().height,
			GUID_WICPixelFormat32bppRGBA1010102, WICBitmapNoCache, &_imageInfo->wBitmap)))return hr;
	}
		
	converter->Release();
	fDecoder->Release();
	decoder->Release();

	return hr;
}

void image::_putImageInfo(void)
{
	_imageInfo->size.x = _imageInfo->bitmap->GetSize().width;
	_imageInfo->size.y = _imageInfo->bitmap->GetSize().height;
	_imageInfo->frameSize.x = _imageInfo->size.x / _imageInfo->maxFrame.x;
	_imageInfo->frameSize.y = _imageInfo->size.y / _imageInfo->maxFrame.y;
}

HRESULT image::init(const wchar_t * fileName, bool isUsePixel)
{
	return init(fileName, 1, 1, isUsePixel);
}

HRESULT image::init(const wchar_t * fileName, int maxFrameX, int maxFrameY, bool isUsePixel)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈를 먼저 해줄것
	if (_imageInfo != NULL) this->release();

	//이미지 정보 새로 생성후 초기화하기
	_imageInfo = new IMAGE_INFO;

	_imageInfo->maxFrame = { (long)maxFrameX, (long)maxFrameY };

	//파일이름
	_fileName = fileName;

	//리소스 입력
	if (S_OK != _putImage(isUsePixel))
	{
		release();
		return E_FAIL;
	}

	// 이미지 정보 입력
	_putImageInfo();

	// 프레임 보정
	--_imageInfo->maxFrame.x;
	--_imageInfo->maxFrame.y;

	return S_OK;
}

void image::release(void)
{
	//이미지 정보가 남아 있다면 해제
	if (_imageInfo)
	{
		// 이미지 삭제
		_imageInfo->bitmap->Release();

		// 픽셀 이미지 삭제
		if (_imageInfo->wBitmap) 
			_imageInfo->wBitmap->Release();

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
	}
}

//렌더 (0, 0지점에 렌더)
void image::render(float alpha)
{
	D2D1_POINT_2F rotateCenter = { _imageInfo->size.x / 2, _imageInfo->size.y / 2 };
	IMAGEMANAGER->setTransform(&rotateCenter);

	_renderTarget->DrawBitmap(_imageInfo->bitmap,
		RectF(
			0, 0,
			_imageInfo->size.x,
			_imageInfo->size.y),
		alpha);

	if (IMAGEMANAGER->getRenderState() & IRS_ALWAYS_RESET_TRANSFORM)
		IMAGEMANAGER->resetTransform();
}

void image::render(float clipX, float clipY, float clipW, float clipH, float alpha)
{
	// 위치 보정
	auto tempPos = IMAGEMANAGER->statePos();
	IMAGEMANAGER->statePos() -= fPOINT(clipX , clipY);

	// 중심점
	D2D1_POINT_2F rotateCenter;
	rotateCenter.x = (clipX + clipW / 2);
	rotateCenter.y = (clipY + clipH / 2);
	IMAGEMANAGER->setTransform(&rotateCenter);

	// 레이어 입력
	fRECT clipArea(clipX, clipY, clipX + clipW, clipY + clipH);
	IMAGEMANAGER->pushLayer(&clipArea);

	// draw
	_renderTarget->DrawBitmap(_imageInfo->bitmap,
		RectF(
			0, 0,
			_imageInfo->size.x,
			_imageInfo->size.y),
		alpha);

	// 레이어 제외
	IMAGEMANAGER->popLayer();

	// 보정 되돌림
	IMAGEMANAGER->statePos() = tempPos;

	// 렌더 상태에 따라 
	if (IMAGEMANAGER->getRenderState() & IRS_ALWAYS_RESET_TRANSFORM)
		IMAGEMANAGER->resetTransform();
}

void image::frameRender(int frameX, int frameY, float alpha)
{
	this->render(
		(float)frameX * _imageInfo->frameSize.x,
		(float)frameY * _imageInfo->frameSize.y , 
		_imageInfo->frameSize.x,
		_imageInfo->frameSize.y,
		alpha);
}

void image::frameRender(fPOINT frame, float alpha)
{
	this->render(
		frame.x * _imageInfo->frameSize.x,
		frame.y * _imageInfo->frameSize.y,
		_imageInfo->frameSize.x,
		_imageInfo->frameSize.y,
		alpha);
}

void image::aniRender(animation * ani, float alpha)
{
	if (ani->isPlay())
		this->render(
			(float)ani->getFramePos().x, (float)ani->getFramePos().y,
			(float)ani->getFrameWidth(), (float)ani->getFrameHeight(),
			alpha);
}

ColorF image::getBitmapPixel(POINT pos)
{
	IWICBitmapLock * bLock;
	BYTE* buffer;
	UINT size;
	WICRect rc;
	rc.X = pos.x; rc.Width = 1;
	rc.Y = pos.y; rc.Height = 1;
	
	_imageInfo->wBitmap->Lock(&rc, WICBitmapLockRead, &bLock);
	bLock->GetDataPointer(&size,&buffer);
	
	ColorF color = ColorF(buffer[2], buffer[1], buffer[0], buffer[3]);
	bLock->Release();
	return color;
}

HRESULT image::getBitmapPixels(POINT posSour, POINT posDest, ColorF * out)
{
	IWICBitmapLock * bLock;
	BYTE* buffer;
	UINT size;
	WICRect rc;
	rc.X = posSour.x; rc.Width = posDest.x - posSour.x;
	rc.Y = posSour.y; rc.Height = posDest.y - posSour.y;

	_imageInfo->wBitmap->Lock(&rc, WICBitmapLockRead, &bLock);
	HRESULT hr = bLock->GetDataPointer(&size, &buffer);

	for (int i = 0; i < size / sizeof(UINT); ++i)
		out[i] = ColorF(buffer[2], buffer[1], buffer[0], buffer[3]);

	bLock->Release();

	return hr;
}
