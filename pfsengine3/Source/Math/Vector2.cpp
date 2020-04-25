#include "Math.h"
#include "Vector2.h"
// ----------------------------------------------------------------------------
const PVector2 PVector2::ZeroVector		= PVector2(0.f, 0.f);
const PVector2 PVector2::OneVector		= PVector2(1.f, 1.f);
const PVector2 PVector2::UpVector		= PVector2(0.f, 1.f);
const PVector2 PVector2::RightVector	= PVector2(1.f, 0.f);
// ----------------------------------------------------------------------------
PVector2::PVector2(float x /*= 0.f*/, float y /*= 0.f*/):
	X(x),
	Y(y)
{

}
// ----------------------------------------------------------------------------
PVector2::PVector2(const PVector2& other):
	X(other.X),
	Y(other.Y)
{

}
// ----------------------------------------------------------------------------
PVector2::PVector2(const sf::Vector2f& sfOther):
	X(sfOther.x),
	Y(sfOther.y)
{
	
}
// ----------------------------------------------------------------------------
float PVector2::DotProduct(const PVector2& v1, const PVector2& v2)
{
	return v1.X * v2.X + v1.Y * v2.Y;
}
// ----------------------------------------------------------------------------
float PVector2::CrossProduct(const PVector2& v1, const PVector2& v2)
{
	return v1.X * v2.Y + v1.Y * v2.X;
}
// ----------------------------------------------------------------------------
float PVector2::Size()
{
	return PMath::Sqrt(this->SizeSquared());
}
// ----------------------------------------------------------------------------
float PVector2::SizeSquared()
{
	return DotProduct(*this, *this);
}
// ----------------------------------------------------------------------------
void PVector2::Normalize()
{
	float size = Size();
	if (PMath::IsNearlyZero(size))
	{
		return;
	}

	operator/=(size);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::GetNormalized()
{
	PVector2 v(*this);
	v.Normalize();
	return v;
}
// ----------------------------------------------------------------------------
bool PVector2::IsNearlyZero(float tolerance /*= KINDA_SMALL_NUMBER*/)
{
	return PMath::IsNearlyZero(X) && PMath::IsNearlyZero(Y);
}
// ----------------------------------------------------------------------------
PString PVector2::ToString()
{
	return PString::Printf("X: %.2f Y: %.2f", X, Y);
}
// ----------------------------------------------------------------------------