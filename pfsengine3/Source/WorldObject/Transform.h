#pragma once
#include "../Math/Vector2.h"
// ----------------------------------------------------------------------------
class PTransform
{
public:
	PTransform(const PVector2& location = PVector2::ZeroVector, float rotation = 0.f);

	PVector2 GetLocation() const;
	float GetRotation() const;

private:
	PVector2 _location;
	float _rotation;
};
// ----------------------------------------------------------------------------