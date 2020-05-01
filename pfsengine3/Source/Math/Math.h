#pragma once
#include <math.h>
#include "EngineDefines.h"
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