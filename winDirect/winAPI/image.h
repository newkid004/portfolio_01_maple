#pragma once

// Ŭ���� ���漱��
class animation;

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//���ҽ��� �ε�
		LOAD_FILE,				//���Ϸ� �ε�
		LOAD_EMPTY,				//���Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;			//���ҽ� ID
		HDC			hMemDC;			//�޸� DC
		HBITMAP		hBit;			//��Ʈ��
		HBITMAP		hOBit;			//�õ��Ʈ��
		
		float		x;				// �̹��� x��ǥ
		float		y;				// �̹��� y��ǥ
		int			width;			//�̹��� ����ũ��
		int			height;			//�̹��� ����ũ��
									
		int			curruntFrameX;	// ���� ������ x��ǥ
		int			curruntFrameY;	// ���� ������ y��ǥ
		int			maxFrameX;		// �ִ� ������ x����
		int			maxFrameY;		// �ִ� ������ y����
		int			frameWidth;		// 1������ ����
		int			frameHeight;	// 1������ ����
									
		BYTE		loadType;		//�̹��� �ε�Ÿ��

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			
			x = y = 0;
			width = 0;
			height = 0;

			curruntFrameX = 0;
			curruntFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;

			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�̹��� �̸�
	BOOL			_isTrans;		//���� ���ٰ���
	COLORREF		_transColor;	//���� ���� RGB�� (����Ÿ = RGB(255, 0, 255))

	LPIMAGE_INFO	_strchImage;	// stretch �̹���

	BLENDFUNCTION	_blendFunc;		// ���ĺ��� ���
	LPIMAGE_INFO	_blendImage;	// ���ĺ��� �̹���

public:
	//�� ��Ʈ������ �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ��� �ʱ�ȭ
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ(�� ���)
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// ������ �ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// stretch �ʱ�ȭ
	HRESULT initForStretch(void);
	// ���ĺ��� �ʱ�ȭ
	HRESULT initForAlphaBlend(void);

	//���� �÷�Ű ���� (���� ��������?, �����)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//����
	void release(void);

	//���� (���� ������ ��ǥ�� �̹��� ����Ѵ�)
	void render(HDC hdc);
	void render(HDC hdc, float ratio);
	void render(HDC hdc, int destX, int destY);

	// �̹��� Ŭ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, int flip);

	// �̹��� stretch
	void render(HDC hdc, int destX, int destY, float ratio);
	void render(HDC hdc, int destX, int destY, float ratioX, float ratioY);

	// �̹��� Ŭ���� stretch (�ø��� -> ����)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratio);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, float ratioX, float ratioY);

	// ���� ����
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha);

	// ���� ���� : ������
	void alphaRender(HDC hdc, BYTE alpha, int flip);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha, int flip);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, int flip);

	// ���� ���� : stretch
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha, float ratioX, float ratioY);

	// ������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, COLORREF changeColor, COLORREF renderColor);

	// ������ ���� : ������ x / y
	void frameRender(HDC hdc, int destX, int destY, int flip);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, int flip);

	// ������ ���� : stretch
	void frameRender(HDC hdc, int destX, int destY, float ratio);
	void frameRender(HDC hdc, int destX, int destY, float ratioX, float ratioY);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratioX, float ratioY);

	// ������ ���� : ������ + stretch
	void frameRender(HDC hdc, int destX, int destY, float ratio, int flip);
	void frameRender(HDC hdc, int destX, int destY, int curruntFrameX, int curruntFrameY, float ratio, int flip);

	// ���� ����
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, float ratio);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// �ִ� ����
	void aniRender(HDC hdc, int destX, int destY, animation * ani);

	//DC ���
	inline HDC &getMemDC(void) { return _imageInfo->hMemDC; }
	inline HDC &getBlendDC(void) { return _blendImage->hMemDC; };

	// =========================== inline ============================== //

	// �̹��� ��ǥ
	inline float getX(void) { return _imageInfo->x; };
	inline void setX(float x) { _imageInfo->x = x; };
	inline float getY(void) { return _imageInfo->y; };
	inline void setY(float y) { _imageInfo->y = y; };

	// �̹��� ����
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// ** �̹��� ����, ����ũ�� **
	inline int getWidth(void) { return _imageInfo->width; };
	inline int getHeight(void) { return _imageInfo->height; };
	inline POINT getSize(void) { return POINT{ _imageInfo->width, _imageInfo->height }; }

	// �ٿ�� �ڽ�(�浹�� ��Ʈ)
	inline RECT boundingBox(void) { return RectMake((int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height); };
	inline RECT boundingBoxFrame(void) { return RectMake((int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->frameWidth, _imageInfo->frameHeight); };

	// ������ X
	inline int getFrameX(void) { return _imageInfo->curruntFrameX; };
	inline void setFrameX(int FrameX) { _imageInfo->curruntFrameX = _imageInfo->maxFrameX < FrameX ? _imageInfo->maxFrameX : FrameX; }

	// ������ Y
	inline int getFrameY(void) { return _imageInfo->curruntFrameY; };
	inline void setFrameY(int FrameY) { _imageInfo->curruntFrameY = _imageInfo->maxFrameY < FrameY ? _imageInfo->maxFrameY : FrameY; }

	// �̹��� 1������ ����, ���� ũ��
	inline int & getFrameWidth(void) { return _imageInfo->frameWidth; };
	inline int & getFrameHeight(void) { return _imageInfo->frameHeight; };
	inline POINT getFrameSize(void) { return POINT{ _imageInfo->frameWidth, _imageInfo->frameHeight }; }

	// �ִ� ������ x, y ����
	inline int & getMaxFrameX(void) { return _imageInfo->maxFrameX; };
	inline int & getMaxFrameY(void) { return _imageInfo->maxFrameY; };

	// ��Ʈ�� �ȼ�
	inline COLORREF getBitmapPixel(POINT pos) { return GetPixel(_imageInfo->hMemDC, pos.x, pos.y); }
	inline COLORREF getTransColor() { return _transColor; };

	image();
	~image() {}
};