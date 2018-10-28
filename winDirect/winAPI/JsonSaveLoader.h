 #pragma once
 #include "singletonBase.h"
 
 #define DATA_FILE_NAME "SaveData.json"

 
 class JsonSaveLoader : public singletonBase <JsonSaveLoader>
 {
 private:
 	void saveString(char* fileName, string data);
 	void saveStringWithFileStream(char* fileName, string data);
 	string loadString(char* fileName);
 	string loadStringWithFileStream(char* fileName);
 
 public:
 	HRESULT init(void);
 	void release(void);
 	void saveJsonFile(char* fileName, Json::Value root);
 	Json::Value loadJsonFile(char* fileName);
 
 	JsonSaveLoader() {}
 	~JsonSaveLoader() {}
 };