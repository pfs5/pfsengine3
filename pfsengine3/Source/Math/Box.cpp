#include "Box.h"
// ----------------------------------------------------------------------------
PBox::PBox(const PVector2& min, const PVector2 max):
	Min(min),
	Max(max)
{

}
// ----------------------------------------------------------------------------
PVector2 PBox::GetCenter() const
{
	return (Min + Max) * 0.5f;
}
// ----------------------------------------------------------------------------
PVector2 PBox::GetSize() const
{
	return Max - Min;
}
// ----------------------------------------------------------------------------
bool PBox::DoesContain(const PBox& other) const
{
	return other.Min.X >= Min.X && other.Max.X <= Max.X &&
		other.Min.Y >= Min.Y && other.Max.Y <= Max.Y;
}
// ----------------------------------------------------------------------------
bool PBox::DoesContain(const PVector2& point) const
{
	return point.X >= Min.X && point.X <= Max.X &&
		point.Y >= Min.Y && point.Y <= Max.Y;
}
// ----------------------------------------------------------------------------