#pragma once
#include "singletonBase.h"

//====================
// # randomFunction # 
//====================
class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction() {}

	HRESULT init() { return S_OK; }

	//getInt
	inline int getInt(int num)			{ return rand() % num; }
	inline int getInt(int min, int max)	{ return rand() % (max - min + 1) + min; }
	//주의사항: 0이 나오면 터진다
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	//getFloat 
	//0.0 ~ 1.0 RAND_MAX의 최대값 (32767)
	inline float getFloat(void)					{ return (float)rand() / (float)RAND_MAX; }
	inline float getFloat(float num)			{ return (float)rand() / (float)RAND_MAX * num; }
	inline float getFloat(float min, float max)	{ return (getFloat() * (max - min) + min); }
	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};