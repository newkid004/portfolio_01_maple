#include "stdafx.h"
#include "effectBase.h"

HRESULT effectBase::init(void)
{
	ZeroMemory(&_infoEffect, sizeof(effectInfo));
	return S_OK;
}

void effectBase::update(void)
{
	_infoEffect.ani->update();
}

void effectBase::render(void)
{
	RENDERMANAGER->add(
		_infoEffect.renderOrder,
		_infoEffect.image,
		_infoEffect.position + _infoEffect.offset,
		_infoEffect.ani->getFramePos(),
		_infoEffect.ani->getFrameSize(),
		_infoEffect.alpha,
		_infoEffect.rotation,
		_infoEffect.flip);
}
