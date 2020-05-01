#include "WorldObject.h"
// ----------------------------------------------------------------------------
OWorldObject::OWorldObject(const PString& name /*= PString()*/):
	_name(name)
{

}
// ----------------------------------------------------------------------------
void OWorldObject::SetName(const PString& name)
{
	_name = name;
}
// ----------------------------------------------------------------------------
PString OWorldObject::GetName() const
{
	return _name;
}
// ----------------------------------------------------------------------------