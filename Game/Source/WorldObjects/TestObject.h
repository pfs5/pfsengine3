#pragma once
#include "Misc/PFSEngineString.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "WorldObject/WorldObject.h"
// ----------------------------------------------------------------------------
class OTestObject : public OWorldObject
{
public:
	OTestObject(const PString& name = PString());

// OWorldObject
public:
	virtual void Draw(PRenderTarget* renderTarget) override;
	virtual void Update(float deltaTime) override;

private:
	sf::RectangleShape _shape;
};
// ----------------------------------------------------------------------------