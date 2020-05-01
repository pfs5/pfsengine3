#include <algorithm>
#include "Transformable.h"
// ----------------------------------------------------------------------------
const PTransform& ITransformable::GetTransform() const
{
	return _transform;
}
// ----------------------------------------------------------------------------
const PArray<ITransformable*>& ITransformable::GetChildren() const
{
	return _children;
}
// ----------------------------------------------------------------------------
void ITransformable::AttachTo(ITransformable* parent)
{
	if (parent == nullptr)
	{
		return;
	}

	DettachFromParent();

	parent->AddChild(this);
	SetParent(parent);
}
// ----------------------------------------------------------------------------
void ITransformable::DettachFromParent()
{
	if (_parent == nullptr)
	{
		return;
	}

	_parent->RemoveChild(this);
	SetParent(nullptr);
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
void ITransformable::AddChild(ITransformable* child)
{
	_children.Add(child);
}
// ----------------------------------------------------------------------------
void ITransformable::RemoveChild(ITransformable* child)
{
	_children.Remove(child);
}
// ----------------------------------------------------------------------------
void ITransformable::ClearChildren()
{
	_children.Clear();
}
// ----------------------------------------------------------------------------