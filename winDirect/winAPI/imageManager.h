#pragma once
#include "singletonBase.h"
#include "image.h"

enum e_IMG_RENDER_STATE
{
	IRS_ALWAYS_RESET_TRANSFORM	= 0x0001,
	IRS_NONE					= 0
};

enum e_IMAGE_FLIP
{
	IMAGE_FLIP_NONE		= 0b00,
	IMAGE_FLIP_VERTICAL	= 0b10,
	IMAGE_FLIP_HORIZON	= 0b01
};

enum e_RESET_TRANSFORM
{
	RTF_NONE		= 0,
	RTF_POSITION	= 0b001,
	RTF_ROTATION	= 0b010,
	RTF_FLIP		= 0b100,
	RTF_ALL			= 0b111
};

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;				// 맵 이미지 목록
	typedef map<string, image*>::iterator mapImageIter;		// 맵 이미지 목록 반복자

private:
	mapImageList _mImageList;

	IWICImagingFactory*	_imgFactory = NULL;
	ID2D1Layer *		_layer = NULL;

private:
	fPOINT	_imgPos;
	int		_imgFlip;
	float	_imgRotate;

	int		_renderState;

public:
	HRESULT init(void);
	void release(void);

public :
	// 키값으로 이미지 탐색
	image* find(string strKey);

	// 키값으로 이미지 삭제
	BOOL deleteImage(string strKey);

	// 전체 이미지 삭제
	BOOL deleteAll();

	IWICImagingFactory * getFactory(void) { return _imgFactory; };

	// ----- image ----- //
	image* add(string strKey, wchar_t * fileName, int maxFrameX = 1, int maxFrameY = 1);

	// ----- layer ----- //
	void pushLayer(fRECT * clippedArea);
	void popLayer(void);

	// ----- state ----- //
	fPOINT &	statePos(void)		{ return _imgPos; };
	int &		stateFlip(void)		{ return _imgFlip; };
	float &		stateRotate(void)	{ return _imgRotate; };

	fPOINT &	statePos(float x, float y) { return _imgPos = fPOINT(x, y); };
	fPOINT &	statePos(fPOINT input)	{ return _imgPos = input; };
	int &		stateFlip(int input)	{ return _imgFlip = input; };
	float &		stateRotate(float input){ return _imgRotate = input; };

	void resetTransform(void);
	void resetTransform(e_RESET_TRANSFORM resetValue);
	void setTransform(D2D1_POINT_2F * pos);

	void setRenderState(e_IMG_RENDER_STATE state, int value);
	const int getRenderState(void) { return _renderState; };
	const int getRenderState(e_IMG_RENDER_STATE state) { return _renderState & state; }

private:
	void	_flip2fpos(int flip, D2D1_SIZE_F & output);

public :
	imageManager() {};
	~imageManager() {};
};