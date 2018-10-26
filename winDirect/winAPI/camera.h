#pragma once
#define REAL_POINT

#ifdef REAL_POINT
#define PNT fPOINT
#else
#define PNT POINT
#endif // REAL_POINT


struct tagShake
{
	float time;

	float decValue;
	float interval;

	PNT offset;
};

class camera
{
private:
	PNT _position;
	PNT _offset;
	PNT _size;

	PNT _minPos;
	PNT _maxPos;
	
	tagShake _shake;

public :	// FW
	void init(void);
	void init(PNT offset);
	void init(PNT offset, PNT size);
	void init(PNT offset, PNT size, PNT minPos, PNT maxPos);
	void init(PNT position, PNT offset, PNT size, PNT minPos, PNT maxPos);

	void update(float elipsedTime);
	void updateShake(float elipsedTime);

public :	// 보조
	void putShake(float time = 0.3f, float interval = 2.0f, float decValue = 1.0f);

public :	// 접근 / 지정자
	void setPosition(PNT pos) { _position = pos; };
	void setOffset(PNT pos);
	void moveOffset(int posX, int posY);
	void moveOffset(PNT move);
	void setSize(PNT size);
	void setMinPos(PNT pos);
	void setMaxPos(PNT pos);

	PNT &getPosition(void) { return _position; };
	PNT &getOffset(void) { return _offset; };
	PNT &getSize(void) { return _size; };
	PNT &getShakedOffset(void) { return _shake.offset; };

	RECT getRect() { return RectMake(_position.x, _position.y, _size.x, _size.y); };
	fRECT getFRect() { return pos2fRect(fPOINT(_position.x, _position.y), fPOINT(_size.x, _size.y)); };
	RECT getCameraRect() { return RectMake(_offset.x, _offset.y, _offset.x + _size.x, _offset.y + _size.y); };
	fRECT getCameraFRect() { return pos2fRect(fPOINT(_offset.x, _offset.y), fPOINT(_offset.x + _size.x, _offset.y + _size.y)); };
	PNT getCameraInnerPos(float posX, float posY);	// 카메라 안 비율대비 좌표

	tagShake & getShake() { return _shake; };

	camera() { init(); };
	~camera() {};
};