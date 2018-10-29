#include "stdafx.h"
#include "bulletBase.h"

HRESULT bulletBase::init(void)
{
	_objectKind = objDef::OBJECT_BULLET;

	_ani = NULL; 
	ZeroMemory(&_info, sizeof(_info));

	return S_OK;
}

void bulletBase::update(void)
{
	getDeltaPos(
		_position,
		getRadian(_position, _info.posDest), 
		_info.velocity * TIMEMANAGER->getElapsedTime());
}

void bulletBase::render(void)
{
	RENDERMANAGER->add(
		RO_SKILL_FRONT,
		_img,
		_position - _ani->getFrameSize() / 2, 
		_ani->getFramePos(), 
		_ani->getFrameSize(), 
		1.0f, 0.0f, _info.flip);
}
