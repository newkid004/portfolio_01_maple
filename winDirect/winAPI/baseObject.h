#pragma once
#include "objectDef.h"
#include "classesDef.h"
#include "itemDef.h"

class image;

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
	fRECT getCollisionRect() { return pos2fRect(fPOINT{ _position.x + _collision.LeftTop.x,_position.y + _collision.LeftTop.y },
								fPOINT{ _position.x + _collision.RightBottom.x,_position.y + _collision.RightBottom.y }); }
};

