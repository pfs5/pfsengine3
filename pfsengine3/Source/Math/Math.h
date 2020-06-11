#pragma once
#include "Box.h"
#include "EngineDefines.h"
#include <math.h>
// ----------------------------------------------------------------------------
#define P_PI 3.14159265359f
// ----------------------------------------------------------------------------
namespace PMath
{
	/**
	 * Square root.
	 */
	float Sqrt(float value);

	/**
	 * Power.
	 */
	float Pow(float base, float power);

	/**
	 * Square.
	 */
	template<typename T>
	inline T Square(T value);

	/**
	 * Absolute value.
	 */
	template<typename T>
	inline T Abs(const T& value);

	/**
	 * Absolute value.
	 */
	template<typename T>
	inline T Min(const T& v1, const T& v2);

	/**
	 * Absolute value.
	 */
	template<typename T>
	inline T Max(const T& v1, const T& v2);

	/**
	 * Clamp value between min and max values.
	 */
	template<typename T>
	inline T Clamp(const T& value, const T& min, const T& max);

	/**
	 * Checks if value is zero, with tolerance.
	 */
	bool IsNearlyZero(float value, float tolerance = KINDA_SMALL_NUMBER);

	/**
	 * Checks if left and right are equal up to a tolerance.
	 */
	bool IsNearlyEqual(float left, float right, float tolerance = KINDA_SMALL_NUMBER);

	/**
	 * Round to nearest integer
	 */
	int RoundToInt(float value);

	/**
	 * Returns floor (nearest smaller round number).
	 */
	float Floor(float value);

	/**
	 * Returns ceil (nearest larger round number).
	 */
	float Ceil(float value);

	/**
	 * Calculate sine function.
	 */
	float Sin(float angleDeg);

	/**
	 * Calculate cosine function.
	 */
	float Cos(float angleDeg);

	/**
	 * Calculate tangent function.
	 */
	float Tan(float angleDeg);

	/**
	 * Calculate arc sine function.
	 */
	float Asin(float value);

	/**
	 * Calculate arc cosine function. Returns angle in radians.
	 */
	float Acos(float value);

	/**
	 * Calculate arc tangent function. Returns angle in radians.
	 */
	float Atan(float value);

	/**
	 * Lerp between a and b using k as factor.
	 * k = 0 returns a. k = 1 returns b.
	 */
	float Lerp(float a, float b, float k);

	/**
	 * Lerp between a and b using k as factor.
	 * k = 0 returns a. k = 1 returns b.
	 */
	int Lerp(int a, int b, float k);

	/**
	 * Lerp between a and b using k as factor.
	 * k = 0 returns a. k = 1 returns b.
	 */
	unsigned int Lerp(unsigned int a, unsigned int b, float k);

	/**
	 * Convert angle from radians to degrees.
	 */
	float RadianToDegree(float angleRad);

	/**
	 * Convert angle from degrees to radians.
	 */
	float DegreeToRadian(float angleDeg);

	/**
	 * Checks if point is contained in a box.
	 */
	bool IsPointContainedInBox(const PVector2& point, const PBox& box);

	/**
	 * Calculates rotation from given direction vector.
	 */
	float RotationFromVector(const PVector2& vector);
};
// ----------------------------------------------------------------------------
template<typename T>
T PMath::Square(T value)
{
	return value * value;
}
// ----------------------------------------------------------------------------
template<typename T>
T PMath::Abs(const T& value)
{
	return (value >= (T)0) ? value : -value;
}
// ----------------------------------------------------------------------------
template<typename T>
T PMath::Min(const T& v1, const T& v2)
{
	return (v1 <= v2) ? v1 : v2;
}
// ----------------------------------------------------------------------------
template<typename T>
T PMath::Max(const T& v1, const T& v2)
{
	return (v1 >= v2) ? v1 : v2;
}
// ----------------------------------------------------------------------------
template<typename T>
T PMath::Clamp(const T& value, const T& min, const T& max)
{
	return Max(min, Min(max, value));
}
// ----------------------------------------------------------------------------