#pragma once


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
	POINT  getPosition_re_POINT()						{ return pos2point(_position); }

	fRECT& getCollisionRect()							{ return _collisionRect; }
};

