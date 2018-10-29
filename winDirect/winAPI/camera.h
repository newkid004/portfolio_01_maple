#pragma once

struct tagShake
{
	float time;

	float decValue;
	float interval;

	POINT offset;
};

class camera
{
private:
	POINT _position;
	POINT _offset;
	POINT _size;

	POINT _minPos;
	POINT _maxPos;
	
	tagShake _shake;

public :	// FW
	void init(void);
	void init(POINT offset);
	void init(POINT offset, POINT size);
	void init(POINT offset, POINT size, POINT minPos, POINT maxPos);
	void init(POINT position, POINT offset, POINT size, POINT minPos, POINT maxPos);

	void update(float elipsedTime);
	void updateShake(float elipsedTime);

public :	// 보조
	void putShake(float time = 0.3f, float interval = 2.0f, float decValue = 1.0f);

public :	// 접근 / 지정자
	void setPosition(POINT pos) { _position = pos; };
	void setOffset(POINT pos);
	void moveOffset(int posX, int posY);
	void moveOffset(POINT move);
	void setSize(POINT size);
	void setMinPos(POINT pos);
	void setMaxPos(POINT pos);

	POINT &getPosition(void) { return _position; };
	POINT &getOffset(void) { return _offset; };
	POINT &getSize(void) { return _size; };
	POINT &getShakedOffset(void) { return _shake.offset; };

	RECT getRect() { return RectMake(_position.x, _position.y, _size.x, _size.y); };
	RECT getCameraRect() { return RectMake(_offset.x, _offset.y, _offset.x + _size.x, _offset.y + _size.y); };
	POINT getCameraInnerPos(float posX, float posY);	// 카메라 안 비율대비 좌표

	tagShake & getShake() { return _shake; };

	camera() { init(); };
	~camera() {};
};