#pragma once
#include "Container/Array.h"
#include "Transform.h"
// ----------------------------------------------------------------------------
class ITransformable
{
public:
	virtual ~ITransformable() = default;

	const PTransform& GetTransform() const;
	void SetTransform(const PTransform& transform);

	const PArray<ITransformable*>& GetChildren() const;

	void AttachTo(ITransformable* parent);
	void DettachFromParent();

private:
	PTransform _transform;

	ITransformable* _parent = nullptr;
	PArray<ITransformable*> _children;

private:
	void SetParent(ITransformable* parent);
	ITransformable* GetParent() const;

	void AddChild(ITransformable* child);
	void RemoveChild(ITransformable* child);
	void ClearChildren();

};
// ----------------------------------------------------------------------------