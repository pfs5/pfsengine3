#pragma once
#include "Misc/PFSEngineString.h"
#include "SFML/Graphics/Color.hpp"
// ----------------------------------------------------------------------------
class PColor
{
public:
	static const PColor Black;
	static const PColor Blue;
	static const PColor Cyan;
	static const PColor Gray;
	static const PColor Green;
	static const PColor Magenta;
	static const PColor Orange;
	static const PColor Red;
	static const PColor White;
	static const PColor Yellow;

public:
	unsigned int R;
	unsigned int G;
	unsigned int B;
	unsigned int A;

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
	
	/**
	 * Lerp between two colors. k = 0 results in color a, k = 1 results in color b.
	 */
	static PColor Lerp(const PColor& a, const PColor& b, float k);

	inline operator sf::Color() const;

};
// ----------------------------------------------------------------------------
PColor::operator sf::Color() const
{
	return sf::Color(R, G, B, A);
}
// ----------------------------------------------------------------------------