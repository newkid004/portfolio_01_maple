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

struct fPOINT
{
	float x;
	float y;
};
struct dPOINT
{
	double x;
	double y;
};
struct physicF
{
	fPOINT pos;
	float radian;
	float speed;
};
struct physicD
{
	dPOINT pos;
	double radian;
	double speed;
};

namespace MY_UTIL
{
	// ----- float ----- //
	inline POINT pos2point(fPOINT & fpos) { return POINT{ (long)fpos.x, (long)fpos.y }; }
	inline fPOINT point2fpos(POINT & pos) { return fPOINT{ (float)pos.x, (float)pos.y }; };
	inline fPOINT point2fpos(POINT * pos) { return fPOINT{ (float)pos->x, (float)pos->y }; };
	inline float getDeltaX(float & radian, float & distance) { return cos(radian) * distance; };
	inline float getDeltaY(float & radian, float & distance) { return -sin(radian) * distance; };
	inline fPOINT getDeltaPt(fPOINT & pos1, fPOINT & pos2) { return fPOINT{ pos2.x - pos1.x, pos2.y - pos1.y }; };

	inline float getDistance(fPOINT & pos1, fPOINT & pos2)
	{
		return sqrt(
			getDeltaPt(pos1, pos2).x * getDeltaPt(pos1, pos2).x +
			getDeltaPt(pos1, pos2).y * getDeltaPt(pos1, pos2).y);
	};

	inline float Deg2Rad(float & Degree) { return PI / 180.0f * Degree; };
	inline float Rad2Deg(float & Radian) { return 180.0f / PI * Radian; };
	inline float normalizeAngle(float & radian) 
	{
		if (radian < 0.0f)	return radian + ((float)((int)(-radian / PI2) + 1) * PI2);
		else				return radian - ((float)((int)(radian / PI2)) * PI2);
	};
	// inline float getDegree(dPOINT pos1, dPOINT pos2) { return acos(getDeltaPt(pos1, pos2).x / getDistance(pos1, pos2)); };
	inline float getRadian(fPOINT & pos1, fPOINT & pos2) 
	{
		fPOINT deltaPt = getDeltaPt(pos1, pos2);
		float radian = atan2(-deltaPt.y, deltaPt.x);
		if (radian < 0) radian = PI2 + radian;
		return radian;
	};

	inline fPOINT getDeltaPos(fPOINT pos, float radian, float distance) { return fPOINT{ pos.x + cos(radian) * distance, pos.y + -sin(radian) * distance }; };
	inline fPOINT getDeltaPos(physicF & p) { return fPOINT{ p.pos.x + cos(p.radian) * p.speed, p.pos.y + -sin(p.radian) * p.speed }; }

