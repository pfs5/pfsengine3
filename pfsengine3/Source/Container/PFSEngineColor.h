#pragma once
#include "Misc/PFSEngineString.h"
#include "SFML/Graphics/Color.hpp"
// ----------------------------------------------------------------------------
class PColor
{
public:
	PColor(unsigned int red = 0u, unsigned int green = 0u, unsigned int blue = 0u, unsigned int alpha = 255u);

	/**
	 * 0xAARRGGBB
	 * AA = alpha
	 * RR = red
	 * GG = green
	 * BB = blue
	 */
	static PColor FromHex(unsigned int hexInt, unsigned int alpha = 255u);

	inline operator sf::Color() const;

private:
	unsigned int _red;
	unsigned int _green;
	unsigned int _blue;
	unsigned int _alpha;
};
// ----------------------------------------------------------------------------
PColor::operator sf::Color() const
{
	return sf::Color(_red, _green, _blue, _alpha);
}
// ----------------------------------------------------------------------------