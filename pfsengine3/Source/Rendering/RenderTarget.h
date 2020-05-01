#pragma once
#include "Container/PFSEngineColor.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"
// ----------------------------------------------------------------------------
class PRenderTarget
{
public:
	virtual void Clear(const PColor& clearColor = PColor(0, 0, 0, 255)) = 0;
	virtual void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) = 0;
	virtual void Display() = 0;
};
// ----------------------------------------------------------------------------