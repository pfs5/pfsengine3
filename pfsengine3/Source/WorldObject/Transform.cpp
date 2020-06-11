#include "Transform.h"
#include "Math/Math.h"
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
void PTransform::SetLocation(const PVector2& location)
{
	_location = location;
}
// ----------------------------------------------------------------------------
float PTransform::GetRotation() const
{
	return _rotation;
}
// ----------------------------------------------------------------------------
void PTransform::SetRotation(float rotation)
{
	_rotation = rotation;
}
// ----------------------------------------------------------------------------
PVector2 PTransform::TransformPoint(const PVector2& point) const
{
	PVector2 pointTransformed = RotatePoint(point);
	pointTransformed = TranslatePoint(pointTransformed);
	return pointTransformed;
}
// ----------------------------------------------------------------------------
PVector2 PTransform::InverseTransformPoint(const PVector2& point) const
{
	PVector2 pointTransformed = InverseTranslatePoint(point);
	pointTransformed = InverseRotatePoint(pointTransformed);
	return pointTransformed;
}
// ----------------------------------------------------------------------------
PVector2 PTransform::TranslatePoint(const PVector2& point) const
{
	return point + _location;
}
// ----------------------------------------------------------------------------
PVector2 PTransform::InverseTranslatePoint(const PVector2& point) const
{
	return point - _location;
}
// ----------------------------------------------------------------------------
PVector2 PTransform::RotatePoint(const PVector2& point) const
{
	return PVector2
	(
		PMath::Cos(_rotation) * _location.X - PMath::Sin(_rotation) * _location.Y,
		PMath::Sin(_rotation) * _location.X + PMath::Cos(_rotation) * _location.Y
	);
}
// ----------------------------------------------------------------------------
PVector2 PTransform::InverseRotatePoint(const PVector2& point) const
{
	return PVector2
	(
		PMath::Cos(-_rotation) * _location.X - PMath::Sin(-_rotation) * _location.Y,
		PMath::Sin(-_rotation) * _location.X + PMath::Cos(-_rotation) * _location.Y
	);
}
// ----------------------------------------------------------------------------