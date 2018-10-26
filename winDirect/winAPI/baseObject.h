#pragma once
#include "objectDef.h"
#include "classesDef.h"
#include "itemDef.h"

class image;

//광선 구조체
struct ray
{
	fPOINT	destfPos;
	fPOINT	sourfPos;

	NUM_REAL	distance;

	ray() {
		destfPos = fPOINT{ 0.0f,0.0f };
		sourfPos = fPOINT{ 0.0f,0.0f };
		distance = 0.0f;
	};
};

//광선 구조체 모음
typedef struct rayStruct
{
	ray	upperRay[RAY_NUM];			//윗방향 ray
	ray rightRay[RAY_NUM];			//오른쪽 ray
	ray leftRay[RAY_NUM];			//왼쪽	ray
	ray bottomRay[RAY_NUM];			//아래쪽 ray
}RAYSTRUCT;


class baseObject
{
protected:
	image*			_img;

	objDef::OBJECT	_objectKind;

	fPOINT			_position;
	fRECT			_collision;
public:
	baseObject() {};
	~baseObject() {};
	
	void setObjectKind(objDef::OBJECT objectID)			{ _objectKind = objectID; }


	objDef::OBJECT getObjectKind()						{ return _objectKind; }

	fPOINT getPosition()								{ return _position; }
	POINT  getPosition_re_POINT()						{ return MY_UTIL::pos2point(_position); }

	fRECT& getCollision()							{ return _collision; }
	fRECT getCollisionRect() { return pos2fRect(fPOINT{ _position.x + _collision.LT.x,_position.y + _collision.LT.y },
								fPOINT{ _position.x + _collision.RB.x,_position.y + _collision.RB.y }); }
};

