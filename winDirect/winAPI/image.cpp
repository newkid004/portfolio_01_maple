#include "stdafx.h"
#include "image.h"
#include "animation.h"

// ���ĺ��带 ����ϱ� ���� ���̺귯�� �߰�
#pragma comment(lib, "msimg32.lib")

image::image() : _imageInfo(NULL)
			   , _fileName(NULL)
			   , _isTrans(FALSE)
			   , _transColor(RGB(0, 0, 0))
			   , _strchImage(NULL)
			   , _blendImage(NULL)
{
}

//�� ��Ʈ������ �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// �����ӹ��� ���� �ʱ�ȭ
	_imageInfo->curruntFrameX = 0;
	_imageInfo->curruntFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ���ҽ��� �ʱ�ȭ
HRESULT image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// �����ӹ��� ���� �ʱ�ȭ
	_imageInfo->curruntFrameX = 0;
	_imageInfo->curruntFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ���Ϸ� �ʱ�ȭ
HRESULT image::init(const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// �����ӹ��� ���� �ʱ�ȭ
	_imageInfo->curruntFrameX = 0;
	_imageInfo->curruntFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	// �����ӹ��� ���� �ʱ�ȭ
	_imageInfo->curruntFrameX = 0;
	_imageInfo->curruntFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->curruntFrameX = 0;
	_imageInfo->curruntFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->curruntFrameX = 0;
	_imageInfo->curruntFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForStretch(void)
{
	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	if (_strchImage == NULL)
		_strchImage = new IMAGE_INFO;
	_strchImage->loadType = LOAD_FILE;
	_strchImage->resID = 0;
	_strchImage->hMemDC = CreateCompatibleDC(hdc);
	_strchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX_R, WINSIZEY_R);
	_strchImage->hOBit = (HBITMAP)SelectObject(_strchImage->hMemDC, _strchImage->hBit);
	_strchImage->width = WINSIZEX_R;
	_strchImage->height = WINSIZEY_R;

	// DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForAlphaBlend(void)
{
	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// ���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;			// ��κ� ���� (0)
	_blendFunc.AlphaFormat = 0;			// (���� ��)�ҽ��� �ۼ��� ��Ʈ�� �ڵ�� ���� ��Ʈ���� ������ �ִ� �ȼ��� �ؼ��ϴ� ����� ����
	_blendFunc.BlendOp = AC_SRC_OVER;	// ��κ� ����

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	if (_blendImage == NULL)
		_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = _imageInfo->width;
	_blendImage->height = _imageInfo->height;

	// DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//���� �÷�Ű ���� (���� ��������, �����)
void image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

void image::release(void)
{
	//�̹��� ������ ���� �ִٸ� ����
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//�����÷�Ű �ʱ�ȭ
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	// stretch�̹��� ����
	if (_strchImage)
	{
		// �̹��� ����
		SelectObject(_strchImage->hMemDC, _strchImage->hOBit);
		DeleteObject(_strchImage->hBit);
		DeleteDC(_strchImage->hMemDC);
		
		// ������ ����
		SAFE_DELETE(_strchImage);
	}

	// �����̹��� ����
	if (_blendImage)
	{
		// �̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		
		// ������ ����
		SAFE_DELETE(_blendImage);
	}
}

//���� (0, 0������ ����)
void image::render(HDC hdc)
{
	if (_isTrans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			0,						//����� ��ǥ ����x
			0,						//����� ��ǥ ����y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, float ratio)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� ratio��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			0, 0,
			(int)(_imageInfo->width * ratio),
			(int)(_imageInfo->height * ratio),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			0,														//����� ��ǥ ����x
			0,														//����� ��ǥ ����y
			(int)(_imageInfo->width * ratio),						//����� �̹��� ����ũ��
			(int)(_imageInfo->height * ratio),						//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->width * ratio),						//���� ���� ����ũ��
			(int)(_imageInfo->height * ratio),						//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			0, 0,
			(int)(_imageInfo->width * ratio),
			(int)(_imageInfo->height * ratio),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);
	}
}

//���� (���� ������ ��ǥ�� �̹��� ���)
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,					//����� ��ǥ ����x
			destY,					//����� ��ǥ ����y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

// �̹��� Ŭ����
// ���� �̹��� ���� ��ǥ�κ��� ����, ���� ũ�⸦ �߶� ���� ���ϴ°��� ���
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH)
{
	if (_isTrans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,					//����� ��ǥ ����x
			destY,					//����� ��ǥ ����y
			sourW,					//����� �̹��� ����ũ��
			sourH,					//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			sourX, sourY,			//���� ��������
			sourW, sourH,			//���� ������
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		BitBlt(hdc, destX, destY, sourW, sourH,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, int flip)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	int flipX = (0 < (flip & 0b10));
	int flipY = (0 < (flip & 0b01));

	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

	if (_isTrans)
	{
		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			sourW	* flipX - flipX,
			sourH	* flipY - flipY,
			sourW	* (flipX ? -1 : 1),
			sourH	* (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			sourX, sourY,
			sourW, sourH,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,					//����� ��ǥ ����x
			destY,					//����� ��ǥ ����y
			sourW,					//����� �̹��� ����ũ��
			sourH,					//����� �̹��� ����ũ��
			_strchImage->hMemDC,	//����� ��� �޸�DC
			0, 0,					//���� ��������
			sourW, sourH,	//���� ������
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(sourW - sourX) * flipX - flipX,
			(sourH - sourY) * flipY - flipY,
			(sourW - sourX) * (flipX ? -1 : 1),
			(sourH - sourY) * (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			sourX, sourY,
			sourW, sourH,
			SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, float ratio)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(_imageInfo->width * (ratio < 0 ? -ratio : 0)),
			(int)(_imageInfo->height * (ratio < 0 ? -ratio : 0)),
			(int)(_imageInfo->width * ratio),
			(int)(_imageInfo->height * ratio),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			(int)(_imageInfo->width * ratio),						//����� �̹��� ����ũ��
			(int)(_imageInfo->height * ratio),						//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->width * ratio),						//���� ���� ����ũ��
			(int)(_imageInfo->height * ratio),						//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + _imageInfo->width * (ratio < 0 ? -ratio : 0)),
			(int)(destY + _imageInfo->height * (ratio < 0 ? -ratio : 0)),
			(int)(_imageInfo->width * ratio),
			(int)(_imageInfo->height * ratio),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, float ratioX, float ratioY)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(_imageInfo->width * (ratioX < 0 ? -ratioX : 0)),
			(int)(_imageInfo->height * (ratioY < 0 ? -ratioY : 0)),
			(int)(_imageInfo->width * ratioX),
			(int)(_imageInfo->height * ratioY),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			(int)(_imageInfo->width * ratioX),						//����� �̹��� ����ũ��
			(int)(_imageInfo->height * ratioY),						//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->width * ratioX),						//���� ���� ����ũ��
			(int)(_imageInfo->height * ratioY),						//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + _imageInfo->width * (ratioX < 0 ? -ratioX : 0)),
			(int)(destY + _imageInfo->height * (ratioY < 0 ? -ratioY : 0)),
			(int)(_imageInfo->width * ratioX),
			(int)(_imageInfo->height * ratioY),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratio)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� ratio��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(sourW * (ratio < 0 ? -ratio : 0)),
			(int)(sourH * (ratio < 0 ? -ratio : 0)),
			(int)(sourW * ratio),
			(int)(sourH * ratio),
			_imageInfo->hMemDC,
			sourX, sourY,
			sourW, sourH,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,										//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,										//����� ��ǥ ����x
			destY,										//����� ��ǥ ����y
			(int)(sourW * ratio),						//����� �̹��� ����ũ��
			(int)(sourH * ratio),						//����� �̹��� ����ũ��
			_strchImage->hMemDC,						//����� ��� �޸�DC
			0, 0,
			(int)(sourW * ratio),						//���� ���� ����ũ��
			(int)(sourH * ratio),						//���� ���� ����ũ��
			_transColor									//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + (ratio < 0 ? sourW * (-ratio) : 0)),
			(int)(destY + (ratio < 0 ? sourH * (-ratio) : 0)),
			(int)(sourW * ratio),
			(int)(sourH * ratio),
			_imageInfo->hMemDC,
			sourX, sourY,
			sourW, sourH,
			SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratioX, float ratioY)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� ratio��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(sourW * (ratioX < 0 ? -ratioX : 0)),
			(int)(sourH * (ratioY < 0 ? -ratioY : 0)),
			(int)(sourW * ratioX),
			(int)(sourH * ratioY),
			_imageInfo->hMemDC,
			sourX, sourY,
			sourW, sourH,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,										//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,										//����� ��ǥ ����x
			destY,										//����� ��ǥ ����y
			(int)(sourW * ratioX),						//����� �̹��� ����ũ��
			(int)(sourH * ratioY),						//����� �̹��� ����ũ��
			_strchImage->hMemDC,						//����� ��� �޸�DC
			0, 0,
			(int)(sourW * ratioX),						//���� ���� ����ũ��
			(int)(sourH * ratioY),						//���� ���� ����ũ��
			_transColor									//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + (ratioX < 0 ? sourW * (-ratioX) : 0)),
			(int)(destY + (ratioY < 0 ? sourH * (-ratioY) : 0)),
			(int)(sourW * ratioX),
			(int)(sourH * ratioY),
			_imageInfo->hMemDC,
			sourX, sourY,
			sourW, sourH,
			SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
	if (!_blendImage) initForAlphaBlend();

	// ���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	// ���� ���� �� ���ĺ��� �Ұ���?
	if (_isTrans)
	{
		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׸�
		BitBlt(_blendImage->hMemDC, 
			0, 0, 
			_imageInfo->width, _imageInfo->height,
			hdc, 
			0, 0, 
			SRCCOPY);

		// 2. �����̹����� ����� ���� �� ���� �̹����� ���
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			0, 0,					//����� ��ǥ ����
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_blendImage->hMemDC,	//����� ��� �޸�DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);

		// 3. ���� �̹����� ȭ�鿡 ���
		AlphaBlend(hdc,
			0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, 
			_blendFunc);
	}
	else
	{
		// 3. ���� �̹����� ȭ�鿡 ���
		AlphaBlend(hdc,
			0, 0,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
	if (!_blendImage) initForAlphaBlend();

	// ���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	// ���� ���� �� ���ĺ��� �Ұ���?
	if (_isTrans)
	{
		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׸�
		BitBlt(_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. �����̹����� ����� ���� �� ���� �̹����� ���
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			0, 0,					//����� ��ǥ ����
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);

		// 3. ���� �̹����� ȭ�鿡 ���
		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		// 3. ���� �̹����� ȭ�鿡 ���
		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha)
{
	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
	if (!_blendImage) initForAlphaBlend();

	// ���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	// ���� ���� �� ���ĺ��� �Ұ���?
	if (_isTrans)
	{
		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׸�
		BitBlt(_blendImage->hMemDC,
			0, 0,
			sourW, sourH,
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. �����̹����� ����� ���� �� ���� �̹����� ���
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			0, 0,					//����� ��ǥ ����
			sourW,					//����� �̹��� ����ũ��
			sourH,					//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			sourX, sourY,			//���� ��������
			sourW,					//���� ���� ����ũ��
			sourH,					//���� ���� ����ũ��
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);

		// 3. ���� �̹����� ȭ�鿡 ���
		AlphaBlend(hdc,
			destX, destY,
			sourW, sourH,
			_blendImage->hMemDC,
			0, 0,
			sourW, sourH,
			_blendFunc);
	}
	else
	{
		// 3. ���� �̹����� ȭ�鿡 ���
		AlphaBlend(hdc,
			destX, destY,
			sourW, sourH,
			_imageInfo->hMemDC,
			0, 0,
			sourW, sourH,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha, int flip)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();
	int flipX = (0 < (flip & 0b10));
	int flipY = (0 < (flip & 0b01));
	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

	// Use alphablend
	if (!_blendImage) initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// hdc�̹��� ����
		BitBlt(_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			_imageInfo->width	* flipX - flipX,
			_imageInfo->height	* flipY - flipY,
			_imageInfo->width	* (flipX ? -1 : 1),
			_imageInfo->height	* (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);

		// ����� flip�̹����� ���ĺ��� �̹����� ���
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_strchImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
			);

		// ���ĺ��� �̹��� ���
		AlphaBlend(hdc,
			0, 0,
			_imageInfo->width, 
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, 
			_imageInfo->height,
			_blendFunc);
	}
	else
	{
		StretchBlt(_blendImage->hMemDC,
			_imageInfo->width	* flipX - flipX,
			_imageInfo->height	* flipY - flipY,
			_imageInfo->width	* (flipX ? -1 : 1),
			_imageInfo->height	* (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);

		AlphaBlend(hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha, int flip)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();
	int flipX = (0 < (flip & 0b10));
	int flipY = (0 < (flip & 0b01));
	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

	// Use alphablend
	if (!_blendImage) initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// hdc�̹��� ����
		BitBlt(_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			_imageInfo->width	* flipX - flipX,
			_imageInfo->height	* flipY - flipY,
			_imageInfo->width	* (flipX ? -1 : 1),
			_imageInfo->height	* (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);

		// ����� flip�̹����� ���ĺ��� �̹����� ���
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_strchImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
			);

		// ���ĺ��� �̹��� ���
		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc);
	}
	else
	{
		StretchBlt(_blendImage->hMemDC,
			_imageInfo->width	* flipX - flipX,
			_imageInfo->height	* flipY - flipY,
			_imageInfo->width	* (flipX ? -1 : 1),
			_imageInfo->height	* (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);

		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, int flip)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();
	int flipX = (0 < (flip & 0b10));
	int flipY = (0 < (flip & 0b01));
	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

	// Use alphablend
	if (!_blendImage) initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// hdc�̹��� ����
		BitBlt(_blendImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			hdc,
			destX, destY,
			SRCCOPY);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			sourW	* flipX - flipX,
			sourH	* flipY - flipY,
			sourW	* (flipX ? -1 : 1),
			sourH	* (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			sourX, 
			sourY,
			sourW,
			sourH,
			SRCCOPY);

		// ����� flip�̹����� ���ĺ��� �̹����� ���
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			_strchImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			_transColor
			);

		// ���ĺ��� �̹��� ���
		AlphaBlend(hdc,
			destX, destY,
			sourW,
			sourH,
			_blendImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			_blendFunc);
	}
	else
	{
		StretchBlt(_blendImage->hMemDC,
			sourW	* flipX - flipX,
			sourH	* flipY - flipY,
			sourW	* (flipX ? -1 : 1),
			sourH	* (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			sourX,
			sourY,
			sourW,
			sourH,
			SRCCOPY);

		AlphaBlend(hdc,
			destX, destY,
			sourW,
			sourH,
			_blendImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, float ratioX, float ratioY)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();
	SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

	// Use alphablend
	if (!_blendImage) initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// hdc�̹��� ����
		BitBlt(_blendImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			hdc,
			destX, destY,
			SRCCOPY);

		// ����� ���� �̹����� ratio��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(sourW * (ratioX < 0 ? -ratioX : 0)),
			(int)(sourH * (ratioY < 0 ? -ratioY : 0)),
			(int)(sourW * ratioX),
			(int)(sourH * ratioY),
			_imageInfo->hMemDC,
			sourX, sourY,
			sourW, sourH,
			SRCCOPY);

		// ����� stretch�̹����� ���ĺ��� �̹����� ���
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			_strchImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			_transColor
			);

		// ���ĺ��� �̹��� ���
		AlphaBlend(hdc,
			destX, destY,
			sourW,
			sourH,
			_blendImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			_blendFunc);
	}
	else
	{
		StretchBlt(_blendImage->hMemDC,
			(int)(sourW * (ratioX < 0 ? -ratioX : 0)),
			(int)(sourH * (ratioY < 0 ? -ratioY : 0)),
			(int)(sourW * ratioX),
			(int)(sourH * ratioY),
			_imageInfo->hMemDC,
			sourX,
			sourY,
			sourW,
			sourH,
			SRCCOPY);

		AlphaBlend(hdc,
			destX, destY,
			sourW,
			sourH,
			_blendImage->hMemDC,
			0, 0,
			sourW,
			sourH,
			_blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_imageInfo->hMemDC,										//����� ��� �޸�DC
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,		// ������ x��ǥ
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,	// ������ y��ǥ
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->curruntFrameX * _imageInfo->frameWidth, 
			_imageInfo->curruntFrameY * _imageInfo->frameHeight, 
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY)
{
	setFrameX(curruntFrameX);
	setFrameY(curruntFrameY);

	if (_isTrans)
	{
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_imageInfo->hMemDC,										//����� ��� �޸�DC
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,		// ������ x��ǥ
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,	// ������ y��ǥ
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, COLORREF changeColor, COLORREF renderColor)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	setFrameX(curruntFrameX);
	setFrameY(curruntFrameY);

	if (_isTrans)
	{
		// ����� �̹��� ���� ����
		HBRUSH hBrush = CreateSolidBrush(renderColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_strchImage->hMemDC, hBrush);
		FillRect(_strchImage->hMemDC, &RectMake(0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight), hBrush);
		SelectObject(_strchImage->hMemDC, oBrush);
		DeleteObject(hBrush);

		GdiTransparentBlt(
			_strchImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			changeColor
			);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int flip)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	int flipX = (0 < (flip & 0b10));
	int flipY = (0 < (flip & 0b01));

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			_imageInfo->frameWidth * flipX - flipX,
			_imageInfo->frameHeight * flipY - flipY,
			_imageInfo->frameWidth * (flipX ? -1 : 1),
			_imageInfo->frameHeight * (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			destX + _imageInfo->frameWidth * flipX - flipX,
			destY + _imageInfo->frameHeight * flipY - flipY,
			_imageInfo->frameWidth * (flipX ? -1 : 1),
			_imageInfo->frameHeight * (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, int flip)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	setFrameX(curruntFrameX);
	setFrameY(curruntFrameY);

	int flipX = (0 < (flip & 0b10));
	int flipY = (0 < (flip & 0b01));

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			_imageInfo->frameWidth * flipX - flipX,
			_imageInfo->frameHeight * flipY - flipY,
			_imageInfo->frameWidth * (flipX ? -1 : 1),
			_imageInfo->frameHeight * (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			destX + _imageInfo->frameWidth * flipX - flipX,
			destY + _imageInfo->frameHeight * flipY - flipY,
			_imageInfo->frameWidth * (flipX ? -1 : 1),
			_imageInfo->frameHeight * (flipY ? -1 : 1),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, float ratio)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(_imageInfo->frameWidth * ratio < 0 ? -ratio : 0),
			(int)(_imageInfo->frameHeight * ratio < 0 ? -ratio : 0),
			(int)(_imageInfo->frameWidth * ratio),
			(int)(_imageInfo->frameHeight * ratio),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			(int)(_imageInfo->frameWidth * ratio),					//����� �̹��� ����ũ��
			(int)(_imageInfo->frameHeight * ratio),					//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->frameWidth * ratio),					//���� ���� ����ũ��
			(int)(_imageInfo->frameHeight * ratio),					//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + _imageInfo->frameWidth * ratio < 0 ? -ratio : 0),
			(int)(destY + _imageInfo->frameHeight * ratio < 0 ? -ratio : 0),
			(int)(_imageInfo->frameWidth * ratio),
			(int)(_imageInfo->frameHeight * ratio),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, float ratioX, float ratioY)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(_imageInfo->frameWidth * ratioX < 0 ? -ratioX : 0),
			(int)(_imageInfo->frameHeight * ratioY < 0 ? -ratioY : 0),
			(int)(_imageInfo->frameWidth * ratioX),
			(int)(_imageInfo->frameHeight * ratioY),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			(int)(_imageInfo->frameWidth * ratioX),					//����� �̹��� ����ũ��
			(int)(_imageInfo->frameHeight * ratioY),				//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->frameWidth * ratioX),					//���� ���� ����ũ��
			(int)(_imageInfo->frameHeight * ratioY),				//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + _imageInfo->frameWidth * ratioX < 0 ? -ratioX : 0),
			(int)(destY + _imageInfo->frameHeight * ratioY < 0 ? -ratioY : 0),
			(int)(_imageInfo->frameWidth * ratioX),
			(int)(_imageInfo->frameHeight * ratioY),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	setFrameX(curruntFrameX);
	setFrameY(curruntFrameY);

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(_imageInfo->frameWidth * ratio < 0 ? -ratio : 0),
			(int)(_imageInfo->frameHeight * ratio < 0 ? -ratio : 0),
			(int)(_imageInfo->frameWidth * ratio),
			(int)(_imageInfo->frameHeight * ratio),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			(int)(_imageInfo->frameWidth * ratio),					//����� �̹��� ����ũ��
			(int)(_imageInfo->frameHeight * ratio),					//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->frameWidth * ratio),					//���� ���� ����ũ��
			(int)(_imageInfo->frameHeight * ratio),					//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + _imageInfo->frameWidth * ratio < 0 ? -ratio : 0),
			(int)(destY + _imageInfo->frameHeight * ratio < 0 ? -ratio : 0),
			(int)(_imageInfo->frameWidth * ratio),
			(int)(_imageInfo->frameHeight * ratio),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratioX, float ratioY)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) { initForStretch(); SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR); }

	setFrameX(curruntFrameX);
	setFrameY(curruntFrameY);

	if (_isTrans)
	{
		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(_imageInfo->frameWidth * (ratioX < 0 ? -ratioX : 0)),
			(int)(_imageInfo->frameHeight * (ratioY < 0 ? -ratioY : 0)),
			(int)(_imageInfo->frameWidth * ratioX),
			(int)(_imageInfo->frameHeight * ratioY),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			(int)(_imageInfo->frameWidth * ratioX),					//����� �̹��� ����ũ��
			(int)(_imageInfo->frameHeight * ratioY),				//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->frameWidth * ratioX),					//���� ���� ����ũ��
			(int)(_imageInfo->frameHeight * ratioY),				//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + _imageInfo->frameWidth * (ratioX < 0 ? -ratioX : 0)),
			(int)(destY + _imageInfo->frameHeight * (ratioY < 0 ? -ratioY : 0)),
			(int)(_imageInfo->frameWidth * ratioX),
			(int)(_imageInfo->frameHeight * ratioY),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, float ratio, int flip)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	int flipX = (0 < (flip & 0b10));
	int flipY = (0 < (flip & 0b01));

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(_imageInfo->frameWidth * ratio * flipX - flipX),
			(int)(_imageInfo->frameHeight * ratio * flipY - flipY),
			(int)(_imageInfo->frameWidth * ratio * (flipX ? -1 : 1)),
			(int)(_imageInfo->frameHeight * ratio * (flipY ? -1 : 1)),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			(int)(_imageInfo->frameWidth * ratio),					//����� �̹��� ����ũ��
			(int)(_imageInfo->frameHeight * ratio),					//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->frameWidth * ratio),					//���� ���� ����ũ��
			(int)(_imageInfo->frameHeight * ratio),					//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + _imageInfo->frameWidth * ratio * flipX - flipX),
			(int)(destY + _imageInfo->frameHeight * ratio * flipY - flipY),
			(int)(_imageInfo->frameWidth * ratio * (flipX ? -1 : 1)),
			(int)(_imageInfo->frameHeight * ratio * (flipY ? -1 : 1)),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio, int flip)
{
	// �Ǵٸ� memDC ���
	if (!_strchImage) initForStretch();

	setFrameX(curruntFrameX);
	setFrameY(curruntFrameY);

	int flipX = (0 < (flip & 0b10));
	int flipY = (0 < (flip & 0b01));

	if (_isTrans)
	{
		SetStretchBltMode(_strchImage->hMemDC, COLORONCOLOR);

		// ����� ���� �̹����� flip��ġ�� ����
		StretchBlt(_strchImage->hMemDC,
			(int)(_imageInfo->frameWidth * ratio * flipX - flipX),
			(int)(_imageInfo->frameHeight * ratio * flipY - flipY),
			(int)(_imageInfo->frameWidth * ratio * (flipX ? -1 : 1)),
			(int)(_imageInfo->frameHeight * ratio * (flipY ? -1 : 1)),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);

		// ������ �̹����� ȭ�鿡 ���
		GdiTransparentBlt(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX,													//����� ��ǥ ����x
			destY,													//����� ��ǥ ����y
			(int)(_imageInfo->frameWidth * ratio),					//����� �̹��� ����ũ��
			(int)(_imageInfo->frameHeight * ratio),					//����� �̹��� ����ũ��
			_strchImage->hMemDC,									//����� ��� �޸�DC
			0, 0,
			(int)(_imageInfo->frameWidth * ratio),					//���� ���� ����ũ��
			(int)(_imageInfo->frameHeight * ratio),					//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
			);
	}
	else
	{
		StretchBlt(hdc,
			(int)(destX + _imageInfo->frameWidth * ratio * flipX - flipX),
			(int)(destY + _imageInfo->frameHeight * ratio * flipY - flipY),
			(int)(_imageInfo->frameWidth * ratio * (flipX ? -1 : 1)),
			(int)(_imageInfo->frameHeight * ratio * (flipY ? -1 : 1)),
			_imageInfo->hMemDC,
			_imageInfo->curruntFrameX * _imageInfo->frameWidth,
			_imageInfo->curruntFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	// offset < 0 ����
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	// �׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// �׷����� DC����(ȭ�� ũ��)
	RECT rcDest;

	// �׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	// ���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		// �ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�
		if (y + sourHeight > drawAreaH)
		{
			// �Ѿ �׸��� �� ��ŭ bottom�� �÷���
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		// �׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// ���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			// �ҽ� ������ �ʺ� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�
			if (x + sourWidth > drawAreaW)
			{
				// �Ѿ �׸��� �� ��ŭ right�� �÷���
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			// �׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			// **�ٽ�** //
			// �Ϲݷ��� - �̹��� �߶� ���̱�
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio)
{
	// offset < 0 ����
	if (offsetX < 0) offsetX = (int)(_imageInfo->width * ratio + (offsetX % (int)(_imageInfo->width * ratio)));
	if (offsetY < 0) offsetY = (int)(_imageInfo->height * ratio + (offsetY % (int)(_imageInfo->height * ratio)));

	// �׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// �׷����� DC����(ȭ�� ũ��)
	RECT rcDest;

	// �׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = (drawArea->right - drawArea->left);
	int drawAreaH = (drawArea->bottom - drawArea->top);

	// ���� ��������
	int y; int x;
	for (y = 0; y < drawAreaH; y += sourHeight)
	{
		// �ҽ� ������ ���� ���
		rcSour.top = (int)(y + offsetY) % (int)(_imageInfo->height * ratio);
		rcSour.bottom = (int)(_imageInfo->height * ratio);
		sourHeight = rcSour.bottom - rcSour.top;

		// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�
		if (y + sourHeight > (int)(drawAreaH * ratio))
		{
			// �Ѿ �׸��� �� ��ŭ bottom�� �÷���
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		// �׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// ���� ��������
		for (x = 0; x < drawAreaW; x += sourWidth)
		{
			// �ҽ� ������ �ʺ� ���
			rcSour.left = (int)(x + offsetX) % (int)(_imageInfo->width * ratio);
			rcSour.right = (int)(_imageInfo->width * ratio);
			sourWidth = rcSour.right - rcSour.left;

			// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�
			if (x + sourWidth > (int)(drawAreaW * ratio))
			{
				// �Ѿ �׸��� �� ��ŭ right�� �÷���
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			// �׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			// **�ٽ�** //
			// Render(stretch) - �̹��� �߶� ���̱� - �����ʿ�
			render(hdc,
				rcDest.left, rcDest.top, 
				x == 0 ? (int)(rcSour.left / ratio) : rcSour.left,
				y == 0 ? (int)(rcSour.top / ratio) : rcSour.top,
				(int)(sourWidth / ratio), (int)(sourHeight / ratio), ratio);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX, destY,
		ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}
