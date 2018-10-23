#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;				// �� �̹��� ���
	typedef map<string, image*>::iterator mapImageIter;		// �� �̹��� ��� �ݺ���

private:
	mapImageList _mImageList;
	IWICImagingFactory * _imgFactory = NULL;

public:
	HRESULT init(void);
	void release(void);

	// ----- ���� / ������ ----- //

	// Ű������ �̹��� Ž��
	image* find(string strKey);

	// Ű������ �̹��� ����
	BOOL deleteImage(string strKey);

	// ��ü �̹��� ����
	BOOL deleteAll();

	IWICImagingFactory * getFactory(void) { return _imgFactory; };

	// ----- add image ----- //
	image* addImage(string strKey, wchar_t * fileName);

	imageManager() {};
	~imageManager() {};
};