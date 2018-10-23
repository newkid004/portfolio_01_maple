#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init(void)
{


	return S_OK;
}

void iniData::release(void)
{
}

void iniData::addData(char * section, char * key, char * value)
{
	// ini 데이터 구조체 선언 후 초기화
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	// ini데이터 구조체 벡터에 넣기
	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

void iniData::iniSave(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(str, sizeof(dir));
	// sprintf : 특정 버퍼에 특정 형식으로 문자를 기록
	sprintf_s(dir, "\\save/%s.ini", fileName);

	// 현재 폴더명 가져오기
	// GetCurrentDirectory(작업 디렉토리의 경로 버퍼크기, 작업 디렉토리의 경로)
	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	for (int i = 0; i < (int)_vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];

		// 파일 쓰기
		// WritePrivateProfileString
		// 파일에 정보(문자열)을 쓰며 해당 섹션과 키값이 없으면 자동으로 생성해주는 함수
		WritePrivateProfileString(
			vData[0].section,
			vData[0].key,
			vData[0].value,
			str);

		vData.clear();
	}
	_vIniData.clear();
}

char * iniData::loadDataString(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(str, sizeof(dir));
	sprintf_s(dir, "\\save\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	char data[64] = { NULL };

	// 파일 읽기
	// GetPrivateProfileString
	// 파일의 정보(문자열)를 읽어오는 함수
	GetPrivateProfileString(
		section,
		key,
		"",			// section, key 불일치 : defalut값
		data,		// value를 저장할 버퍼
		64,			// 버퍼 사이즈
		str);

	return data;
}

int iniData::loadDataInt(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(str, sizeof(dir));
	sprintf_s(dir, "\\save\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	// GetPrivateProfileInt
	// 파일의 정보(정수)를 읽어오는 함수
	return GetPrivateProfileInt(section, key, 0, str);;
}
