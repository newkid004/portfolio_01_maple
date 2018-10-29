#include "stdafx.h"
#include "camera.h"

void camera::init(void)
{
	_position = { 0, 0 };
	_offset = { 0, 0 };
	_size = { (long)WINSIZEX, (long)WINSIZEY };

	_minPos = { 0, 0 };
	_maxPos = { (long)WINSIZEX, (long)WINSIZEY };

	ZeroMemory(&_shake, sizeof(_shake));
}

void camera::init(PNT offset)
{
	init();

	_offset = offset;
}

void camera::init(PNT offset, PNT size)
{
	init();

	_offset = offset;
	_size = size;
}

void camera::init(PNT offset, PNT size, PNT minPos, PNT maxPos)
{
	_offset = offset;
	_size = size;

	_minPos = minPos;
	_maxPos = maxPos;

	_minPos.x = _minPos.x < 0 ? 0 : _minPos.x;
	_minPos.y = _minPos.y < 0 ? 0 : _minPos.y;
}

void camera::init(PNT position, PNT offset, PNT size, PNT minPos, PNT maxPos)
{
	init(offset, size, minPos, maxPos);

	_position = position;
}

void camera::update(float elipsedTime)
{
	_shake.offset = _offset;

	if (_shake.time < 0) return;
	updateShake(elipsedTime);
}

void camera::updateShake(float elipsedTime)
{
	if (_shake.interval < 0) return;

	_shake.time -= elipsedTime;
	_shake.interval -= _shake.decValue * elipsedTime;

	PNT & shakedOffset = _shake.offset;
	shakedOffset.x += RND->getFromFloatTo(-_shake.interval, _shake.interval);
	shakedOffset.y += RND->getFromFloatTo(-_shake.interval, _shake.interval);
	// shakedOffset.x += RND->getInt(2) ? -_shake.interval : _shake.interval;
	// shakedOffset.y += RND->getInt(2) ? -_shake.interval : _shake.interval;

	// 화면 밖으로 안나가게
	if (shakedOffset.x <= _minPos.x)				shakedOffset.x = _minPos.x;
	else if (_maxPos.x <= shakedOffset.x + _size.x)	shakedOffset.x = _maxPos.x - _size.x;

	if (shakedOffset.y <= _minPos.y)				shakedOffset.y = _minPos.y;
	else if (_maxPos.y <= shakedOffset.y + _size.y)	shakedOffset.y = _maxPos.y - _size.y;
}

void camera::putShake(float time, float interval, float decValue)
{
	if (_shake.time < time) _shake.time = time;

	_shake.interval = interval;
	_shake.decValue = decValue;
}

void camera::setOffset(PNT pos)
{
	// 화면 밖으로 안나가게
	if (_minPos.x <= pos.x && pos.x + _size.x <= _maxPos.x) _offset.x = pos.x;
	else if (pos.x < _minPos.x)								_offset.x = _minPos.x;
	else if (_maxPos.x < pos.x + _size.x)					_offset.x = _maxPos.x - _size.x;

	if (_minPos.y <= pos.y && pos.y + _size.y <= _maxPos.y) _offset.y = pos.y;
	else if (pos.y < _minPos.y)								_offset.y = _minPos.y;
	else if (_maxPos.y < pos.y + _size.y)					_offset.y = _maxPos.y - _size.y;
}

void camera::moveOffset(int posX, int posY)
{
	// 화면 밖으로 안나가게
	if (_minPos.x <= _offset.x + posX && _offset.x + _size.x + posX <= _maxPos.x)	_offset.x += posX;
	else if (_offset.x + posX <= _minPos.x)											_offset.x = _minPos.x;
	else if (_maxPos.x <= _offset.x + posX + _size.x)								_offset.x = _maxPos.x - _size.x;

	if (_minPos.y <= _offset.y + posY && _offset.y + _size.y + posY <= _maxPos.y)	_offset.y += posY;
	else if (_offset.y + posY <= _minPos.y)											_offset.y = _minPos.y;
	else if (_maxPos.y <= _offset.y + posY + _size.y)								_offset.y = _maxPos.y - _size.y;
}
void camera::moveOffset(PNT move)
{
	// 화면 밖으로 안나가게
	if (_minPos.x <= _offset.x + move.x && _offset.x + _size.x + move.x <= _maxPos.x)	_offset.x += move.x;
	else if (move.x + _offset.x <= _minPos.x)											_offset.x = _minPos.x;
	else if (_maxPos.x <= move.x + _offset.x + _size.x)									_offset.x = _maxPos.x - _size.x;

	if (_minPos.y <= _offset.y + move.y && _offset.y + _size.y + move.y <= _maxPos.y)	_offset.y += move.y;
	else if (move.y + _offset.y <= _minPos.y)											_offset.y = _minPos.y;
	else if (_maxPos.y <= move.y + _offset.y + _size.y)									_offset.y = _maxPos.y - _size.y;
}

void camera::setSize(PNT size)
{
	// if (0 < size.x && size.x < WINSIZEX) _size.x = size.x;
	// if (0 < size.y && size.y < WINSIZEY) _size.y = size.y;
	_size.x = size.x;
	_size.y = size.y;
}

void camera::setMinPos(PNT pos)
{
	_minPos = pos;
}

void camera::setMaxPos(PNT pos)
{
	_maxPos = pos;
}

PNT camera::getCameraInnerPos(float posX, float posY)
{
	return PNT{
		_offset.x + (int)(_size.x * posX),
		_offset.y + (int)(_size.y * posY) };
}