	inline float getHommingRadian(float sourRadian, float destRadian, float hommingValue)	// hommingVale = 0.0 ~ 1
	{
		// degree형 각 계산
		float sourAngle = normalizeAngle(sourRadian);
		float destAngle = normalizeAngle(destRadian);

		float changeAngle;
		float angle1 = destAngle - (sourAngle + hommingValue);
		float angle2 = destAngle - (sourAngle - hommingValue);
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

	inline bool IsCrashEllipse(fPOINT & pos1, float & radius1, fPOINT & pos2, float & radius2) { return getDistance(pos1, pos2) < (radius1 + radius2); }

	inline fPOINT addF(fPOINT & p1, fPOINT & p2) { return fPOINT{ p1.x + p2.x, p1.y + p2.y }; };
	inline fPOINT decF(fPOINT & p1, fPOINT & p2) { return fPOINT{ p1.x - p2.x, p1.y - p2.y }; };
	inline fPOINT mltF(fPOINT & p1, fPOINT & p2) { return fPOINT{ p1.x * p2.x, p1.y * p2.y }; };
	inline fPOINT devF(fPOINT & p1, fPOINT & p2) { return fPOINT{ p1.x / p2.x, p1.y / p2.y }; };

	inline float getAngle(fPOINT pos1, fPOINT pos2)
	{
		float x = pos2.x - pos1.x;
		float y = pos2.y - pos1.y;
		float d = sqrt(x * x + y * y);
		float angle = acos(x / d);
		if (y > 0) angle = PI2 - angle;	
		return angle;
	}

	// ----- double ----- //
	inline POINT pos2point(dPOINT & fpos) { return POINT{ (long)fpos.x, (long)fpos.y }; }
	inline dPOINT point2dpos(POINT & pos) { return dPOINT{ (double)pos.x, (double)pos.y }; };
	inline double getDeltaX(double & radian, double & distance) { return cos(radian) * distance; };
	inline double getDeltaY(double & radian, double & distance) { return -sin(radian) * distance; };
	inline dPOINT getDeltaPt(dPOINT & pos1, dPOINT & pos2) { return dPOINT{ pos2.x - pos1.x, pos2.y - pos1.y }; };

	inline double getDistance(dPOINT & pos1, dPOINT & pos2)
	{
		return sqrt(
			getDeltaPt(pos1, pos2).x * getDeltaPt(pos1, pos2).x +
			getDeltaPt(pos1, pos2).y * getDeltaPt(pos1, pos2).y);
	};

	inline double Deg2Rad(double & Degree) { return PI / 180.0 * Degree; };
	inline double Rad2Deg(double & Radian) { return 180.0 / PI * Radian; };
	inline double normalizeAngle(double & radian)
	{
		if (radian < 0.0)	return radian + ((double)((long)(-radian / PI2) + 1) * PI2);
		else				return radian - ((double)((long)(radian / PI2)) * PI2);
	};
	// inline double getDegree(dPOINT pos1, dPOINT pos2) { return acos(getDeltaPt(pos1, pos2).x / getDistance(pos1, pos2)); };
	inline double getRadian(dPOINT & pos1, dPOINT & pos2)
	{
		dPOINT deltaPt = getDeltaPt(pos1, pos2);
		double radian = atan2(-deltaPt.y, deltaPt.x);
		if (radian < 0) radian = PI2 + radian;
		return radian;
	};

	inline dPOINT getDeltaPos(dPOINT pos, double & radian, double & distance) { return dPOINT{ pos.x + cos(radian) * distance, pos.y + -sin(radian) * distance }; };
	inline dPOINT getDeltaPos(physicD & p) { return dPOINT{ p.pos.x + cos(p.radian) * p.speed, p.pos.y + -sin(p.radian) * p.speed }; }

	inline double getHommingRadian(double sourRadian, double destRadian, double hommingValue)
	{
		// degree형 각 계산
		double sourDegree = sourRadian < 0 ? PI2 + sourRadian : sourRadian;
		double destDegree = destRadian < 0 ? PI2 + destRadian : destRadian;

		double changeAngle;
		double angle1 = destDegree - sourDegree;
		double angle2 = sourDegree - destDegree;
		angle1 = angle1 < 0 ? angle1 + PI2 : angle1;
		angle2 = angle2 < 0 ? angle2 + PI2 : angle2;
		changeAngle = angle1 < angle2 ? angle1 : angle2; // 더 작은 각의 방향으로

		// degree -> radian
		if (angle2 < angle1) changeAngle = -(PI - changeAngle);

		return changeAngle * hommingValue;
	}

	inline dPOINT addD(dPOINT & p1, dPOINT & p2) { return dPOINT{ p1.x + p2.x, p1.y + p2.y }; };
	inline dPOINT decD(dPOINT & p1, dPOINT & p2) { return dPOINT{ p1.x - p2.x, p1.y - p2.y }; };
	inline dPOINT mltD(dPOINT & p1, dPOINT & p2) { return dPOINT{ p1.x * p2.x, p1.y * p2.y }; };
	inline dPOINT devD(dPOINT & p1, dPOINT & p2) { return dPOINT{ p1.x / p2.x, p1.y / p2.y }; };

	inline bool IsCrashEllipse(dPOINT & pos1, double & radius1, dPOINT & pos2, double & radius2) { return getDistance(pos1, pos2) < (radius1 + radius2); }

	inline double getAngle(dPOINT pos1, dPOINT pos2)
	{
		double x = pos2.x - pos1.x;
		double y = pos2.y - pos1.y;
		double d = sqrt(x * x + y * y);
		double angle = acos(x / d);
		if (y > 0) angle = PI2 - angle;
		return angle;
	}

	// ----- bit ----- //
	inline int bit_put(int b1, int b2) { return b1 | b2; };
	inline int bit_reverse(int b) { return 0xFFFFFF - b; };
	inline int bit_pick(int b1, int b2) { return b1 & bit_reverse(b2); };
}

