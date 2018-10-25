#pragma once
#include "state.h"

class skillBase
{
public:
	enum class SKILLTYPE
	{
		ACTIVE, PASSIVE
	};

protected:
	typedef struct spend {
		NUM_REAL					_spendHp;						//hp 소모 비용
		NUM_REAL					_spendMP;						//mp 소모 비용

		NUM_REAL					_spendMoney;					//돈 소모 비용

		int							_spendWeapon_Thief;				//표창 소모 비용
		int							_spendWeapon_Archer;			//화살 소모 비용

	}SPEND;

protected:
	string						_name;								//스킬 이름
	string						_explain;							//스킬 설명

	SKILLTYPE					_skillType;							//스킬 타입 (패시브,액티브)		<- 건들지 말것
	SPEND						_spendStruct;						//스킬 사용 비용 구조체

	stateBasic					_adjStateBasic;						//hp,mp,공격력,방어력,마력,마법방어력 관련 적용 수치
	statePoint					_adjStatePoint;						//주스텟(str,dex,int,luk)적용 수치
	statePersent				_adjStatePersent;					//퍼센트 수치(주스텟,공격력,방어력,maxHp,maxMp,크리티컬 확률,크리티컬 데미지, 총데미지,보스공격력데미지 etc..)

	int							_Lv;
public:
	
	SKILLTYPE	getSkillType()		{ return _skillType; }
	SPEND		getSpendStruct()	{ return _spendStruct; }

	virtual HRESULT	init();
	virtual void release();
	virtual void render();

	skillBase() {};
	~skillBase() {};
};

