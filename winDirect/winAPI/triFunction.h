#pragma once

/*

#define PI 3.14159265358979f

struct dPOINT
{
	double x;
	double y;
};

// 삼각함수
inline double getDeltaX(double radian, double distance) { return cos(radian) * distance; };
inline double getDeltaY(double radian, double distance) { return -sin(radian) * distance; };
inline dPOINT getDeltaPt(dPOINT pos1, dPOINT pos2) { return dPOINT{ pos2.x - pos1.x, pos2.y - pos1.y }; };

inline double getDistance(dPOINT pos1, dPOINT pos2)
{
	return sqrt(
		getDeltaPt(pos1, pos2).x * getDeltaPt(pos1, pos2).x +
		getDeltaPt(pos1, pos2).y * getDeltaPt(pos1, pos2).y);
};

inline double Deg2Rad(double Degree) { return PI / 180 * Degree; };
inline double Rad2Deg(double Radian) { return 180 / PI * Radian; };
// inline double getDegree(dPOINT pos1, dPOINT pos2) { return acos(getDeltaPt(pos1, pos2).x / getDistance(pos1, pos2)); };
inline double getRadian(dPOINT pos1, dPOINT pos2) { return atan2(-getDeltaPt(pos1, pos2).y, getDeltaPt(pos1, pos2).x); };

// inline dPOINT getDeltaPos(dPOINT pos, double Degree, double distance)
// {
// 	return dPOINT{
// 		pos.x + cos(Deg2Rad(Degree)) * distance,
// 		pos.y + sin(Deg2Rad(Degree)) * distance
// 	};
// };

inline dPOINT getDeltaPos(dPOINT pos, double radian, double distance) { return dPOINT{ pos.x + cos(radian) * distance, pos.y + -sin(radian) * distance }; };

// 기타함수
inline bool IsCrashEllipse(dPOINT pos1, double radius1, dPOINT pos2, double radius2) { return getDistance(pos1, pos2) < (radius1 + radius2); }

*/