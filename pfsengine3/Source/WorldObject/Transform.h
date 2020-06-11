#pragma once
#include "Math/Matrix2.h"
#include "Math/Vector2.h"
// ----------------------------------------------------------------------------
class PTransform
{
public:
	PTransform(const PVector2& location = PVector2::ZeroVector, float rotation = 0.f);


	PVector2 GetLocation() const;
	void SetLocation(const PVector2& location);

	float GetRotation() const;
	void SetRotation(float rotation);

	PVector2 TransformPoint(const PVector2& point) const;
	PVector2 InverseTransformPoint(const PVector2& point) const;

	PVector2 TranslatePoint(const PVector2& point) const;
	PVector2 InverseTranslatePoint(const PVector2& point) const;

	PVector2 RotatePoint(const PVector2& point) const;
	PVector2 InverseRotatePoint(const PVector2& point) const;

private:
	PVector2 _location;
	float _rotation;

	PMatrix2 _translationMatrix;
	PMatrix2 _invTranslationMatrix;
	PMatrix2 _rotationMatrix;
	PMatrix2 _invRotationMatrix;
};
// ----------------------------------------------------------------------------