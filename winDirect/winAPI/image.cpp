#include "stdafx.h"
#include "image.h"
#include "animation.h"

// 알파블렌드를 사용하기 위한 라이브러리 추가
#pragma comment(lib, "msimg32.lib")

image::image() : _imageInfo(NULL)
{
}

HRESULT image::_putImage(void)
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

	converter->Release();
	fDecoder->Release();
	decoder->Release();

	return hr;
}

void image::_putImageInfo(void)
{
	_imageInfo->size.x = _imageInfo->bitmap->GetSize().width;
	_imageInfo->size.y = _imageInfo->bitmap->GetSize().height;
	_imageInfo->frameSize.x = _imageInfo->size.x;
	_imageInfo->frameSize.y = _imageInfo->size.y;
}

void image::_flip2fpos(int flip, D2D1_SIZE_F & output)
{
	output.width	= 0 < (flip & e_IMAGE_FLIP::IMAGE_FLIP_VERTICAL) ? -1.0f : 1.0f;
	output.height	= 0 < (flip & e_IMAGE_FLIP::IMAGE_FLIP_HORIZON) ? -1.0f : 1.0f;
}

HRESULT image::init(const wchar_t * fileName)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈를 먼저 해줄것
	if (_imageInfo != NULL) this->release();

	//이미지 정보 새로 생성후 초기화하기
	_imageInfo = new IMAGE_INFO;

	// 프레임범위 임의 초기화
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;

	//파일이름
	_fileName = fileName;

	// 리소스 입력
	_putImage();

	//리소스 얻어오는데 실패했을때
	if (_imageInfo->bitmap == 0)
	{
		release();
		return E_FAIL;
	}

	// 이미지 정보 입력
	_putImageInfo();

	return S_OK;
}

HRESULT image::init(const wchar_t * fileName, int maxFrameX, int maxFrameY)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈를 먼저 해줄것
	if (_imageInfo != NULL) this->release();

	//이미지 정보 새로 생성후 초기화하기
	_imageInfo = new IMAGE_INFO;

	// 프레임범위 임의 초기화
	_imageInfo->maxFrameX = maxFrameX;
	_imageInfo->maxFrameY = maxFrameY;

	//파일이름
	_fileName = fileName;

	//리소스 입력
	if (S_OK != _putImage())
	{
		release();
		return E_FAIL;
	}

	// 이미지 정보 입력
	_putImageInfo();

	return S_OK;
}

void image::release(void)
{
	//이미지 정보가 남아 있다면 해제
	if (_imageInfo)
	{
		//이미지 삭제
		_imageInfo->bitmap->Release();

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
	}
}


//렌더 (0, 0지점에 렌더)
void image::render(int flip, float rotate, float alpha)
{
	D2D1_POINT_2F rotateCenter = { _imageInfo->size.x / 2, _imageInfo->size.y / 2 };
	D2D1_SIZE_F flipPos; _flip2fpos(flip, flipPos);
	
	_renderTarget->SetTransform(Matrix3x2F::Rotation(rotate, rotateCenter));
	_renderTarget->SetTransform(Matrix3x2F::Scale(flipPos, rotateCenter));

	_renderTarget->DrawBitmap(_imageInfo->bitmap,
		RectF(
			0, 0,
			_imageInfo->size.x,
			_imageInfo->size.y),
		alpha);
}

