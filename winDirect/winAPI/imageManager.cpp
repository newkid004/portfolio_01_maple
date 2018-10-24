#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init(void)
{
	// �̹��� ���丮 ����
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_imgFactory));

	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();

	_imgFactory->Release();
}

image * imageManager::addImage(string strKey, wchar_t * fileName)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = find(strKey);

	// �̹� �ִٸ� ����
	if (img) return img;

	// ������ ����
	img = new image;
	img->init(fileName);

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// imageManager �ٽ� �Լ�
image * imageManager::find(string strKey)
{
	// �ش� Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	// ã��
	if (key != _mImageList.end()) return key->second;

	// ��ã��
	return NULL;
}

BOOL imageManager::deleteImage(string strKey)
{
	// �ش� Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	// ã��
	if (key != _mImageList.end())
	{
		// �̹��� ����
		key->second->release();
		SAFE_DELETE(key->second);

		// �� ���� ����
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

BOOL imageManager::deleteAll()
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		// �̹����� ������
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		// �̹����� ������
		else
		{
			++iter;
		}
	}

	// ������ġ
	_mImageList.clear();

	return TRUE;
}