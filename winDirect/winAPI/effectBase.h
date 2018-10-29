#pragma once
struct effectInfo
{
	animation* ani;
	image* image;
	float alpha;
	fPOINT position;			//위치
	fPOINT offset;				//기준 간격
	float rotation;				//회전
	int flip;					//반전
	e_RENDER_ORDER renderOrder; //z오더
};

class effectBase
{
protected:
	effectInfo _infoEffect;

public:
	virtual HRESULT init(void);
	virtual void release(void){}
	virtual void update(void);
	virtual void render(void);

	effectInfo &getInfo() { return _infoEffect; }

	effectBase(){}
	~effectBase(){}
};

