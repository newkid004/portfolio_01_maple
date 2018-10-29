#pragma once

#define DEG_TO_RID			0.017453f	// degree 1도의 radian 값
#define PI					3.141592654f
#define PI2					6.283185308f

// 부동소수점은 정확한 실수표현 불가능
// : 컴퓨터가 표현할 실수는 한계가 있기 때문
// -> 근사값 표현 -> 부동소수점 반올림 오차
#define FLOAT_EPSILON		0.001f

// 캐스팅 연산자 : static_cast<type>(obj) -> 논리적으로 성립이 될 때 형변환 실행
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)

#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)

#define FLOAT_USE	

#ifdef  FLOAT_USE
#define NUM_REAL	float
#else
#define NUM_REAL	double
#endif

//ray 한방향에 쏘는 갯수
#define RAY_NUM				3


struct fPOINT
{
	NUM_REAL x;
	NUM_REAL y;

	fPOINT()						{ this->x = 0; this->y = 0; }
	fPOINT(NUM_REAL xy)				{ this->x = xy; this->y = xy; };
	fPOINT(NUM_REAL x, NUM_REAL y) { this->x = x; this->y = y; };

	fPOINT operator+(fPOINT input) { return fPOINT(this->x + input.x, this->y + input.y); }
	fPOINT operator-(fPOINT input) { return fPOINT(this->x - input.x, this->y - input.y); }
	fPOINT operator*(fPOINT input) { return fPOINT(this->x * input.x, this->y * input.y); }
	fPOINT operator/(fPOINT input) { return fPOINT(this->x / input.x, this->y / input.y); }

	fPOINT operator+(NUM_REAL input) { return fPOINT(this->x + input, this->y + input); }
	fPOINT operator-(NUM_REAL input) { return fPOINT(this->x - input, this->y - input); }
	fPOINT operator*(NUM_REAL input) { return fPOINT(this->x * input, this->y * input); }
	fPOINT operator/(NUM_REAL input) { return fPOINT(this->x / input, this->y / input); }

	void operator+=(fPOINT input) { this->x += input.x; this->y += input.y; };
	void operator-=(fPOINT input) { this->x -= input.x; this->y -= input.y; };
	void operator*=(fPOINT input) { this->x *= input.x; this->y *= input.y; };
	void operator/=(fPOINT input) { this->x /= input.x; this->y /= input.y; };

	void operator+=(NUM_REAL input) { this->x += input; this->y += input; }
	void operator-=(NUM_REAL input) { this->x -= input; this->y -= input; }
	void operator*=(NUM_REAL input) { this->x *= input; this->y *= input; }
	void operator/=(NUM_REAL input) { this->x /= input; this->y /= input; }
};

struct fRECT
{
	fPOINT LT;
	fPOINT RB;

	fRECT() {}
	fRECT(fPOINT LT, fPOINT RB) { this->LT = LT; this->RB = RB; };
	fRECT(NUM_REAL left, NUM_REAL top, NUM_REAL right, NUM_REAL bottom) 
	{ 
		this->LT = fPOINT(left, top);
		this->RB = fPOINT(right, bottom); 
	}

	fRECT operator+(fPOINT input) { return fRECT(fPOINT(LT + input), fPOINT(RB + input)); }
	fRECT operator-(fPOINT input) { return fRECT(fPOINT(LT - input), fPOINT(RB - input)); }
	fRECT operator*(fPOINT input) { return fRECT(fPOINT(LT * input), fPOINT(RB * input)); }
	fRECT operator/(fPOINT input) { return fRECT(fPOINT(LT / input), fPOINT(RB / input)); }

	fRECT operator+(NUM_REAL input) { return fRECT(fPOINT(LT + input), fPOINT(RB + input)); }
	fRECT operator-(NUM_REAL input) { return fRECT(fPOINT(LT - input), fPOINT(RB - input)); }
	fRECT operator*(NUM_REAL input) { return fRECT(fPOINT(LT * input), fPOINT(RB * input)); }
	fRECT operator/(NUM_REAL input) { return fRECT(fPOINT(LT / input), fPOINT(RB / input)); }
};

struct physicF
{
	fPOINT pos;
	NUM_REAL radian;
	NUM_REAL speed;
};


namespace MY_UTIL
{
	// ----- NUM_REAL ----- //
	inline POINT pos2point(fPOINT & fpos) { return POINT{ (long)fpos.x, (long)fpos.y }; }
	inline fPOINT point2fpos(POINT & pos) { return fPOINT{ (NUM_REAL)pos.x, (NUM_REAL)pos.y }; };
	inline fPOINT point2fpos(POINT * pos) { return fPOINT{ (NUM_REAL)pos->x, (NUM_REAL)pos->y }; };
	
	inline NUM_REAL getDeltaX(NUM_REAL & radian, NUM_REAL & distance) { return cos(radian) * distance; };
	inline NUM_REAL getDeltaY(NUM_REAL & radian, NUM_REAL & distance) { return -sin(radian) * distance; };
	inline fPOINT getDeltaPt(fPOINT & pos1, fPOINT & pos2) { return fPOINT{ pos2.x - pos1.x, pos2.y - pos1.y }; };

