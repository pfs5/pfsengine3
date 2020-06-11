#include "DebugRenderer.h"
#include "Rendering/RenderTarget.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
// ----------------------------------------------------------------------------
PDebugRenderer& PDebugRenderer::GetInstance()
{
	static PDebugRenderer Instance;
	return Instance;
}
// ----------------------------------------------------------------------------
void PDebugRenderer::DrawDebugLine(const PVector2& start, const PVector2& end, float thickness, const PColor& color, float lifetime /*= 0.f*/)
{
	PVector2 lineVector = end - start;
	float length = lineVector.Size();

	sf::RectangleShape* shape = new sf::RectangleShape();
	shape->setSize(PVector2(length, thickness));
	shape->setOrigin(PVector2(0.f, thickness / 2.f));
	shape->setRotation(PMath::RotationFromVector(lineVector));
	shape->setPosition(start);
	shape->setFillColor(color);

	_activeDebugShapes.Add(PDebugShape{ shape, lifetime });
}
// ----------------------------------------------------------------------------
void PDebugRenderer::Update(float deltaTime)
{
	for (psize i = 0; i < _activeDebugShapes.Size(); ++i)
	{
		PDebugShape& shape = _activeDebugShapes[i];
		shape.Lifetime -= deltaTime;

		if (shape.Lifetime < 0.f)
		{
			delete shape.Drawable;
			_activeDebugShapes.RemoveAtSwap(i);
			--i;
		}
	}
}
// ----------------------------------------------------------------------------
void PDebugRenderer::Draw(PRenderTarget* renderTarget)
{
	for (const PDebugShape& shape : _activeDebugShapes)
	{
		if (shape.Drawable != nullptr)
		{
			renderTarget->Draw(*shape.Drawable);
		}
	}
}
// ----------------------------------------------------------------------------