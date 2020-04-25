#pragma once
#include "EngineDefines.h"
#include <math.h>
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
	 * Checks if value is zero, with tolerance.
	 */
	float IsNearlyZero(float value, float tolerance = KINDA_SMALL_NUMBER);
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
T Min(const T& v1, const T& v2)
{
	return (v1 <= v2) ? v1 : v2;
}
// ----------------------------------------------------------------------------
template<typename T>
T Max(const T& v1, const T& v2)
{
	return (v1 >= v2) ? v1 : v2;
}
// ----------------------------------------------------------------------------