	inline NUM_REAL getDistance(fPOINT & pos1, fPOINT & pos2)
	{
		return sqrt(
			getDeltaPt(pos1, pos2).x * getDeltaPt(pos1, pos2).x +
			getDeltaPt(pos1, pos2).y * getDeltaPt(pos1, pos2).y);
	};

	inline NUM_REAL Deg2Rad(NUM_REAL & Degree) { return PI / 180.0f * Degree; };
	inline NUM_REAL Rad2Deg(NUM_REAL & Radian) { return 180.0f / PI * Radian; };
	inline NUM_REAL normalizeAngle(NUM_REAL & radian) 
	{
		if (radian < 0.0f)	return radian + ((NUM_REAL)((int)(-radian / PI2) + 1) * PI2);
		else				return radian - ((NUM_REAL)((int)(radian / PI2)) * PI2);
	};
	// inline NUM_REAL getDegree(dPOINT pos1, dPOINT pos2) { return acos(getDeltaPt(pos1, pos2).x / getDistance(pos1, pos2)); };
	inline NUM_REAL getRadian(fPOINT & pos1, fPOINT & pos2) 
	{
		fPOINT deltaPt = getDeltaPt(pos1, pos2);
		NUM_REAL radian = atan2(-deltaPt.y, deltaPt.x);
		if (radian < 0) radian = PI2 + radian;
		return radian;
	};

	inline fPOINT getDeltaPos(fPOINT pos, NUM_REAL radian, NUM_REAL distance) { return fPOINT{ pos.x + cos(radian) * distance, pos.y + -sin(radian) * distance }; };
	inline fPOINT getDeltaPos(physicF & p) { return fPOINT{ p.pos.x + cos(p.radian) * p.speed, p.pos.y + -sin(p.radian) * p.speed }; }

	inline NUM_REAL getHommingRadian(NUM_REAL sourRadian, NUM_REAL destRadian, NUM_REAL hommingValue)	// hommingVale = 0.0 ~ 1
	{
		// degree형 각 계산
		NUM_REAL sourAngle = normalizeAngle(sourRadian);
		NUM_REAL destAngle = normalizeAngle(destRadian);

		NUM_REAL changeAngle;
		NUM_REAL angle1 = destAngle - (sourAngle + hommingValue);
		NUM_REAL angle2 = destAngle - (sourAngle - hommingValue);
		if (fabs(angle1) < fabs(angle2))
		{
			changeAngle = sourAngle + hommingValue;
			if (destRadian < changeAngle) changeAngle = destRadian;
		}
		else
		{
			changeAngle = sourAngle - hommingValue;
			if (changeAngle < destRadian) changeAngle = destRadian;
		}

		return changeAngle;
	}

	inline bool IsCrashEllipse(fPOINT & pos1, NUM_REAL & radius1, fPOINT & pos2, NUM_REAL & radius2) { return getDistance(pos1, pos2) < (radius1 + radius2); }

	inline fPOINT addF(fPOINT & p1, fPOINT & p2) { return fPOINT{ p1.x + p2.x, p1.y + p2.y }; };
	inline fPOINT decF(fPOINT & p1, fPOINT & p2) { return fPOINT{ p1.x - p2.x, p1.y - p2.y }; };
	inline fPOINT mltF(fPOINT & p1, fPOINT & p2) { return fPOINT{ p1.x * p2.x, p1.y * p2.y }; };
	inline fPOINT devF(fPOINT & p1, fPOINT & p2) { return fPOINT{ p1.x / p2.x, p1.y / p2.y }; };

	inline NUM_REAL getAngle(fPOINT pos1, fPOINT pos2)
	{
		NUM_REAL x = pos2.x - pos1.x;
		NUM_REAL y = pos2.y - pos1.y;
		NUM_REAL d = sqrt(x * x + y * y);
		NUM_REAL angle = acos(x / d);
		if (y > 0) angle = PI2 - angle;	
		return angle;
	}
	// -----fRECT----- //
	inline fRECT rect2fRect(RECT& rect) { return fRECT{ fPOINT{ (NUM_REAL)rect.left,(NUM_REAL)rect.top },fPOINT{ (NUM_REAL)rect.right,(NUM_REAL)rect.bottom } }; }
	inline fRECT rect2fRect(RECT* rect) { return fRECT{ fPOINT{ (NUM_REAL)rect->left,(NUM_REAL)rect->top },fPOINT{ (NUM_REAL)rect->right,(NUM_REAL)rect->bottom } }; }

	inline fRECT  pos2fRect(fPOINT startPoint, fPOINT endPoint) { return fRECT{ startPoint,endPoint }; }
	inline fRECT  point2fRect(POINT startPoint, POINT endPoint) { return fRECT{ point2fpos(startPoint),point2fpos(endPoint) }; }
	
	// ----- bit ----- //
	inline int bit_put(int b1, int b2) { return b1 | b2; };
	inline int bit_reverse(int b) { return 0x7FFFFFF - b; };
	inline int bit_pick(int b1, int b2) { return b1 & bit_reverse(b2); };
	inline int bit_flip(int b1, int b2) { return b1 ^ b2; };
}

