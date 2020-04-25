#pragma once
#include "EngineDefines.h"
#include "SFML/System/Vector2.hpp"
#include "../Misc/PFSEngineString.h"
// ----------------------------------------------------------------------------
struct PVector2
{
public:
	float X;
	float Y;

public:
	static const PVector2 ZeroVector;
	static const PVector2 OneVector;
	static const PVector2 UpVector;
	static const PVector2 RightVector;

public:
	PVector2(float x = 0.f, float y = 0.f);
	PVector2(const PVector2& other);
	PVector2(const sf::Vector2f& sfOther);

public:
	/**
	 * Copy assignment.
	 */
	inline PVector2 operator=(const PVector2& v);

	/**
	 * Copy assignment.
	 */
	inline PVector2 operator=(const sf::Vector2f& v);

	/**
	 * Equality operator.
	 */
	inline bool operator==(const PVector2& v);

	/**
	 * Inequality operator.
	 */
	inline bool operator!=(const PVector2& v);

	/**
	 * Vector addition.
	 */
	inline PVector2 operator+(const PVector2& v);

	/**
	 * Vector addition.
	 */
	inline PVector2 operator+=(const PVector2& v);

	/**
	 * Vector subtraction.
	 */
	inline PVector2 operator-(const PVector2& v);

	/**
	 * Vector subtraction.
	 */
	inline PVector2 operator-=(const PVector2& v);

	/**
	 * Component-wise multiplication.
	 */
	inline PVector2 operator*(const PVector2& v);

	/**
	 * Component-wise multiplication.
	 */
	inline PVector2 operator*=(const PVector2& v);

	/**
	 * Component-wise multiplication.
	 */
	inline PVector2 operator/(const PVector2& v);

	/**
	 * Component-wise multiplication.
	 */
	inline PVector2 operator/=(const PVector2& v);

	/**
	 * Adds to all vector components.
	 */
	inline PVector2 operator+(float f);

	/**
	 * Adds to all vector components.
	 */
	inline PVector2 operator+=(float f);
	
	/**
	 * Subtracts from all vector components.
	 */
	inline PVector2 operator-(float f);

	/**
	 * Subtracts from all vector components.
	 */
	inline PVector2 operator-=(float f);

	/**
	 * Vector scaling (multiply each component by value).
	 */
	inline PVector2 operator*(float f);

	/**
	 * Vector scaling (multiply each component by value).
	 */
	inline PVector2 operator*=(float f);

	/**
	 * Divides each component by value.
	 */
	inline PVector2 operator/(float f);

	/**
	 * Divides each component by value.
	 */
	inline PVector2 operator/=(float f);

	/**
	 * Negate each component of vector.
	 */
	inline PVector2 operator-();

	inline operator sf::Vector2f() const;

public:
	/**
	 * Vector dot product.
	 */
	static float DotProduct(const PVector2& v1, const PVector2& v2);

	/**
	 * Vector cross product in 2D. Basically return the relative rotation of two vectors.
	 */
	static float CrossProduct(const PVector2& v1, const PVector2& v2);

public:
	/**
	 * Returns the size of the vector.
	 */
	float Size();

	/**
	 * Returns the squared size of the vector.
	 */
	float SizeSquared();

	/**
	 * Normalizes the vector in place.
	 */
	void Normalize();

	/**
	 * Return normalized version of the vector.
	 */
	PVector2 GetNormalized();

	/**
	 * Checks if vector is zero with tolerance.
	 */
	bool IsNearlyZero(float tolerance = KINDA_SMALL_NUMBER);

	/**
	 * Returns string representation of vector.
	 */
	PString ToString();
};
// ----------------------------------------------------------------------------
PVector2 PVector2::operator=(const PVector2& v)
{
	X = v.X;
	Y = v.Y;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator=(const sf::Vector2f& v)
{
	X = v.x;
	Y = v.y;

	return *this;
}
// ----------------------------------------------------------------------------
bool PVector2::operator==(const PVector2& v)
{
	return (*this - v).IsNearlyZero();
}
// ----------------------------------------------------------------------------
bool PVector2::operator!=(const PVector2& v)
{
	return !(*this == v);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator+(const PVector2& v)
{
	return PVector2(X + v.X, Y + v.Y);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator+=(const PVector2& v)
{
	X += v.X;
	Y += v.Y;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator-(const PVector2& v)
{
	return PVector2(X - v.X, Y - v.Y);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator-=(const PVector2& v)
{
	X -= v.X;
	Y -= v.Y;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator*(const PVector2& v)
{
	return PVector2(X * v.X, Y * v.Y);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator*=(const PVector2& v)
{
	X *= v.X;
	Y *= v.Y;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator/(const PVector2& v)
{
	return PVector2(X / v.X, Y / v.Y);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator/=(const PVector2& v)
{
	X /= v.X;
	Y /= v.Y;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator+(float f)
{
	return PVector2(X + f, Y + f);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator+=(float f)
{
	X += f;
	Y += f;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator-(float f)
{
	return PVector2(X - f, Y - f);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator-=(float f)
{
	X -= f;
	Y -= f;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator*(float f)
{
	return PVector2(X * f, Y * f);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator*=(float f)
{
	X *= f;
	Y *= f;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator/(float f)
{
	return PVector2(X / f, Y / f);
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator/=(float f)
{
	X /= f;
	Y /= f;

	return *this;
}
// ----------------------------------------------------------------------------
PVector2 PVector2::operator-()
{
	return PVector2(-X, -Y);
}
// ----------------------------------------------------------------------------
PVector2::operator sf::Vector2f() const
{
	return sf::Vector2f(X, Y);
}
// ----------------------------------------------------------------------------