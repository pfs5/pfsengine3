#include "Transformable.h"
#include <algorithm>
// ----------------------------------------------------------------------------
const PTransform& ITransformable::GetTransform() const
{
	return _transform;
}
// ----------------------------------------------------------------------------
void ITransformable::SetTransform(const PTransform& transform)
{
	_transform = transform;
}
// ----------------------------------------------------------------------------
void ITransformable::SetParent(ITransformable* parent)
{
	_parent = parent;
}
// ----------------------------------------------------------------------------
ITransformable* ITransformable::GetParent() const
{
	return _parent;
}
// ----------------------------------------------------------------------------
std::vector<ITransformable*> ITransformable::GetChildren() const
{
	return _children;
}
// ----------------------------------------------------------------------------
void ITransformable::AddChild(ITransformable* child)
{
	_children.push_back(child);
}
// ----------------------------------------------------------------------------
void ITransformable::RemoveChild(ITransformable* child)
{
	_children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
}
// ----------------------------------------------------------------------------
void ITransformable::ClearChildren()
{
	_children.clear();
}
// ----------------------------------------------------------------------------