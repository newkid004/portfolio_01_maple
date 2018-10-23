#include "stdafx.h"
#include "txtDataManager.h"


HRESULT txtDataManager::init(void)
{
	return S_OK;
}

void txtDataManager::release(void)
{
}

// 한 줄 짜리 데이터를 담아둘 것(Line 단위로 구분하여 저장)
void txtDataManager::save(const char * fileName, vector<string> vStr)
{
	HANDLE file;
	char str[SAVEBUFFER];
	DWORD write;

	// strncpy_s : 복사할 크기를 인자로 잡아줄 수 있다
	// 변수명, 변수, 길이
	// strncpy_s, strncpy : NULL문자 자동 삽입 유무
	strncpy_s(str, SAVEBUFFER, vectorArrayCombine(vStr), SAVEBUFFER - 1);

	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}

// 현재 사용할 데이터(한 줄 짜리 데이터를 쉼표 단위로 구분하여 저장)
char * txtDataManager::vectorArrayCombine(vector<string> vArray)
{
	char str[SAVEBUFFER];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < (int)vArray.size(); i++)
	{
		// strcat : 문자열 결합
		// c_str : string클래스 -> cstr형으로 변환
		strncat_s(str, SAVEBUFFER, vArray[i].c_str(), SAVEBUFFER - 1);
		if (i + 1 < (int)vArray.size()) strcat_s(str, ",");
	}
	return str;
}

vector<string> txtDataManager::load(const char * fileName)
{
	HANDLE file;
	char str[LOADBUFFER];
	DWORD read;

	memset(str, 0, LOADBUFFER);
	file = CreateFile(fileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, LOADBUFFER, &read, NULL);
	CloseHandle(file);
	return charArraySeparation(str);
}

vector<string> txtDataManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* separator = ",";	// 분리
	// 컴파일러가 인식할 수 있는 기본 요소
	// 연산자, 식별자, 문자, 부호 등...
	char* token;
	char* token2;

	// 문자열을 토큰으로 분리
	// 자른 문자열 = strtok_s(분리할 문자열, 구분 문자, 자른 후 나머지 문자열);
	token = strtok_s(charArray, separator, &token2);

	while (NULL != (token = strtok_s(NULL, separator, &token2)))
	{
		vArray.push_back(token);
	}

	return vector<string>();
}