#include "Container/Array.h"
#include "Logging/DebugLog.h"
#include "Transformable.h"
#include <algorithm>
// ----------------------------------------------------------------------------
const int ITransformable::MAX_TREE_DEPTH = 20;
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
PVector2 ITransformable::GetWorldLocation() const
{
	const ITransformable* parent = GetParent();
	if (parent == nullptr)
	{
		return GetTransform().GetLocation();
	}

	// Follow tree until root node is reached
	static PArray<PTransform> transformQueue;
	transformQueue.Clear();

	int depth = 0;
	const ITransformable* currentNode = parent;
	while (currentNode != nullptr)
	{
		transformQueue.Add(currentNode->GetTransform());
		currentNode = currentNode->GetParent();
		depth++;

		if (depth > MAX_TREE_DEPTH)
		{
			PDebugLog::LogMessage("[GetWorldLocation] Error getting root parent. Max tree depth reached.", PDebugLog::ELogType::Error);
			return PVector2();
		}
	}

	PVector2 worldLocation = GetTransform().GetLocation();
	for (psize i = transformQueue.Size() - 1; i != 0; --i)
	{
		transformQueue[i].TransformPoint(worldLocation);
	}

	return worldLocation;
}
// ----------------------------------------------------------------------------
float ITransformable::GetWorldRotation() const
{
	// #TODO
	return -1;
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

	ITransformable* prevParent = GetParent();

	DettachFromParent();

	parent->AddChild(this);
	SetParent(parent);

	if (GetParent() != prevParent)
	{
		OnParentChanged();
	}
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

	OnParentChanged();
}
// ----------------------------------------------------------------------------
ITransformable* ITransformable::GetParent() const
{
	return _parent;
}
// ----------------------------------------------------------------------------
void ITransformable::OnParentChanged()
{

}
// ----------------------------------------------------------------------------
void ITransformable::SetParent(ITransformable* parent)
{
	_parent = parent;
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