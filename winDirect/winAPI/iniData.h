#pragma once
#include "singletonBase.h"

/*
	<정의>
	응용 프로그램이나 윈도우 자체의 초기 설정값에 필요한 정보가 기입된 텍스트 파일
	
	<용도>
	주로 게임의 옵션을 다룰 때
	값이 자주 바뀌는 경우

	<구성> : Section, key, value
	[Section]
	Name = Value
*/

struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class iniData : public singletonBase<iniData>
{
private :
	typedef vector<tagIniData> arrIniData;
	typedef vector<arrIniData> arrIniDatas;

private :
	arrIniDatas _vIniData;

public :
	HRESULT init(void);
	void release(void);

	// 데이터 추가
	void addData(char* section, char* key, char* value);
	// 세이브
	void iniSave(char* fileName);

	// 문자값 로드
	char* loadDataString(char* fileName, char* section, char* key);
	// 정수값 로드
	int loadDataInt(char* fileName, char* section, char* key);

public:
	iniData() {};
	~iniData() {};
};

