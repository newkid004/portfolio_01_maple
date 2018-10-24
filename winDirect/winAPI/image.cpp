#include "stdafx.h"
#include "image.h"
#include "animation.h"

// ���ĺ��带 ����ϱ� ���� ���̺귯�� �߰�
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

	// ���� �б�
	if (S_OK != (hr =IMAGEMANAGER->getFactory()->CreateDecoderFromFilename(_fileName.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &decoder))) return hr;

	// ������ ���� �ؼ� ���ڴ�
	decoder->GetFrame(0, &fDecoder);

	// �̹��� ���� ��ȯ
	if (S_OK != (hr = IMAGEMANAGER->getFactory()->CreateFormatConverter(&converter))) return hr;
	if (S_OK != (hr = converter->Initialize(fDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom))) return hr;

	// D2D�� ��Ʈ�� ����
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
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;

	// �����ӹ��� ���� �ʱ�ȭ
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;

	//�����̸�
	_fileName = fileName;

	// ���ҽ� �Է�
	_putImage();

	//���ҽ� �����µ� ����������
	if (_imageInfo->bitmap == 0)
	{
		release();
		return E_FAIL;
	}

	// �̹��� ���� �Է�
	_putImageInfo();

	return S_OK;
}

HRESULT image::init(const wchar_t * fileName, int maxFrameX, int maxFrameY)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;

	// �����ӹ��� ���� �ʱ�ȭ
	_imageInfo->maxFrameX = maxFrameX;
	_imageInfo->maxFrameY = maxFrameY;

	//�����̸�
	_fileName = fileName;

	//���ҽ� �Է�
	if (S_OK != _putImage())
	{
		release();
		return E_FAIL;
	}

	// �̹��� ���� �Է�
	_putImageInfo();

	return S_OK;
}

void image::release(void)
{
	//�̹��� ������ ���� �ִٸ� ����
	if (_imageInfo)
	{
		//�̹��� ����
		_imageInfo->bitmap->Release();

		//������ ����
		SAFE_DELETE(_imageInfo);
	}
}


