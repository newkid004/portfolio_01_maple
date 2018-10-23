#include "stdafx.h"
#include "pEnforcer.h"
#include "tileMap.h"

// player bullet
#include "bullet_Enforcer_0.h"
#include "bullet_Enforcer_1.h"
#include "bullet_Enforcer_3.h" 

HRESULT pEnforcer::init(void)
{
	playerableBase::init();
	initCharImage();

	initStatus();
	initAnimation();
	initInfo();

	// ----- member ----- //
	_isShoot = false;
	_skill_3_fixedDirection = 0;

	return S_OK;
}

void pEnforcer::release(void)
{
	playerableBase::release();
}

void pEnforcer::update(void)
{
	playerableBase::update();

	ctrlAnimation();
}

void pEnforcer::initCharImage(void)
{
	_img = IMAGEMANAGER->findImage("player_enforcer");
}

void pEnforcer::pressDirection(int dir)
{
	playerableBase::pressDirection(dir);

	// 방패 들기 중, 방향 고정
	if (_infoPlayerable.special & PLAYERABLE_SPECIAL_BLOCK) _info.draw.isLeft = _skill_3_fixedDirection;
}

void pEnforcer::initStatus()
{
	_infoCharacter.status_basic.HP = 119;
	_infoCharacter.status_basic.regen = 1.1f;
	_infoCharacter.status_basic.atk = 12;
	_infoCharacter.status_basic.def = 0;
	_infoCharacter.status_basic.spd_move *= 1.1f;
	_infoCharacter.status_basic.crit = 0.0f;

	_infoPlayerable.status_inc.HP = 50;

	_infoPlayerable.status_levelUp.HP = 34;
	_infoPlayerable.status_levelUp.regen = 0.2f;
	_infoPlayerable.status_levelUp.def = 2;
	_infoPlayerable.status_levelUp.atk = 3;

	calTotalStatus();

	getCurrentHP() = getCharStatus().HP;
}

void pEnforcer::initAnimation(void)
{
	animation* tAni;
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 8, 0 }, POINT{ 8, 0 }, false, false);		_ani->add("stand", tAni, true);	tAni->start();	tAni->setFPS(10);
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 8, 5 }, POINT{ 8, 5 }, false, false);		_ani->add("guard", tAni, true);	tAni->start();	tAni->setFPS(10);
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 10, 0 }, POINT{ 11, 0 }, false, true);	_ani->add("rope", tAni);		tAni->start();	tAni->setFPS(4);
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 13, 0 }, POINT{ 13, 0 }, false, false);	_ani->add("jump", tAni);		tAni->start();	tAni->setFPS(10);
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 8, 1 }, POINT{ 15, 1 }, false, true);		_ani->add("walk", tAni);		tAni->start();	tAni->setFPS(16);
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 8, 2 }, POINT{ 15, 2 }, false, true);		_ani->add("walk_g", tAni);		tAni->start();	tAni->setFPS(16);

	// skill
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 8, 3 }, POINT{ 21, 3 }, false, false);	_ani->add("skill_2", tAni);		tAni->start();	tAni->setFPS(16);
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 8, 4 }, POINT{ 15, 4 }, false, false);	_ani->add("skill_3_on", tAni);	tAni->start();	tAni->setFPS(16);
	tAni = new animation; tAni->init(_img); tAni->setPlayFrame(POINT{ 8, 5 }, POINT{ 13, 5 }, false, false);	_ani->add("skill_3_off", tAni);	tAni->start();	tAni->setFPS(16);

	// custom
	POINT posAttack[6];
	for (int i = 0; i < 6; ++i) posAttack[i] = { 0, i };
	tAni = new animation; tAni->init(550, 150, 100, 25); tAni->setPlayFrame(posAttack, 6, false);	_ani->add("skill_1_stand", tAni);		tAni->start();	tAni->setFPS(12);

	for (int i = 0; i < 6; ++i) posAttack[i] = { 1, i };
	tAni = new animation; tAni->init(550, 150, 100, 25); tAni->setPlayFrame(posAttack, 6, false);	_ani->add("skill_1_guard", tAni);		tAni->start();	tAni->setFPS(15);
}

