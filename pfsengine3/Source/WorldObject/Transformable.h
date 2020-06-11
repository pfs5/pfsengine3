#pragma once
#include "Container/Array.h"
#include "Transform.h"
// ----------------------------------------------------------------------------
class ITransformable
{
public:
	static const int MAX_TREE_DEPTH;

public:
	virtual ~ITransformable() = default;

	const PTransform& GetTransform() const;
	void SetTransform(const PTransform& transform);

	PVector2 GetWorldLocation() const;
	float GetWorldRotation() const;

	const PArray<ITransformable*>& GetChildren() const;

	void AttachTo(ITransformable* parent);
	void DettachFromParent();

	ITransformable* GetParent() const;

protected:
	virtual void OnParentChanged();

private:
	PTransform _transform;

	ITransformable* _parent = nullptr;
	PArray<ITransformable*> _children;

private:
	void SetParent(ITransformable* parent);

	void AddChild(ITransformable* child);
	void RemoveChild(ITransformable* child);
	void ClearChildren();

};
// ----------------------------------------------------------------------------