#pragma once

class image;

class animation
{
private :
	// 프레임 리스트
	typedef vector<fPOINT> _vFrameList;
	// 프레임 플레이 리스트
	typedef vector<int> _vPlayList;

private :
	int _frameNum;				// 프레임 수
	_vFrameList _frameList;		// 프레임 위치 리스트
	_vPlayList _playList;		// 플레이 리스트

	NUM_REAL _frameWidth;			// 프레임 가로크기
	NUM_REAL _frameHeight;			// 프레임 세로크기
	int _frameNumWidth;			// 가로 프레임 총 개수
	int _frameNumHeight;		// 세로 프레임 총 개수

	BOOL _isLoop;				// 루프 여부
	NUM_REAL _frameUpdateSec;		// 초당 프레임 업데이트 수
	NUM_REAL _elapsedSec;			// 프레임 사이 시간

	DWORD _nowPlayIndex;		// 현재 플레이 인덱스
	BOOL _isPlay;				// 플레이 여부

public:
	HRESULT init(image* img);
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);
	animation * update(float ratio = 1.0f);

	void setDefPlayFrame(BOOL reverse = NULL, BOOL loop = NULL);
	void setPlayFrame(int * playArr = NULL, int arrLen = 0, BOOL loop = NULL);
	void setPlayFrame(POINT * playArr, int arrLen = 0, BOOL loop = NULL);
	void setPlayFrame(int start, int end, BOOL reverse = NULL, BOOL loop = NULL);
	void setPlayFrame(POINT start, POINT end, BOOL reverse = NULL, BOOL loop = NULL);
	void setFrameIndex(int i) { _nowPlayIndex = i; };
	void setFrameIndex(int x, int y) { _nowPlayIndex = x + (y * _frameNumWidth); };
	void setFrameIndex(POINT pos) { setFrameIndex(pos.x, pos.y); };
	
	// 초당 프레임 갱신 횟수
	void setFPS(float framePerSec) { _frameUpdateSec = 1.0f / framePerSec; };
	void setElapsedSec(float eTime) { _elapsedSec = eTime; };
	void frameUpdate(float elpasedTime);

	void start(void);
	void stop(void);
	void pause(void);
	void resume(void);

	// 플레이 여부
	inline BOOL & isPlay(void) { return _isPlay; }
	inline BOOL & isLoop(void) { return _isLoop; }
	inline BOOL isEnd(void) { return _nowPlayIndex == (_playList.size() - 1); }
	// 프레임 위치
	inline fPOINT & getFramePos(void) { return _frameList[_playList[_nowPlayIndex]]; };
	inline fPOINT & getFramePosIndex(void) { fPOINT & p = _frameList[_playList[_nowPlayIndex]]; return fPOINT{ p.x / _frameWidth, p.y / _frameHeight }; }
	inline int & getFramePlay(void) { return _playList[_nowPlayIndex]; };
	// 프레임 크기
	inline NUM_REAL & getFrameWidth(void) { return _frameWidth; };
	inline NUM_REAL & getFrameHeight(void) { return _frameHeight; };
	inline fPOINT & getFrameSize(void) { return fPOINT{ _frameWidth, _frameHeight }; };
	// 현재 재생중인 프레임의 순번
	inline DWORD & getNowPlayIndex(void) { return _nowPlayIndex; };
	// 순차 프레임의 minFrame
	inline int & getMinPlayIndex(void) { return *_playList.begin(); };
	// 순차 프레임의 maxFrame : reverse 주의
	inline int & getMaxPlayIndex(void) { return *(_playList.end() - 1);};
	inline int getPlaySize(void) { return _playList.size(); };

	// 현 재생 프레임만 남기고 메모리 해제
	void setAnimationFixed(void);

public :	// operator
	void operator=(animation e);
	void operator=(animation* e);

	animation();
	~animation() {};
};

