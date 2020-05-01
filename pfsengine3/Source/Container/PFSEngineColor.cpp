#include "PFSEngineColor.h"
// ----------------------------------------------------------------------------
PColor::PColor(unsigned int red/* = 0u*/, unsigned int green/* = 0u*/, unsigned int blue/* = 0u*/, unsigned int alpha/* = 255u*/):
	_red(red),
	_green(green),
	_blue(blue),
	_alpha(alpha)
{

}
// ----------------------------------------------------------------------------
PColor PColor::FromHex(unsigned int hexInt, unsigned int alpha/* = 255u*/)
{
	unsigned int red = (hexInt >> 16) & 0xFF;
	unsigned int green = (hexInt >> 8) & 0xFF;
	unsigned int blue = (hexInt >> 0) & 0xFF;

	return PColor(red, green, blue, alpha);
}
// ----------------------------------------------------------------------------