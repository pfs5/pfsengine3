#pragma once
#include "Math/Vector2.h"
// ----------------------------------------------------------------------------
class PRenderTarget;
// ----------------------------------------------------------------------------
class PPanel
{
public:
	virtual void Draw(PRenderTarget* renderTarget) = 0;

	virtual void SetSize(const PVector2& size) = 0;
	virtual const PVector2& GetSize() const = 0;

	virtual void SetPosition(const PVector2& pos) = 0;
	virtual const PVector2& GetPosition() const = 0;
};
// ----------------------------------------------------------------------------