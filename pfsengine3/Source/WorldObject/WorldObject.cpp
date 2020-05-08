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
const PArray<OWorldObject*> OWorldObject::GetChildren() const
{
	static PArray<OWorldObject*> children;
	children.Clear(ITransformable::GetChildren().Size());

	for (ITransformable* child : ITransformable::GetChildren())
	{
		if (OWorldObject* childObject = dynamic_cast<OWorldObject*>(child))
		{
			children.Add(childObject);
		}
	}
	return children;
}
// ----------------------------------------------------------------------------