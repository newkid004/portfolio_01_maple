#include "stdafx.h"
#include "charaterSelectScene.h"


HRESULT charaterSelectScene::init()
{
	int backSizeX = IMAGEMANAGER->find("charaterSelectBack")->getSize().x;
	int backSizeY = IMAGEMANAGER->find("charaterSelectBack")->getSize().y;

	getBackColor() = C_COLOR_BLACK;

	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, true);
	
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			//winsize 기반의 좌표 (수정)
			//_charater[i * 4 + j].pos = { WINSIZEX / 2.0f - WINSIZEX/4.5f  + WINSIZEX/10.5f*j,
			//	                           WINSIZEY / 2.0f - WINSIZEY/10.0f + WINSIZEY/3.6f*i};

			//배경 크기기반의 좌표
			_charater[i * 4 + j].pos = { WINSIZEX / 2.0f - backSizeX / 2.8f + backSizeX / 6.5f*j,
				                         WINSIZEY / 2.0f - backSizeY / 5.8f + backSizeY / 3.0f*i };
			_charater[i * 4 + j].currentFrameY = 0;
			_charater[i * 4 + j].elapsedTime = 0;
			_charater[i * 4 + j].updateTime = 0.1f;
			_charater[i * 4 + j].pB = nullptr;
		}
	}
	return S_OK;
}

void charaterSelectScene::release()
{
}

void charaterSelectScene::update()
{
	for (int i = 0; i < 8; i++)
	{
		_charater[i].elapsedTime += TIMEMANAGER->getElapsedTime();
		if (_charater[i].elapsedTime >= _charater[i].updateTime)
		{
			_charater[i].elapsedTime = 0;
			++_charater[i].currentFrameY;
			if (_charater[i].pB == nullptr &&
				_charater[i].currentFrameY > IMAGEMANAGER->find("nonePlayerB")->getMaxFrame().y)
			{
				_charater[i].currentFrameY = 0;
			}
		}
	}
}

void charaterSelectScene::render()
{
	IMAGEMANAGER->statePos(fPOINT(WINSIZEX / 2 - IMAGEMANAGER->find("charaterSelectBack")->getFrameSize().x / 2,
		                          WINSIZEY / 2 - IMAGEMANAGER->find("charaterSelectBack")->getFrameSize().y / 2));
	IMAGEMANAGER->find("charaterSelectBack")->render();
	for (int i = 0; i < 8; i++)
	{
		if (_charater[i].pB == nullptr)
		{
			IMAGEMANAGER->statePos(fPOINT(_charater[i].pos.x - IMAGEMANAGER->find("nonePlayer")->getSize().x / 2,
				_charater[i].pos.y - IMAGEMANAGER->find("nonePlayer")->getSize().y / 2));
			if ((i % 4) >= 2) IMAGEMANAGER->stateFlip(IMAGE_FLIP_NONE);
			else IMAGEMANAGER->stateFlip(IMAGE_FLIP_VERTICAL);
			IMAGEMANAGER->find("nonePlayer")->render();
			IMAGEMANAGER->statePos(fPOINT(_charater[i].pos.x - IMAGEMANAGER->find("nonePlayerB")->getFrameSize().x / 2,
				_charater[i].pos.y - IMAGEMANAGER->find("nonePlayerB")->getFrameSize().y / 2
				+ IMAGEMANAGER->find("nonePlayer")->getSize().y / 2));
			IMAGEMANAGER->find("nonePlayerB")->frameRender(0, _charater[i].currentFrameY);
		}
	}
}