//���� (0, 0������ ����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� ratio��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			0,														//����� ��ǥ ����x
//			0,														//����� ��ǥ ����y
//			(int)(_imageInfo->width * ratio),						//����� �̹��� ����ũ��
//			(int)(_imageInfo->height * ratio),						//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->width * ratio),						//���� ���� ����ũ��
//			(int)(_imageInfo->height * ratio),						//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
////���� (���� ������ ��ǥ�� �̹��� ���)
//void image::render(HDC hdc, int destX, int destY)
//{
//	if (_isTrans)
//	{
//		GdiTransparentBlt(
//			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,					//����� ��ǥ ����x
//			destY,					//����� ��ǥ ����y
//			_imageInfo->width,		//����� �̹��� ����ũ��
//			_imageInfo->height,		//����� �̹��� ����ũ��
//			_imageInfo->hMemDC,		//����� ��� �޸�DC
//			0, 0,					//���� ��������
//			_imageInfo->width,		//���� ���� ����ũ��
//			_imageInfo->height,		//���� ���� ����ũ��
//			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
//		);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC, 0, 0, SRCCOPY);
//	}
//}
//
//// �̹��� Ŭ����
//// ���� �̹��� ���� ��ǥ�κ��� ����, ���� ũ�⸦ �߶� ���� ���ϴ°��� ���
//void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH)
//{
//	if (_isTrans)
//	{
//		GdiTransparentBlt(
//			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,					//����� ��ǥ ����x
//			destY,					//����� ��ǥ ����y
//			sourW,					//����� �̹��� ����ũ��
//			sourH,					//����� �̹��� ����ũ��
//			_imageInfo->hMemDC,		//����� ��� �޸�DC
//			sourX, sourY,			//���� ��������
//			sourW, sourH,			//���� ������
//			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//
//	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//	if (_isTrans)
//	{
//		// ����� ���� �̹����� flip��ġ�� ����
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
//			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,					//����� ��ǥ ����x
//			destY,					//����� ��ǥ ����y
//			sourW,					//����� �̹��� ����ũ��
//			sourH,					//����� �̹��� ����ũ��
//			_strchImage->hMemDC,	//����� ��� �޸�DC
//			0, 0,					//���� ��������
//			sourW, sourH,	//���� ������
//			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			(int)(_imageInfo->width * ratio),						//����� �̹��� ����ũ��
//			(int)(_imageInfo->height * ratio),						//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->width * ratio),						//���� ���� ����ũ��
//			(int)(_imageInfo->height * ratio),						//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			(int)(_imageInfo->width * ratioX),						//����� �̹��� ����ũ��
//			(int)(_imageInfo->height * ratioY),						//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->width * ratioX),						//���� ���� ����ũ��
//			(int)(_imageInfo->height * ratioY),						//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� ratio��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,										//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,										//����� ��ǥ ����x
//			destY,										//����� ��ǥ ����y
//			(int)(sourW * ratio),						//����� �̹��� ����ũ��
//			(int)(sourH * ratio),						//����� �̹��� ����ũ��
//			_strchImage->hMemDC,						//����� ��� �޸�DC
//			0, 0,
//			(int)(sourW * ratio),						//���� ���� ����ũ��
//			(int)(sourH * ratio),						//���� ���� ����ũ��
//			_transColor									//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� ratio��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,										//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,										//����� ��ǥ ����x
//			destY,										//����� ��ǥ ����y
//			(int)(sourW * ratioX),						//����� �̹��� ����ũ��
//			(int)(sourH * ratioY),						//����� �̹��� ����ũ��
//			_strchImage->hMemDC,						//����� ��� �޸�DC
//			0, 0,
//			(int)(sourW * ratioX),						//���� ���� ����ũ��
//			(int)(sourH * ratioY),						//���� ���� ����ũ��
//			_transColor									//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
//	if (!_blendImage) initForAlphaBlend();
//
//	// ���İ� �ʱ�ȭ
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	// ���� ���� �� ���ĺ��� �Ұ���?
//	if (_isTrans)
//	{
//		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׸�
//		BitBlt(_blendImage->hMemDC, 
//			0, 0, 
//			_imageInfo->width, _imageInfo->height,
//			hdc, 
//			0, 0, 
//			SRCCOPY);
//
//		// 2. �����̹����� ����� ���� �� ���� �̹����� ���
//		GdiTransparentBlt(
//			_blendImage->hMemDC,	//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			0, 0,					//����� ��ǥ ����
//			_imageInfo->width,		//����� �̹��� ����ũ��
//			_imageInfo->height,		//����� �̹��� ����ũ��
//			_blendImage->hMemDC,	//����� ��� �޸�DC
//			0, 0,					//���� ��������
//			_imageInfo->width,		//���� ���� ����ũ��
//			_imageInfo->height,		//���� ���� ����ũ��
//			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
//			);
//
//		// 3. ���� �̹����� ȭ�鿡 ���
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
//		// 3. ���� �̹����� ȭ�鿡 ���
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
//	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
//	if (!_blendImage) initForAlphaBlend();
//
//	// ���İ� �ʱ�ȭ
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	// ���� ���� �� ���ĺ��� �Ұ���?
//	if (_isTrans)
//	{
//		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׸�
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width, _imageInfo->height,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// 2. �����̹����� ����� ���� �� ���� �̹����� ���
//		GdiTransparentBlt(
//			_blendImage->hMemDC,	//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			0, 0,					//����� ��ǥ ����
//			_imageInfo->width,		//����� �̹��� ����ũ��
//			_imageInfo->height,		//����� �̹��� ����ũ��
//			_imageInfo->hMemDC,		//����� ��� �޸�DC
//			0, 0,					//���� ��������
//			_imageInfo->width,		//���� ���� ����ũ��
//			_imageInfo->height,		//���� ���� ����ũ��
//			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
//			);
//
//		// 3. ���� �̹����� ȭ�鿡 ���
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
//		// 3. ���� �̹����� ȭ�鿡 ���
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
//	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
//	if (!_blendImage) initForAlphaBlend();
//
//	// ���İ� �ʱ�ȭ
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	// ���� ���� �� ���ĺ��� �Ұ���?
//	if (_isTrans)
//	{
//		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׸�
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			sourW, sourH,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// 2. �����̹����� ����� ���� �� ���� �̹����� ���
//		GdiTransparentBlt(
//			_blendImage->hMemDC,	//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			0, 0,					//����� ��ǥ ����
//			sourW,					//����� �̹��� ����ũ��
//			sourH,					//����� �̹��� ����ũ��
//			_imageInfo->hMemDC,		//����� ��� �޸�DC
//			sourX, sourY,			//���� ��������
//			sourW,					//���� ���� ����ũ��
//			sourH,					//���� ���� ����ũ��
//			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
//			);
//
//		// 3. ���� �̹����� ȭ�鿡 ���
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
//		// 3. ���� �̹����� ȭ�鿡 ���
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
//	// �Ǵٸ� memDC ���
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
//		// hdc�̹��� ����
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			hdc,
//			0, 0,
//			SRCCOPY);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ����� flip�̹����� ���ĺ��� �̹����� ���
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
//		// ���ĺ��� �̹��� ���
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
//	// �Ǵٸ� memDC ���
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
//		// hdc�̹��� ����
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			_imageInfo->width,
//			_imageInfo->height,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ����� flip�̹����� ���ĺ��� �̹����� ���
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
//		// ���ĺ��� �̹��� ���
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
//	// �Ǵٸ� memDC ���
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
//		// hdc�̹��� ����
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ����� flip�̹����� ���ĺ��� �̹����� ���
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
//		// ���ĺ��� �̹��� ���
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//	// Use alphablend
//	if (!_blendImage) initForAlphaBlend();
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	if (_isTrans)
//	{
//		// hdc�̹��� ����
//		BitBlt(_blendImage->hMemDC,
//			0, 0,
//			sourW,
//			sourH,
//			hdc,
//			destX, destY,
//			SRCCOPY);
//
//		// ����� ���� �̹����� ratio��ġ�� ����
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
//		// ����� stretch�̹����� ���ĺ��� �̹����� ���
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
//		// ���ĺ��� �̹��� ���
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
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
//			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
//			_imageInfo->hMemDC,										//����� ��� �޸�DC
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,		// ������ x��ǥ
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,	// ������ y��ǥ
//			_imageInfo->frameWidth,									//���� ���� ����ũ��
//			_imageInfo->frameHeight,								//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
//			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
//			_imageInfo->hMemDC,										//����� ��� �޸�DC
//			_imageInfo->curruntFrameX * _imageInfo->frameWidth,		// ������ x��ǥ
//			_imageInfo->curruntFrameY * _imageInfo->frameHeight,	// ������ y��ǥ
//			_imageInfo->frameWidth,									//���� ���� ����ũ��
//			_imageInfo->frameHeight,								//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	if (_isTrans)
//	{
//		// ����� �̹��� ���� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
//			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			_imageInfo->frameWidth,									//���� ���� ����ũ��
//			_imageInfo->frameHeight,								//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
//			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			_imageInfo->frameWidth,									//���� ���� ����ũ��
//			_imageInfo->frameHeight,								//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
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
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
//			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			_imageInfo->frameWidth,									//���� ���� ����ũ��
//			_imageInfo->frameHeight,								//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			(int)(_imageInfo->frameWidth * ratio),					//����� �̹��� ����ũ��
//			(int)(_imageInfo->frameHeight * ratio),					//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratio),					//���� ���� ����ũ��
//			(int)(_imageInfo->frameHeight * ratio),					//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			(int)(_imageInfo->frameWidth * ratioX),					//����� �̹��� ����ũ��
//			(int)(_imageInfo->frameHeight * ratioY),				//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratioX),					//���� ���� ����ũ��
//			(int)(_imageInfo->frameHeight * ratioY),				//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			(int)(_imageInfo->frameWidth * ratio),					//����� �̹��� ����ũ��
//			(int)(_imageInfo->frameHeight * ratio),					//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratio),					//���� ���� ����ũ��
//			(int)(_imageInfo->frameHeight * ratio),					//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) { initForStretch(); SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR); }
//
//	setFrameX(curruntFrameX);
//	setFrameY(curruntFrameY);
//
//	if (_isTrans)
//	{
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			(int)(_imageInfo->frameWidth * ratioX),					//����� �̹��� ����ũ��
//			(int)(_imageInfo->frameHeight * ratioY),				//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratioX),					//���� ���� ����ũ��
//			(int)(_imageInfo->frameHeight * ratioY),				//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
//	if (!_strchImage) initForStretch();
//
//	int flipX = (0 < (flip & 0b10));
//	int flipY = (0 < (flip & 0b01));
//
//	if (_isTrans)
//	{
//		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);
//
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			(int)(_imageInfo->frameWidth * ratio),					//����� �̹��� ����ũ��
//			(int)(_imageInfo->frameHeight * ratio),					//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratio),					//���� ���� ����ũ��
//			(int)(_imageInfo->frameHeight * ratio),					//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// �Ǵٸ� memDC ���
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
//		// ����� ���� �̹����� flip��ġ�� ����
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
//		// ������ �̹����� ȭ�鿡 ���
//		GdiTransparentBlt(
//			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
//			destX,													//����� ��ǥ ����x
//			destY,													//����� ��ǥ ����y
//			(int)(_imageInfo->frameWidth * ratio),					//����� �̹��� ����ũ��
//			(int)(_imageInfo->frameHeight * ratio),					//����� �̹��� ����ũ��
//			_strchImage->hMemDC,									//����� ��� �޸�DC
//			0, 0,
//			(int)(_imageInfo->frameWidth * ratio),					//���� ���� ����ũ��
//			(int)(_imageInfo->frameHeight * ratio),					//���� ���� ����ũ��
//			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
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
//	// offset < 0 ����
//	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
//	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
//
//	// �׷����� ���� ����
//	RECT rcSour;
//	int sourWidth;
//	int sourHeight;
//
//	// �׷����� DC����(ȭ�� ũ��)
//	RECT rcDest;
//
//	// �׷��� �� ��ü ����
//	int drawAreaX = drawArea->left;
//	int drawAreaY = drawArea->top;
//	int drawAreaW = drawArea->right - drawArea->left;
//	int drawAreaH = drawArea->bottom - drawArea->top;
//
//	// ���� ��������
//	for (int y = 0; y < drawAreaH; y += sourHeight)
//	{
//		// �ҽ� ������ ���� ���
//		rcSour.top = (y + offsetY) % _imageInfo->height;
//		rcSour.bottom = _imageInfo->height;
//		sourHeight = rcSour.bottom - rcSour.top;
//
//		// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�
//		if (y + sourHeight > drawAreaH)
//		{
//			// �Ѿ �׸��� �� ��ŭ bottom�� �÷���
//			rcSour.bottom -= (y + sourHeight) - drawAreaH;
//			sourHeight = rcSour.bottom - rcSour.top;
//		}
//		// �׷����� ����
//		rcDest.top = y + drawAreaY;
//		rcDest.bottom = rcDest.top + sourHeight;
//
//		// ���� ��������
//		for (int x = 0; x < drawAreaW; x += sourWidth)
//		{
//			// �ҽ� ������ �ʺ� ���
//			rcSour.left = (x + offsetX) % _imageInfo->width;
//			rcSour.right = _imageInfo->width;
//			sourWidth = rcSour.right - rcSour.left;
//
//			// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�
//			if (x + sourWidth > drawAreaW)
//			{
//				// �Ѿ �׸��� �� ��ŭ right�� �÷���
//				rcSour.right -= (x + sourWidth) - drawAreaW;
//				sourWidth = rcSour.right - rcSour.left;
//			}
//
//			// �׷����� ����
//			rcDest.left = x + drawAreaX;
//			rcDest.right = rcDest.left + sourWidth;
//
//			// **�ٽ�** //
//			// �Ϲݷ��� - �̹��� �߶� ���̱�
//			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
//		}
//	}
//}
//
//void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio)
//{
//	// offset < 0 ����
//	if (offsetX < 0) offsetX = (int)(_imageInfo->width * ratio + (offsetX % (int)(_imageInfo->width * ratio)));
//	if (offsetY < 0) offsetY = (int)(_imageInfo->height * ratio + (offsetY % (int)(_imageInfo->height * ratio)));
//
//	// �׷����� ���� ����
//	RECT rcSour;
//	int sourWidth;
//	int sourHeight;
//
//	// �׷����� DC����(ȭ�� ũ��)
//	RECT rcDest;
//
//	// �׷��� �� ��ü ����
//	int drawAreaX = drawArea->left;
//	int drawAreaY = drawArea->top;
//	int drawAreaW = (drawArea->right - drawArea->left);
//	int drawAreaH = (drawArea->bottom - drawArea->top);
//
//	// ���� ��������
//	int y; int x;
//	for (y = 0; y < drawAreaH; y += sourHeight)
//	{
//		// �ҽ� ������ ���� ���
//		rcSour.top = (int)(y + offsetY) % (int)(_imageInfo->height * ratio);
//		rcSour.bottom = (int)(_imageInfo->height * ratio);
//		sourHeight = rcSour.bottom - rcSour.top;
//
//		// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�
//		if (y + sourHeight > (int)(drawAreaH * ratio))
//		{
//			// �Ѿ �׸��� �� ��ŭ bottom�� �÷���
//			rcSour.bottom -= (y + sourHeight) - drawAreaH;
//			sourHeight = rcSour.bottom - rcSour.top;
//		}
//		// �׷����� ����
//		rcDest.top = y + drawAreaY;
//		rcDest.bottom = rcDest.top + sourHeight;
//
//		// ���� ��������
//		for (x = 0; x < drawAreaW; x += sourWidth)
//		{
//			// �ҽ� ������ �ʺ� ���
//			rcSour.left = (int)(x + offsetX) % (int)(_imageInfo->width * ratio);
//			rcSour.right = (int)(_imageInfo->width * ratio);
//			sourWidth = rcSour.right - rcSour.left;
//
//			// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�
//			if (x + sourWidth > (int)(drawAreaW * ratio))
//			{
//				// �Ѿ �׸��� �� ��ŭ right�� �÷���
//				rcSour.right -= (x + sourWidth) - drawAreaW;
//				sourWidth = rcSour.right - rcSour.left;
//			}
//
//			// �׷����� ����
//			rcDest.left = x + drawAreaX;
//			rcDest.right = rcDest.left + sourWidth;
//
//			// **�ٽ�** //
//			// Render(stretch) - �̹��� �߶� ���̱� - �����ʿ�
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
