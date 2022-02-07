#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <limits>
#include <algorithm>

namespace Math
{
	const float C_POS_INFINITY = std::numeric_limits<float>::infinity();
	const float C_NEG_INFINITY = -std::numeric_limits<float>::infinity();
	const float C_PI = 3.14159265358979323846264338327950288419716939937510f;
	const float C_FOUR_PI = 4.0f * C_PI;
	const float C_TWO_PI = 2.0f * C_PI;
	const float C_HALF_PI = 0.5f * C_PI;
	const float C_DEG_TO_RAD = C_PI / 180.0f;
	const float C_RAD_TO_DEG = 180.0f / C_PI;

	inline float degreesToRadians(float degrees) { return degrees * C_DEG_TO_RAD; }
	inline float radiansToDegrees(float radians) { return radians * C_RAD_TO_DEG; }

	inline bool isNaN(float f)
	{
		return (f == C_POS_INFINITY || f == C_NEG_INFINITY);
	}

	/** Clamp a value within an inclusive range. */
	template<typename T>
	inline T clamp(T val, T a, T b)
	{
		return (a < b ? std::max<T>(std::min<T>(val, b), a) : std::max<T>(std::min<T>(val, a), b) );
	}

	template<typename T>
	inline bool between(T val, T a, T b, bool inclusive = true)
	{
		return (a < b ? (inclusive ? (val <= b && val >= a) : (val < b && val > a) )
			: (inclusive ? (val <= a && val >= b) : (val < a && val > b) ) );
	}

	template<typename T>
	inline int getSign(T val) { return (val < 0 ? -1 : 1); }

	template<typename T>
	inline T lerp(T& a, T& b, float t) { return a + (b - a) * t; }

	inline float frand(float min, float max)
	{
		float r = (float)rand() / (float)RAND_MAX;
		return min + r * (max - min);
	}
}

#endif