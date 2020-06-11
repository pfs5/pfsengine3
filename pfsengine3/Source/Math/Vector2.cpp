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
PVector2::PVector2(const sf::Vector2i& sfOther):
	X((float)sfOther.x),
	Y((float)sfOther.y)
{

}
// ----------------------------------------------------------------------------
PVector2::operator sf::Vector2i() const
{
	return sf::Vector2i(PMath::RoundToInt(X), PMath::RoundToInt(Y));
}
// ----------------------------------------------------------------------------
const float& PVector2::operator[](int col) const
{
	return col <= 0 ? X : Y;
}
// ----------------------------------------------------------------------------
float& PVector2::operator[](int col)
{
	return col <= 0 ? X : Y;
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
float PVector2::VectorAngle(const PVector2& v1, const PVector2& v2)
{
	float size1 = v1.Size();
	if (PMath::IsNearlyZero(size1))
	{
		return 0.f;
	}

	float size2 = v2.Size();
	if (PMath::IsNearlyZero(size2))
	{
		return 0.f;
	}

	return PMath::Acos(PVector2::DotProduct(v1, v2) / size1 / size2);
}
// ----------------------------------------------------------------------------
float PVector2::Size() const
{
	return PMath::Sqrt(this->SizeSquared());
}
// ----------------------------------------------------------------------------
float PVector2::SizeSquared() const
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
PVector2 PVector2::GetNormalized() const
{
	PVector2 v(*this);
	v.Normalize();
	return v;
}
// ----------------------------------------------------------------------------
bool PVector2::IsNearlyZero(float tolerance /*= KINDA_SMALL_NUMBER*/) const
{
	return PMath::IsNearlyZero(X) && PMath::IsNearlyZero(Y);
}
// ----------------------------------------------------------------------------
PString PVector2::ToString() const
{
	return PString::Printf("X: %.2f Y: %.2f", X, Y);
}
// ----------------------------------------------------------------------------