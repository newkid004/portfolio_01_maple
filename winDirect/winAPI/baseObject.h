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
	fRECT			_collisionRect;
public:
	baseObject() {};
	~baseObject() {};
	
	void setObjectKind(objDef::OBJECT objectID)			{ _objectKind = objectID; }


	objDef::OBJECT getObjectKind()						{ return _objectKind; }

	fPOINT getPosition()								{ return _position; }
	POINT  getPosition_re_POINT()						{ return MY_UTIL::pos2point(_position); }

	fRECT& getCollisionRect()							{ return _collisionRect; }
};