void pEnforcer::initInfo(void)
{
	// baseObject
	_info.collision.rc = RECT{ -2, -2, 2, 11 };

	_infoPlayerable.kind |= PLAYERABLE_KIND_ENFORCER;

	_infoPlayerable.skillDelay[0] = 0.0f;
	_infoPlayerable.skillDelay[1] = 5.0f;
	_infoPlayerable.skillDelay[2] = 5.0f;
	_infoPlayerable.skillDelay[3] = 5.0f;
}

void pEnforcer::useSkill_0(void)
{
	if (_infoCharacter.movement & (ACT_MESSAGE_ROPE | ACT_MESSAGE_ATTACK)) return;

	_infoCharacter.movement |= ACT_MESSAGE_ATTACK;
	_infoCharacter.movement |= ACT_MESSAGE_SKILL_0;

	// send message
	tagMessage msg;
	msg.info.type = ACT_MESSAGE_SKILL_0;
	msg.info.paramValue = 0;
	msg.order = this;
	GAMESYSTEM->takeMessage(msg);

	if (_infoPlayerable.special & PLAYERABLE_SPECIAL_BLOCK)
		_ani->set("skill_1_guard", true);
	else
		_ani->set("skill_1_stand", true);
}

void pEnforcer::useSkill_1(void)
{
	if (_infoCharacter.movement & (ACT_MESSAGE_ROPE | ACT_MESSAGE_SKILL_1)) return;
	if (GAMESYSTEM->getTime() < _infoPlayerable.skillCooldown[1]) return;

	_infoCharacter.movement = bit_pick(_infoCharacter.movement, ACT_MESSAGE_SKILL_A);
	_infoCharacter.movement |= ACT_MESSAGE_ATTACK;
	_infoCharacter.movement |= ACT_MESSAGE_SKILL_1;

	// send message
	tagMessage msg;
	msg.info.type = ACT_MESSAGE_SKILL_1;
	msg.info.paramValue = _infoPlayerable.skillDelay[1];
	msg.order = this;
	GAMESYSTEM->takeMessage(msg);

	_infoPlayerable.skillCooldown[1] = GAMESYSTEM->getTime() + msg.info.paramValue;

	_ani->set("skill_2");
}

void pEnforcer::useSkill_2(void)
{
	if (_infoCharacter.movement & (ACT_MESSAGE_ROPE | ACT_MESSAGE_ATTACK)) return;
	if (GAMESYSTEM->getTime() < _infoPlayerable.skillCooldown[2]) return;

	_infoCharacter.movement |= ACT_MESSAGE_ATTACK;
	_infoCharacter.movement |= ACT_MESSAGE_SKILL_2;

	// send message
	tagMessage msg;
	msg.info.type = ACT_MESSAGE_SKILL_2;
	msg.info.paramValue = _infoPlayerable.skillDelay[2];
	msg.order = this;
	GAMESYSTEM->takeMessage(msg);

	if (_infoPlayerable.special & PLAYERABLE_SPECIAL_BLOCK)
	{
		_infoPlayerable.skillCooldown[2] = GAMESYSTEM->getTime() + msg.info.paramValue;
		_infoPlayerable.status_mlt.spd_move += 0.25f;
		_ani->set("skill_3_off", true);
	}
	else
	{
		_infoPlayerable.skillCooldown[2] = GAMESYSTEM->getTime() + (5.0f * (msg.info.paramValue / _infoPlayerable.skillDelay[2]));
		_infoPlayerable.status_mlt.spd_move -= 0.25f;
		_ani->set("skill_3_on", true);
	}
	calTotalStatus();	// 이동속도 변화
}

void pEnforcer::useSkill_3(void)
{
	if (_infoCharacter.movement & (ACT_MESSAGE_ROPE | ACT_MESSAGE_ATTACK)) return;
	if (GAMESYSTEM->getTime() < _infoPlayerable.skillCooldown[3]) return;

	_infoCharacter.movement |= ACT_MESSAGE_ATTACK;
	_infoCharacter.movement |= ACT_MESSAGE_SKILL_3;

	// send message
	tagMessage msg;
	msg.info.type = ACT_MESSAGE_SKILL_3;
	msg.info.paramValue = _infoPlayerable.skillDelay[3];
	msg.order = this;
	GAMESYSTEM->takeMessage(msg);

	_infoPlayerable.skillCooldown[3] = GAMESYSTEM->getTime() + msg.info.paramValue;

	if (_infoPlayerable.special & PLAYERABLE_SPECIAL_BLOCK)
		_ani->set("skill_1_guard", true);
	else
		_ani->set("skill_1_stand", true);
}

