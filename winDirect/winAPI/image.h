#pragma once

// Ŭ���� ���漱��
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
		ID2D1Bitmap*	bitmap;			// ��Ʈ��
		
		fPOINT			size;			// ũ��
										
		int				maxFrameX;		// �ִ� ������ x����
		int				maxFrameY;		// �ִ� ������ y����
		POINT			frameSize;		// ������ ũ��

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
	IMAGE_INFO*		_imageInfo;		//�̹��� ����
	wstring			_fileName;		//�̹��� �̸�

private :
	HRESULT _putImage(void);
	void	_putImageInfo(void);
	void	_flip2fpos(int flip, D2D1_SIZE_F & output);

public:
	// ������ �ʱ�ȭ
	HRESULT init(const wchar_t * fileName);
	HRESULT init(const wchar_t * fileName, int maxFrameX, int maxFrameY);

	//����
	void release(void);

	//���� (���� ������ ��ǥ�� �̹��� ����Ѵ�)
	void render(int flip = IMAGE_FLIP_NONE, float rotate = 0.0f, float alpha = 1.0f);

	//// �̹��� Ŭ����
	//void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH);
	//void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, int flip);

	//// �̹��� stretch
	//void render(HDC hdc, int destX, int destY, float ratio);
	//void render(HDC hdc, int destX, int destY, float ratioX, float ratioY);

	//// �̹��� Ŭ���� stretch (�ø��� -> ����)
	//void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratio);
	//void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratioX, float ratioY);

	//// ���� ����
	//void alphaRender(HDC hdc, BYTE alpha);
	//void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	//void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha);

	//// ���� ���� : ������
	//void alphaRender(HDC hdc, BYTE alpha, int flip);
	//void alphaRender(HDC hdc, int destX, int destY, BYTE alpha, int flip);
	//void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, int flip);

	//// ���� ���� : stretch
	//void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, float ratioX, float ratioY);

	//// ������ ����
	//void frameRender(HDC hdc, int destX, int destY);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, COLORREF changeColor, COLORREF renderColor);

	//// ������ ���� : ������ x / y
	//void frameRender(HDC hdc, int destX, int destY, int flip);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, int flip);

	//// ������ ���� : stretch
	//void frameRender(HDC hdc, int destX, int destY, float ratio);
	//void frameRender(HDC hdc, int destX, int destY, float ratioX, float ratioY);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratioX, float ratioY);

	//// ������ ���� : ������ + stretch
	//void frameRender(HDC hdc, int destX, int destY, float ratio, int flip);
	//void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio, int flip);

	//// ���� ����
	//void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	//void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio);
	//void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//// �ִ� ����
	//void aniRender(HDC hdc, int destX, int destY, animation * ani);

	// =========================== inline ============================== //

	// ** �̹��� ����, ����ũ�� **
	inline const fPOINT & getSize(void) { return _imageInfo->size; };

	// �̹��� 1������ ����, ���� ũ��
	inline const POINT & getFrameSize(void) { return _imageInfo->frameSize; }

	// ��Ʈ�� �ȼ�
	D3DCOLORVALUE getBitmapPixel(POINT pos);

	image();
	~image() {}
};