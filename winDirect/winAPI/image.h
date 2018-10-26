#pragma once

// Ŭ���� ���漱��
class animation;

class image
{
public:
	typedef struct tagImage
	{
		IWICBitmap*		wBitmap;
		ID2D1Bitmap*	bitmap;			// ��Ʈ��
		fPOINT			size;			// ũ��
		POINT			maxFrame;		// �ִ� ������ ��
		POINT			frameSize;		// ������ ũ��

		tagImage()
		{
			bitmap		= NULL;
			size		= { 0.0f, 0.0f };
			maxFrame	= { 0, 0 };
			frameSize	= { 0, 0 };
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO*		_imageInfo;		//�̹��� ����
	wstring			_fileName;		//�̹��� �̸�

private :
	HRESULT _putImage(void);
	void	_putImageInfo(void);

public:
	// ������ �ʱ�ȭ
	HRESULT init(const wchar_t * fileName);
	HRESULT init(const wchar_t * fileName, int maxFrameX, int maxFrameY);

	//����
	void release(void);

	//���� (���� ������ ��ǥ�� �̹��� ����Ѵ�)
	void render(float alpha = 1.0f);

	// �̹��� Ŭ����
	void render(float clipX, float clipY, float clipW, float clipH, float alpha = 1.0f);

	// ������ ����
	void frameRender(int frameX, int frameY, float alpha = 1.0f);

	// �ִ� ����
	void aniRender(animation * ani, float alpha = 1.0f);

public :
	// ��Ʈ�� �ȼ�
	ColorF getBitmapPixel(POINT pos);

	// ��� ����
	// static void initRenderState(void);

public :
	// =========================== inline ============================== //
	// �̹��� ����, ����ũ��
	inline const fPOINT & getSize(void) { return _imageInfo->size; };

	// �̹��� 1������ ����, ���� ũ��
	inline const POINT & getFrameSize(void) { return _imageInfo->frameSize; }

	// �̹��� ������ ����
	inline const POINT & getMaxFrame(void) { return _imageInfo->maxFrame; };

	image();
	~image() {}
};