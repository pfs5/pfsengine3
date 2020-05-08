#pragma once
#include "Vector2.h"
// ----------------------------------------------------------------------------
/**
 * Axis aligned box.
 */
struct PBox
{
public:
	PVector2 Min;
	PVector2 Max;

public:
	PBox(const PVector2& min = PVector2::ZeroVector, const PVector2 max = PVector2::ZeroVector);
	PVector2 GetCenter() const;
	PVector2 GetSize() const;

	/**
	 * Check if box completely contains the other box.
	 */
	bool DoesContain(const PBox& other) const;

	/**
	 * Check if box contains point.
	 */
	bool DoesContain(const PVector2& point) const;
};
// ----------------------------------------------------------------------------