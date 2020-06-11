#pragma once
#include "Container/Array.h"
#include "Container/PFSEngineColor.h"
#include "Math/Vector2.h"
// ----------------------------------------------------------------------------
class PRenderTarget;
namespace sf
{
	class Drawable;
}
// ----------------------------------------------------------------------------
class PDebugRenderer
{
public:
	static PDebugRenderer& GetInstance();

	void DrawDebugLine(const PVector2& start, const PVector2& end, float thickness, const PColor& color, float lifetime = 0.f);

public:
	PDebugRenderer() = default;
	
	void Update(float deltaTime);
	void Draw(PRenderTarget* renderTarget);

private:
	struct PDebugShape
	{
		sf::Drawable* Drawable;
		float Lifetime;
	};

	PArray<PDebugShape> _activeDebugShapes;
};
// ----------------------------------------------------------------------------