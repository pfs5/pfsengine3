#include "PFSEngineColor.h"
#include "Math/Math.h"
// ----------------------------------------------------------------------------
const PColor PColor::Black		= PColor::FromHex(0x000000);
const PColor PColor::Blue		= PColor::FromHex(0x0000ff);;
const PColor PColor::Cyan		= PColor::FromHex(0x00ffff);;
const PColor PColor::Gray		= PColor::FromHex(0xaaaaaa);;
const PColor PColor::Green		= PColor::FromHex(0x00ff00);;
const PColor PColor::Magenta	= PColor::FromHex(0xff00ff);;
const PColor PColor::Orange		= PColor::FromHex(0xffa500);;
const PColor PColor::Red		= PColor::FromHex(0xff0000);;
const PColor PColor::White		= PColor::FromHex(0xffffff);;
const PColor PColor::Yellow		= PColor::FromHex(0xffff00);;

// ----------------------------------------------------------------------------
PColor::PColor(unsigned int red/* = 0u*/, unsigned int green/* = 0u*/, unsigned int blue/* = 0u*/, unsigned int alpha/* = 255u*/):
	R(red),
	G(green),
	B(blue),
	A(alpha)
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
PColor PColor::Lerp(const PColor& a, const PColor& b, float k)
{
	k = PMath::Clamp(k, 0.f, 1.f);

	unsigned int red = PMath::Lerp(a.R, b.R, k);
	unsigned int green = PMath::Lerp(a.G, b.G, k);
	unsigned int blue = PMath::Lerp(a.B, b.B, k);
	unsigned int alpha = PMath::Lerp(a.A, b.A, k);

	return PColor(red, green, blue, alpha);
}
// ----------------------------------------------------------------------------