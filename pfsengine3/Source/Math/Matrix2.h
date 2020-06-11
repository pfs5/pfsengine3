#pragma once
#include <initializer_list>
#include "Vector2.h"
// ----------------------------------------------------------------------------
class PMatrix2
{
public:
	/**
	 * Initialize matrix with zeros.
	 */
	PMatrix2() = default;

	/**
	 * Initialize matrix from data.
	 */
	PMatrix2(std::initializer_list<PVector2> rows);

	/**
	 * Copy constructor.
	 */
	PMatrix2(const PMatrix2& other);

	const PVector2& operator[](int row) const;
		  PVector2& operator[](int row);

	PVector2 GetColumn(int column) const;

	PString ToString() const;

public:
	PMatrix2 operator+(const PMatrix2& other) const;
	PMatrix2 operator-(const PMatrix2& other) const;
	PMatrix2 operator*(const PMatrix2& other) const;

	PMatrix2 operator+(float value) const;
	PMatrix2 operator-(float value) const;
	PMatrix2 operator*(float value) const;

	PMatrix2& operator+=(const PMatrix2& other);
	PMatrix2& operator-=(const PMatrix2& other);
	PMatrix2& operator*=(const PMatrix2& other);

	PMatrix2& operator+=(float value);
	PMatrix2& operator-=(float value);
	PMatrix2& operator*=(float value);

private:
	PVector2 _rows[2];
};
// ----------------------------------------------------------------------------