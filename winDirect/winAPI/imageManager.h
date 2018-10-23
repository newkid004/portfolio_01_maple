#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;				// 맵 이미지 목록
	typedef map<string, image*>::iterator mapImageIter;		// 맵 이미지 목록 반복자

private:
	mapImageList _mImageList;
	IWICImagingFactory * _imgFactory = NULL;

public:
	HRESULT init(void);
	void release(void);

	// ----- 접근 / 지정자 ----- //

	// 키값으로 이미지 탐색
	image* find(string strKey);

	// 키값으로 이미지 삭제
	BOOL deleteImage(string strKey);

	// 전체 이미지 삭제
	BOOL deleteAll();

	IWICImagingFactory * getFactory(void) { return _imgFactory; };

	// ----- add image ----- //
	image* addImage(string strKey, wchar_t * fileName);

	imageManager() {};
	~imageManager() {};
};