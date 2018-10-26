#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init(void)
{
	return S_OK;
}

void cameraManager::release(void)
{
	mapiCamera iter = _mCamera.begin();
	for (; iter != _mCamera.end(); ++iter)
		SAFE_DELETE(iter->second);
	_mCamera.clear();
}

camera * cameraManager::find(string keyName)
{
	mapiCamera c = _mCamera.find(keyName);

	if (c != _mCamera.end()) return c->second;

	return NULL;
}

camera * cameraManager::addCamera(string keyName)
{
	camera* c = find(keyName);
	if (c != NULL) return c;

	c = new camera;
	c->init();
	_mCamera.insert(make_pair(keyName, c));

	return c;
}

camera * cameraManager::addCamera(string keyName, fPOINT offset)
{
	camera* c = find(keyName);
	if (c != NULL) return c;

	c = new camera;
	c->init(offset);
	_mCamera.insert(make_pair(keyName, c));

	return c;
}

camera * cameraManager::addCamera(string keyName, fPOINT offset, fPOINT size)
{
	camera* c = find(keyName);
	if (c != NULL) return c;

	c = new camera;
	c->init(offset, size);
	_mCamera.insert(make_pair(keyName, c));

	return c;
}

camera * cameraManager::addCamera(string keyName, fPOINT offset, fPOINT size, fPOINT minPos, fPOINT maxPos)
{
	camera* c = find(keyName);
	if (c != NULL) return c;

	c = new camera;
	c->init(offset, size, minPos, maxPos);
	_mCamera.insert(make_pair(keyName, c));

	return c;
}

