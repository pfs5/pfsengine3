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
bool PMath::IsNearlyZero(float value, float tolerance/* = KINDA_SMALL_NUMBER*/)
{
	return Abs(value) < tolerance;
}
// ----------------------------------------------------------------------------
bool PMath::IsNearlyEqual(float left, float right, float tolerance /*= KINDA_SMALL_NUMBER*/)
{
	return IsNearlyZero(left - right, tolerance);
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
float PMath::Sin(float angleDeg)
{
	float angleRad = DegreeToRadian(angleDeg);

	return sin(angleRad);
}
// ----------------------------------------------------------------------------
float PMath::Cos(float angleDeg)
{
	float angleRad = DegreeToRadian(angleDeg);

	return cos(angleRad);
}
// ----------------------------------------------------------------------------
float PMath::Tan(float angleDeg)
{
	float angleRad = DegreeToRadian(angleDeg);

	return tan(angleRad);
}
// ----------------------------------------------------------------------------
float PMath::Asin(float value)
{
	return asin(value);
}
// ----------------------------------------------------------------------------
float PMath::Acos(float value)
{
	return acos(value);
}
// ----------------------------------------------------------------------------
float PMath::Atan(float value)
{
	float angleRad = DegreeToRadian(value);

	return atan(angleRad);
}
// ----------------------------------------------------------------------------
float PMath::Lerp(float a, float b, float k)
{
	return a * (1.f - k) + b * k;
}
// ----------------------------------------------------------------------------
int PMath::Lerp(int a, int b, float k)
{
	return PMath::RoundToInt(Lerp((float)a, (float)b, k));
}
// ----------------------------------------------------------------------------
unsigned int PMath::Lerp(unsigned int a, unsigned int b, float k)
{
	int value = PMath::RoundToInt(Lerp((float)a, (float)b, k));
	value = PMath::Max(0, value);	// clamp to zero from bottom

	return (unsigned int) value;
}
// ----------------------------------------------------------------------------
float PMath::RadianToDegree(float angleRad)
{
	return angleRad * 180.f / P_PI;
}
// ----------------------------------------------------------------------------
float PMath::DegreeToRadian(float angleDeg)
{
	return angleDeg / 180.f * P_PI;
}
// ----------------------------------------------------------------------------
bool PMath::IsPointContainedInBox(const PVector2& point, const PBox& box)
{
	return point.X >= box.Min.X && point.X <= box.Max.X &&
		point.Y >= box.Min.Y && point.Y <= box.Max.Y;
}
// ----------------------------------------------------------------------------
float PMath::RotationFromVector(const PVector2& vector)
{
	float angle = PMath::Clamp(RadianToDegree(PVector2::VectorAngle(vector, PVector2::RightVector)), 0.f, 180.f);
	angle *= PVector2::CrossProduct(vector, PVector2::RightVector) > 0.f ? 1.f : -1.f;
	if (angle < 0.f)
	{
		angle += 360.f;
	}

	return angle;
}
// ----------------------------------------------------------------------------