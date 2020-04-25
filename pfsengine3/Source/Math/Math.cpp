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