void pEnforcer::ctrlAnimation(void)
{
	tagCharacterStatus nowStat; putCharStatus(&nowStat);
	int & move = _infoCharacter.movement;

	if (move & ACT_MESSAGE_DEAD)
		_ani->set("dead");
	else if (move & ACT_MESSAGE_ROPE)
	{
		_ani->set("rope");

		if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN))
			_ani->update();
	}
	else if (move & ACT_MESSAGE_ATTACK)
	{
		_ani->update(getCharStatus().spd_atk);

		DWORD & index = _ani->get()->getNowPlayIndex();

		// movement
		if (move & ACT_MESSAGE_SKILL_0)
		{
			switch (index)
			{
			case 0: {
				if (_isShoot) break;

				bullet_Enforcer_0 * b = new bullet_Enforcer_0;
				POINT offset = { -3, 0 };
				b->init(this, offset);
				BULLETMANAGER->add(b);
				
				SOUNDMANAGER->find("player_enforcer_attack_1")->play(0.5f, getCharStatus().spd_atk);

				_isShoot = true;
			} break;

			default: _isShoot = false; break;
			}
		}
		if (move & ACT_MESSAGE_SKILL_1)
		{
			switch (index)
			{
			case 5: {
				if (_isShoot) break;

				bullet_Enforcer_1 * b = new bullet_Enforcer_1;
				POINT offset = { -10, 0 };
				b->init(this, offset);
				BULLETMANAGER->add(b);
				
				SOUNDMANAGER->find("player_comando_attack_2")->play(0.5f);

				_isShoot = true;
			} break;

			default: _isShoot = false; break;
			}
		}
		if (move & ACT_MESSAGE_SKILL_2)
		{
			switch (index)
			{
			case 3: {
				if (_isShoot) break;

				CAMERAMANAGER->find("gameMap")->putShake(0.1f, 0.1f);

				SOUNDMANAGER->find("gun_heavy_2")->play(0.5f);

				_isShoot = true;
			} break;

			default: _isShoot = false; break;
			}

			if (!_ani->get()->isPlay())
			{
				if (_infoPlayerable.special & PLAYERABLE_SPECIAL_BLOCK)
					_infoPlayerable.special = bit_pick(_infoPlayerable.special, PLAYERABLE_SPECIAL_BLOCK);
				else
				{
					_infoPlayerable.special |= PLAYERABLE_SPECIAL_BLOCK;
					_skill_3_fixedDirection = _info.draw.isLeft;
				}
			}
		}
		if (move & ACT_MESSAGE_SKILL_3)
		{
			switch (index)
			{
			case 0: {
				if (_isShoot) break;

				bullet_Enforcer_3 * b = new bullet_Enforcer_3;
				b->init(this);
				BULLETMANAGER->add(b);

				SOUNDMANAGER->find("player_enforcer_attack_4")->play(0.625f, 0.75f);

				_isShoot = true;
			} break;

			default: _isShoot = false; break;
			}
		}

		if (!_ani->get()->isPlay())
		{
			move = bit_pick(move, ACT_MESSAGE_ATTACK | ACT_MESSAGE_SKILL_A);
		}
	}
	else if ((move & ACT_MESSAGE_LAND) == 0)
		_ani->set("jump");
	else if (move & ACT_MESSAGE_MOVE)
	{
		if (_infoPlayerable.special & PLAYERABLE_SPECIAL_BLOCK)
			_ani->set("walk_g");
		else
			_ani->set("walk");

		_ani->update();
	}
	else
	{
		if (_infoPlayerable.special & PLAYERABLE_SPECIAL_BLOCK)
			_ani->set("guard");
		else
			_ani->set("stand");
	}
}
