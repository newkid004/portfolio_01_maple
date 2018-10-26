#include "stdafx.h"
#include "characterBase.h"



void characterBase::setRayStruct()
{
	fPOINT	_currentPos		= _position;
	fPOINT	_destPos		= addF(_position, _velocity);
	fPOINT	_deltaDistance	= getDeltaPt(_currentPos, _destPos);

	NUM_REAL	_height = _collision.RB.y - _collision.LT.y;
	NUM_REAL	_width	= _collision.RB.x - _collision.LT.x;

	
	ZeroMemory(&_rayStruct.rightRay, sizeof(ray)*RAY_NUM);
	ZeroMemory(&_rayStruct.leftRay, sizeof(ray)*RAY_NUM);
	ZeroMemory(&_rayStruct.upperRay, sizeof(ray)*RAY_NUM);
	ZeroMemory(&_rayStruct.bottomRay, sizeof(ray)*RAY_NUM);
	

	if (_deltaDistance.x > 0)
	{
		for (int i = 0; i < RAY_NUM; i++)
		{
			_rayStruct.rightRay[i].sourfPos		= fPOINT{ _collision.RB.x,_collision.LT.y+(_height*i/(RAY_NUM-1)) };
			_rayStruct.rightRay[i].destfPos		= fPOINT{ _collision.RB.x + _deltaDistance.x,_collision.LT.y + (_height*i / (RAY_NUM - 1)) };
			_rayStruct.rightRay[i].distance		= abs(_rayStruct.rightRay[i].destfPos.x - _rayStruct.rightRay[i].sourfPos.x);
		}
	}
	else if (_deltaDistance.x < 0)
	{
		for (int i = 0; i < RAY_NUM; i++)
		{
			_rayStruct.leftRay[i].sourfPos		= fPOINT{ _collision.LT.x,_collision.LT.y + (_height*i / (RAY_NUM - 1)) };
			_rayStruct.leftRay[i].destfPos		= fPOINT{ _collision.LT.x + _deltaDistance.x,_collision.LT.y + (_height*i / (RAY_NUM - 1)) };
			_rayStruct.leftRay[i].distance		= abs(_rayStruct.rightRay[i].destfPos.x - _rayStruct.rightRay[i].sourfPos.x);
		}
	}

	if (_deltaDistance.y > 0)
	{
		for (int i = 0; i < RAY_NUM; i++)
		{
			_rayStruct.bottomRay[i].sourfPos	= fPOINT{ _collision.LT.x + (_width*i / (RAY_NUM - 1)),_collision.RB.y  };
			_rayStruct.bottomRay[i].destfPos	= fPOINT{ _collision.LT.x + (_width*i / (RAY_NUM - 1)),_collision.RB.y+_deltaDistance.y };
			_rayStruct.bottomRay[i].distance	= abs(_rayStruct.bottomRay[i].destfPos.x - _rayStruct.bottomRay[i].sourfPos.x);
		}
	}
	else if (_deltaDistance.y < 0)
	{
		for (int i = 0; i < RAY_NUM; i++)
		{
			_rayStruct.upperRay[i].sourfPos		= fPOINT{ _collision.LT.x + (_width*i / (RAY_NUM - 1)),_collision.LT.y };
			_rayStruct.upperRay[i].destfPos		= fPOINT{ _collision.LT.x + (_width*i / (RAY_NUM - 1)),_collision.LT.y + _deltaDistance.y };
			_rayStruct.upperRay[i].distance		= abs(_rayStruct.upperRay[i].destfPos.x - _rayStruct.upperRay[i].sourfPos.x);
		}
	}

}

void characterBase::rayCollision()
{
	_isCollision = false;
	if (_rayStruct.upperRay[0].distance != 0)
	{
		_isCollision = true;
	}
	else if (_rayStruct.bottomRay[0].distance != 0)
	{
		_isCollision = true;
	}
	else if (_rayStruct.rightRay[0].distance != 0)
	{
		_isCollision = true;
	}
	else if (_rayStruct.bottomRay[0].distance != 0)
	{
		_isCollision = true;
	}
}