//void image::render(HDC hdc, float ratio)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 ratio수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			0, 0,
//			(int)(_imageInfo->width * ratio),
//			(int)(_imageInfo->height * ratio),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			0,														//복사될 좌표 시작x
//			0,														//복사될 좌표 시작y
//			(int)(_imageInfo->width * ratio),						//복사될 이미지 가로크기
//			(int)(_imageInfo->height * ratio),						//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->width * ratio),						//복사 영역 가로크기
//			(int)(_imageInfo->height * ratio),						//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			0, 0,
//			(int)(_imageInfo->width * ratio),
//			(int)(_imageInfo->height * ratio),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//	}
//}
//
////렌더 (내가 지정한 좌표에 이미지 출력)
//void image::render(HDC hdc, int destX, int destY)
//{
//	if (_isTrans)
//	{
//		GdiTransparentBlt(
//			hdc,					//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,					//복사될 좌표 시작x
//			destY,					//복사될 좌표 시작y
//			_imageInfo->width,		//복사될 이미지 가로크기
//			_imageInfo->height,		//복사될 이미지 세로크기
//			_imageInfo->hMemDC,		//복사될 대상 메모리DC
//			0, 0,					//복사 시작지점
//			_imageInfo->width,		//복사 영역 가로크기
//			_imageInfo->height,		//복사 영역 세로크기
//			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
//		);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC, 0, 0, SRCCOPY);
//	}
//}
//
//// 이미지 클리핑
//// 원본 이미지 지정 좌표로부터 가로, 세로 크기를 잘라서 내가 원하는곳에 출력
//void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH)
//{
//	if (_isTrans)
//	{
//		GdiTransparentBlt(
//			hdc,					//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,					//복사될 좌표 시작x
//			destY,					//복사될 좌표 시작y
//			sourW,					//복사될 이미지 가로크기
//			sourH,					//복사될 이미지 세로크기
//			_imageInfo->hMemDC,		//복사될 대상 메모리DC
//			sourX, sourY,			//복사 시작지점
//			sourW, sourH,			//복사 끝지점
//			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, sourW, sourH,
//			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
//	}
//}
//
//void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, int flip)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//
//	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//	if (_isTrans)
//	{
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			sourW	* flipX - flipX,
//			sourH	* flipY - flipY,
//			sourW	* (flipX ? -1 : 1),
//			sourH	* (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			sourX, sourY,
//			sourW, sourH,
//			SRCCOPY);
//
//		GdiTransparentBlt(
//			hdc,					//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,					//복사될 좌표 시작x
//			destY,					//복사될 좌표 시작y
//			sourW,					//복사될 이미지 가로크기
//			sourH,					//복사될 이미지 세로크기
//			_strchImage->hMemDC,	//복사될 대상 메모리DC
//			0, 0,					//복사 시작지점
//			sourW, sourH,	//복사 끝지점
//			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(sourW - sourX) * flipX - flipX,
//			(sourH - sourY) * flipY - flipY,
//			(sourW - sourX) * (flipX ? -1 : 1),
//			(sourH - sourY) * (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			sourX, sourY,
//			sourW, sourH,
//			SRCCOPY);
//	}
//}
//
//void image::render(HDC hdc, int destX, int destY, float ratio)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(_imageInfo->width * (ratio < 0 ? -ratio : 0)),
//			(int)(_imageInfo->height * (ratio < 0 ? -ratio : 0)),
//			(int)(_imageInfo->width * ratio),
//			(int)(_imageInfo->height * ratio),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			(int)(_imageInfo->width * ratio),						//복사될 이미지 가로크기
//			(int)(_imageInfo->height * ratio),						//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->width * ratio),						//복사 영역 가로크기
//			(int)(_imageInfo->height * ratio),						//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + _imageInfo->width * (ratio < 0 ? -ratio : 0)),
//			(int)(destY + _imageInfo->height * (ratio < 0 ? -ratio : 0)),
//			(int)(_imageInfo->width * ratio),
//			(int)(_imageInfo->height * ratio),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//	}
//}
//
//void image::render(HDC hdc, int destX, int destY, float ratioX, float ratioY)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(_imageInfo->width * (ratioX < 0 ? -ratioX : 0)),
//			(int)(_imageInfo->height * (ratioY < 0 ? -ratioY : 0)),
//			(int)(_imageInfo->width * ratioX),
//			(int)(_imageInfo->height * ratioY),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			(int)(_imageInfo->width * ratioX),						//복사될 이미지 가로크기
//			(int)(_imageInfo->height * ratioY),						//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->width * ratioX),						//복사 영역 가로크기
//			(int)(_imageInfo->height * ratioY),						//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + _imageInfo->width * (ratioX < 0 ? -ratioX : 0)),
//			(int)(destY + _imageInfo->height * (ratioY < 0 ? -ratioY : 0)),
//			(int)(_imageInfo->width * ratioX),
//			(int)(_imageInfo->height * ratioY),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//	}
//}
//
//void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratio)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 ratio수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(sourW * (ratio < 0 ? -ratio : 0)),
//			(int)(sourH * (ratio < 0 ? -ratio : 0)),
//			(int)(sourW * ratio),
//			(int)(sourH * ratio),
//			_imageInfo->hMemDC,
//			sourX, sourY,
//			sourW, sourH,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,										//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,										//복사될 좌표 시작x
//			destY,										//복사될 좌표 시작y
//			(int)(sourW * ratio),						//복사될 이미지 가로크기
//			(int)(sourH * ratio),						//복사될 이미지 세로크기
//			_strchImage->hMemDC,						//복사될 대상 메모리DC
//			0, 0,
//			(int)(sourW * ratio),						//복사 영역 가로크기
//			(int)(sourH * ratio),						//복사 영역 세로크기
//			_transColor									//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + (ratio < 0 ? sourW * (-ratio) : 0)),
//			(int)(destY + (ratio < 0 ? sourH * (-ratio) : 0)),
//			(int)(sourW * ratio),
//			(int)(sourH * ratio),
//			_imageInfo->hMemDC,
//			sourX, sourY,
//			sourW, sourH,
//			SRCCOPY);
//	}
//}
//
//void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratioX, float ratioY)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 ratio수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(sourW * (ratioX < 0 ? -ratioX : 0)),
//			(int)(sourH * (ratioY < 0 ? -ratioY : 0)),
//			(int)(sourW * ratioX),
//			(int)(sourH * ratioY),
//			_imageInfo->hMemDC,
//			sourX, sourY,
//			sourW, sourH,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,										//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,										//복사될 좌표 시작x
//			destY,										//복사될 좌표 시작y
//			(int)(sourW * ratioX),						//복사될 이미지 가로크기
//			(int)(sourH * ratioY),						//복사될 이미지 세로크기
//			_strchImage->hMemDC,						//복사될 대상 메모리DC
//			0, 0,
//			(int)(sourW * ratioX),						//복사 영역 가로크기
//			(int)(sourH * ratioY),						//복사 영역 세로크기
//			_transColor									//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + (ratioX < 0 ? sourW * (-ratioX) : 0)),
//			(int)(destY + (ratioY < 0 ? sourH * (-ratioY) : 0)),
//			(int)(sourW * ratioX),
//			(int)(sourH * ratioY),
//			_imageInfo->hMemDC,
//			sourX, sourY,
//			sourW, sourH,
//			SRCCOPY);
//	}
//}
//
//void image::alphaRender(HDC hdc, BYTE alpha)
//{
//	// 알파블렌드를 사용할 수 있도록 초기화
//	if (!_blendImage) initForAlphaBlend();
//
//	// 알파값 초기화
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	// 배경색 없앤 후 알파블렌드 할건지?
//	if (_isTrans)
//	{
//		// 1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그림
//		BitBlt(_blendImage->hMemDC, 
//			0, 0, 
//			_imageInfo->width, _imageInfo->height,
//			hdc, 
//			0, 0, 
//			SRCCOPY);
//
//		// 2. 원본이미지의 배경을 없앤 후 블렌드 이미지에 출력
//		GdiTransparentBlt(
//			_blendImage->hMemDC,	//복사할 장소의 DC (화면에 보여지는 화면DC)
//			0, 0,					//복사될 좌표 시작
//			_imageInfo->width,		//복사될 이미지 가로크기
//			_imageInfo->height,		//복사될 이미지 세로크기
//			_blendImage->hMemDC,	//복사될 대상 메모리DC
//			0, 0,					//복사 시작지점
//			_imageInfo->width,		//복사 영역 가로크기
//			_imageInfo->height,		//복사 영역 세로크기
//			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//
//		// 3. 블렌드 이미지를 화면에 출력
//		AlphaBlend(hdc,
//			0, 0,
//			_imageInfo->width, _imageInfo->height,
//			_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width, _imageInfo->height, 
//			_blendFunc);
//	}
//	else
//	{
//		// 3. 블렌드 이미지를 화면에 출력
//		AlphaBlend(hdc,
//			0, 0,
//			_imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width, _imageInfo->height,
//			_blendFunc);
//	}
//}
//
//void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
//{
//	// 알파블렌드를 사용할 수 있도록 초기화
//	if (!_blendImage) initForAlphaBlend();
//
//	// 알파값 초기화
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	// 배경색 없앤 후 알파블렌드 할건지?
//	if (_isTrans)
//	{
//		// 1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그림
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width, _imageInfo->height,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// 2. 원본이미지의 배경을 없앤 후 블렌드 이미지에 출력
//		GdiTransparentBlt(
//			_blendImage->hMemDC,	//복사할 장소의 DC (화면에 보여지는 화면DC)
//			0, 0,					//복사될 좌표 시작
//			_imageInfo->width,		//복사될 이미지 가로크기
//			_imageInfo->height,		//복사될 이미지 세로크기
//			_imageInfo->hMemDC,		//복사될 대상 메모리DC
//			0, 0,					//복사 시작지점
//			_imageInfo->width,		//복사 영역 가로크기
//			_imageInfo->height,		//복사 영역 세로크기
//			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//
//		// 3. 블렌드 이미지를 화면에 출력
//		AlphaBlend(hdc,
//			destX, destY,
//			_imageInfo->width, _imageInfo->height,
//			_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width, _imageInfo->height,
//			_blendFunc);
//	}
//	else
//	{
//		// 3. 블렌드 이미지를 화면에 출력
//		AlphaBlend(hdc,
//			destX, destY,
//			_imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width, _imageInfo->height,
//			_blendFunc);
//	}
//}
//
//void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha)
//{
//	// 알파블렌드를 사용할 수 있도록 초기화
//	if (!_blendImage) initForAlphaBlend();
//
//	// 알파값 초기화
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	// 배경색 없앤 후 알파블렌드 할건지?
//	if (_isTrans)
//	{
//		// 1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그림
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			sourW, sourH,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// 2. 원본이미지의 배경을 없앤 후 블렌드 이미지에 출력
//		GdiTransparentBlt(
//			_blendImage->hMemDC,	//복사할 장소의 DC (화면에 보여지는 화면DC)
//			0, 0,					//복사될 좌표 시작
//			sourW,					//복사될 이미지 가로크기
//			sourH,					//복사될 이미지 세로크기
//			_imageInfo->hMemDC,		//복사될 대상 메모리DC
//			sourX, sourY,			//복사 시작지점
//			sourW,					//복사 영역 가로크기
//			sourH,					//복사 영역 세로크기
//			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//
//		// 3. 블렌드 이미지를 화면에 출력
//		AlphaBlend(hdc,
//			destX, destY,
//			sourW, sourH,
//			_blendImage->hMemDC,
//			0, 0,
//			sourW, sourH,
//			_blendFunc);
//	}
//	else
//	{
//		// 3. 블렌드 이미지를 화면에 출력
//		AlphaBlend(hdc,
//			destX, destY,
//			sourW, sourH,
//			_imageInfo->hMemDC,
//			0, 0,
//			sourW, sourH,
//			_blendFunc);
//	}
//}
//
//void image::alphaRender(HDC hdc, BYTE alpha, int flip)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//	// Use alphablend
//	if (!_blendImage) initForAlphaBlend();
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	if (_isTrans)
//	{
//		// hdc이미지 저장
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			hdc,
//			0, 0,
//			SRCCOPY);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			_imageInfo->width	* flipX - flipX,
//			_imageInfo->height	* flipY - flipY,
//			_imageInfo->width	* (flipX ? -1 : 1),
//			_imageInfo->height	* (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//
//		// 저장된 flip이미지를 알파블렌드 이미지에 출력
//		GdiTransparentBlt(
//			_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			_strchImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			_transColor
//			);
//
//		// 알파블렌드 이미지 출력
//		AlphaBlend(hdc,
//			0, 0,
//			_imageInfo->width, 
//			_imageInfo->height,
//			_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width, 
//			_imageInfo->height,
//			_blendFunc);
//	}
//	else
//	{
//		StretchBlt(_blendImage->hMemDC,
//			_imageInfo->width	* flipX - flipX,
//			_imageInfo->height	* flipY - flipY,
//			_imageInfo->width	* (flipX ? -1 : 1),
//			_imageInfo->height	* (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//
//		AlphaBlend(hdc,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			_blendFunc);
//	}
//}
//
//void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha, int flip)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//	// Use alphablend
//	if (!_blendImage) initForAlphaBlend();
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	if (_isTrans)
//	{
//		// hdc이미지 저장
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			_imageInfo->width	* flipX - flipX,
//			_imageInfo->height	* flipY - flipY,
//			_imageInfo->width	* (flipX ? -1 : 1),
//			_imageInfo->height	* (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//
//		// 저장된 flip이미지를 알파블렌드 이미지에 출력
//		GdiTransparentBlt(
//			_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			_strchImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			_transColor
//			);
//
//		// 알파블렌드 이미지 출력
//		AlphaBlend(hdc,
//			destX, destY,
//			_imageInfo->width,
//			_imageInfo->height,
//			_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			_blendFunc);
//	}
//	else
//	{
//		StretchBlt(_blendImage->hMemDC,
//			_imageInfo->width	* flipX - flipX,
//			_imageInfo->height	* flipY - flipY,
//			_imageInfo->width	* (flipX ? -1 : 1),
//			_imageInfo->height	* (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			SRCCOPY);
//
//		AlphaBlend(hdc,
//			destX, destY,
//			_imageInfo->width,
//			_imageInfo->height,
//			_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			_blendFunc);
//	}
//}
//
//void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, int flip)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//	// Use alphablend
//	if (!_blendImage) initForAlphaBlend();
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	if (_isTrans)
//	{
//		// hdc이미지 저장
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			sourW	* flipX - flipX,
//			sourH	* flipY - flipY,
//			sourW	* (flipX ? -1 : 1),
//			sourH	* (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			sourX, 
//			sourY,
//			sourW,
//			sourH,
//			SRCCOPY);
//
//		// 저장된 flip이미지를 알파블렌드 이미지에 출력
//		GdiTransparentBlt(
//			_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			_strchImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			_transColor
//			);
//
//		// 알파블렌드 이미지 출력
//		AlphaBlend(hdc,
//			destX, destY,
//			sourW,
//			sourH,
//			_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			_blendFunc);
//	}
//	else
//	{
//		StretchBlt(_blendImage->hMemDC,
//			sourW	* flipX - flipX,
//			sourH	* flipY - flipY,
//			sourW	* (flipX ? -1 : 1),
//			sourH	* (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			sourX,
//			sourY,
//			sourW,
//			sourH,
//			SRCCOPY);
//
//		AlphaBlend(hdc,
//			destX, destY,
//			sourW,
//			sourH,
//			_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			_blendFunc);
//	}
//}
//
//void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, float ratioX, float ratioY)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//	// Use alphablend
//	if (!_blendImage) initForAlphaBlend();
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	if (_isTrans)
//	{
//		// hdc이미지 저장
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// 출력할 원본 이미지를 ratio수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(sourW * (ratioX < 0 ? -ratioX : 0)),
//			(int)(sourH * (ratioY < 0 ? -ratioY : 0)),
//			(int)(sourW * ratioX),
//			(int)(sourH * ratioY),
//			_imageInfo->hMemDC,
//			sourX, sourY,
//			sourW, sourH,
//			SRCCOPY);
//
//		// 저장된 stretch이미지를 알파블렌드 이미지에 출력
//		GdiTransparentBlt(
//			_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			_strchImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			_transColor
//			);
//
//		// 알파블렌드 이미지 출력
//		AlphaBlend(hdc,
//			destX, destY,
//			sourW,
//			sourH,
//			_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			_blendFunc);
//	}
//	else
//	{
//		StretchBlt(_blendImage->hMemDC,
//			(int)(sourW * (ratioX < 0 ? -ratioX : 0)),
//			(int)(sourH * (ratioY < 0 ? -ratioY : 0)),
//			(int)(sourW * ratioX),
//			(int)(sourH * ratioY),
//			_imageInfo->hMemDC,
//			sourX,
//			sourY,
//			sourW,
//			sourH,
//			SRCCOPY);
//
//		AlphaBlend(hdc,
//			destX, destY,
//			sourW,
//			sourH,
//			_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			_blendFunc);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY)
//{
//	if (_isTrans)
//	{
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			_imageInfo->frameWidth,									//복사될 이미지 가로크기
//			_imageInfo->frameHeight,								//복사될 이미지 세로크기
//			_imageInfo->hMemDC,										//복사될 대상 메모리DC
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,		// 프레임 x좌표
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,	// 프레임 y좌표
//			_imageInfo->frameWidth,									//복사 영역 가로크기
//			_imageInfo->frameHeight,								//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC, 
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth, 
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight, 
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY)
//{
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	if (_isTrans)
//	{
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			_imageInfo->frameWidth,									//복사될 이미지 가로크기
//			_imageInfo->frameHeight,								//복사될 이미지 세로크기
//			_imageInfo->hMemDC,										//복사될 대상 메모리DC
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,		// 프레임 x좌표
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,	// 프레임 y좌표
//			_imageInfo->frameWidth,									//복사 영역 가로크기
//			_imageInfo->frameHeight,								//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, COLORREF changeColor, COLORREF renderColor)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	if (_isTrans)
//	{
//		// 출력할 이미지 색상 변경
//		HBRUSH hBrush = CreateSolidBrush(renderColor);
//		HBRUSH oBrush = (HBRUSH)SelectObject(_strchImage->hMemDC, hBrush);
//		FillRect(_strchImage->hMemDC, &RectMake(0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight), hBrush);
//		SelectObject(_strchImage->hMemDC, oBrush);
//		DeleteObject(hBrush);
//
//		GdiTransparentBlt(
//			_strchImage->hMemDC,
//			0, 0,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			changeColor
//			);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			_imageInfo->frameWidth,									//복사될 이미지 가로크기
//			_imageInfo->frameHeight,								//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			_imageInfo->frameWidth,									//복사 영역 가로크기
//			_imageInfo->frameHeight,								//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, int flip)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			_imageInfo->frameWidth * flipX - flipX,
//			_imageInfo->frameHeight * flipY - flipY,
//			_imageInfo->frameWidth * (flipX ? -1 : 1),
//			_imageInfo->frameHeight * (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			_imageInfo->frameWidth,									//복사될 이미지 가로크기
//			_imageInfo->frameHeight,								//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			_imageInfo->frameWidth,									//복사 영역 가로크기
//			_imageInfo->frameHeight,								//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			destX + _imageInfo->frameWidth * flipX - flipX,
//			destY + _imageInfo->frameHeight * flipY - flipY,
//			_imageInfo->frameWidth * (flipX ? -1 : 1),
//			_imageInfo->frameHeight * (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, int flip)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			_imageInfo->frameWidth * flipX - flipX,
//			_imageInfo->frameHeight * flipY - flipY,
//			_imageInfo->frameWidth * (flipX ? -1 : 1),
//			_imageInfo->frameHeight * (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			_imageInfo->frameWidth,									//복사될 이미지 가로크기
//			_imageInfo->frameHeight,								//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			_imageInfo->frameWidth,									//복사 영역 가로크기
//			_imageInfo->frameHeight,								//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			destX + _imageInfo->frameWidth * flipX - flipX,
//			destY + _imageInfo->frameHeight * flipY - flipY,
//			_imageInfo->frameWidth * (flipX ? -1 : 1),
//			_imageInfo->frameHeight * (flipY ? -1 : 1),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, float ratio)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(_imageInfo->frameWidth * ratio < 0 ? -ratio : 0),
//			(int)(_imageInfo->frameHeight * ratio < 0 ? -ratio : 0),
//			(int)(_imageInfo->frameWidth * ratio),
//			(int)(_imageInfo->frameHeight * ratio),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			(int)(_imageInfo->frameWidth * ratio),					//복사될 이미지 가로크기
//			(int)(_imageInfo->frameHeight * ratio),					//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratio),					//복사 영역 가로크기
//			(int)(_imageInfo->frameHeight * ratio),					//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + _imageInfo->frameWidth * ratio < 0 ? -ratio : 0),
//			(int)(destY + _imageInfo->frameHeight * ratio < 0 ? -ratio : 0),
//			(int)(_imageInfo->frameWidth * ratio),
//			(int)(_imageInfo->frameHeight * ratio),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, float ratioX, float ratioY)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(_imageInfo->frameWidth * ratioX < 0 ? -ratioX : 0),
//			(int)(_imageInfo->frameHeight * ratioY < 0 ? -ratioY : 0),
//			(int)(_imageInfo->frameWidth * ratioX),
//			(int)(_imageInfo->frameHeight * ratioY),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			(int)(_imageInfo->frameWidth * ratioX),					//복사될 이미지 가로크기
//			(int)(_imageInfo->frameHeight * ratioY),				//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratioX),					//복사 영역 가로크기
//			(int)(_imageInfo->frameHeight * ratioY),				//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + _imageInfo->frameWidth * ratioX < 0 ? -ratioX : 0),
//			(int)(destY + _imageInfo->frameHeight * ratioY < 0 ? -ratioY : 0),
//			(int)(_imageInfo->frameWidth * ratioX),
//			(int)(_imageInfo->frameHeight * ratioY),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(_imageInfo->frameWidth * ratio < 0 ? -ratio : 0),
//			(int)(_imageInfo->frameHeight * ratio < 0 ? -ratio : 0),
//			(int)(_imageInfo->frameWidth * ratio),
//			(int)(_imageInfo->frameHeight * ratio),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			(int)(_imageInfo->frameWidth * ratio),					//복사될 이미지 가로크기
//			(int)(_imageInfo->frameHeight * ratio),					//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratio),					//복사 영역 가로크기
//			(int)(_imageInfo->frameHeight * ratio),					//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + _imageInfo->frameWidth * ratio < 0 ? -ratio : 0),
//			(int)(destY + _imageInfo->frameHeight * ratio < 0 ? -ratio : 0),
//			(int)(_imageInfo->frameWidth * ratio),
//			(int)(_imageInfo->frameHeight * ratio),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratioX, float ratioY)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) { initForStretch(); SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR); }
//
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	if (_isTrans)
//	{
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(_imageInfo->frameWidth * (ratioX < 0 ? -ratioX : 0)),
//			(int)(_imageInfo->frameHeight * (ratioY < 0 ? -ratioY : 0)),
//			(int)(_imageInfo->frameWidth * ratioX),
//			(int)(_imageInfo->frameHeight * ratioY),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			(int)(_imageInfo->frameWidth * ratioX),					//복사될 이미지 가로크기
//			(int)(_imageInfo->frameHeight * ratioY),				//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratioX),					//복사 영역 가로크기
//			(int)(_imageInfo->frameHeight * ratioY),				//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + _imageInfo->frameWidth * (ratioX < 0 ? -ratioX : 0)),
//			(int)(destY + _imageInfo->frameHeight * (ratioY < 0 ? -ratioY : 0)),
//			(int)(_imageInfo->frameWidth * ratioX),
//			(int)(_imageInfo->frameHeight * ratioY),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, float ratio, int flip)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(_imageInfo->frameWidth * ratio * flipX - flipX),
//			(int)(_imageInfo->frameHeight * ratio * flipY - flipY),
//			(int)(_imageInfo->frameWidth * ratio * (flipX ? -1 : 1)),
//			(int)(_imageInfo->frameHeight * ratio * (flipY ? -1 : 1)),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			(int)(_imageInfo->frameWidth * ratio),					//복사될 이미지 가로크기
//			(int)(_imageInfo->frameHeight * ratio),					//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratio),					//복사 영역 가로크기
//			(int)(_imageInfo->frameHeight * ratio),					//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + _imageInfo->frameWidth * ratio * flipX - flipX),
//			(int)(destY + _imageInfo->frameHeight * ratio * flipY - flipY),
//			(int)(_imageInfo->frameWidth * ratio * (flipX ? -1 : 1)),
//			(int)(_imageInfo->frameHeight * ratio * (flipY ? -1 : 1)),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio, int flip)
//{
//	// 또다른 memDC 사용
//	if (!_strchImage) initForStretch();
//
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// 출력할 원본 이미지를 flip수치로 저장
//		StretchBlt(_strchImage->hMemDC,
//			(int)(_imageInfo->frameWidth * ratio * flipX - flipX),
//			(int)(_imageInfo->frameHeight * ratio * flipY - flipY),
//			(int)(_imageInfo->frameWidth * ratio * (flipX ? -1 : 1)),
//			(int)(_imageInfo->frameHeight * ratio * (flipY ? -1 : 1)),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//
//		// 저장한 이미지를 화면에 출력
//		GdiTransparentBlt(
//			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
//			destX,													//복사될 좌표 시작x
//			destY,													//복사될 좌표 시작y
//			(int)(_imageInfo->frameWidth * ratio),					//복사될 이미지 가로크기
//			(int)(_imageInfo->frameHeight * ratio),					//복사될 이미지 세로크기
//			_strchImage->hMemDC,									//복사될 대상 메모리DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratio),					//복사 영역 가로크기
//			(int)(_imageInfo->frameHeight * ratio),					//복사 영역 세로크기
//			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
//			);
//	}
//	else
//	{
//		StretchBlt(hdc,
//			(int)(destX + _imageInfo->frameWidth * ratio * flipX - flipX),
//			(int)(destY + _imageInfo->frameHeight * ratio * flipY - flipY),
//			(int)(_imageInfo->frameWidth * ratio * (flipX ? -1 : 1)),
//			(int)(_imageInfo->frameHeight * ratio * (flipY ? -1 : 1)),
//			_imageInfo->hMemDC,
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth,
//			_imageInfo->frameHeight,
//			SRCCOPY);
//	}
//}
//
//void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
//{
//	// offset < 0 교정
//	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
//	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
//
//	// 그려지는 영역 세팅
//	RECT rcSour;
//	int sourWidth;
//	int sourHeight;
//
//	// 그려지는 DC영역(화면 크기)
//	RECT rcDest;
//
//	// 그려야 할 전체 영역
//	int drawAreaX = drawArea->left;
//	int drawAreaY = drawArea->top;
//	int drawAreaW = drawArea->right - drawArea->left;
//	int drawAreaH = drawArea->bottom - drawArea->top;
//
//	// 세로 루프영역
//	for (int y = 0; y < drawAreaH; y += sourHeight)
//	{
//		// 소스 영역의 높이 계산
//		rcSour.top = (y + offsetY) % _imageInfo->height;
//		rcSour.bottom = _imageInfo->height;
//		sourHeight = rcSour.bottom - rcSour.top;
//
//		// 소스 영역이 그리는 화면을 넘어갔다면
//		if (y + sourHeight > drawAreaH)
//		{
//			// 넘어간 그림의 값 만큼 bottom값 올려줌
//			rcSour.bottom -= (y + sourHeight) - drawAreaH;
//			sourHeight = rcSour.bottom - rcSour.top;
//		}
//		// 그려지는 영역
//		rcDest.top = y + drawAreaY;
//		rcDest.bottom = rcDest.top + sourHeight;
//
//		// 가로 루프영역
//		for (int x = 0; x < drawAreaW; x += sourWidth)
//		{
//			// 소스 영역의 너비 계산
//			rcSour.left = (x + offsetX) % _imageInfo->width;
//			rcSour.right = _imageInfo->width;
//			sourWidth = rcSour.right - rcSour.left;
//
//			// 소스 영역이 그리는 화면을 넘어갔다면
//			if (x + sourWidth > drawAreaW)
//			{
//				// 넘어간 그림의 값 만큼 right값 올려줌
//				rcSour.right -= (x + sourWidth) - drawAreaW;
//				sourWidth = rcSour.right - rcSour.left;
//			}
//
//			// 그려지는 영역
//			rcDest.left = x + drawAreaX;
//			rcDest.right = rcDest.left + sourWidth;
//
//			// **핵심** //
//			// 일반렌더 - 이미지 잘라서 붙이기
//			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
//		}
//	}
//}
//
//void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio)
//{
//	// offset < 0 교정
//	if (offsetX < 0) offsetX = (int)(_imageInfo->width * ratio + (offsetX % (int)(_imageInfo->width * ratio)));
//	if (offsetY < 0) offsetY = (int)(_imageInfo->height * ratio + (offsetY % (int)(_imageInfo->height * ratio)));
//
//	// 그려지는 영역 세팅
//	RECT rcSour;
//	int sourWidth;
//	int sourHeight;
//
//	// 그려지는 DC영역(화면 크기)
//	RECT rcDest;
//
//	// 그려야 할 전체 영역
//	int drawAreaX = drawArea->left;
//	int drawAreaY = drawArea->top;
//	int drawAreaW = (drawArea->right - drawArea->left);
//	int drawAreaH = (drawArea->bottom - drawArea->top);
//
//	// 세로 루프영역
//	int y; int x;
//	for (y = 0; y < drawAreaH; y += sourHeight)
//	{
//		// 소스 영역의 높이 계산
//		rcSour.top = (int)(y + offsetY) % (int)(_imageInfo->height * ratio);
//		rcSour.bottom = (int)(_imageInfo->height * ratio);
//		sourHeight = rcSour.bottom - rcSour.top;
//
//		// 소스 영역이 그리는 화면을 넘어갔다면
//		if (y + sourHeight > (int)(drawAreaH * ratio))
//		{
//			// 넘어간 그림의 값 만큼 bottom값 올려줌
//			rcSour.bottom -= (y + sourHeight) - drawAreaH;
//			sourHeight = rcSour.bottom - rcSour.top;
//		}
//		// 그려지는 영역
//		rcDest.top = y + drawAreaY;
//		rcDest.bottom = rcDest.top + sourHeight;
//
//		// 가로 루프영역
//		for (x = 0; x < drawAreaW; x += sourWidth)
//		{
//			// 소스 영역의 너비 계산
//			rcSour.left = (int)(x + offsetX) % (int)(_imageInfo->width * ratio);
//			rcSour.right = (int)(_imageInfo->width * ratio);
//			sourWidth = rcSour.right - rcSour.left;
//
//			// 소스 영역이 그리는 화면을 넘어갔다면
//			if (x + sourWidth > (int)(drawAreaW * ratio))
//			{
//				// 넘어간 그림의 값 만큼 right값 올려줌
//				rcSour.right -= (x + sourWidth) - drawAreaW;
//				sourWidth = rcSour.right - rcSour.left;
//			}
//
//			// 그려지는 영역
//			rcDest.left = x + drawAreaX;
//			rcDest.right = rcDest.left + sourWidth;
//
//			// **핵심** //
//			// Render(stretch) - 이미지 잘라서 붙이기 - 개선필요
//			render(hdc,
//				rcDest.left, rcDest.top, 
//				x == 0 ? (int)(rcSour.left / ratio) : rcSour.left,
//				y == 0 ? (int)(rcSour.top / ratio) : rcSour.top,
//				(int)(sourWidth / ratio), (int)(sourHeight / ratio), ratio);
//		}
//	}
//}
//
//void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
//{
//}
//
//void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
//{
//	render(hdc, destX, destY,
//		ani->getFramePos().x, ani->getFramePos().y,
//		ani->getFrameWidth(), ani->getFrameHeight());
//}



//D3DCOLORVALUE image::getBitmapPixel(POINT pos)
//{
//	IWICBitmapLock * bLock;
//	BYTE buffer[4];
//	WICRect rc;
//	rc.X = pos.x; rc.Width = 1;
//	rc.Y = pos.y; rc.Height = 1;
//
//	HRESULT hr = IWICBitmap::Lock(&rc, WICBitmapLockRead, &bLock);
//	bLock->GetDataPointer()
//
//	return D3DCOLORVALUE();
//}
