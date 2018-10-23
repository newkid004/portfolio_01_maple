#pragma once
#include "singletonBase.h"

#define SAVEBUFFER	128
#define LOADBUFFER	128

class txtDataManager : public singletonBase<txtDataManager>
{
public:
	HRESULT init(void);
	void release(void);
	
	// 세이브
	void save(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	// 로드
	vector<string> load(const char * fileName);
	vector<string> charArraySeparation(char charArray[]);

	txtDataManager() {};
	~txtDataManager() {};
};

