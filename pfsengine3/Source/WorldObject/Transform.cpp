#include "Transform.h"
// ----------------------------------------------------------------------------
PTransform::PTransform(const PVector2& location /*= PVector2::ZeroVector*/, float rotation /*= 0.f*/):
	_location(location),
	_rotation(rotation)
{

}
// ----------------------------------------------------------------------------
PVector2 PTransform::GetLocation() const
{
	return _location;
}
// ----------------------------------------------------------------------------
float PTransform::GetRotation() const
{
	return _rotation;
}
// ----------------------------------------------------------------------------