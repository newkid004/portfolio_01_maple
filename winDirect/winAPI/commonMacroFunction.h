#pragma once

enum e_DIR
{
	DIR_UP =		0b1000,
	DIR_DOWN =		0b0100,
	DIR_LEFT =		0b0010,
	DIR_RIGHT =		0b0001
};

// commonMacroFunction : 필요 함수는 직접 만들어서 추가함

// * POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x , y };
	return pt;
}

// * 선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

// * Rect 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x ,y, x + width, y + height };
	return rc;
}

// * Rect 중심점
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

// * 사각형 출력
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectanglePrint(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

// * 타원 출력
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// * 타원 중심점 출력
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

// * 원 중심점 출력
inline void EllipseMakeCenter(HDC hdc, int x, int y, int length)
{
	Ellipse(hdc, x - length / 2, y - length / 2, x + length / 2, y + length / 2);
}

// 충돌 영역 리사이징
inline RECT CollisionAreaResizeing(RECT &rcDest, int width, int height)
{
	RECT rc = {
		rcDest.left + width / 2,
		rcDest.top + height / 2,
		rcDest.right - width / 2,
		rcDest.bottom - height / 2
	};
	return rc;
}

// ----- 사용자 함수 -----
// * RECT이동
inline void moveRect(RECT& rc, int x, int y)
{
	rc.left		+= x;
	rc.right	+= x;
	rc.top		+= y;
	rc.bottom	+= y;
}
inline void moveRect(RECT& rc, POINT pos)
{
	rc.left		+= pos.x;
	rc.right	+= pos.x;
	rc.top		+= pos.y;
	rc.bottom	+= pos.y;
}

// * RECT resize
inline void resizeRect(RECT & rc, int direction, int x, int y)
{
	rc.top +=		(0 < (direction & DIR_UP))		* y;
	rc.bottom +=	(0 < (direction & DIR_DOWN))	* y;
	rc.left +=		(0 < (direction & DIR_LEFT))	* x;
	rc.right +=		(0 < (direction & DIR_RIGHT))	* x;
}

// * RECT 충돌 판정
inline bool IsCrash(RECT *rc1, RECT *rc2, int direction)
{
	bool isCrash = false;

	long *pMin, *pMax;
	long *bMin, *bMax;

	// 방향 판별
	if (direction == DIR_UP || direction == DIR_DOWN)
	{
		pMin = &rc1->left;	pMax = &rc1->right;
		bMin = &rc2->left;	bMax = &rc2->right;
	}
	else if (direction == DIR_LEFT || direction == DIR_RIGHT)
	{
		pMin = &rc1->top;	pMax = &rc1->bottom;
		bMin = &rc2->top;	bMax = &rc2->bottom;
	}

	// 폭 판별
	isCrash =
		(*bMin <= *pMin && *pMax <= *bMax) ||
		(*pMin <  *bMin && *bMin <  *pMax) ||
		(*pMin <  *bMax && *bMax <  *pMax);

	// 충돌 판별
	switch (direction)
	{
	case DIR_UP		:	isCrash &= rc1->top		< rc2->bottom	&& rc2->bottom	< rc1->bottom;	break;
	case DIR_DOWN	:	isCrash &= rc1->bottom	> rc2->top		&& rc2->top		> rc1->top;		break;
	case DIR_LEFT	:	isCrash &= rc1->left	< rc2->right	&& rc2->right	< rc1->right;	break;
	case DIR_RIGHT	:	isCrash &= rc1->right	> rc2->left		&& rc2->left	> rc1->left;	break;
	}

	return isCrash;
}

// * RECT 충돌 판정
inline bool IsCrash(RECT & rc1, RECT & rc2)
{
	if (rc1.left	< rc2.right &&
		rc1.top		< rc2.bottom &&
		rc1.right	> rc2.left &&
		rc1.bottom	> rc2.top)
		return true;

	return false;
}

// * RECT 벗어남 판정
inline bool IsEscape(RECT & rcMain, RECT & rcInner, int direction)
{
	bool isEscape = false;

	// 충돌 판별
	switch (direction)
	{
	case DIR_UP		:	isEscape = rcMain.bottom	< rcInner.bottom; 	break;
	case DIR_DOWN	:	isEscape = rcMain.top		> rcInner.top;		break;
	case DIR_LEFT	:	isEscape = rcMain.right		< rcInner.right;	break;
	case DIR_RIGHT	:	isEscape = rcMain.left		> rcInner.left; 	break;
	}

	return isEscape;
}

// * RECT 클릭 판정
inline bool IsClickRect(RECT &rc, POINT &cursor)
{
	return
		rc.top	< cursor.y && cursor.y < rc.bottom &&
		rc.left	< cursor.x && cursor.x < rc.right;
}

// * RECT 클릭 판정
inline bool IsClickRect(int x, int y, int w, int h, POINT &cursor)
{
	return
		y < cursor.y && cursor.y < h &&
		x < cursor.x && cursor.x < w;
}

// * RECT 모서리 클릭 판정
inline int IsClickEdge(RECT *rc, POINT cursor)
{
	int direction = 0;

	direction += 0b1000 * (rc->top - 10 < cursor.y && cursor.y < rc->top + 10);
	direction += 0b0100 * (rc->bottom - 10 < cursor.y && cursor.y < rc->bottom + 10);
	direction += 0b0010 * (rc->left - 10 < cursor.x && cursor.x < rc->left + 10);
	direction += 0b0001 * (rc->right - 10 < cursor.x && cursor.x < rc->right + 10);

	return direction;
}

// 선 충돌 판정 : 삼각형 내적, 외적을 이용한 공식?
inline bool IsCrashLine(POINT & L1sour, POINT & L1dest, POINT & L2sour, POINT & L2dest)
{
	float den = (L2dest.y - L2sour.y) * (L1dest.x - L1sour.x) - (L2dest.x - L2sour.x) * (L1dest.y - L1sour.y);
	
	// 평행선
	if (den == 0) return false;

	float ua = ((L2dest.x - L2sour.x) * (L1sour.y - L2sour.y) - (L2dest.y - L2sour.y) * (L1sour.x - L2sour.x)) / den;
	float ub = ((L1dest.x - L1sour.x) * (L1sour.y - L2sour.y) - (L1dest.y - L1sour.y) * (L1sour.x - L2sour.x)) / den;

	if (ua <= 0.0f || 1.0f <= ua || ub <= 0.0f || 1.0f <= ub) return false;

	return true;
}

inline POINT PointRectCenter(RECT & rc) { return POINT{ rc.right - (rc.right - rc.left) / 2, rc.bottom - (rc.bottom - rc.top) / 2 }; };

inline int getDirection2Speed(POINT speed)  { int direction = 0; direction |= (0 < speed.x) ? DIR_RIGHT : ((speed.x < 0) ? DIR_LEFT : 0); direction |= (0 < speed.y) ? DIR_DOWN : ((speed.y < 0) ? DIR_UP : 0); return direction; }
inline int getDirection2Speed(fPOINT speed) { int direction = 0; direction |= (0 < speed.x) ? DIR_RIGHT : ((speed.x < 0) ? DIR_LEFT : 0); direction |= (0 < speed.y) ? DIR_DOWN : ((speed.y < 0) ? DIR_UP : 0); return direction; }
//inline int getDirection2Speed(dPOINT speed) { int direction = 0; direction |= (0 < speed.x) ? DIR_RIGHT : ((speed.x < 0) ? DIR_LEFT : 0); direction |= (0 < speed.y) ? DIR_DOWN : ((speed.y < 0) ? DIR_UP : 0); return direction; }

inline int getDirection2Radian(float rad)
{
	int direction = 0;

	if (0 < rad)			direction |= DIR_UP;
	else					direction |= DIR_DOWN;
	if (PI / 2 < fabs(rad))	direction |= DIR_LEFT;
	else					direction |= DIR_RIGHT;

	return direction;
}

inline long RectWidth(RECT & rc) { return rc.right - rc.left; };
inline long RectHeight(RECT & rc) { return rc.bottom - rc.top; };

template<typename T>
inline void swaper(T &a, T &b) { T tempA = a; T tempB = b; a = tempB; b = tempA; }

// * 체력 바 출력
inline void PrintHpBar(HDC hdc, POINT & pos, POINT & size, double value[3], COLORREF color[3])
{
	// value -> now, max, damage

	// 예외처리
	if (value[1] < value[0] + value[2])
		value[2] += value[1] - (value[0] + value[2]);
	if (value[0] < 0) value[0] = 0;

	HBRUSH pBrush = CreateSolidBrush(color[1]);
	RECT rcTotal = RectMake(pos.x, pos.y, size.x, size.y);
	// 전체 값 출력
	FillRect(hdc, &rcTotal, pBrush);

	// 현재 값 출력
	int posNow = (int)(size.x * (value[0] / value[1]));
	if (value[0] != 0)
	{
		DeleteObject(pBrush);
		pBrush = CreateSolidBrush(color[0]);

		RECT rcNow = RectMake(pos.x, pos.y, posNow, size.y);
		FillRect(hdc, &rcNow, pBrush);
	}

	// 데미지 출력
	if (value[2] != 0)
	{
		DeleteObject(pBrush);
		pBrush = CreateSolidBrush(color[2]);

		int posDamage = (int)(size.x * ((float)(value[2]) / (float)value[1]));
		if (0 <= posDamage)
		{
			pos.x += posNow;
			RECT rcDamage = RectMake(pos.x, pos.y, posDamage, size.y);
			FillRect(hdc, &rcDamage, pBrush);
		}
	}

	// 브러쉬 해제
	DeleteObject(pBrush);
}