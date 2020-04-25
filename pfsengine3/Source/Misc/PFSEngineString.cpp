#include "PFSEngineString.h"
// ----------------------------------------------------------------------------
PString::PString(const std::string& str /*= std::string()*/):
	_cppstr(str)
{

}
// ----------------------------------------------------------------------------
PString::PString(const char* cstr):
	_cppstr(cstr)
{

}
// ----------------------------------------------------------------------------
PString PString::FromInt(int i)
{
	return PString(std::to_string(i));
}
// ----------------------------------------------------------------------------
PString PString::FromFloat(float f)
{
	return PString(std::to_string(f));
}
// ----------------------------------------------------------------------------