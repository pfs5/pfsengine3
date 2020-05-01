#include <cmath>
#include "Math.h"
// ----------------------------------------------------------------------------
float PMath::Sqrt(float value)
{
	return sqrtf(value);
}
// ----------------------------------------------------------------------------
float PMath::Pow(float base, float power)
{
	return powf(base, power);
}
// ----------------------------------------------------------------------------
float PMath::IsNearlyZero(float value, float tolerance/* = KINDA_SMALL_NUMBER*/)
{
	return Abs(value) < tolerance;
}
// ----------------------------------------------------------------------------
int PMath::RoundToInt(float value)
{
	return (int)std::round(value);
}
// ----------------------------------------------------------------------------
float PMath::Floor(float value)
{
	return std::floorf(value);
}
// ----------------------------------------------------------------------------
float PMath::Ceil(float value)
{
	return std::ceilf(value);
}
// ----------------------------------------------------------------------------