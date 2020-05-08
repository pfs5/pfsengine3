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
bool PMath::IsPointContainedInBox(const PVector2& point, const PBox& box)
{
	return point.X >= box.Min.X && point.X <= box.Max.X &&
		point.Y >= box.Min.Y && point.Y <= box.Max.Y;
}
// ----------------------------------------------------------------------------