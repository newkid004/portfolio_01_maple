#pragma once
#include "singletonBase.h"

class gameNode;

class 
sceneManager : public singletonBase<sceneManager>
{
public :
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private :
	static gameNode* _currentScene;		// 현재 씬
	static gameNode* _loadingScene;		// 로딩 씬
	static gameNode* _readyScene;		// 교체 대기중인 씬

	mapSceneList _mSceneList;			// 씬 리스트
	mapSceneList _mLoadingSceneList;	// 로딩 씬 리스트

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// 씬 추가
	gameNode* addScene(string sceneName, gameNode* scene);
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	// 씬 변경
	HRESULT changeScene(string sceneName, bool isInit = true);

	// 씬 초기화
	HRESULT initScene(string sceneName);

	// 씬 가져오기
	gameNode* find(string sceneName);

	// friend
	// 정보은닉을 허물어버리는 키워드
	// private까지 모두 접근이 가능
	// 클래스 외부에서 작성된 함수 or 변수 접근가능
	// friend 선언은 단방향으로 이루어짐

	// LPVOID : void* 형(어떤 타입이든 변환가능)
	// 로딩 쓰레드 함수
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	sceneManager() {};
	~sceneManager() {};
};

