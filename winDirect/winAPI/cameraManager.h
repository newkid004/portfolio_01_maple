#pragma once
#include "singletonBase.h"
#include "camera.h"

class cameraManager : public singletonBase<cameraManager>
{
private :
	typedef map<string, camera*>			mapCamera;
	typedef map<string, camera*>::iterator	mapiCamera;

private :
	mapCamera _mCamera;

public:
	HRESULT init(void);
	void release(void);

	camera* find(string keyName);

	camera* addCamera(string keyName);
	camera* addCamera(string keyName, POINT offset);
	camera* addCamera(string keyName, POINT offset, POINT size);
	camera* addCamera(string keyName, POINT offset, POINT size, POINT minPos, POINT maxPos);

	cameraManager() {};
	~cameraManager() {};
};

