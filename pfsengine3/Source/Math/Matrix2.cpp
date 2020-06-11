#include <cstring>
#include "Math.h"
#include "Matrix2.h"
// ----------------------------------------------------------------------------
PMatrix2::PMatrix2(std::initializer_list<PVector2> rows)
{
	int currentRow = 0;
	for (const PVector2& row : rows)
	{
		if (currentRow >= 2)
		{
			break;
		}

		_rows[currentRow++] = row;
	}
}
// ----------------------------------------------------------------------------
PMatrix2::PMatrix2(const PMatrix2& other)
{
	_rows[0] = other._rows[0];
	_rows[1] = other._rows[1];
}
// ----------------------------------------------------------------------------
const PVector2& PMatrix2::operator[](int row) const
{
	return _rows[row];
}
// ----------------------------------------------------------------------------
PVector2& PMatrix2::operator[](int row)
{
	return _rows[row];
}
// ----------------------------------------------------------------------------
PVector2 PMatrix2::GetColumn(int column) const
{
	column = PMath::Clamp(column, 0, 1);

	return PVector2
	(
		_rows[0][column],
		_rows[1][column]
	);
}
// ----------------------------------------------------------------------------
PString PMatrix2::ToString() const
{
	return PString::Printf("[%.2f\t%.2f]\n[%.2f\t%.2f]", _rows[0][0], _rows[0][1], _rows[1][0], _rows[1][1]);
}
// ----------------------------------------------------------------------------
PMatrix2 PMatrix2::operator+(const PMatrix2& other) const
{
	PMatrix2 m(*this);
	m += other;

	return m;
}
// ----------------------------------------------------------------------------
PMatrix2 PMatrix2::operator-(const PMatrix2& other) const
{
	PMatrix2 m(*this);
	m -= other;

	return m;
}
// ----------------------------------------------------------------------------
PMatrix2 PMatrix2::operator*(const PMatrix2& other) const
{
	PMatrix2 m(*this);
	m *= other;

	return m;
}
// ----------------------------------------------------------------------------
PMatrix2 PMatrix2::operator+(float value) const
{
	PMatrix2 m(*this);
	m += value;

	return m;
}
// ----------------------------------------------------------------------------
PMatrix2 PMatrix2::operator-(float value) const
{
	PMatrix2 m(*this);
	m -= value;

	return m;
}
// ----------------------------------------------------------------------------
PMatrix2 PMatrix2::operator*(float value) const
{
	PMatrix2 m(*this);
	m *= value;

	return m;
}
// ----------------------------------------------------------------------------
PMatrix2& PMatrix2::operator+=(const PMatrix2& other)
{
	_rows[0] += other._rows[0];
	_rows[1] += other._rows[1];
	
	return *this;
}
// ----------------------------------------------------------------------------
PMatrix2& PMatrix2::operator-=(const PMatrix2& other)
{
	_rows[0] -= other._rows[0];
	_rows[1] -= other._rows[1];

	return *this;
}
// ----------------------------------------------------------------------------
PMatrix2& PMatrix2::operator*=(const PMatrix2& other)
{
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			_rows[y][x] = PVector2::DotProduct(_rows[y], other.GetColumn(x));
		}
	}

	return *this;
}
// ----------------------------------------------------------------------------
PMatrix2& PMatrix2::operator+=(float value)
{
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			_rows[y][x] += value;
		}
	}

	return *this;
}
// ----------------------------------------------------------------------------
PMatrix2& PMatrix2::operator-=(float value)
{
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			_rows[y][x] -= value;
		}
	}

	return *this;
}
// ----------------------------------------------------------------------------
PMatrix2& PMatrix2::operator*=(float value)
{
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			_rows[y][x] *= value;
		}
	}

	return *this;
}
// ----------------------------------------------------------------------------