<<<<<<< HEAD
#pragma once
#include "baseObject.h"

struct infoBullet
{
	float damage;

	fPOINT posDest;
	float velocity;

	float timeAlive;

	int flip;
};

class bulletBase : public baseObject
{
protected :
	animation* _ani;
	infoBullet _info;

public :
	virtual HRESULT init(void);
	virtual void release(void) {};
	virtual void update(void);
	virtual void render(void);

public :
	animation *& getAni() { return _ani; };
	infoBullet & getInfo() { return _info; };

public:
	bulletBase() : baseObject() {};
	~bulletBase() {};
};

=======
#pragma once
class bulletBase
{
public:
	bulletBase();
	~bulletBase();
};

>>>>>>> parent of d0a58f6... 오류 커밋
