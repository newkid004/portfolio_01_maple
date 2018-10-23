#include "stdafx.h"
#include "JsonSaveLoader.h"

HRESULT JsonSaveLoader::init(void)
{
	return S_OK;
}

void JsonSaveLoader::release(void)
{
}

string JsonSaveLoader::loadString(char* fileName)
{
	TCHAR buf[8193];
	ZeroMemory(buf, sizeof(buf));

	HANDLE file;
	DWORD dwBytes;

	file = CreateFile(fileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
		return "";
	}
	else
	{
		ReadFile(file, buf, 8192, &dwBytes, NULL);
		CloseHandle(file);
	}

	return string(buf);
}

void JsonSaveLoader::saveString(char* fileName, string data)
{
	TCHAR* buf = (TCHAR*)data.c_str();
	HANDLE file;
	WORD wc = 0xFEFF;
	DWORD dwBytes = 0;
	DWORD dwRead;

	file = CreateFile(fileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
	}
	else
	{
		//WriteFile(File, &wc, 2, &dwBytes, NULL);
		WriteFile(file, buf, strlen(buf) * sizeof(TCHAR), &dwRead, NULL);
		CloseHandle(file);
	}
}

string JsonSaveLoader::loadStringWithFileStream(char* fileName)
{
	ifstream fileIn;
	fileIn.open(fileName, ios::in);

	char data;
	string jsonStr;

	while (fileIn.get(data))
	{
		jsonStr += data;
	}

	fileIn.close();

	return jsonStr;
}

void JsonSaveLoader::saveStringWithFileStream(char* fileName, string data)
{
	ofstream outFile(fileName);

	outFile << data << endl;

	outFile.close();
}

void JsonSaveLoader::saveJsonFile(char* fileName, Json::Value root)
{
	Json::StyledWriter writer;
	string outputConfig = writer.write(root);
	//saveString(fileName, outputConfig);
	saveStringWithFileStream(fileName, outputConfig);
}

Json::Value JsonSaveLoader::loadJsonFile(char* fileName)
{
	//string jsonStr = loadString(fileName);
	string jsonStr = loadStringWithFileStream(fileName);
	if (jsonStr == "")
	{
		MessageBox(_hWnd, "데이터가 없다", "Warning", MB_OK);
		return NULL;
	}

	Json::Reader reader;
	Json::Value root;

	bool parsingRet = reader.parse(jsonStr, root);

	if (!parsingRet)
	{
		string errMsg = reader.getFormatedErrorMessages();
		MessageBox(_hWnd, errMsg.c_str(), "오류", MB_OK);
		PostQuitMessage(0);
	}

	return root;
}