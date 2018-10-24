#include "stdafx.h"
#include "renderManager.h"

HRESULT renderManager::init(void)
{
	return S_OK;
}

void renderManager::release(void)
{
	for (int i = 0; i < RO_COUNT; ++i)
		releaseList(i);
	
	releaseUiList();
}

void renderManager::update(void)
{
}

void renderManager::render(void)
{
	int renderStateTemp = IMAGEMANAGER->getRenderState(IRS_ALWAYS_RESET_TRANSFORM);
	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	for (int i = 0; i < RO_COUNT; ++i)
	{
		renderList(i);
		releaseList(i);
	}

	if (renderStateTemp)
		IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, true);
}

void renderManager::releaseList(int order)
{
	_vRenderList[order].clear();
}

void renderManager::releaseUiList(void)
{
	_vRenderUi.clear();
}

void renderManager::renderList(int order)
{
	for (tagRender & stRender : _vRenderList[order])
	{
		IMAGEMANAGER->statePos(stRender.pos);
		IMAGEMANAGER->stateFlip(stRender.flip);
		IMAGEMANAGER->stateRotate(stRender.rotate);

		stRender.img->render(
			stRender.clip.x,
			stRender.clip.y,
			stRender.size.x,
			stRender.size.y,
			stRender.alpha);
	}
}

void renderManager::renderUiList(void)
{
	for (uiBase* i : _vRenderUi)
	{
		// i->render();
	}
}

void renderManager::add(e_RENDER_ORDER order, image * img, fPOINT pos, fPOINT clip, fPOINT size, float alpha, float rotate, int flip)
{
	_vRenderList[order].push_back(tagRender(img, pos, clip, size, alpha, rotate, flip));
}

void renderManager::addUi(uiBase * inputUI)
{
	_vRenderUi.push_back(inputUI);
}

void renderManager::clipRender(tagRender & r)
{
}
