<<<<<<< HEAD
#pragma once
#include "singletonBase.h"

enum e_RENDER_ORDER
{
	// µÞ¹è°æ
	RO_BACK_0,
	RO_BACK_1,
	RO_BACK_2,
	RO_BACK_3,

	// Àå½Ä¹°
	RO_DECO_0,
	RO_DECO_1,

	// Æ÷Å»
	RO_PORTAL,

	// º¸½º
	RO_BOSS,

	// ¸ó½ºÅÍ
	RO_MONSTER,

	// ½ºÅ³ : µÚ
	RO_SKILL_BACK,

	// ÇÃ·¹ÀÌ¾î
	RO_PLAYER,

	// ½ºÅ³ : ¾Õ
	RO_SKILL_FRONT,

	// ¾Õ¹è°æ
	RO_FRONT_0,
	RO_FRONT_1,

	// µ¥¹ÌÁö
	RO_DAMAGE,

	// ¾ÆÀÌÅÛ
	RO_ITEM,

	// ½ºÅ³ : Á¦ÀÏ ¾Õ
	RO_SKILL_FRONTEST,

	// ·»´õ Á¾·ù °³¼ö
	RO_COUNT
};

enum e_RENDER_MANAGER_STATE
{
	RMS_CLIP_INTO_CAMERA = 0x0001,

	RMS_NONE = 0
};

class renderManager : public singletonBase<renderManager>
{
private :
	struct tagRender
	{
		image * img;
		fPOINT pos;
		fPOINT clip;
		fPOINT size;

		float alpha;
		float rotate;
		int flip;

		tagRender() : 
			img(NULL),
			pos(0.0f), 
			clip(0.0f), 
			size(0.0f), 
			alpha(1.0f), 
			rotate(0.0f),
			flip(0)
		{};

		tagRender(image* inImage) : 
			tagRender()
		{
			this->img = inImage;
			this->size = img->getSize();
		};

		tagRender(image* inImage, fPOINT inPos) : 
			tagRender(inImage) 
		{ 
			this->pos = inPos; 
		};

		tagRender(image* img, fPOINT pos, fPOINT sour, fPOINT dest, float alpha = 1.0f, float rotate = 0.0f, int flip = 0)
		{
			this->img = img;
			this->pos = pos;
			this->clip = sour;
			this->size = dest;

			this->alpha = alpha;
			this->rotate = rotate;
			this->flip = flip;
		};
	};

private:
	int					_renderState;
	camera*				_currentCamera;
	vector<tagRender>	_vRenderList[RO_COUNT];

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void releaseList(int order);
	void renderList(int order);

public :
	void add(e_RENDER_ORDER order, image * img, fPOINT pos, fPOINT clip, fPOINT size, float alpha = 1.0f, float rotate = 0.0f, int flip = 0);

	void setCamera(camera* c) { _currentCamera = c; };

	void setRenderState(e_RENDER_MANAGER_STATE s, int value);
	int  getRenderState(e_RENDER_MANAGER_STATE s);

private :
	bool clipRender(tagRender & r);

public:
	renderManager() {};
	~renderManager() {};
};

=======
#pragma once
#include "singletonBase.h"

enum e_RENDER_ORDER
{
	// µÞ¹è°æ
	RO_BACK_0,
	RO_BACK_1,
	RO_BACK_2,
	RO_BACK_3,

	// Àå½Ä¹°
	RO_DECO_0,
	RO_DECO_1,

	// Æ÷Å»
	RO_PORTAL,

	// º¸½º
	RO_BOSS,

	// ¸ó½ºÅÍ
	RO_MONSTER,

	// ½ºÅ³ : µÚ
	RO_SKILL_BACK,

	// ÇÃ·¹ÀÌ¾î
	RO_PLAYER,

	// ½ºÅ³ : ¾Õ
	RO_SKILL_FRONT,

	// ¾Õ¹è°æ
	RO_FRONT_0,
	RO_FRONT_1,

	// µ¥¹ÌÁö
	RO_DAMAGE,

	// ¾ÆÀÌÅÛ
	RO_ITEM,

	// ½ºÅ³ : Á¦ÀÏ ¾Õ
	RO_SKILL_FRONTEST,

	// ·»´õ Á¾·ù °³¼ö
	RO_COUNT
};

enum e_RENDER_MANAGER_STATE
{
	RMS_CLIP_INTO_CAMERA = 0x0001,

	RMS_NONE = 0
};

class renderManager : public singletonBase<renderManager>
{
private :
	struct tagRender
	{
		image * img;
		fPOINT pos;
		fPOINT clip;
		fPOINT size;

		float alpha;
		float rotate;
		int flip;

		tagRender() : 
			img(NULL),
			pos(0.0f), 
			clip(0.0f), 
			size(0.0f), 
			alpha(1.0f), 
			rotate(0.0f),
			flip(0)
		{};

		tagRender(image* inImage) : 
			tagRender()
		{
			this->img = inImage;
			this->size = img->getSize();
		};

		tagRender(image* inImage, fPOINT inPos) : 
			tagRender(inImage) 
		{ 
			this->pos = inPos; 
		};

		tagRender(image* img, fPOINT pos, fPOINT sour, fPOINT dest, float alpha = 1.0f, float rotate = 0.0f, int flip = 0)
		{
			this->img = img;
			this->pos = pos;
			this->clip = sour;
			this->size = dest;

			this->alpha = alpha;
			this->rotate = rotate;
			this->flip = flip;
		};
	};

private:
	int					_renderState;
	camera*				_currentCamera;
	vector<tagRender>	_vRenderList[RO_COUNT];

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void releaseList(int order);
	void renderList(int order);

public :
	void add(e_RENDER_ORDER order, image * img, fPOINT pos, fPOINT clip, fPOINT size, float alpha = 1.0f, float rotate = 0.0f, int flip = 0);

	void setCamera(camera* c) { _currentCamera = c; };

	void setRenderState(e_RENDER_MANAGER_STATE s, int value);
	int  getRenderState(e_RENDER_MANAGER_STATE s);

private :
	bool clipRender(tagRender & r);

public:
	renderManager() {};
	~renderManager() {};
};

>>>>>>> parent of d0a58f6... ì˜¤ë¥˜ ì»¤ë°‹
